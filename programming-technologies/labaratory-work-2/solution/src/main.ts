import express, { type Request, type Response } from 'express';
import path from 'path';
import { PrismaClient, type Product } from './generated/prisma/index.js';

const prisma = new PrismaClient();
const app = express();

app.use(express.static(path.resolve(process.cwd(), 'public')));
app.use(express.json());

app.get('/', (req: Request, res: Response) => {
  res.sendFile(path.resolve(process.cwd(), 'index.html'));
});

app.get('/api/v1/products', async (req: Request, res: Response) => {
  const products = await prisma.product.findMany();

  res.status(200).send(products);
});

app.post('/api/v1/orders', async (req: Request, res: Response) => {
  const order = await prisma.order.create({
    data: {
      username: req.body.username,
      phoneNumber: req.body.phone_number,
      cardNumber: req.body.card_number,
    },
  });

  req.body.cart.forEach(async (product: Product) => {
    await prisma.orderProduct.create({
      data: {
        orderId: order.id,
        productId: product.id,
      },
    });
  });

  res.status(200).send();
});

app.listen(3000, () => {
  console.log('Listening on http://localhost:3000');
});
