DROP TABLE IF EXISTS "users" CASCADE;
DROP TABLE IF EXISTS "payments" CASCADE;
DROP TABLE IF EXISTS "user_payments" CASCADE;
DROP TABLE IF EXISTS "categories" CASCADE;
DROP TABLE IF EXISTS "products" CASCADE;
DROP TABLE IF EXISTS "ingredients" CASCADE;
DROP TABLE IF EXISTS "product_ingredients" CASCADE;
DROP TABLE IF EXISTS "variants" CASCADE;
DROP TABLE IF EXISTS "product_variants" CASCADE;
DROP TABLE IF EXISTS "carts" CASCADE;
DROP TABLE IF EXISTS "cart_products" CASCADE;
DROP TABLE IF EXISTS "cart_product_ingredients" CASCADE;
DROP TABLE IF EXISTS "orders" CASCADE;
DROP TABLE IF EXISTS "order_products" CASCADE;
DROP TABLE IF EXISTS "order_product_ingredients" CASCADE;

DROP TYPE IF EXISTS ORDER_STATUS_ENUM;

CREATE TABLE "users" (
    "id" BIGSERIAL PRIMARY KEY,
    "phone_number" VARCHAR(11) NOT NULL UNIQUE,
    "username" VARCHAR(256),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE "payments" (
    "id" BIGSERIAL PRIMARY KEY,
    "title" VARCHAR(256) NOT NULL UNIQUE,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE "user_payments" (
    "id" BIGSERIAL PRIMARY KEY,
    "user_id" BIGINT NOT NULL,
    "payment_id" BIGINT NOT NULL,
    "card_number" VARCHAR(16),
    "cvv" VARCHAR(3),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("user_id") REFERENCES "users"("id") ON DELETE CASCADE,
    FOREIGN KEY ("payment_id") REFERENCES "payments"("id") ON DELETE CASCADE
);

CREATE TABLE "categories" (
    "id" BIGSERIAL PRIMARY KEY,
    "title" VARCHAR(256) NOT NULL UNIQUE,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE "products" (
    "id" BIGSERIAL PRIMARY KEY,
    "category_id" BIGINT NOT NULL,
    "title" VARCHAR(256) NOT NULL,
    "description" VARCHAR(512),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("category_id") REFERENCES "categories"("id") ON DELETE RESTRICT
);

CREATE TABLE "ingredients" (
    "id" BIGSERIAL PRIMARY KEY,
    "title" VARCHAR(256) NOT NULL UNIQUE,
    "image_url" VARCHAR(512) NOT NULL,
    "price" INT NOT NULL CHECK ("price" >= 0),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE "product_ingredients" (
    "id" BIGSERIAL PRIMARY KEY,
    "product_id" BIGINT NOT NULL,
    "ingredient_id" BIGINT NOT NULL,
    "is_required" BOOLEAN NOT NULL DEFAULT FALSE,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("product_id") REFERENCES "products"("id") ON DELETE RESTRICT,
    FOREIGN KEY ("ingredient_id") REFERENCES "ingredients"("id") ON DELETE RESTRICT
);

CREATE TABLE "product_variants" (
    "id" BIGSERIAL PRIMARY KEY,
    "product_id" BIGINT NOT NULL,
    "image_url" VARCHAR(512) NOT NULL,
    "size" INT CHECK ("size" > 0),
    "volume" INT CHECK ("volume" >0),
    "weight" INT NOT NULL CHECK ("weight" > 0),
    "price" INT NOT NULL CHECK ("price" >= 0),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("product_id") REFERENCES "products"("id") ON DELETE RESTRICT
);

CREATE TABLE "carts" (
    "id" BIGSERIAL PRIMARY KEY,
    "user_id" BIGINT NOT NULL,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE "cart_products" (
    "id" BIGSERIAL PRIMARY KEY,
    "cart_id" BIGINT NOT NULL,
    "product_variant_id" BIGINT NOT NULL,
    "quantity" INT NOT NULL DEFAULT 1 CHECK ("quantity" >= 1),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("cart_id") REFERENCES "carts"("id") ON DELETE RESTRICT,
    FOREIGN KEY ("product_variant_id") REFERENCES "product_variants"("id") ON DELETE RESTRICT
);

CREATE TABLE "cart_product_ingredients" (
    "id" BIGSERIAL PRIMARY KEY,
    "cart_product_id" BIGINT NOT NULL,
    "product_ingredient_id" BIGINT NOT NULL,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("cart_product_id") REFERENCES "cart_products"("id") ON DELETE RESTRICT,
    FOREIGN KEY ("product_ingredient_id") REFERENCES "product_ingredients"("id") ON DELETE RESTRICT
);

CREATE TYPE ORDER_STATUS_ENUM AS ENUM (
    'pending', 'succeeded', 'canceled'
);

CREATE TABLE "orders" (
    "id" BIGSERIAL PRIMARY KEY,
    "user_id" BIGINT NOT NULL,
    "payment_id" BIGINT NOT NULL,
    "status" ORDER_STATUS_ENUM DEFAULT 'pending',
    "address" VARCHAR(256) NOT NULL,
    "cost" INT NOT NULL CHECK ("cost" >= 0),
    "comment" VARCHAR(255),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("user_id") REFERENCES "users"("id") ON DELETE CASCADE,
    FOREIGN KEY ("payment_id") REFERENCES "payments"("id") ON DELETE CASCADE
);

CREATE TABLE "order_products" (
    "id" BIGSERIAL PRIMARY KEY,
    "order_id" BIGINT NOT NULL,
    "product_variant_id" BIGINT NOT NULL,
    "quantity" INT NOT NULL CHECK ("quantity" >= 1),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("order_id") REFERENCES "orders"("id") ON DELETE RESTRICT,
    FOREIGN KEY ("product_variant_id") REFERENCES "product_variants"("id") ON DELETE RESTRICT
);

CREATE TABLE "order_product_ingredients" (
    "id" BIGSERIAL PRIMARY KEY,
    "order_product_id" BIGINT NOT NULL,
    "product_ingredient_id" BIGINT NOT NULL,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("order_product_id") REFERENCES "order_products"("id") ON DELETE RESTRICT,
    FOREIGN KEY ("product_ingredient_id") REFERENCES "product_ingredients"("id") ON DELETE RESTRICT
);
