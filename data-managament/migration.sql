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
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("category_id") REFERENCES "categories"("id") ON DELETE RESTRICT
);

CREATE TABLE "ingredients" (
    "id" BIGSERIAL PRIMARY KEY,
    "title" VARCHAR(256) NOT NULL UNIQUE,
    "image_url" VARCHAR(512) NOT NULL,
    "price" INT NOT NULL CHECK (price >= 0),
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

CREATE TABLE "variants" (
    "id" BIGSERIAL PRIMARY KEY,
    "title" VARCHAR(256) NOT NULL,
    "value" VARCHAR(256) NOT NULL UNIQUE,
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE "product_variants" (
    "id" BIGSERIAL PRIMARY KEY,
    "product_id" BIGINT NOT NULL,
    "variant_id" BIGINT NOT NULL,
    "image_url" VARCHAR(512) NOT NULL,
    "price" INT NOT NULL CHECK (price >= 0),
    "created_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    "updated_at" TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY ("product_id") REFERENCES "products"("id") ON DELETE RESTRICT,
    FOREIGN KEY ("variant_id") REFERENCES "variants"("id") ON DELETE RESTRICT
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
    "quantity" INT NOT NULL DEFAULT 1 CHECK (quantity >= 1),
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
    "cost" INT NOT NULL CHECK (cost >= 0),
    "username" VARCHAR(256),
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
    "quantity" INT NOT NULL CHECK (quantity >= 1),
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
