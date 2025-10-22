class Settings:
    __db_host = 'localhost'
    __db_port = '5432'
    __db_name = 'dm_db'
    __db_user = 'root'
    __db_password = 'root'

    @property
    def dsn(self):
        return f"dbname={self.__db_name} user={self.__db_user} password={self.__db_password} host={self.__db_host} port={self.__db_port}"

settings = Settings()
