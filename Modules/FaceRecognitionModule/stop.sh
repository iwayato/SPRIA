#!/bin/bash

# Run from FaceRecognitionModule folder

curl \
    -X DELETE \
      http://localhost:8080/v1/schema/Images

docker compose down

rm FaceRecognition
rm -rf ./build