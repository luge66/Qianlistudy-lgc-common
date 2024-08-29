#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main() {
	string path = "test.png";
	Mat img = imread(path);
	Mat imggray, imgblur,imgdil,imgero;
	cvtColor(img, imggray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgblur, Size(3, 3), 3, 0);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(imgblur, imgdil, kernel);
	erode(imgblur, imgero, kernel);
	imshow("image dil", imgdil);
	imshow("image ero", imgero);

	imshow("Image", img);
	imshow("Image g", imggray);
	imshow("Image b", imgblur);
	waitKey(0);
}
