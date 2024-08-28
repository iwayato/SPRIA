import cv2 as cv
import dlib
import helpers
import requests
import json
from datetime import datetime, date

api_url = "http://127.0.0.1:5000/insert_vector"
headers =  {"Content-Type":"application/json"}

video = cv.VideoCapture(0)
faceDetector = dlib.get_frontal_face_detector()
predictorPath = '../Predictors/shape_predictor_68_face_landmarks.dat'
shapePredictor = dlib.shape_predictor(predictorPath)
  
while(True): 
    sucess, img = video.read()
    imgCopy = img.copy()
    
    facesDetected = faceDetector(img)
    for faceDetected in facesDetected:
        x, y, w, h = faceDetected.left(), faceDetected.top(), faceDetected.width(), faceDetected.height()
        cv.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv.imshow('Face register', img)
        
    cv.imshow('Face register', img)
    
    if cv.waitKey(1) & 0xFF == ord('c'):    
        landmarks = shapePredictor(imgCopy, faceDetected)
        faceChip = dlib.get_face_chip(imgCopy, landmarks)
        faceEncoding = helpers.processFaceChip(faceChip)
        data = {
            'faces': faceEncoding,
            'counter': 0,
            'last_seen': datetime.now(),
            'creation_date': date.today()
        }
        response = requests.post(api_url, data=json.dumps(data, default=str), headers=headers)
        print(response.json())
        cv.imshow('Face chip', faceChip)
        
    if cv.waitKey(1) & 0xFF == ord('q'): 
        break
  
video.release() 
cv.destroyAllWindows() 