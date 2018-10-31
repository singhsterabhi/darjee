import cv2
import numpy as np

cap = cv2.VideoCapture(2)
# cap.set( cv2.CV_CAP_PROP_FRAME_WIDTH, 1280 )
# cap.set( cv2.CV_CAP_PROP_FRAME_HEIGHT, 720 )

cap.set(3,1280)
cap.set(4,720)

ret, frame = cap.read()

while not ret:
    ret, frame = cap.read()

cv2.imshow('frame',frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite('image.jpg',frame)

# When everything done, release the capture
cap.release()
