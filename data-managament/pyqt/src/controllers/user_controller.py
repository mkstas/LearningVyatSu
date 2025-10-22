from database.connection import db

class UserController:
    def __init__(self):
        self.db = db

    def get_users(self):
        users = self.db.fetch_all("SELECT * FROM users ORDER BY id")
        if users is None:
            return []
        return users

    def create_user(self, phone_number, username = None):
        if username is not None:
            return self.db.execute_query(f"SELECT create_user('{phone_number}', '{username}')")
        return self.db.execute_query(f"SELECT create_user('{phone_number}')")

    def update_user(self, id, phone_number, username=None):
        query = "UPDATE users SET phone_number = %s, username = %s WHERE id = %s"
        return self.db.execute_query(query, (phone_number, username, id))

    def delete_user(self, id):
        return self.db.execute_query(f"DELETE FROM users WHERE id = {id}")
