// ・OpenCVの同梱パッケージに学習済みモデルとしてdnnモジュールが存在する
// ・ImageNet2012というデータベースには1クラス5万枚、1000クラスの画像が用意されている
// ・上記の画像を学習して得られたモデルがbvlc_reference_caffenet.caffemodelである
// ・上記のモデルファイルに加えて、プロトテキストファイルと説明ファイルが必要
// ・モデルデータファイル、ニューラルネットの構造が定義されたファイル、クラスの名称がまとめられているファイル
// ・モデルファイル；https://github.com/BVLC/caffe/tree/master/models/bvlc_reference_caffenet
// ・プロトテキストファイル:https://gist.github.com/dudu159632/dd2e7ed4f2dd00cc69c810eeb2ff2930
// ・説明ファイル：https://github.com/HoldenCaulfieldRye/caffe/blob/master/data/ilsvrc12/synset_words.txt
// ・dnnの関数：https://docs.opencv.org/4.6.0/d6/d0f/group__dnn.html

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace std;
using namespace cv;
using namespace cv::dnn;

int main(){
    // Caffeモデルの読み込み(3.x系): https://docs.opencv.org/3.2.0/d6/d0f/group__dnn.html
    // Ptr<Importer> caffe=createCaffeImporter("bvlc_googlenet.prototxt", "bvlc_googlenet.caffemodel");
    // Net deepnet
    // caffe->populateNet(deepnet);
    // caffe.release();

    // Caffeモデルの読み込み(4.x系): http://tecsingularity.com/opencv/opencv_googlenet/
    Net deepnet;
    deepnet=readNetFromCaffe("bvlc_googlenet.prototxt", "bvlc_googlenet.caffemodel");
    
    // クラス説明ファイル読み込み(1000クラス)
    vector<string> classNames;
    ifstream fp("synset_words.txt");
    string name;
    while(getline(fp,name)){
        if(name.length()){
            classNames.push_back(name.substr(name.find(' ')+1));
        }
    }
    fp.close();

    // 入力画像(サイズは224x224)
    vector<string> files{"space_shuttle.jpg","cats.jpg","car.png","bear.jpg","rappi.jpg"};
    for(int i=0; i<files.size(); i++){
        // 画像読み込み, Mat型
        Mat src=imread(files[i]);
        // 224x224にリサイズ
        resize(src, src, Size(224,224));
        // blob型に変換
        src=blobFromImage(src);
        // 入力層にデータ渡す, dataという名前の層に値を入力する
        deepnet.setInput(src, "data");
        // DeepLearningによる分類、出力結果の取得,probという名前の層の値を取得する
        Mat probMat=deepnet.forward("prob");
        // 結果を1000x1に変換
        probMat=probMat.reshape(1,1);

        // 出力値が最も高くなるクラスの位置を求める
        double maxVal;
        Point maxLoc;
        minMaxLoc(probMat, NULL, &maxVal, NULL, &maxLoc);

        // 出力値が最も高くなるクラス名と信頼度の表示
        cout << "最も一致するクラス:" << classNames.at(maxLoc.x) << endl;
        cout << "信頼度:" <<  maxVal*100 << "%" << endl;
        // waitKey(0);
    }
    
    return 0;
}