#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "core/polygon.hpp"
#include "core/drawer.hpp"
#include "core/compare.hpp"
#include "core/pro_hc_em.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
using namespace cv;

// const string filepath = "evelinushka.jpg";
const string filepath = "evelinushka_short_2.png";
// const int H = 500;
// const int W = 300;

const int m = 1000;
const int maxFE = 500;

void drawPolygon(Mat img, const vector<Point> &points, int red, int green, int blue, float alpha);

int main() {
    Mat source = imread(filepath);
    int W = source.cols;
    int H = source.rows;
    
    Mat img = Mat::zeros(H, W, CV_8UC3);
    Drawer drawer(img);
    Compare comparator(img);
    ProHillClimbingEnergyMap solver(m, maxFE, source, drawer, comparator);

    auto start = high_resolution_clock::now();

    solver.Solve();

    auto stop = high_resolution_clock::now();

    cout << "Time elapsed: " << duration_cast<microseconds>(stop - start).count() << endl;

    imshow("Aboba", img);
    waitKey(0);

    // Mat image = Mat::zeros(H, W, CV_8UC3);

    // vector<Polygon> polygons = {
    //     Polygon(0, 0, 0, H, W, 0, 255, 0, 0, 0.5),
    //     Polygon(W, H, W, 0, 0, 0, 0, 0, 255, 0.5)
    // };

    // Drawer d(image);
    // d.DrawPolygons(polygons);

    // imshow("Aboba", image);
    // waitKey(0);
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