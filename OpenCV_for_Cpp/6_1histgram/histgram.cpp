// 動画のフレーム内のRGBの各チャンネルがどれだけ含まれているかをヒストグラムで可視化できる
// 横軸は輝度(0-255),縦軸は画素数(0-255)
// calcHistはフレーム内の各チャンネルの画素数を計算できる、複数のチャンネルを指定して計算できる


#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // パスを指定して動画ファイル読み込み
    // auto filename="../examples/sample1.avi";
    auto filename="../examples/short_movie2.mov";
    VideoCapture cap(filename);
    Mat src;
    namedWindow("Input movie");

    // 色の指定
    vector<String> cName{"red", "green", "blue"};
    vector<Scalar> cScalar{Scalar(255,0,0),Scalar(0,255,0),Scalar(0,0,255)};

    // ヒストグラム
    Mat hist(Size(256,256), CV_8UC3);

    while(1){
        // 動画のフレーム読み込み、表示
        cap >> src; 
        if(src.empty()) break;
        imshow("Input movie", src);

        // RGBの各要素に分割
        vector<Mat> ch(3);
        split(src, ch);

        // ヒストグラムの定義
        vector<int> size{256};
        vector<float> range{0,256};
        hist.setTo(255);
        for(int c=0; c<3; c++){
            // チャンネル指定
            vector<int> channel{c};
            Mat bins;
            calcHist(ch, channel, noArray(), bins, size, range);
            Point prev=Point(0, 255);
            // ビン描画
            for(int x=0; x<256; x++){
                Point current=Point(x, 256-(int)(bins.at<float>(x)/50));
                line(hist, prev, current, cScalar[c]);
                prev=current;
            }
        }
        imshow("histgram", hist);

        // 終了
        if(waitKey(50)==27) break;
    }

    return 0;
}