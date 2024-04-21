#!/bin/bash

#script made just to recompile the code when modified

cd ./build
cmake ..
make
mv ./FaceRecognition ../FaceRecognition