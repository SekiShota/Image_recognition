#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // ビデオファイル読み込み
    auto input="../examples/Kyoko.mov";
    auto output="output.mp4";
    VideoCapture cap(input);
    if(!cap.isOpened()){
        cout << "cannot open a video file!";
        cin.get();
        return -1;
    }
    // 元動画のサイズ，FPSを取得しておく(サイズが不一致だとエラーになる)
    auto width = int(cap.get(CAP_PROP_FRAME_WIDTH));
    auto height = int(cap.get(CAP_PROP_FRAME_HEIGHT));
    auto fps = cap.get(CAP_PROP_FPS);
    // auto fps=30;
    cout << "width: " << width << endl;
    cout << "height: " << height << endl;
    cout << "fps: " << fps << endl;

    // 保存するビデオファイルの設定
    VideoWriter rec(output, 
    VideoWriter::fourcc('m','p','4','v'), fps, Size(width,height));

    // Matオブジェクト生成, src:元画像、gray:グレースケール画像、dst:拡張子指定した出力画像
    Mat src, gray, dst;

    while(1){
        cap >> src;
        if(src.empty()){
            break;
        }

        // グレースケール、二値化、3chに変換
        cvtColor(src, gray, COLOR_BGR2GRAY);
        threshold(gray, gray, 128, 255, THRESH_BINARY);
        cvtColor(gray, dst, COLOR_GRAY2BGR);
        imshow("Input video", src);
        imshow("Output video", dst);

        rec << dst;
        // ESCキーで終了
        if(waitKey(30)==27){
            break;
        }
    }

    return 0;
}