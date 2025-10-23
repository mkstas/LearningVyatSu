import express, { type Request, type Response } from 'express';
import path from 'path';
import { PrismaClient, type Payment } from './generated/prisma/index.js';

type PaymentDTO = Omit<Payment, 'id'>;

const prisma = new PrismaClient();
const app = express();

app.use(express.static(path.resolve(process.cwd(), 'public')));
app.use(express.json());

app.get('/', (req: Request, res: Response) => {
  res.sendFile(path.resolve(process.cwd(), 'index.html'));
});

app.post('/api/v1/payments', async (req: Request, res: Response) => {
  const body = req.body as PaymentDTO;
  await prisma.payment.create({ data: body });

  res.send({ success: true }).status(201);
});

app.listen(3000, () => {
  console.log('Listening on http://localhost:3000');
});
