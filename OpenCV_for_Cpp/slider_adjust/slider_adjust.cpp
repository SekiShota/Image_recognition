#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double brightness=1.0;
void changeBrightness(int position, void* userdata);

int main(){
    int val=128;
    Mat src, gray, dst;
    auto filename="../examples/Kyoko.mov";
    VideoCapture cap(filename);
    namedWindow("Input movie");
    namedWindow("binary movie");

    // トラックバー作成
    createTrackbar("threshold", "binary movie", &val, 255);
    createTrackbar("brightness", "Input movie", NULL, 200, changeBrightness);
    setTrackbarPos("brightness", "Input movie", 100);

    while(1){
        cap >> src;
        if(src.empty()) return -1;
        src=src*brightness;
        cvtColor(src, gray, COLOR_BGR2GRAY);
        threshold(gray, dst, val, 255, THRESH_BINARY_INV);
        imshow("INPUT VIDEO", src);
        imshow("BINARY VIDEO", dst);
        if(waitKey(30)==27) break;
    }

    return 0;
}

void changeBrightness(int position, void* userdata){
    brightness=(double)position/100.0;
    cout << "bright ratio: " << brightness << endl;
}