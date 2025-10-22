from database.connection import db

class PaymentsController:
    def __init__(self):
        self.db = db

    def get_payments(self):
        payments = self.db.fetch_all("SELECT * FROM payments")
        if payments is None:
            return []
        return payments
