#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat src=imread("../examples/image.png");
    Size size=src.size();
    Mat dst(size, CV_8SC3, Scalar::all(128));

    // ピクセル情報を元に代表する色に応じて、点描画を行う
    for(int y=8; y<size.height; y+=16){
        for(int x=8; x<size.width; x+=16){
            Vec3b bgr;
            bgr=src.at<Vec3b>(y,x);

            circle(dst, Point(x+4,y+3), int(bgr[0]/50.0),Scalar(255,0,0), -1);
            circle(dst, Point(x-4,y+3), int(bgr[1]/50.0),Scalar(0,255,0), -1);
            circle(dst, Point(x,y-3), int(bgr[2]/50.0),Scalar(0,0,255), -1);
        }
    }
    imshow("Input", src);
    imshow("pixel", dst);
    waitKey();

    return 0;
}