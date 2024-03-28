#include <bits/stdc++.h>
using namespace std;

class Polygon {
public:
    vector<int> xCoord;
    vector<int> yCoord;
    int red, green, blue, alpha;

    Polygon(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a) {
        xCoord = {x1, x2, x3};
        yCoord = {y1, y2, y3};

        red = r;
        green = g;
        blue = b;
        alpha = a;
    }
};