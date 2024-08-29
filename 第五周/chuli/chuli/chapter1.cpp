
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// �����任����
Mat logTransform(const Mat& src) {
    Mat srcFloat;

    // ȷ��ͼ��ת��Ϊ������
    src.convertTo(srcFloat, CV_32F);

    // ִ�ж����任����ֹ log(0)
    srcFloat = srcFloat + 1;
    Mat logImage;
    log(srcFloat, logImage);

    // ��һ���� [0, 255] ��Χ
    normalize(logImage, logImage, 0, 255, NORM_MINMAX);

    // �����ת��Ϊ 8 λ�޷�����������
    logImage.convertTo(logImage, CV_8U);

    return logImage;
}

// ٤��У������
Mat gammaCorrection(const Mat& src, float gamma) {
    Mat srcFloat;

    // ת��Ϊ������
    src.convertTo(srcFloat, CV_32F);
    srcFloat = srcFloat / 255.0;

    // Ӧ��٤��У��
    pow(srcFloat, gamma, srcFloat);

    // ������������ŵ� [0, 255] ��Χ��ת���� CV_8U ����
    srcFloat = srcFloat * 255.0;
    Mat gammaImage;
    srcFloat.convertTo(gammaImage, CV_8U);

    return gammaImage;
}

int main(int argc, char** argv) {
    // ��ȡͼ�� src.png
    Mat image = imread("src.png", IMREAD_GRAYSCALE);

    if (image.empty()) {
        cout << "�޷�����ͼ��!" << endl;
        return -1;
    }

    // �����任��ǿ
    Mat logImage = logTransform(image);

    // ٤��У����ǿ (ʹ�ý�С��٤��ֵ��ǿ����)
    float gammaValue = 0.5; // ����٤��ֵ����ǿЧ��
    Mat gammaImage = gammaCorrection(image, gammaValue);

    // ��ʾԭʼͼ�񡢶����任���ͼ��٤��У�����ͼ��
    imshow("Original Image", image);
    imshow("Log Transformed Image", logImage);
    imshow("Gamma Corrected Image", gammaImage);

    // ���洦����ͼ��
    imwrite("log_transformed_image.png", logImage);
    imwrite("gamma_corrected_image.png", gammaImage);

    waitKey(0);
    return 0;
}
