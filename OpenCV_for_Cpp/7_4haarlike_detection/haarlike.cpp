// ・明暗で構成されたパターンのことをHaar状(HaarLike)、それを使って顔や目の検出を行うのがHaarLike特徴検出
// ・顔か否かの学習はAdaBoostが使われている
// ・OpenCVの中に含まれるxmlファイルのパスを指定するだけで分類器を実装することができる

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    auto filename=0;
    auto hide="../examples/star.png";
    VideoCapture cap(filename);
    Mat src, star(imread(hide)), star_r;

    // 顔検出
    auto f="haarcascade_frontalface_alt2.xml";
    CascadeClassifier face(f);

    // 目検出
    auto e="haarcascade_eye.xml";
    CascadeClassifier eye(e);
    

    while(1){
        cap >> src;
        vector<Rect> faceLoc, eyeLoc;

        // 顔検出と枠描画
        face.detectMultiScale(src, faceLoc, 1.1, 5, 0, Size(100,100));
        for(int i=0; i<faceLoc.size(); i++){
            rectangle(src, faceLoc[i], 255, 4);
        }

        // 目検出と星描画
        eye.detectMultiScale(src, eyeLoc, 1.1, 20, 0, Size(30,30), Size(100,100));
        for(int i=0; i<eyeLoc.size(); i++){
            resize(star, star_r, eyeLoc[i].size());
            star_r.copyTo(src(eyeLoc[i]));
        }

        imshow("HaarLike detector", src);
        if(waitKey(20)==27) break;
    }
    return 0;
}