-- CreateTable
CREATE TABLE "payments" (
    "id" BIGSERIAL NOT NULL,
    "username" TEXT NOT NULL,
    "phone_number" TEXT NOT NULL,
    "method" TEXT NOT NULL,
    "card_number" TEXT NOT NULL,
    "cvv" TEXT NOT NULL,

    CONSTRAINT "payments_pkey" PRIMARY KEY ("id")
);
