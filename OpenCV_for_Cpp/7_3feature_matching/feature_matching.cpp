// ・シンプルなテンプレートマッチングはテンプレート画像のサイズと探索範囲の広さによって計算コストが大きくなる
// ・ヒストグラムの方法では背景色の違いによって色構成が異なるので、検出できないことがある
// ・上記の問題を解決するために、対象物の特徴点を決めてそこを基準にどのような恰好をしているかの情報を取得する特徴量を使った方法がある
// ・特徴量の不変性に対応したORBというアルゴリズムで特徴点と特徴量を高速かつ高精度で抽出することができる

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // 探索画像（映像）
    // auto filename="../examples/sample2.avi";
    auto filename="../examples/Kyoko.mov";
    // テンプレート画像
    // auto template_img="../examples/robo.png";
    auto template_img="../examples/08.png";

    VideoCapture cap(filename);
    Mat src, ref(imread(template_img));

    cout << "rキーで参照画像更新" << endl;

    while(1){
        cap >> src; if(src.empty()) break;

        // 特徴の抽出と記述
        vector<KeyPoint> keypoint1, keypoint2;
        Mat descriptor1, descriptor2;
        Ptr<ORB> feature=ORB::create();
        feature->detectAndCompute(ref, noArray(), keypoint1, descriptor1);
        feature->detectAndCompute(src, noArray(), keypoint2, descriptor2);

        // 特徴点マッチング, ハミング距離で算出しておりデータがどれだけ違うかを示す
        vector<DMatch> allMatch, goodMatch;
        BFMatcher matcher(NORM_HAMMING);
        matcher.match(descriptor1, descriptor2, allMatch);

        // 似ている特徴点のみピックアップ
        for(int i=0; i<(int)allMatch.size(); i++){
            if(allMatch[i].distance<10){
                goodMatch.push_back(allMatch[i]);
            }
        }

        // 描画
        Mat dst(480, 1280, CV_8UC3);
        drawMatches(
            ref, keypoint1, src, keypoint2, goodMatch, dst,
            Scalar::all(-1), Scalar::all(-1), vector<char>(),
            DrawMatchesFlags::DRAW_RICH_KEYPOINTS
        );

        // 一致率
        float matchRate=(float)goodMatch.size()/(float)keypoint1.size();
        stringstream ss;
        ss.precision(3);
        ss << fixed << matchRate;
        putText(dst, ss.str(), Point(8,30), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0,0,255), 4);
        if(matchRate>0.01){
            putText(dst, "detect", Point(650,40), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0,0,255), 4);
        }
        imshow("feature point matching", dst);

        if(waitKey(20)=='r') src.copyTo(ref);
        if(waitKey(20)==27) break;
    }

    return 0;
}