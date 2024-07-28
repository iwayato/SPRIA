from flask import Flask, render_template, request
from pymilvus import MilvusClient
import json

app = Flask(__name__)
# Run with <flask --app api run --debug>

# Connect to Milvus Server
try:
    server = MilvusClient(
        uri="http://192.168.4.20:19530",
        db_name="spria"
    )
except:
    print("Error al conectar con el servidor")

@app.route("/", methods=['GET'])
def root():
    return render_template('root.html')

@app.route("/collections", methods=['GET'])
def collections():
    available_collections = server.list_collections()
    return available_collections

@app.route("/collection_description/<collection_name>", methods=['GET'])
def collection_description(collection_name):
    try:
        collection_description = server.describe_collection(
            collection_name=collection_name
        )
        return collection_description
    except:
        return "Collection name does not exist"
        
@app.route("/load_collection/<collection_name>", methods=['GET'])
def load_collection(collection_name):
    try:
        server.load_collection(
            collection_name=collection_name,
            replica_number=1
        )
        return "Collection loaded correctly"
    except:
        return "Collection name does not exist"
    
@app.route("/unload_collection/<collection_name>", methods=['GET'])
def unload_collection(collection_name):
    try:
        server.release_collection(
            collection_name=collection_name,
        )
        return "Collection released correctly"
    except:
        return "Collection name does not exist"

@app.route("/load_state/<collection_name>", methods=['GET'])
def load_state(collection_name):
    try:
        state = server.get_load_state(
            collection_name=collection_name,
        )
        return state
    except:
        return "Collection name does not exist"

@app.route("/insert_vector", methods=['POST'])
def insert_vector():
    try:
        response = server.insert(
            collection_name='faces',
            data=request.get_json()
        )
        res = json.dumps(response, default=str)
        return res
    except:
        return "An error has occurred"