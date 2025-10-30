from database.connection import db

class UsersService:
    def __init__(self):
        self.db = db

    def get_users(self):
        users = self.db.fetch_all("SELECT * FROM users ORDER BY id")
        if users is None:
            return []
        return users
