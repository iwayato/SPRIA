#!/bin/bash

#RUN THIS TEST CODE FROM "base64" folder
#At the moment it only works with .jpg image files

IMAGES_PATH="../images"
ENCODINGS_PATH="./test/base64_encodings"

for img in $IMAGES_PATH/*
do
    filename=$(basename $img .jpg)
    encoded=$(cat $img | base64 | tr -d '\n') 
    echo $encoded > $ENCODINGS_PATH/$filename.txt

done

g++ -o ./test/test ./test/test.cpp base64.cpp `pkg-config --cflags --libs opencv4`

./test/test