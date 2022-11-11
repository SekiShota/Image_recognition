#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    VideoCapture cap(0);
    Mat src, floatConstant, floatNormal;
    int constant=255, normal=1;

    namedWindow("constant");
    createTrackbar("constant 1/X", "constant", &constant, 255);
    namedWindow("normalize");
    createTrackbar("normalize 0-X", "normalize", &normal, 10);
    
    while(1){
        cap >> src;
        if(src.empty()) break;
        cvtColor(src, src, COLOR_BGR2GRAY);

        if(constant==0){
            constant=1;
        }
        src.convertTo(floatConstant, CV_32FC1, 1.0/constant);
        imshow("constant", floatConstant);

        src.convertTo(floatConstant, CV_32FC1, 1.0/constant);
        normalize(floatNormal, floatNormal, 0, normal, NORM_MINMAX);
        imshow("normalize", floatConstant);

        if(waitKey(100)==27) break;
    }
    return 0;
}