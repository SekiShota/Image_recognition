#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // グレースケール画像として読み込み
    Mat src=imread("../examples/test1.jpg", IMREAD_GRAYSCALE);
    Mat dst;
    // // 縦方向のエッジ抽出(グラディエントフィルタ)
    // float data_v[9]={
    //     -1,0,1,
    //     -1,0,1,
    //     -1,0,1
    // };
    // // 横方向のエッジ抽出(グラディエントフィルタ)
    // float data_h[9]={
    //     -1,-1,-1,
    //     0,0,0,
    //     1,1,1
    // };

    // エッジ抽出(ハイパスフィルタ)
    // float data_v[9]={
    //     -1,-1,-1,
    //     -1,8,-1,
    //     -1,-1,-1
    // };

    // エッジ抽出(ラプラシアンフィルタ)
    // float data_v[9]={
    //     1,1,1,
    //     1,-8,1,
    //     1,1,1
    // };
    // エッジ抽出(ラプラシアンフィルタ)
    // float data_v[25]={
    //     -1,-3,-4,-3,-1,
    //     -3,0,6,0,-3,
    //     -4,6,20,6,-4,
    //     -3,0,6,0,-3,
    //     -1,-3,-4,-3,-1
    // };

    // エッジ抽出(ガウシアンフィルタ)
    float data_v[25]={
        1,4,6,4,1,
        4,16,24,16,4,
        6,24,36,24,6,
        4,16,24,16,4,
        1,4,6,4,1
    };
    auto size=5;
    Mat filter_v(Size(size,size), CV_32FC1, data_v);
    filter_v/=256.0;
    // Mat filter_h(Size(3,3), CV_32FC1, data_h);

    // 畳み込み演算
    filter2D(src, dst, -1, filter_v);
    // filter2D(dst, dst, -1, filter_h);

    imshow("input", src);
    imshow("output", dst);
    waitKey();
    
    return 0;
}