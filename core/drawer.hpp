#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <bits/stdc++.h>
#include "polygon.hpp"

using namespace std;
using namespace cv;

class Drawer {
public:
    Drawer(Mat &image) :_img(&image) {
        cout << "making drawer" << endl;
    }
    
    void DrawPolygons(vector<Polygon> polygons);

private:
    Mat *_img;

    void drawPolygon(Polygon p);

    vector<Point> getPoints(Polygon polygon);
};