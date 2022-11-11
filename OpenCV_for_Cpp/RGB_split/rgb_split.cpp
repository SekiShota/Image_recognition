#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xphoto.hpp>

using namespace std;
using namespace cv;

int main(){
    // 動画ファイル読み込み
    auto filename="../examples/Kyoko.mov";
    VideoCapture cap(filename);
    // 画像サイズ
    Size frame((int)cap.get(CAP_PROP_FRAME_WIDTH),
                (int)cap.get(CAP_PROP_FRAME_HEIGHT));
    // ゼロ画像
    Mat src;
    Mat imgzero=Mat::zeros(frame, CV_8UC1);

    // 3チャンネル出力用
    vector<Mat> dst(3);
    vector<string> colors{"red", "green", "blue"};

    // 
    while(1){
        cap >> src;
        if(src.empty()) break;

        // Mat型vectorコンテナ（３要素）を用意
        vector<Mat> ch(3);

        // RGBチャンネルに分離
        split(src, ch);

        // チャンネル合成
        for(int i=0; i<ch.size(); i++){
            vector<Mat> temp {imgzero,imgzero,imgzero};
            temp[i]=ch[i];
            merge(temp, dst[i]);
            imshow(colors[i], dst[i]);
        }

        // RGBピクセル平均値を計算して表示する
        Scalar ave=mean(src);
        cout.precision(0);
        cout << fixed << "RGB平均値:" << ave << ";";

        // 最大値の要素番号を求める
        Point maxLoc;
        minMaxLoc(ave, NULL, NULL, NULL, &maxLoc);
        cout << colors[maxLoc.y] + "成分が多い" << endl;

        if(waitKey(30)==27) break;
    }
    return 0;
}