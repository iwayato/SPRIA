import dlib

# Modelos
faceRecogPath = '../Models/dlib_face_recognition_resnet_model_v1.dat'
faceRecognitionModel = dlib.face_recognition_model_v1(faceRecogPath)

def processFaceChip(faceChip):
    return list(faceRecognitionModel.compute_face_descriptor(faceChip))