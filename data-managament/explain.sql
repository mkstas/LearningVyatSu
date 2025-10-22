EXPLAIN (analyze) SELECT * FROM product_variants;

EXPLAIN (verbose) SELECT * FROM product_variants;

EXPLAIN (costs) SELECT * FROM product_variants;

EXPLAIN (analyze, buffers) SELECT * FROM product_variants;

EXPLAIN (analyze, timing) SELECT * FROM product_variants;

EXPLAIN (timing off) SELECT * FROM product_variants;

EXPLAIN (FORMAT XML) SELECT * FROM products p
    JOIN product_variants pv ON p.id = pv.product_id
    JOIN product_ingredients pi ON p.id = pi.product_id;

EXPLAIN (FORMAT JSON) SELECT * FROM products p
    JOIN product_variants pv ON p.id = pv.product_id
    JOIN product_ingredients pi ON p.id = pi.product_id;

EXPLAIN (FORMAT YAML) SELECT * FROM products p
    JOIN product_variants pv ON p.id = pv.product_id
    JOIN product_ingredients pi ON p.id = pi.product_id;

EXPLAIN INSERT INTO users(phone_number, username)
VALUES ('89000028750', 'Николай');

EXPLAIN (FORMAT JSON) SELECT * FROM products;

EXPLAIN (FORMAT JSON) SELECT * FROM products WHERE id = 1;

EXPLAIN (FORMAT JSON) SELECT id FROM products WHERE id = 1;

EXPLAIN (FORMAT JSON) SELECT * FROM product_variants WHERE price > 500;

SET enable_mergejoin = OFF;
SET enable_hashjoin = OFF;
EXPLAIN (FORMAT JSON) SELECT * FROM products p
    JOIN product_variants pv ON p.id = pv.product_id
    JOIN product_ingredients pi ON p.id = pi.product_id;

SET enable_hashjoin = ON;
EXPLAIN (FORMAT JSON) SELECT * FROM products p
    JOIN product_variants pv ON p.id = pv.product_id
    JOIN product_ingredients pi ON p.id = pi.product_id;

SET enable_mergejoin = ON;
SET enable_hashjoin = OFF;
EXPLAIN (FORMAT JSON) SELECT * FROM products p
    JOIN product_variants pv ON p.id = pv.product_id
    JOIN product_ingredients pi ON p.id = pi.product_id;
