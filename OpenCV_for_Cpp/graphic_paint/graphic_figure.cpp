#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // 色の設定, OpenCVはBGRの順番で色指定
    Scalar red(0,0,255), green(0,255,0), blue(255,0,0);
    Scalar gray(128,128,128);
    Scalar dgray=gray/4;
    Scalar white=Scalar::all(255);
    Mat img(Size(640,480), CV_8UC3, white);

    // 直線と矢印
    line(img, Point(50,50), Point(150,150), blue, 8, LINE_AA);
    arrowedLine(img, Point(50,250), Point(150,200), red, 8, LINE_4, 0, 0.3);

    // 波線の格子メモリ
    for(int lx=50; lx<640; lx+=50){
        for(int ly=0; ly<480; ly+=15){
            line(img, Point(lx,ly), Point(lx,ly+10), gray);
        }
    }
    for(int ly=50; ly<480; ly+=50){
        for(int lx=0; lx<640; lx+=15){
            line(img, Point(lx,ly), Point(lx+10,ly), gray);
        }
    }
    
    // 長方形, dlib::get_frontal_face_detectorは左上の座標、右下の座標を返すので一番目の書き方が好ましい
    rectangle(img, Point(200,100), Point(300,250), dgray, 3);
    Rect waku(250,50,75,100);
    rectangle(img, waku, green, 16);

    // 多角形（塗りつぶし）
    vector<Point> points{Point(400,100), Point(475,150), Point(400,250), Point(350,200), Point(350,150)};
    fillConvexPoly(img, points, Scalar(200,0,0));

    // 多角形（線のみ）
    vector<Point> poly={Point(130,280), Point(550,200), Point(420,450)};
    polylines(img, poly, true, Scalar(0,200,255), 5);

    // 円と楕円
    circle(img, Point(550,200), 50, red, 5);
    ellipse(img, Point(550,100), Size(60,30), 30, 90, 360, green, FILLED);
 
    // 文字
    putText(img, "Machine Learning", Point(50,400), FONT_HERSHEY_SIMPLEX, 2, blue, 4);
 
    // 表示
    imshow("graphic figures", img);
    waitKey();

    return 0;
}