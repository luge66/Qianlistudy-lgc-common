
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

// 对数变换函数
Mat logTransform(const Mat& src) {
    Mat srcFloat;

    // 确保图像转换为浮点型
    src.convertTo(srcFloat, CV_32F);

    // 执行对数变换，防止 log(0)
    srcFloat = srcFloat + 1;
    Mat logImage;
    log(srcFloat, logImage);

    // 归一化到 [0, 255] 范围
    normalize(logImage, logImage, 0, 255, NORM_MINMAX);

    // 将结果转换为 8 位无符号整数类型
    logImage.convertTo(logImage, CV_8U);

    return logImage;
}

// 伽马校正函数
Mat gammaCorrection(const Mat& src, float gamma) {
    Mat srcFloat;

    // 转换为浮点型
    src.convertTo(srcFloat, CV_32F);
    srcFloat = srcFloat / 255.0;

    // 应用伽马校正
    pow(srcFloat, gamma, srcFloat);

    // 将结果重新缩放到 [0, 255] 范围并转换回 CV_8U 类型
    srcFloat = srcFloat * 255.0;
    Mat gammaImage;
    srcFloat.convertTo(gammaImage, CV_8U);

    return gammaImage;
}

int main(int argc, char** argv) {
    // 读取图像 src.png
    Mat image = imread("src.png", IMREAD_GRAYSCALE);

    if (image.empty()) {
        cout << "无法加载图像!" << endl;
        return -1;
    }

    // 对数变换增强
    Mat logImage = logTransform(image);

    // 伽马校正增强 (使用较小的伽马值增强暗部)
    float gammaValue = 0.5; // 调整伽马值以增强效果
    Mat gammaImage = gammaCorrection(image, gammaValue);

    // 显示原始图像、对数变换后的图像、伽马校正后的图像
    imshow("Original Image", image);
    imshow("Log Transformed Image", logImage);
    imshow("Gamma Corrected Image", gammaImage);

    // 保存处理后的图像
    imwrite("log_transformed_image.png", logImage);
    imwrite("gamma_corrected_image.png", gammaImage);

    waitKey(0);
    return 0;
}
