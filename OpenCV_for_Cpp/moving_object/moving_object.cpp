#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    auto file="../examples/short_movie2.mov";
    VideoCapture cap(file);
    auto width=(int)cap.get(CAP_PROP_FRAME_WIDTH);
    auto height=(int)cap.get(CAP_PROP_FRAME_HEIGHT);
    Size frame(width, height);
    Mat src, diff, diffInv, srcFloat, dstFloat, diffFloat;
    dstFloat.create(frame, CV_32FC3);
    dstFloat.setTo(0.0); 

    while(1){
        cap >> src;
        if(src.empty()) break;
        imshow("Input movie", src);
        // 入力動画を小数点型に変換
        src.convertTo(srcFloat, CV_32FC3, 1/255.0);
        // 重み付き和
        addWeighted(srcFloat, 0.01, dstFloat, 0.99, 0, dstFloat, -1);
        imshow("backgroud image", dstFloat);

        // 差分の絶対値の計算
        absdiff(srcFloat, dstFloat, diffFloat);
        imshow("diff movie", diffFloat);

        // ネガポジ反転（色、明るさが反転する）
        diffFloat.convertTo(diff, CV_8UC3, 255.0);
        bitwise_not(diff, diffInv);
        imshow("diff_inv_image",diffInv);

        if(waitKey(30)==27) break;
    }

    return 0;
}