#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "polygon.hpp"
#include "drawer.hpp"
#include "compare.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

#ifndef PROHCEM_H
#define PROHCEM_H

class ProHillClimbingEnergyMap {
public:
    ProHillClimbingEnergyMap(int _m, int _maxFE, Mat _source, Drawer _drawer, Compare _comparator);
    
    void Solve();

private:
    int H;
    int W;
    int m;
    int maxFE;

    Mat img;
    Mat source;
    Drawer drawer;
    Compare comparator;

    vector<Polygon> solution;
    vector<vector<int>> energyMap;

    // random
    mt19937 gen;
    random_device rd;

    Polygon generatePolygon();
    void mutateColor(int i);
    void mutateVertex(int i);
    int randInt(int left, int right);
    float randFloat(float left, float right);
    int randomChoice(vector<float> prob);
    bool onTheSameLine(int x1, int y1, int x2, int y2, int x3, int y3);
    void initEnergyMap();
    int64 getLoss();
    void draw();
};

#endif