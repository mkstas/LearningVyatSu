DROP TABLE IF EXISTS users CASCADE;
DROP TABLE IF EXISTS payments CASCADE;
DROP TABLE IF EXISTS user_payments CASCADE;
DROP TABLE IF EXISTS categories CASCADE;
DROP TABLE IF EXISTS products CASCADE;
DROP TABLE IF EXISTS ingredients CASCADE;
DROP TABLE IF EXISTS product_ingredients CASCADE;
DROP TABLE IF EXISTS variants CASCADE;
DROP TABLE IF EXISTS product_variants CASCADE;
DROP TABLE IF EXISTS carts CASCADE;
DROP TABLE IF EXISTS cart_products CASCADE;
DROP TABLE IF EXISTS cart_product_ingredients CASCADE;
DROP TABLE IF EXISTS orders CASCADE;

CREATE TABLE users (
    "id" BIGINT PRIMARY KEY,
    "phone_number" VARCHAR(11) NOT NULL UNIQUE,
    "fullname" VARCHAR(255) NULL,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE payments (
    "id" BIGINT PRIMARY KEY,
    "title" VARCHAR(255) NOT NULL,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE user_payments (
    "id" BIGINT PRIMARY KEY,
    "user_id" BIGINT NOT NULL REFERENCES users(id),
    "payment_id" BIGINT NOT NULL REFERENCES payments(id),
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE categories (
    "id" BIGINT PRIMARY KEY,
    "title" VARCHAR(255) NOT NULL UNIQUE,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE products (
    "id" BIGINT PRIMARY KEY,
    "category_id" BIGINT NOT NULL REFERENCES categories(id) ON DELETE CASCADE,
    "title" VARCHAR(255) NOT NULL,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE ingredients (
    "id" BIGINT PRIMARY KEY,
    "title" VARCHAR(255) NOT NULL UNIQUE,
    "image_url" VARCHAR(255) NOT NULL,
    "price" INT NOT NULL,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE product_ingredients (
    "id" BIGINT PRIMARY KEY,
    "product_id" BIGINT NOT NULL REFERENCES products(id) ON DELETE CASCADE,
    "ingredient_id" BIGINT NOT NULL REFERENCES ingredients(id) ON DELETE CASCADE,
    "is_required" BOOLEAN NOT NULL DEFAULT false,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE variants (
    "id" BIGINT PRIMARY KEY,
    "title" VARCHAR(255) NOT NULL,
    "value" VARCHAR(255) NOT NULL UNIQUE,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE product_variants (
    "id" BIGINT PRIMARY KEY,
    "product_id" BIGINT NOT NULL REFERENCES products(id) ON DELETE CASCADE,
    "variant_id" BIGINT NOT NULL REFERENCES variants(id) ON DELETE CASCADE,
    "image_url" VARCHAR(255) NOT NULL,
    "price" INT NOT NULL,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE cart_product_ingredients (
    "id" BIGINT PRIMARY KEY,
    "product_ingredient_id" BIGINT NOT NULL REFERENCES product_ingredients(id) ON DELETE CASCADE,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE cart_products (
    "id" BIGINT PRIMARY KEY,
    "product_variant_id" BIGINT NOT NULL REFERENCES product_variants(id) ON DELETE CASCADE,
    "cart_product_ingredient_id" BIGINT NOT NULL REFERENCES cart_product_ingredients(id) ON DELETE CASCADE,
    "quantity" INT NOT NULL DEFAULT 0,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);


CREATE TABLE carts (
    "id" BIGINT PRIMARY KEY,
    "user_id" BIGINT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    "cart_product_id" BIGINT NOT NULL REFERENCES cart_products(id) ON DELETE CASCADE,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);

CREATE TABLE orders (
    "id" BIGINT PRIMARY KEY,
    "user_id" BIGINT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    "payment_id" BIGINT NOT NULL REFERENCES payments(id) ON DELETE CASCADE,
    "products" JSON NOT NULL,
    "address" VARCHAR(255) NOT NULL,
    "cost" INT NOT NULL,
    "status" VARCHAR(255) CHECK (status IN ('pending', 'succeeded', 'canceled')),
    "comment" VARCHAR(255) DEFAULT NULL,
    "created_at" TIMESTAMP(3) NOT NULL DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP(3) NOT NULL
);
