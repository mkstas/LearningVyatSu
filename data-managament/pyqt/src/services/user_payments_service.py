from database.connection import db

class UserPaymentsService:
    def __init__(self):
        self.db = db

    def get_user_payments(self):
        payments = self.db.fetch_all(
            "SELECT up.id, u.phone_number, p.title, up.card_number, up.cvv " \
            "FROM user_payments up " \
                "JOIN users u ON u.id = up.user_id " \
                "JOIN payments p ON p.id = up.payment_id"
        )
        if payments is None:
            return []
        return payments

    def get_user_payments_by_search(self, substring):
        payments = self.db.fetch_all(
            "SELECT up.id, u.phone_number, p.title, up.card_number, up.cvv " \
                "FROM user_payments up " \
                "JOIN users u ON u.id = up.user_id " \
                "JOIN payments p ON p.id = up.payment_id " \
            f"WHERE up.card_number LIKE '%{substring}%'"
        )
        if payments is None:
            return []
        return payments

    def create_user_payment(self, user_id, payment_id, card_number, cvv):
        return self.db.execute_query(
            f"SELECT create_user_payment({user_id}, {payment_id}, '{card_number}', '{cvv}')"
        )

    def update_user_payment(self, id, user_id, payment_id, card_number, cvv):
        return self.db.execute_query(
            f"SELECT update_user_payment({id}, {user_id}, {payment_id}, '{card_number}', '{cvv}')"
        )

    def delete_user_payment(self, id):
        return self.db.execute_query(f"DELETE FROM user_payments WHERE id = {id}")
