TRUNCATE TABLE "users" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "payments" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "user_payments" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "products" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "ingredients" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "product_ingredients" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "product_variants" RESTART IDENTITY CASCADE;
TRUNCATE TABLE "categories" RESTART IDENTITY CASCADE;

DO $$
DECLARE

userId BIGINT;
paymentId BIGINT;
categoryId BIGINT;
productId BIGINT;
ingredientId BIGINT;

BEGIN

INSERT INTO "users"(phone_number, username)
VALUES ('89000000000', 'Николай')
RETURNING id INTO userId;

INSERT INTO "payments" (title)
VALUES ('Мир')
RETURNING id INTO paymentId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '2400100020003000', '135');

INSERT INTO "payments" (title)
VALUES ('Visa')
RETURNING id INTO paymentId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '6500100020003000', '246');

INSERT INTO "users" (phone_number, username)
VALUES ('89001110000', 'Александр')
RETURNING id INTO userId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '6500300020001000', '975');

INSERT INTO "users" (phone_number, username)
VALUES ('89002220000', 'Екатерина')
RETURNING id INTO userId;

INSERT INTO "payments" (title)
VALUES ('MasterCard')
RETURNING id INTO paymentId;

INSERT INTO "user_payments" (user_id, payment_id, card_number, cvv)
VALUES (userId, paymentId, '4200400050006000', '864');

INSERT INTO "categories" (title)
VALUES ('Пиццы')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title)
VALUES (categoryId, 'Карбонара')
RETURNING id INTO productId;

INSERT INTO "ingredients" (title, image_url, price)
VALUES ('Сырный бортик', 'https://cdn.dodostatic.net/static/Img/Ingredients/99f5cb91225b4875bd06a26d2e842106.png', 179)
RETURNING id INTO ingredientId;

INSERT INTO "product_ingredients" (product_id, ingredient_id, is_required)
VALUES (productId, ingredientId, TRUE)
RETURNING id INTO ingredientId;

INSERT INTO "ingredients" (title, image_url, price)
VALUES ('Пряная говядина', 'https://cdn.dodostatic.net/static/Img/Ingredients/11ef5ed5f8f64595a6d6a99c1fe6f7f0.png', 119)
RETURNING id INTO ingredientId;

INSERT INTO "product_ingredients" (product_id, ingredient_id, is_required)
VALUES (productId, ingredientId, TRUE)
RETURNING id INTO ingredientId;

INSERT INTO "ingredients" (title, image_url, price)
VALUES ('Моцарелла', 'https://cdn.dodostatic.net/static/Img/Ingredients/cdea869ef287426386ed634e6099a5ba.png', 79)
RETURNING id INTO ingredientId;

INSERT INTO "product_ingredients" (product_id, ingredient_id, is_required)
VALUES (productId, ingredientId, TRUE)
RETURNING id INTO ingredientId;

INSERT INTO "ingredients" (title, image_url, price)
VALUES ('Свежие томаты', 'https://cdn.dodostatic.net/static/Img/Ingredients/000D3A39D824A82E11E9AFA7AC1A1D67', 59)
RETURNING id INTO ingredientId;

INSERT INTO "product_ingredients" (product_id, ingredient_id, is_required)
VALUES (productId, ingredientId, DEFAULT)
RETURNING id INTO ingredientId;

INSERT INTO "ingredients" (title, image_url, price)
VALUES ('Сладкий перец', 'https://cdn.dodostatic.net/static/Img/Ingredients/000D3A22FA54A81411E9AFA63F774C1B', 59)
RETURNING id INTO ingredientId;

INSERT INTO "product_ingredients" (product_id, ingredient_id, is_required)
VALUES (productId, ingredientId, DEFAULT)
RETURNING id INTO ingredientId;

INSERT INTO "product_variants" (product_id, image_url, size, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/0196361c3c34728dbed2f01a37f04284.jpg', 20, 220, 479);

INSERT INTO "product_variants" (product_id, image_url, size, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/019591b1343c746bb4c108bede4d469c.jpg', 25, 410, 659);

INSERT INTO "product_variants" (product_id, image_url, size, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/019591b13a1a724b90092c16d9b1c05a.jpg', 30, 590, 1009);

INSERT INTO "product_variants" (product_id, image_url, size, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/019591b14a2e7663a8daf17169cfd23f.jpg', 35, 800, 1119);

INSERT INTO "categories" (title)
VALUES ('Закуски')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title, description)
VALUES (categoryId, 'Додстер', 'Легендарная горячая закуска с цыпленком, томатами, моцареллой, соусом ранч в тонкой пшеничной лепешке')
RETURNING id INTO productId;

INSERT INTO "product_variants" (product_id, image_url, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/01980cb92528769295aeb186fb501f8e.jpg', 190, 249);

INSERT INTO "categories" (title)
VALUES ('Завтрак')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title, description)
VALUES (categoryId, 'Омлет с ветчиной и грибами в пите', 'Горячий сытный омлет с поджаристой корочкой, ветчина, шампиньоны и моцарелла в пшеничной пите. Удобно взять с собой')
RETURNING id INTO productId;

INSERT INTO "product_variants" (product_id, image_url, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/019860510daa726fa023e04a1ae06a87.jpg', 170, 239);

INSERT INTO "categories" (title)
VALUES ('Десерты')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title, description)
VALUES (categoryId, 'Чизкейк Банановый с шоколадным печеньем', 'Солнечная версия классического рецепта: нежный чизкейк с бананом и шоколадным печеньем')
RETURNING id INTO productId;

INSERT INTO "product_variants" (product_id, image_url, weight, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/0198138723e478fba518947539dbbdcb.jpg', 100, 189);

INSERT INTO "categories" (title)
VALUES ('Коктейли')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title, description)
VALUES (categoryId, 'Молочный коктейль Фисташка', 'Сочетание нежности, сливочной текстуры и тонкого вкуса фисташки')
RETURNING id INTO productId;

INSERT INTO "product_variants" (product_id, image_url, weight, volume, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/0198138723e478fba518947539dbbdcb.jpg', 320, 300, 269);

INSERT INTO "product_variants" (product_id, image_url, weight, volume, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/0198138723e478fba518947539dbbdcb.jpg', 500, 400, 439);

INSERT INTO "categories" (title)
VALUES ('Кофе')
RETURNING id INTO categoryId;

INSERT INTO "products" (category_id, title, description)
VALUES (categoryId, 'Кофе Капучино', 'Легендарный рецепт кофе: эспрессо, горячее молоко и плотная молочная пенка')
RETURNING id INTO productId;

INSERT INTO "product_variants" (product_id, image_url, weight, volume, price)
VALUES (productId, 'https://media.dodostatic.net/image/r:292x292/019840b6488170018dd640026aea9961.jpg', 240, 400, 179);

end;
$$ language plpgsql;
