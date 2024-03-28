#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "polygon.hpp"
#include "drawer.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

Drawer::Drawer(Mat img) :_img(img) {
}

void Drawer::DrawPolygons(vector<Polygon> &polygons) {
    // Mat overlay;
    // this->_img.copyTo(overlay);

    for (Polygon p : polygons) {
        auto points = p.getPoints();
        // fillPoly(overlay, points, Scalar(p.blue, p.green, p.red) * p.alpha, LINE_8);
        fillPoly(_img, p.getPoints(), Scalar(p.blue, p.green, p.red) * p.alpha);
        // addWeighted(overlay, p.alpha, this->_img, p.alpha, 0, this->_img);
        // addWeighted(overlay, 1, this->_img, p.alpha, 0, this->_img);
    }
}