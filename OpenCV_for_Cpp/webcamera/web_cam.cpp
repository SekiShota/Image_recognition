#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // ビデオファイル読み込み
    auto cam_id=1;
    VideoCapture cap(cam_id);
    if(!cap.isOpened()){
        cout << "cannot find a camera!";
        cin.get();
        return -1;
    }

    // 表示ウィンドウ作成
    // namedWindow("反転", WINDOW_NORMAL);
    // resizeWindow("反転", 800, 600);

    // Matオブジェクト生成, src:元画像、gray:グレースケール画像、dst:拡張子指定した出力画像
    Mat src,dst;

    while(1){
        cap >> src;
        if(src.empty()){
            break;
        }

        // 左右反転
        flip(src, dst, 1);
        // 表示
        imshow("Camera", src);
        imshow("flip", dst);

        // ESCキーで終了
        if(waitKey(30)==27){
            break;
        }
    }

    return 0;
}