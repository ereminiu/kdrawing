#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "core/polygon.hpp"
#include "core/drawer.hpp"
#include "core/compare.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

const string filepath = "evelinushka.jpg";
const int H = 500;
const int W = 300;

void drawPolygon(Mat img, const vector<Point> &points, int red, int green, int blue, float alpha);

int main() {
    Mat image = Mat::zeros(H, W, CV_8UC4);

    vector<Polygon> polygons = {
        Polygon(0, 0, 0, H, W, 0, 255, 0, 0, 0.5),
        Polygon(W, H, W, 0, 0, 0, 0, 0, 255, 0.5)
    };

    Drawer d(image);
    d.DrawPolygons(polygons);

    Mat anotherImage = Mat::zeros(H, W, CV_8UC4);
    vector<Point> other = {
        Point(0, 0), 
        Point(0, H),
        Point(W, 0)
    };
    drawPolygon(anotherImage, other, 255, 0, 0, 0.5);
    other = {
        Point(W, H),
        Point(W, 0),
        Point(0, 0)
    };
    drawPolygon(anotherImage, other, 0, 0, 255, 0.5);

    Compare compare(image);
    cout << "Loss: " <<  compare.Loss(anotherImage) << endl;

    imshow("Aboba", image);
    waitKey(0);

    imshow("Aboba", anotherImage);
    waitKey(0);
}

void drawPolygon(Mat img, const vector<Point> &points, int red, int green, int blue, float alpha) {
    fillPoly(img, points, Scalar(blue, green, red) * alpha, LINE_8);
    // addWeighted(overlay, alpha, img, 1-alpha, 0, img);
}

// int main() {
//     Mat image = Mat::zeros(H, W, CV_8UC4); // 3 канала

//     vector<Point> points = {Point(0, 0), Point(0, H), Point(W, 0)};
//     int red = 255, green = 0, blue = 0;
//     float alpha = 0.5;

//     drawPolygon(image, points, red, green, blue, alpha);

//     vector<Point> triangle = {Point(10, 10), Point(10, 200), Point(300, 300)};

//     drawPolygon(image, triangle, 0, 0, 255, 0.5);
    
//     auto pixel = image.at<Vec3b>(0, 0);
//     cout << pixel << endl;
    
//     imshow("Aboba", image);
//     waitKey(0);

//     return 0;
// }