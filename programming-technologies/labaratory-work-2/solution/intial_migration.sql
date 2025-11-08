CREATE TABLE products (
    id BIGSERIAL PRIMARY KEY,
    title VARCHAR(256) NOT NULL UNIQUE,
    image_url VARCHAR(512) NOT NULL,
    price INT NOT NULL CHECK (price >= 0),
)

CREATE TABLE orders (
    id BIGSERIAL PRIMARY KEY,
    username VARCHAR(256) NOT NULL
    phone_number VARCHAR(11) NOT NULL,
    card_number VARCHAR(16),
)

CREATE TABLE order_products (
    order_id BIGINT NOT NULL,
    product_id BIGINT NOT NULL,

    FOREIGN KEY (order_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES payments(id) ON DELETE CASCADE
)
