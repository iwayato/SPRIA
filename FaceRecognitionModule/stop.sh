#!/bin/bash

curl \
    -X DELETE \
      http://localhost:8080/v1/schema/Images

docker compose down