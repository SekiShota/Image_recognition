// テンプレートマッチングは対象物との類似度で特定の物体を検出する
// 残差法は対象物とのピクセルの差分の絶対値(SAD)と差分の二乗(SSD)がある=最小となるポイントを探索
// 相関法は対象物との相関から特定の物体かどうか判断する(0:全く違う、1に近ければ同じ物体)=最大となるポイントを探索
// テンプレート画像は探索画像から抜き出したものを使うのが好ましい

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    auto filename="../examples/sample1.avi";
    VideoCapture cap(filename);
    Mat src;
    // テンプレート画像
    vector<Mat> img{imread("../examples/ball.png"), imread("../examples/car.png")};
    vector<String> name{"ball", "car"};

    while(1){
        cap >> src; if(src.empty()) break;
        for(int num=0; num<2; num++){
            Mat mapCC;
            // テンプレートマッチング,類似度計算手法はTM_CCOEFF_NORMED（ゼロ平均正規化相互相関）
            matchTemplate(src, img[num], mapCC, TM_CCOEFF_NORMED);
            double maxCC;
            Point maxLoc;
            // 相互相関係数の最大値の探索
            minMaxLoc(mapCC, NULL, &maxCC, NULL, &maxLoc);
            // 類似度が0.4以上ならば枠を描画
            if(maxCC>0.4){
                rectangle(src, maxLoc, maxLoc+Point(img[num].cols, img[num].rows), Scalar(0,0,255), 8);
                putText(src, name[num], maxLoc+Point(10,30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 4);
            }
            imshow("Interactive correlations"+name[num], mapCC);
        }
        imshow("template matching", src);
        if(waitKey(20)==27) break;
    }

    return 0;
}