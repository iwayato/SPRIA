#!/bin/bash

import_images() {
  name=$(basename $1)

  for img in $1/*.jp*; do
    encoded=$(cat $img | base64 -w0)
    echo $img
    curl \
    -X POST \
    -H "Content-Type: application/json" \
    -d "{
      \"class\": \"Images\",
      \"properties\": {
        \"filename\": \"$img\",
        \"image\": \"$encoded\",
        \"name\": \"$name\"
      }
    }" \
      http://localhost:8080/v1/objects
  done
}

for dir in images/*; do
  import_images $dir
done