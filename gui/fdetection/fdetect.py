import cv2
import numpy as np
import matplotlib.pyplot as plt
import math
import copy

def detect():
    image = cv2.imread('panel.jpg',3)
    template = cv2.imread('templates/5.jpg',0)
    init=copy.deepcopy(image)
##    image = cv2.imread('cloth1.jpg',3)
##    image = cv2.imread('cloth4.jpg',3)
##    image = cv2.imread('cloth5.jpg',3)

##    cv2.imshow('original',resized)
##    cv2.waitKey(0)
##    cv2.destroyAllWindows()


    x=image.shape[0]
    y=image.shape[1]
##    pixelperinch= y/78.7402
    pixelperinch= y/39.4

    # dim = (600, int(round(float(x) * 600/y)))


# perform the actual resizing of the image and show it
    resized = cv2.resize(image, dim, interpolation = cv2.INTER_AREA)
##    cv2.imshow('original image',resized)
##    print resized.shape
##
##
##    cv2.waitKey(0)
##    cv2.destroyAllWindows()

    blurred = cv2.GaussianBlur(resized, (15, 15), 0)
    imgray = cv2.cvtColor(blurred,cv2.COLOR_BGR2GRAY)
    blurred = imgray
##    cv2.imshow('cont',blurred)
##    cv2.waitKey(0)
##    cv2.destroyAllWindows()
    edges = cv2.Canny(blurred,100,110,5)
##    cv2.imshow('canny edged image',edges)
##
##    cv2.waitKey(0)
##    cv2.destroyAllWindows()

    kernel = np.ones((10,10), np.uint8)
    edges = cv2.dilate(edges,kernel,iterations = 1)
    kernel = np.ones((7,7), np.uint8)
    edges = cv2.erode(edges,kernel,iterations = 1)
    ret,thresh = cv2.threshold(edges,127,255,cv2.THRESH_BINARY_INV)

##    kernel = np.ones((35,35), np.uint8)
#    thresh = cv2.dilate(thresh,kernel,iterations = 1)

    im2,contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
##    contours=edges
##    print contours
    a1 = (resized.shape[0])*(resized.shape[1])
##    print a1
##    print len(contours)
    f=0
    for f in range((len(contours)-1),0,-1):
        a= cv2.contourArea(contours[f])
##        print a
        if a<(a1-10000) and a>20000:
            break
    cv2.drawContours(resized, contours, f, (255,0,0), 2)
##    cv2.imshow('cont',resized)
##    cv2.waitKey(0)
##    cv2.destroyAllWindows()


    stencil = np.ones(blurred.shape).astype(blurred.dtype)
    stencil.fill(255)
    color=[0,0,0]
    contour = [np.array(contours[f])]
##    print contour
    cv2.fillPoly(stencil,contour,color)
    image = stencil
    abc= image
    cv2.imshow('stencil',image)
##
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    abc.astype(np.float32)

    cv2.imshow('aacc',template)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    w, h = template.shape[::-1]

##    gray = cv2.cvtColor(abc, cv2.COLOR_BGR2GRAY)
    res=cv2.matchTemplate(abc,template,cv2.TM_CCOEFF)
    a,b,c,d=cv2.minMaxLoc(res)
    top_left = d
    bottom_right = (top_left[0] + w, top_left[1] + h)
##    print a,b,c,d #(470, 296) (243, 118)
    print top_left,bottom_right
    cv2.rectangle(init,top_left, bottom_right, (0,255,0), 1)
    cv2.imshow('Template',init)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == '__main__':
    detect()
