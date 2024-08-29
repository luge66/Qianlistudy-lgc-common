#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // ���̸���ڽǵ���������Ⱥ͸߶ȣ�
    int boardWidth = 9;
    int boardHeight = 6;
    Size boardSize(boardWidth - 1, boardHeight - 1); // 8x5 �ڽǵ�

    // ׼�����̸����������
    vector<Point3f> obj;
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            obj.push_back(Point3f(j, i, 0));
        }
    }

    // ��ȡ���ű궨ͼƬ
    string imageFile = "image1.jpg";  // �滻Ϊ���ͼƬ·��
    Mat image = imread(imageFile);
    if (image.empty()) {
        cout << "�޷�����ͼ��" << imageFile << endl;
        return -1;
    }

    // �������̸�ǵ�
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, boardSize, corners);

    if (found) {
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
            TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.001));

        // ���ƽǵ�
        drawChessboardCorners(image, boardSize, corners, found);
        imshow("Chessboard Corners", image);
        waitKey(500);  // ��ʾͼ��Ƭ��

        // ׼���궨
        vector<vector<Point3f>> objectPoints(1, obj);  // ��������
        vector<vector<Point2f>> imagePoints(1, corners);  // ͼ������

        // ִ������궨
        Mat cameraMatrix, distCoeffs, rvecs, tvecs;
        calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);

        // �������ڲξ���ͻ���ϵ��
        cout << "Camera Matrix:\n" << cameraMatrix << endl;
        cout << "Distortion Coefficients:\n" << distCoeffs << endl;

        // ���������ļ�
        FileStorage fs("camera_calibration.yml", FileStorage::WRITE);
        fs << "CameraMatrix" << cameraMatrix;
        fs << "DistCoeffs" << distCoeffs;
        fs.release();
    }
    else {
        cout << "δ�ܼ�⵽���̸�ǵ㣬�궨ʧ�ܡ�" << endl;
    }

    return 0;
}
