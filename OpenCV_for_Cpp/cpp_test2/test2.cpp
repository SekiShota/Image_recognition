#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printMat(string, Mat &m);

int main() {
    // Mat img1(480, 640, CV_8UC1);
    Mat img1=imread("IMG_1884.jpg"), img2;
    resize(img1, img2, Size(), 1.5, 1.5);
    imwrite("image_dst.jpg", img2,{IMWRITE_JPEG_QUALITY,100});

    // 画像の情報を表示
    printMat("img2", img2);
    return 0;
}

void printMat(string str, Mat &m){
    cout << "----" << str << "----" << endl;
    cout << "Size(attr): " << "[" << m.cols << "," << m.rows << "]" << endl;
    cout << "Dim(attr)" << m.dims << endl;
    cout << "Size(method)" << m.size() << endl;
    cout << "Total(method)" << m.total() << endl;
    cout << "Channels(method)" << m.channels() << endl;
    cout << "Depth(method)" << m.depth() << endl;
    cout << "Type(method)" << m.type() << endl;
    imshow("generated image", m);
    waitKey();
}