TRUNCATE TABLE "users" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "payments" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "user_payments" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "products" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "categories" RESTART IDENTITY CASCADE;

DO $$
DECLARE

userId BIGINT;
paymentId BIGINT;
categoryId BIGINT;
productId BIGINT;
ingredientId BIGINT;
variantId BIGINT;

BEGIN

-- Generate users and payments
INSERT INTO "users"(phone_number, username)
VALUES ('89000000000', 'Николай')
RETURNING id INTO userId;

INSERT INTO "payments" (title)
VALUES ('Мир')
RETURNING id INTO paymentId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '0000000000000000', '000');

INSERT INTO "users" (phone_number, username)
VALUES ('89001110000', 'Александр')
RETURNING id INTO userId;

INSERT INTO "payments" (title)
VALUES ('Visa')
RETURNING id INTO paymentId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '1111111111111111', '111');

INSERT INTO "users" (phone_number, username)
VALUES ('89002220000', 'Екатерина')
RETURNING id INTO userId;

INSERT INTO "payments" (title)
VALUES ('MasterCard')
RETURNING id INTO paymentId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '2222222222222222', '222');

-- Generate categories and products
INSERT INTO "categories" (title)
VALUES ('Пиццы')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title)
VALUES (category_id, 'Карбонара')
RETURNING id INTO productId;

end;
$$ language plpgsql;
