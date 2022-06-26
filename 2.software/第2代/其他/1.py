
from matplotlib import pyplot as plt
import cv2
import numpy as np
import os
from flask import Flask, render_template, Response

app = Flask(__name__)

capture1 = cv2.VideoCapture(1)
capture2 = cv2.VideoCapture(2)
def gen1():
	while(True):
		
		ret1, frame1 = capture1.read()
		#ret2, frame2 = capture2.read()
		image = cv2.imencode('.jpg', frame1)[1].tobytes()
		yield (b'--frame\r\n'
		       b'Content-Type: image/jpeg\r\n\r\n' + image + b'\r\n')

	#out.write(eye)
	#counter += 1
	#cv2.imwrite('./test.png',eye)
	#os.system('scp test.png ceremony@192.168.1.131:/home/ceremony/png')
	#cv2.imshow('sad',eye)
	#cv2.waitKey(10)
	#os.system('rm test.png')
def gen2():
	while(True):
		
		ret2, frame2 = capture2.read()
		#ret2, frame2 = capture2.read()
		image = cv2.imencode('.jpg', frame2)[1].tobytes()
		yield (b'--frame\r\n'
		       b'Content-Type: image/jpeg\r\n\r\n' + image + b'\r\n')

		
@app.route('/video1')
def video1():
    return Response(gen1(), mimetype='multipart/x-mixed-replace; boundary=frame')


@app.route('/video2')
def video2():
    return Response(gen2(), mimetype='multipart/x-mixed-replace; boundary=frame')

app.run(host='0.0.0.0',port=5000)	
