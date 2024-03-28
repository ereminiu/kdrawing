#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "polygon.hpp"
#include "drawer.hpp"
#include "compare.hpp"
#include "pro_hc_em.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace cv;

ProHillClimbingEnergyMap::ProHillClimbingEnergyMap(int m_, int maxFE_, Mat _source, Drawer _drawer, Compare _comparator): m(m_), maxFE(maxFE_), source(_source), drawer(_drawer), comparator(_comparator) {
    this->W = this->source.cols;
    this->H = this->source.rows;

    this->img = Mat::zeros(H, W, CV_8UC3);
    this->gen.seed(this->rd());
}

void ProHillClimbingEnergyMap::Solve() {
    vector<Polygon> solution(m);
    for (int i = 0; i < m; i++) {
        solution[i] = generatePolygon();
    }
    drawer.DrawPolygons(solution);
}

Polygon ProHillClimbingEnergyMap::generatePolygon() {
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
    while (onTheSameLine(x1, y1, x2, y2, x3, y3)) {
        x1 = randInt(0, W);
        x2 = randInt(0, W);
        x3 = randInt(0, W);
        y1 = randInt(0, H);
        y2 = randInt(0, H);
        y3 = randInt(0, H);
    }
    int red = randInt(0, 255);
    int green = randInt(0, 255);
    int blue = randInt(0, 255);
    float alpha = randFloat();
    return Polygon(x1, y1, x2, y2, x3, y3, red, green, blue, alpha);   
}

bool ProHillClimbingEnergyMap::onTheSameLine(int x1, int y1, int x2, int y2, int x3, int y3) {
    int xa = x2-x1, ya = y2-y1;
    int xb = x3-x1, yb = y3-y1;
    return xa*yb - xb*ya == 0;
}

int ProHillClimbingEnergyMap::randInt(int left, int right) {
    uniform_int_distribution<int> dist(left, right);
    return dist(this->gen);
}

float ProHillClimbingEnergyMap::randFloat() {
    uniform_real_distribution<float> dist(0.5, 1.0);
    return dist(this->gen);
}

void ProHillClimbingEnergyMap::mutate_color(int i) {

}

void ProHillClimbingEnergyMap::mutate_vertex(int i) {

}

void ProHillClimbingEnergyMap::draw() {

}

int64 ProHillClimbingEnergyMap::getLoss() {
    return 0;
}