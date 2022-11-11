#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // ビデオファイル読み込み
    auto filename="../examples/Kyoko.mov";
    VideoCapture cap(filename);
    if(!cap.isOpened()){
        cout << "cannot open a video file!";
        cin.get();
        return -1;
    }
    // Matオブジェクト生成
    Mat img;

    while(1){
        cap>>img;
        if(img.empty()){
            break;
        }
        imshow("Display video", img);
        // ESCキーで終了
        if(waitKey(30)==27){
            break;
        }
    }

    return 0;
}