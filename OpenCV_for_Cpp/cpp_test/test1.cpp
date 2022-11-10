#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // 読み込んだ画像をウィンドウに表示
    // cv::Mat img = cv::imread("test1.jpg");

    // cv::namedWindow("test", cv::WINDOW_AUTOSIZE);
    // cv::imshow("test", img);
    // cv::waitKey(0);
    // cv::destroyWindow("test");

    // エッジ検出
    Mat src = cv::imread("test.jpg"), dst;
    // 白黒でエッジ検出
    // Canny(src,dst,30,180,3);

    // イラスト風
    // stylization(src,dst);

    // 鉛筆画風
    Mat dst2;
    pencilSketch(src, dst, dst2);
    // cv::namedWindow("test", cv::WINDOW_AUTOSIZE);
    imshow("入力画像", src);
    imshow("出力画像", dst2);

    imwrite("image_dst.jpg", dst,{IMWRITE_JPEG_QUALITY,100});

    waitKey(0);
    // cv::destroyWindow("test");

    return 0;
}

// https://qiita.com/toshi_machine/items/908e9be57e8afa629159
// mkdir build (ビルド用にディレクトリを用意)
// cd build
// cmake .. . (ビルドするために必要な手続きを用意)
// make (ビルドするためのファイルが生成される)
// cd ..
// ./build/Main (ビルドしてプログラムを実行)