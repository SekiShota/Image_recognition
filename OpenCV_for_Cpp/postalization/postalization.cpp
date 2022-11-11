#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // 何色で表現するかを決める候補たち
    vector<int> lColor {180, 1, 2, 3, 4, 5, 6, 9, 10, 12, 15, 18, 20, 30, 36, 45, 60, 90};

    // 元画像：src, hsv変換：hsv, ポスタリゼーション：poster
    Mat src, hsv, poster;
    auto filename="../examples/test1.jpg";
    src=imread(filename);
    // hsv変換
    cvtColor(src, hsv, COLOR_BGR2HSV);

    for(int i=0; i<lColor.size(); i++){
        // ch[0]:h, ch[1]:s, ch[2]:v, 色相・彩度・明度
        vector<Mat> ch(3);
        split(hsv, ch);
        int nColor=lColor[i];
        int colorRange=180/nColor;
        ch[0]/=colorRange;
        ch[0]*=colorRange;
        merge(ch, poster);
        cvtColor(poster, poster, COLOR_HSV2BGR);

        stringstream ss;
        ss << "C=" << nColor;
        putText(poster, ss.str(), Point(20,30), FONT_HERSHEY_SIMPLEX, 1, Scalar::all(0));
        imshow("postalization", poster);

        if(waitKey()==27) break;

    }
    return 0;
}