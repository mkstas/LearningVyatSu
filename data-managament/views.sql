CREATE OR REPLACE VIEW "users_payments_v" AS
SELECT u.phone_number AS "Номер телефона", u.username AS "Имя пользователя", up.card_number AS "Номер карты", up.cvv AS "CVV код", p.title AS "Тип карты"
FROM "users" u
    JOIN "user_payments" up on u.id = up.user_id
    JOIN "payments" p on p.id = up.payment_id;

SELECT * FROM "users_payments_v";

CREATE OR REPLACE VIEW "categories_products_v" AS
SELECT c.title AS "Категория", p.title AS "Название продукта", p.description AS "Описание продукта"
FROM "categories" c
    JOIN "products" p on c.id = p.category_id;

SELECT * FROM "categories_products_v";

CREATE OR REPLACE VIEW "products_required_ingredients_v" AS
SELECT p.title AS "Название продукта", i.title AS "Ингредиент", i.price AS "Цена ингредиента" 
FROM "products" p
    JOIN "product_ingredients" pi on p.id = pi.product_id
    JOIN "ingredients" i on i.id = pi.ingredient_id
WHERE pi.is_required = true;

SELECT * FROM "products_required_ingredients_v";

CREATE OR REPLACE VIEW "ingredients_price_metric_v" AS

SELECT
    'Минимальное значение' as metric,
    MIN(price) as price,
    (SELECT id FROM "ingredients" ORDER BY price ASC LIMIT 1) as id
FROM "ingredients"

UNION ALL

SELECT
    'Максимальное значение',
    MAX(price),
    (SELECT id FROM "ingredients" ORDER BY price DESC LIMIT 1)
FROM "ingredients"

UNION ALL

SELECT
    'Среднее значение',
    ROUND(AVG(price)),
    NULL
FROM "ingredients"

UNION ALL

SELECT
    'Сумма значений',
    SUM(price),
    NULL
FROM "ingredients";

SELECT * FROM "ingredients_price_metric_v";
