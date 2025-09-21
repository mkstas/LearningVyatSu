CREATE OR REPLACE FUNCTION save_category (
    _id BIGINT,
    _title VARCHAR(256)
)
RETURNS BIGINT
AS $$
DECLARE
    category_id BIGINT;

BEGIN
    IF _id IS NULL THEN
        INSERT INTO categories (title)
        VALUES (_title)
        RETURNING id INTO category_id;
    ELSE
        UPDATE categories SET
            title = _title
        WHERE id = _id;

        category_id := _id;
    END IF;

    RETURN category_id;
END;
$$ LANGUAGE plpgsql;

SELECT save_category(null, 'Обед');
SELECT save_category(4, 'Сладости');

CREATE OR REPLACE FUNCTION delete_category (
    _id BIGINT
)
RETURNS VOID
AS $$
BEGIN
    DELETE FROM categories
    WHERE id = _id;

EXCEPTION
    WHEN foreign_key_violation THEN
        RAISE EXCEPTION 'Невозможно выполнить удаление, так как есть внешние ссылки.';
END;
$$ LANGUAGE plpgsql;

SELECT delete_category(7);
SELECT delete_category(1);

CREATE OR REPLACE FUNCTION filter_product_variant_by_price (
    min_val INT
)
RETURNS SETOF product_variants
AS $$
BEGIN
    RETURN QUERY (SELECT * FROM product_variants 
                    WHERE price >= min_val);
END;
$$ LANGUAGE plpgsql;

SELECT * FROM filter_product_variant_by_price(500);

CREATE TYPE t_ingredient AS (
    id BIGINT,
    title VARCHAR(256),
    price INT
);

CREATE OR REPLACE FUNCTION filter_array_of_ingredients (
    arr t_ingredient[],
    fitler_var INT
)
RETURNS t_ingredient[]
AS $$
BEGIN
    RETURN ARRAY(
        SELECT (id, title, price)::t_ingredient
        FROM ingredients
        WHERE price >= fitler_var
    );
END;
$$ LANGUAGE plpgsql;

SELECT filter_array_of_ingredients(
    ARRAY(SELECT (id, title, price)::t_ingredient FROM ingredients),
    60
);

DROP TABLE IF EXISTS log_ingredients CASCADE;

CREATE TABLE log_ingredeints (
    id BIGSERIAL PRIMARY KEY,
    ingredient_id BIGINT,
    change_datetime TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    old_value INT,
    new_value INT,

    FOREIGN KEY (ingredient_id) REFERENCES ingredients(id) ON DELETE RESTRICT
)

CREATE OR REPLACE FUNCTION ingredients_trigger_func ()
RETURNS TRIGGER
AS $$
DECLARE
    old_val INT;

BEGIN
    IF (TG_OP = 'UPDATE') THEN
        old_val := OLD.price;
    ELSEIF (TG_OP = 'INSERT') THEN
        old_val := NULL;
    END IF;

    INSERT INTO log_ingredeints (ingredient_id, old_value, new_value)
    VALUES (NEW.id, old_val, NEW.price);

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER commit_ingredients_change
AFTER UPDATE OR INSERT
ON ingredients
FOR EACH ROW
EXECUTE PROCEDURE ingredients_trigger_func();

INSERT INTO ingredients (title, image_url, price)
VALUES ('Острый перец халапенью', 'https://cdn.dodostatic.net/static/Img/Ingredients/11ee95b6bfdf98fb88a113db92d7b3df.png', 59);
UPDATE ingredients SET price = 89 WHERE id = 6;

CREATE OR REPLACE FUNCTION get_value_by_id (
    table_name VARCHAR,
    column_name VARCHAR,
    id BIGINT
)
RETURNS TEXT
AS $$
DECLARE
    result TEXT;
BEGIN
    EXECUTE 'SELECT ' || column_name || ' FROM ' || table_name || ' WHERE id = $1' USING id INTO result;

    RETURN result;
END;
$$ LANGUAGE plpgsql;

SELECT get_value_by_id('categories', 'title', 4);
