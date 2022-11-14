// ピクセルの位置と色が同じでないと対象物を検出できないという欠点を補うために色相と彩度の二次元ヒストグラムを用いる
// ヒストグラムの交差法は対象物と探索画像のヒストグラムを重ねた時、重なった面積が1に近いと同じものとみなされる
// 積分を使わずに、比較して小さい方の値を全階級分算出してそれらの和が面積として求められる、OpenCVではcompareHist関数を使用

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 二次元ヒストグラム取得関数
void hist2D(Mat& src, Mat& hist);

int main(){
    // 動画ファイル読み込み
    auto filename="../examples/sample3.avi";
    VideoCapture cap(filename);
    Mat src;

    // 参照画像
    vector<Mat> img{imread("../examples/chipmonk.jpg"), imread("../examples/duckling.jpg")};
    // 名称
    vector<String> name{"chipmonk", "duckling"};
    // ヒストグラム
    vector<Mat> histRef(2);
    hist2D(img[0], histRef[0]);
    hist2D(img[1], histRef[1]);
    Mat histSrc;

    while(1){
        cap >> src; if(src.empty()) break;
        // 入力画像のヒストグラム取得
        hist2D(src, histSrc);

        for(int num=0; num<2; num++){
            // ヒストグラムの類似度計算, HISTCMP_INTERSECT
            double similarity=compareHist(histRef[num], histSrc, HISTCMP_INTERSECT);
            if(similarity>0.7){
                putText(src, name[num], Point(20,40), FONT_HERSHEY_SIMPLEX, 1, 0, 4);
            }
        }
        imshow("Input_movie", src);
        Mat ShowHistSrc;
        resize(histSrc*3000, ShowHistSrc, histSrc.size()*4);
        imshow("histgram", ShowHistSrc);

        if(waitKey(2000)==27) break;
    }

    return 0;
}

// 二次元ヒストグラム取得関数
void hist2D(Mat& src, Mat& hist){
    Mat hsv;
    cvtColor(src, hsv, COLOR_BGR2HSV);
    vector<Mat> ch(3);
    split(hsv, ch);
    vector<int> channel{0,1};
    vector<int> size{45,64};
    vector<float> range{0,180,0,256};
    calcHist(ch, channel, noArray(), hist, size, range);
    hist=hist/(src.cols*src.rows);
}