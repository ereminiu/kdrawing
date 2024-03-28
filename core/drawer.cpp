#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <bits/stdc++.h>
#include "polygon.hpp"
#include "drawer.hpp"

using namespace std;
using namespace cv;

void Drawer::DrawPolygons(vector<Polygon> polygons) {

}

void Drawer::drawPolygon(Polygon p) {
    auto points = getPoints(p);
    Mat overlay;
    this->_img->copyTo(overlay);
    fillPoly(overlay, points, Scalar(p.blue, p.green, p.red));
}

// TODO: перенести на слой полигона
vector<Point> Drawer::getPoints(Polygon polygon) {
    vector<Point> points(3);
    for (int i = 0; i < 3; i++) {
        points[i] = Point(polygon.xCoord[i], polygon.yCoord[i]);
    }
    return points;
}