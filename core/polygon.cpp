#include <bits/stdc++.h>
#include "polygon.hpp"

using namespace std;

Polygon::Polygon(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, float a)
    :red(r), green(g), blue(b), alpha(a) {
    xCoord = vector<int>{x1, x2, x3};
    yCoord = vector<int>{y1, y2, y3};
}

vector<Point> Polygon::getPoints() {
    vector<Point> points(3);
    for (int i = 0; i < 3; i++) {
        points[i] = Point(xCoord[i], yCoord[i]);
    }
    return points;
}