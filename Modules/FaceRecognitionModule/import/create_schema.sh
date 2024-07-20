#!/bin/bash

curl \
    -X POST \
    -H "Content-Type: application/json" \
    -d '{
      "class": "Images",
      "moduleConfig": {
          "img2vec-neural": {
              "imageFields": [
                  "image"
              ]
          }
      },
      "vectorIndexType": "hnsw",
      "vectorizer": "img2vec-neural",
      "properties": [
        {
          "dataType": [
            "string"
          ],
          "name": "filename",
          "description": "Full path of image file"
        },
        {
          "dataType": [
              "blob"
          ],
          "name": "image",
          "description": "Content of image in base64"
        },
        {
          "dataType": [
            "string"
          ],
          "name": "name",
          "description": "Name of person in the image"
        }
      ]
    }' \
    http://localhost:8080/v1/schema