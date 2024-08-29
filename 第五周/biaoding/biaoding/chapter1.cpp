#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // 棋盘格的内角点数量（宽度和高度）
    int boardWidth = 9;
    int boardHeight = 6;
    Size boardSize(boardWidth - 1, boardHeight - 1); // 8x5 内角点

    // 准备棋盘格的物理坐标
    vector<Point3f> obj;
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            obj.push_back(Point3f(j, i, 0));
        }
    }

    // 读取单张标定图片
    string imageFile = "image1.jpg";  // 替换为你的图片路径
    Mat image = imread(imageFile);
    if (image.empty()) {
        cout << "无法加载图像：" << imageFile << endl;
        return -1;
    }

    // 查找棋盘格角点
    vector<Point2f> corners;
    bool found = findChessboardCorners(image, boardSize, corners);

    if (found) {
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
            TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.001));

        // 绘制角点
        drawChessboardCorners(image, boardSize, corners, found);
        imshow("Chessboard Corners", image);
        waitKey(500);  // 显示图像片刻

        // 准备标定
        vector<vector<Point3f>> objectPoints(1, obj);  // 物理坐标
        vector<vector<Point2f>> imagePoints(1, corners);  // 图像坐标

        // 执行相机标定
        Mat cameraMatrix, distCoeffs, rvecs, tvecs;
        calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);

        // 输出相机内参矩阵和畸变系数
        cout << "Camera Matrix:\n" << cameraMatrix << endl;
        cout << "Distortion Coefficients:\n" << distCoeffs << endl;

        // 保存结果到文件
        FileStorage fs("camera_calibration.yml", FileStorage::WRITE);
        fs << "CameraMatrix" << cameraMatrix;
        fs << "DistCoeffs" << distCoeffs;
        fs.release();
    }
    else {
        cout << "未能检测到棋盘格角点，标定失败。" << endl;
    }

    return 0;
}
