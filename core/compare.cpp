#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "compare.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

Compare::Compare(Mat img) :Y(img) {
}

int64 Compare::Loss(const Mat &X) {
    int W = X.cols, H = X.rows;
    assert(W == Y.cols);
    assert(H == Y.rows);

    int64 loss = 0;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            auto x = X.at<Vec3b>(i, j), y = Y.at<Vec3b>(i, j);
            for (int k = 0; k < 3; k++) {
                // if (abs(x[k]-y[k]) != 0) {
                //     cout << "found" << endl;
                // }
                loss += abs(x[k]-y[k]);
            }
        }
    }
    return loss;
}