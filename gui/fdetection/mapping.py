import cv2
import numpy as np
import math
import copy


def detect():
	image = cv2.imread('image.jpg',1)
	init=copy.deepcopy(image)
	
	x=image.shape[0]
	y=image.shape[1]
	print x,' ',y

	cv2.imshow('image',image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	image = cv2.GaussianBlur(image, (5, 5), 0)
	image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

	cv2.imshow('image',image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	# image = cv2.Canny(image,100,110,5)
	ret,image= cv2.threshold(image,100,255,cv2.THRESH_BINARY)
	cv2.imshow('image',image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	kernel = np.ones((10,10),np.uint8)
	image = cv2.dilate(image,kernel,iterations = 1)
	kernel = np.ones((20,20),np.uint8)
	image = cv2.erode(image,kernel,iterations = 1)
	kernel = np.ones((10,10),np.uint8)
	image = cv2.dilate(image,kernel,iterations = 1)
	cv2.imshow('image',image)
	cv2.waitKey(0)
	cv2.destroyAllWindows()

	im2, contours, hierarchy = cv2.findContours(image,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
	cv2.drawContours(init, contours, -1, (0,0,255), 3)
	print len(contours[0])
	cv2.imshow('image',init)
	cv2.waitKey(0)
	cv2.destroyAllWindows()
	
if __name__ == '__main__':
	detect()
