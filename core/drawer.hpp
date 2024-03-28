#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "polygon.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

#ifndef PRO_HC_EM_DRAWER_H
#define PRO_HC_EM_DRAWER_H

class Drawer {
public:
    Drawer(Mat img);

    void DrawPolygons(vector<Polygon> p);

private:
    Mat _img;
};

#endif