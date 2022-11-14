// 音は横軸時間・縦軸振幅の複数の正弦波で表現できることから、周波数とその強度（棒グラフ）に変換することができる
// 上記の内容で特定の周波数の音を消去することをフーリエ変換を用いた周波数フィルタリングという
// 逆フーリエ変換で棒グラフから正弦波に変換することができる
// 音は横軸時間で考えていたが、画像は位置で考えることができ同じ要領で変換処理ができる
// 画像の輝度（ピクセルの強度）は位置によって飛び飛びの値なので離散フーリエ変換(Discrete Fourier Transformation)を用いる
// 周波数領域は中心が0,四隅は周波数は大きい値となる
// 上記の中心部分を0にする(=黒くする)と逆離散フーリエ変換すると輪郭抽出ができる、高い周波数すなわちピクセル強度が大きい部分のみ抽出
// 画像のサイズの2乗に比例した時間がフーリエ変換するのにかかるので、OpenCVの関数には高速フーリエ変換が採用されている
// dft関数の出力は中心が高周波、四隅は低周波なので配置の並び替えが必要
// 上記の関数は2,3,5の冪乗の積の画像サイズでなければならない、そうでないときはゼロパディングでサイズを調整する
// 高周波領域をカットすることで画像の圧縮ができる、元画像とあまり変化がない

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void onMouse(int event, int x, int y, int flags, void* userdata);
void shiftImage(Mat& img);              // 画像入れ替え関数

int main()
{
  VideoCapture cap("../examples/sample2.avi");
  Mat src, srcW, freqW, dstW;

  // DFT用最適サイズ取得
  int oW = getOptimalDFTSize((int)cap.get(CAP_PROP_FRAME_WIDTH));
  int oH = getOptimalDFTSize((int)cap.get(CAP_PROP_FRAME_HEIGHT));
  Mat mask(Size(oW, oH), CV_32FC2, Scalar(1.0, 1.0));
  namedWindow("周波数分布");
  setMouseCallback("周波数分布", onMouse, &mask);

  while (1) {
    cap >> src; if (src.empty()) break;

    // 入力映像を DFT 入力形式に変換
    copyMakeBorder(src, src,
      0, oH - src.rows, 0, oW - src.cols,
      BORDER_CONSTANT, Scalar::all(0));
    cvtColor(src, src, COLOR_BGR2GRAY);
    src.convertTo(src, CV_32FC1, 1.0 / 255.0);
    imshow("入力映像", src);
    vector<Mat> chW{ src, Mat::zeros(src.size(), CV_32FC1) };
    merge(chW, srcW);                   // チャンネル数2の入力画像srcWを合成

    // DFT
    dft(srcW, freqW);                   // DFT計算
    shiftImage(freqW);                  // 画像入れ替え
    freqW = freqW.mul(mask);            // フィルタリング（マスクとの積）
    split(freqW, chW);
    imshow("周波数分布", chW[0] / 10);

    // 逆 DFT
    shiftImage(freqW);                  // 画像入れ替え（元に戻す）
    idft(freqW, dstW);                  // 逆DFT計算
    split(dstW, chW);
    normalize(chW[0], chW[0], 0.0, 1.0, NORM_MINMAX);
    imshow("逆DFT映像", chW[0]);

    if (waitKey(20) == 27) break;
  }

  return 0;
}

// マウスによる塗りつぶし
void onMouse(int event, int x, int y, int flags, void* userdata)
{
  Mat* mask = (Mat*)(userdata);         // void型をMat型にキャスト
  switch (event) {
  case EVENT_MOUSEMOVE:                 // マウス移動中
    if (flags == EVENT_FLAG_LBUTTON) {  // 左ボタンを押したとき
      circle(*mask, Point(x, y), 32, Scalar(0.0), -1);  // 黒円を描画
    }
    break;
  case EVENT_RBUTTONDOWN:               // 右ボタンを押したとき
    (*mask).setTo(1.0);                 // リセット
    break;
  }
}

// 画像入れ替え関数
void shiftImage(Mat& img) {
  int cx = img.cols / 2, cy = img.rows / 2;
  Mat q0(img, Rect(0, 0, cx, cy)), q1(img, Rect(cx, 0, cx, cy));
  Mat q2(img, Rect(0, cy, cx, cy)), q3(img, Rect(cx, cy, cx, cy)), tmp;
  q0.copyTo(tmp);
  q3.copyTo(q0);
  tmp.copyTo(q3);
  q1.copyTo(tmp);
  q2.copyTo(q1);
  tmp.copyTo(q2);
}
