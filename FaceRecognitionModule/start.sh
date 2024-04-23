#!/bin/bash

# Run from FaceRecognitionModule folder

docker compose up -d

while ! curl --fail -o /dev/null -s http://localhost:8080/v1/.well-known/ready; do
    echo "Waiting for Weaviate to be ready..."
    sleep 1;
done

echo "Weaviate DataBase Ready"

echo "Creating schema..."
./import/create_schema.sh
echo "Schema created"

echo "Importing images to database..."
./import/import_images.sh
echo "Images imported"

echo "All nice and ready to go"

mkdir build
cd ./build
cmake ..
make
mv ./FaceRecognition ../FaceRecognition


