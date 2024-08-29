#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat img, imgHSV, maskb, masky;
int hminb = 89, sminb = 82, vminb = 0;
int hmaxb = 157, smaxb = 255, vmaxb = 255;

int hminy = 20, sminy = 145, vminy = 77;
int hmaxy = 33, smaxy = 255, vmaxy = 255;

void main() {
	string path = "Image.png";
	img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);\
	Scalar lowerb(hminb, sminb, vminb);
	Scalar upperb(hmaxb, smaxb, vmaxb);

	Scalar lowery(hminy, sminy, vminy);
	Scalar uppery(hmaxy, smaxy, vmaxy);

	inRange(imgHSV, lowerb, upperb, maskb);
	inRange(imgHSV, lowery, uppery, masky);
	imshow("Image", img);
	imshow("Maskb", maskb);
	imshow("Masky", masky);
	waitKey(0);
	
}