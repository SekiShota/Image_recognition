#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    // ビデオファイル読み込み
    auto input="../examples/Kyoko.mov";
    // auto output="output.mp4";
    VideoCapture cap(input);
    Mat src,tmp,gaussian, moving;

    // ビデオ属性の取得
    int frameWidth=(int)cap.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight=(int)cap.get(CAP_PROP_FRAME_HEIGHT);
    int frameCount=(int)cap.get(CAP_PROP_FRAME_COUNT);
    int fps=(int)cap.get(CAP_PROP_FPS);
    int wait=1000/fps;

    // ビデオ属性の表示
    cout << "--------------------------" << endl;
    cout << "frameWidth: " << frameWidth << endl;
    cout << "frameHeight: " << frameHeight << endl;
    cout << "frameCount: " << frameCount << endl;
    cout << "fps: " << fps << endl;
    cout << "frameCount/fps: " << frameCount/fps << endl;
    cout << "wait: " << wait << endl;
    cout << "--------------------------" << endl;
    
    auto loop=true;
    while(loop){
        int pos=rand()%frameCount;
        int window=rand()%30+10;
        int direction=2*(rand()%2)-1;
        cout << "開始: " << pos << "," << "コマ数: " << window << "," << "方向: " << direction << endl;

        for(int f=0; f<window; f++){
            cap.set(CAP_PROP_POS_FRAMES, pos);
            cap >> src;
            imshow("shuffle", src);
            pos+=direction;
            pos=min(pos, frameCount-1);
            pos=max(pos, 0);
            if(waitKey(wait)==27){
                loop=false;
                break;
            }
        }
    }

    cap.release();
    destroyWindow("shuffle");

    cout << "キーを押して終了してください" << endl;
    cin.get();return 0;
}