#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

class Comparator {
public:
    Comparator(Mat &image) :_image(&image) {
        cout << "making comparator" << endl;
    }
    
    void Compare(Mat solution) {
        cout << "comparing" << endl;
    }

private:
    Mat *_image;
};