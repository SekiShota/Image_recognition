// オプティカルフローは動画の前フレームにあるピクセルと同じものを次のフレームで見つけること、ピクセルの移動量を推定する技術
// 対象の画像サイズを順次変えることで細かい解像度から粗い解像度まで階層化して処理することを画像ピラミッドという
// 上記の内容を扱う理由はある一点のピクセルに着目するのは難しいから
// #include <opencv2/optflow.hpp>, cv::optflow...と記述しないとオプティカルフローは実装できない


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/optflow.hpp>

using namespace std;
using namespace cv;

void drawOpticalFlow(const Mat& src, Mat& flowVec, Mat& flowHue);

int main()
{
  VideoCapture cap("../examples/sample1.avi");
//   VideoCapture cap("../examples/short_movie2.mov");
  Mat src, flowVec, flowHue;

  while (1) {
    cap >> src; if (src.empty()) break;
    drawOpticalFlow(src, flowVec, flowHue);       // フロー描画（自作関数）
    imshow("入力映像", src);
    imshow("フローベクトル", flowVec);
    imshow("フロー色相", flowHue);
    if (waitKey(20) == 27) break;
  }
}

// フロー描画（自作関数）
void drawOpticalFlow(const Mat& src, Mat& flowVec, Mat& flowHue)
{
  int step = 8;                                   // 計算ステップ
  Mat now, flow, flowXY[2], length, angle, hsv;
  static Mat pre(src.size() / step, CV_8UC1);     // 事前画像（pre）
  cvtColor(src, now, COLOR_RGB2GRAY);             // 現在画像（now）
  resize(now, now, src.size() / step);            // 縮小
  flowVec.create(src.size(), CV_8UC1); flowVec.setTo(255);
  flowHue.create(src.size(), CV_8UC3);
  Ptr<cv::optflow::DualTVL1OpticalFlow> opf = cv::optflow::createOptFlow_DualTVL1();  // 計算手法（DualTV-L1法）
  opf->setWarpingsNumber(3);                      // パラメータ設定
  opf->setEpsilon(0.05);
  opf->calc(pre, now, flow);                      // フロー計算	
  split(flow, flowXY);
  cartToPolar(flowXY[0], flowXY[1], length, angle, true);   // ベクトルの長さと角度を計算

  // ベクトル描画
  for (int py = 0; py < flowVec.rows; py += step) {
    for (int px = 0; px < flowVec.cols; px += step) {
      int dx = (int)(flowXY[0].at<float>(py / step, px / step) * 8);
      int dy = (int)(flowXY[1].at<float>(py / step, px / step) * 8);
      arrowedLine(flowVec, Point(px, py), Point(px + dx, py + dy), 0); // 矢印描画
    }
  }

  // 色相描画
  angle.convertTo(angle, CV_8U, 0.5, 45);         // 0～360度 → 0～180(色相範囲)
  length.convertTo(length, CV_8U, 255);
  // 角度→色相、長さ→彩度、明るさ→255
  vector<Mat> ch{ angle, length, Mat::ones(src.size() / step, CV_8U) * 255 };
  merge(ch, hsv);
  cvtColor(hsv, hsv, COLOR_HSV2BGR);              // 色空間をHSVからBGRに変換
  resize(hsv, flowHue, src.size());               // 入力サイズに拡大

  // 全体の平均移動方向矢印描画
  Point cp = flowVec.size() / 2;
  int mh = mean(flowXY[0]).val[0] * 100;
  int mv = mean(flowXY[1]).val[0] * 100;
  arrowedLine(flowVec, cp, cp + Point(mh, mv), Scalar(128), 10, LINE_8, 0, 1);
  now.copyTo(pre);                                // 現在画像を事前画像にコピー
}
