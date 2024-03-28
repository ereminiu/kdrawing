#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

#ifndef POLYGON_H
#define POLYGON_H

class Polygon {
public:
    vector<int> xCoord;
    vector<int> yCoord;
    int red, green, blue;
    float alpha;

    Polygon(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, float a);
    Polygon();

    vector<Point> getPoints(); 
};

#endif