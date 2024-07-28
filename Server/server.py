# The Collection was created manually via Attu

from pymilvus import MilvusClient
# To print in json format compatible data
from pprint import pprint

server = MilvusClient(
    uri="http://192.168.4.20:19530",
    db_name="spria"
)

available_collections = server.list_collections()
print("Colecciones disponibles: ", available_collections)

collection_description = server.describe_collection(
    collection_name=available_collections[0]
)
pprint(collection_description)

# Before make searches, it is important to ensure that the collection is loaded
server.load_collection(
    collection_name=available_collections[0],
    # Max value is 1 for Milvus Standalone
    replica_number=1
)

is_loaded = server.get_load_state(
    collection_name=available_collections[0]
)
print("Estado de carga de la colección: ", is_loaded)

# To release the collection
server.release_collection(
    collection_name=available_collections[0]
)

