import cv2

url1 = 'http://192.168.31.130:5000/video1'
url2 = 'http://192.168.31.130:5000/video2'
cap1 = cv2.VideoCapture(url1)
cap2 = cv2.VideoCapture(url2)

while True:
    ret1, frame1 = cap1.read()
    ret2, frame2 = cap2.read()
    cv2.imshow("video1", frame1)
    cv2.imshow("video2", frame2)
    key = cv2.waitKey(1)
    if key  == ord('q'):  #判断是哪一个键按下
        break
cap1.release()
cap2.release()
cv2.destroyAllWindows()
