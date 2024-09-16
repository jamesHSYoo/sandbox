from pymongo import MongoClient

class DB:
    def __init__(self) -> None:
        self.user = 'admin'
        self.password = 'admin'
        self.uri = 'mongodb://localhost:27017'
        self.client = MongoClient()

    def connection_mongo_db(self):
        client = MongoClient(self.uri)
        try:
            client.admin.command("ping")
            print("Connected successfully")
            # other application code
            # client.close()
        except Exception as e:
            print(f"Cannot Connect to MongoDB : {e}")
            raise 
        self.client = client
        
    def disconnect_connection(self):
        try:
            self.client.close()    
        except Exception as e:
            print(f"Cannot disconnect to MongoDB : {e}")

    def set_collection(self, database : str, collection: str):
        database = self.client[database]
        collection = database[collection]
        return collection

if __name__ == '__main__':
    db = DB()
    db.connection_mongo_db()
    collection = db.set_collection("admin", "price_data")
    results = collection.find_one({ "asset_code" : "KOSPI200" })
    print(results)
    db.disconnect_connection()

