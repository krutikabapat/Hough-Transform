import cv2
import numpy as np
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-i","--image", help = 'required image path file')
args = vars(ap.parse_args())


def onTrackbarChange(max_slider):
	global img
	global dst
	global gray
	dst = np.copy(gray)
	edges = cv2.Canny(gray, 75, 150)
	lines = cv2.HoughLinesP(edges, 1, np.pi/180, max_slider, maxLineGap=250)
	
	for line in lines:
		x1, y1, x2, y2 = line[0]
		cv2.line(dst, (x1, y1), (x2, y2), (0, 255, 0), 3)

	# cv2.imshow("edges", edges)
	cv2.imshow("frame",dst)
	


if __name__ == "__main__":
	img = cv2.imread(args["image"])
	dst = np.copy(img)
	cv2.namedWindow("frame")

	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	
	thresh = 80
	val = 100

	cv2.createTrackbar("threshold", "frame", thresh, val, onTrackbarChange)
	onTrackbarChange(val)

	while True:
		cv2.imshow("source image",img)
		key = cv2.waitKey(1)
		if key == ord('q'):
			break

	cv2.destroyAllWindows()