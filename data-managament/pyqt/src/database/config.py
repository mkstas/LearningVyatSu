class Config:
    db_host = 'localhost'
    db_port = '5432'
    db_name = 'dm_db'
    db_user = 'root'
    db_password = 'root'

    @property
    def dsn(self):
        return f"dbname={self.db_name} user={self.db_user} password={self.db_password} host={self.db_host} port={self.db_port}"

config = Config()
