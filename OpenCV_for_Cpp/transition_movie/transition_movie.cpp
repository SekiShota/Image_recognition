#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void transition(Mat &m, int current, int start, int end, char type);

int main(){
    VideoCapture cap1("../examples/sample1.avi"), cap2("../examples/video.avi");
    Mat src1,src2,dst;
    Mat matrix(Size((int)cap1.get(CAP_PROP_FRAME_WIDTH),(int)cap1.get(CAP_PROP_FRAME_HEIGHT)), CV_8UC3);

    int transFrames=60;
    int maxframe=min((int)cap1.get(CAP_PROP_FRAME_COUNT), (int)cap2.get(CAP_PROP_FRAME_COUNT));

    bool flag=true;
    while(flag){
        int start=0;
        int end=maxframe;
        char mode=0;

        for(int frame=0; frame<maxframe; frame++){
            cap1>>src1;
            cap2>>src2;
            resize(src2, src2, src1.size());

            transition(matrix, frame, start, end, mode);
            dst=src1.mul(matrix/255.0)+src2.mul(~matrix/255.0);
            imshow("mask_image", matrix);
            imshow("transition", dst);
            int key=waitKey(30);
            if(key==27){
                flag=false;
                break;
            }
            else if(key=='w'||key=='d'||key=='c'){
                start=(int)cap1.get(CAP_PROP_POS_FRAMES);
                end=start+transFrames;
                mode=key;
            }
        }

        cap1.set(CAP_PROP_POS_FRAMES,0);
        cap2.set(CAP_PROP_POS_FRAMES,0);
        cout<<"Next run"<<endl;
    }

    return 0;
}

void transition(Mat &m, int current, int start, int end, char type){
    int pos=max(end-start,0);
    int duration=end-start;
    m.setTo(255);
    switch(type){
        case 'w':{
            int boundary=min(m.cols, m.cols*pos/duration);
            rectangle(m,Point(0,0), Point(boundary,m.rows), Scalar::all(0), FILLED, LINE_4,0);
            break;
        }
        case 'd':{
            int density=max(0,255-255*pos/duration);
            m.setTo(density);
            break;
        }
        case 'c':{
            int diag=norm(Point(m.cols, m.rows))/2;
            int rad=min(diag, diag*pos/duration);
            circle(m, m.size()/2, rad, Scalar::all(0), FILLED);
            blur(m, m, Size(100,100));
            break;
        }
    }
}