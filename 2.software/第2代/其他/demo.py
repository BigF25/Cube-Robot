import cv2
screen=cv2.VideoCapture(0)
while True:
    #img即为
    sucess,img=screen.read()
    #转为灰度图片
    gray=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #显示摄像头
    cv2.imshow("img",img)
    #保持画面的持续。
    k=cv2.waitKey(1)      #这里如果为0的话，就是将你目前所在的画面定定格，为其他数字比如1的时候，表示1秒后程序结束。但是由于是死循环，所以结束后马上开启，就为连续图像，
    if k == 27:
        #通过esc键退出摄像
        cv2.destroyAllWindows()
        break
    elif k==ord("s"):
        #通过s键保存图片，并退出。
        cv2.imwrite("image2.jpg",img)
        cv2.destroyAllWindows()
        break
#关闭摄像头
screen.release()