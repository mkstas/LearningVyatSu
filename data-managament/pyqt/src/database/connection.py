import psycopg2
import psycopg2.extras

class Connection:
    connection = None

    def __init__(self):
        self.connection = psycopg2.connect("dbname=dm_db user=root password=root host=localhost port=5432")

    def get_cursor(self):
        return self.connection.cursor(cursor_factory=psycopg2.extras.DictCursor)
  
    def execute_query(self, query, params=None):
        cursor = self.get_cursor()
        try:
            cursor.execute(query, params)
            self.connection.commit()

            return True
        except Exception as e:
            self.connection.rollback()
            print(f"Database error: {e}")

            return False
        finally:
            cursor.close()

    def fetch_all(self, query, params=None):
        cursor = self.get_cursor()

        try:
            cursor.execute(query, params)
            results = cursor.fetchall()

            return results
        except Exception as e:
            print(f"Database error: {e}")

            return None
        finally:
            cursor.close()

    def fetch_one(self, query, params=None):
        cursor = self.get_cursor()

        try:
            cursor.execute(query, params)
            result = cursor.fetchone()

            return result
        except Exception as e:
            print(f"Database error: {e}")

            return None
        finally:
            cursor.close()

    def close(self):
        self.connection.close()

db = Connection()
