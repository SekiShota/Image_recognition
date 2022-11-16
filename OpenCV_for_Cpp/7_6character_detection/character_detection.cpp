// ・文字認識はOptical Character Recognition(OCR)
// ・部分領域の発見を「検出」、何の文字なのかを判定することを「認識」
// ・cv::textは上記どちらの機能も備わっている
// ・OpenCVではNeumann&Matasの文字検出アルゴリズムを利用して文字領域の検出をしている
// ・入力画像よりRGB, HSV, エッジ画像の合計7チャンネルの画像を利用して文字とおぼしき候補を検出している
// ・External Region(ER)は木構造で領域を関連づけて文字の検出をする
// ・２メガピクセルから10^6の候補領域があるが、第一段階では2600,第二段階では20まで絞ることができる
// ・NM1は第一段階、NM2は第二段階：https://github.com/Chris10M/text-detection-and-recognition
// https://github.com/opencv/opencv_contrib

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>

using namespace std;
using namespace cv;
using namespace text;

int main(){
    Mat img=imread("sign.png");
    string winName="character detection";
    imshow(winName, img);
    waitKey(10);

    // 多チャンネル化：BGRをHSVに変換
    Mat hsv;
    vector<Mat> ch;
    cvtColor(img, hsv, COLOR_BGR2HSV);
    split(hsv, ch);

    // 第一段階用ERFilterオブジェクト生成
    Ptr<ERFilter> filter1=createERFilterNM1(loadClassifierNM1("trained_classifierNM1.xml"), 5,0.00025,0.10,0.9,true,0.1);
    // 第二段階用ERFilterオブジェクト生成
    Ptr<ERFilter> filter2=createERFilterNM1(loadClassifierNM2("trained_classifierNM2.xml"), 5,0.00025,0.10,0.9,true,0.1);

    // 各チャンネルから領域抽出
    vector< vector<ERStat> > regions(ch.size());
    for(int i=0; i<ch.size(); i++){
        filter1->run(ch[i], regions[i]);
        filter2->run(ch[i], regions[i]);
    }

    // 文字領域のグルーピング
    vector< vector<Vec2i> > groups;
    vector<Rect> box;
    erGrouping(img, ch, regions, groups, box);
    for(int i=0; i<box.size(); i++){
        rectangle(img, box[i], Scalar(0,0,255),4,4);
    }
    imshow(winName, img);
    waitKey(0);

    return 0;
}