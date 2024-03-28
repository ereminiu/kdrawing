#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

#ifndef COMPARE_H
#define COMPARE_H

class Compare {
public:
    Compare(Mat img);

    int64 Loss(const Mat &X);

private:
    Mat Y;
};

#endif