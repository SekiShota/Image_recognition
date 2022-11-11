#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat src1, src2, mask, dst, hsv;
    VideoCapture cap1("../examples/video.avi"),cap2("../examples/duck_greenback.avi");
    vector<Mat> ch(3);

    // 色相範囲ウィンドウ
    Mat imgHue1(Size(300,300), CV_8UC3, Scalar::all(0)), imgHue2;

    // 色相環
    for(int h=0; h<180; h++){
        ellipse(imgHue1, Point(150,150), Size(120,120), -90, 2*h-1, 2*h+1, Scalar(h,255,255), -1);
    }
    cvtColor(imgHue1, imgHue1, COLOR_HSV2BGR);
    imshow("Hue range", imgHue1);
    int minTrack=30, maxTrack=110;
    createTrackbar("min", "Hue range", &minTrack, 180);
    createTrackbar("Max", "Hue range", &maxTrack, 180);

    while(1){
        cap1 >> src1; if(src1.empty()) break;
        cap2 >> src2; if(src2.empty()) break;
        resize(src2, src2, src1.size());

        cvtColor(src2, hsv, COLOR_BGR2HSV);
        split(hsv, ch);

        int maxH=max(maxTrack, minTrack);
        int minH=min(maxTrack, minTrack);

        // 上限
        threshold(ch[0], mask, maxH, 255, THRESH_BINARY_INV);
        // 下限
        threshold(mask, mask, minH, 255, THRESH_BINARY);
        // ノイズ除去
        morphologyEx(mask, mask, MORPH_OPEN, noArray(), Point(-1,-1), 2);

        // 合成
        src2.copyTo(dst);
        src1.copyTo(dst, mask);

        // 色相環と範囲の描画
        imgHue1.copyTo(imgHue2);
        ellipse(imgHue1, Point(150,150), Size(130,130), -90, 2*minH-1, 2*maxH+1, Scalar::all(255), 16);

        imshow("mask_img", mask);
        imshow("conv_img", dst);
        imshow("Hue range", imgHue2);
        if(waitKey(20)==27) break;
    }

    return 0;
}