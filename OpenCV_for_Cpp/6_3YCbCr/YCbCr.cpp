// 離散コサイン変換(Discrete Cosine Transformation)では複素数が出てくるのでcos波成分(実部)とsin波成分(虚部)を扱う
// 離散コサイン変換はcos波成分(実部)のみ扱うので計算コストを抑えることができる
// 上記の処理では低周波領域に集中することから効率の良い圧縮方法である
// YCbCrはY(明るさ)、Cb(青み)、Cr(赤み)を表現しているが、ヒトの目は明るさ以外は敏感ではないのでCb,Crを削っても気づかれない
// 離散コサイン変換の周波数領域は左上が低周波、右・下が高周波で表現される

#include <iostream>
#include <opencv2/opencv.hpp>
// #pragma comment(lib, "opencv_world320d.lib")
using namespace std;
using namespace cv;

int main()
{
  int bs = 80;                     // 分割ブロックサイズ（ピクセル）
  int th = bs / 2;                 // カット閾値thの初期値はbsの半分
  int cn = 0;                      // カットする成分の初期値（0=Y 1=Cr 2=Cb）
  VideoCapture cap("../examples/sample2.avi");
  int frameWidth = (int)cap.get(CAP_PROP_FRAME_WIDTH);
  int frameHeight = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
  namedWindow("周波数分布");
  createTrackbar("Y-Cr-Cb", "周波数分布", &cn, 2);
  createTrackbar("カット閾値", "周波数分布", &th, bs - 1);
  Mat src, yrb, tmp, dst;
  Size size((frameWidth / bs) * bs, (frameHeight / bs) * bs);    // bsの倍数サイズ
  Mat imgDCT(size, CV_32FC1);

  while (1) {
    cap >> src; if (src.empty()) break;
    resize(src, src, size);                  // bsの倍数サイズに合わせる
    cvtColor(src, yrb, COLOR_BGR2YCrCb);
    yrb.convertTo(yrb, CV_32FC3);
    vector<Mat> ch;
    split(yrb, ch);                          // Y, Cr, Cbチャンネルの分離
    imgDCT.setTo(0.0);                       // 周波数領域画像を黒く塗る

    for (int y = 0; y < size.height; y += bs)
    {
      for (int x = 0; x < size.width; x += bs)
      {
        Rect roi(x, y, bs, bs);              // 変換対象ブロック（bs×bsピクセル）
        dct(ch[cn](roi), tmp);               // DCT変換
        // カット閾値内だけ周波数領域画像にコピー（残りは黒のまま）
        tmp(Rect(0, 0, th + 1, th + 1)).copyTo(
          imgDCT(Rect(roi.x, roi.y, th + 1, th + 1)));
        idct(imgDCT(roi), ch[cn](roi));      // 逆DCT変換
      }
    }

    merge(ch, dst);                          // Y, Cr, Cbチャンネルの結合
    dst.convertTo(dst, CV_8UC3);
    cvtColor(dst, dst, COLOR_YCrCb2BGR);
    normalize(ch[0], ch[0], 0.0, 1.0, NORM_MINMAX);
    normalize(ch[1], ch[1], 0.0, 1.0, NORM_MINMAX);
    normalize(ch[2], ch[2], 0.0, 1.0, NORM_MINMAX);
    imshow("Y（輝度）", ch[0]);
    imshow("Cr（赤み）", ch[1]);
    imshow("Cb（青み）", ch[2]);
    imshow("周波数分布", imgDCT);
    imshow("逆DCT映像", dst);

    if (waitKey(20) == 27) break;
  }

  return 0;
}
