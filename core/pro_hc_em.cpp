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
    this->H = this->source.rows;
    this->W = this->source.cols;

    this->img = Mat::zeros(H, W, CV_8UC3);
    this->gen.seed(this->rd());
}

void ProHillClimbingEnergyMap::Solve() {
    solution.resize(0);
    solution.push_back(generatePolygon());
    
    int64 best = this->comparator.Loss(this->source);
    int cnt = 0;
    vector<float> prob = {1.00000};
    int k = 1;
    initEnergyMap();
    for (int t = 0; t < maxFE; t++) {
        int i = randomChoice(prob);
        int r = randInt(0, 3);
        auto newSolution = solution;
        if (r % 3 == 0) {
            mutateColor(i);
        } else if (r % 3 == 1) {
            mutateVertex(i);
        } 
        int64 current = this->comparator.Loss(this->source);
    }

    draw();
}

void ProHillClimbingEnergyMap::initEnergyMap() {
    this->energyMap.resize(H);
    for (int i = 0; i < H; i++) {
        this->energyMap[i].resize(W);
    }
    draw();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int val = 0;
            auto x = this->img.at<Vec3b>(i, j),
                 y = this->source.at<Vec3b>(i, j);
            for (int k = 0; k < 3; k++) {
                val += abs(x[k] - y[k]);
            }
            this->energyMap[i][j] = val;
        }
    }
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
    float alpha = randFloat(0.0, 1.0);
    return Polygon(x1, y1, x2, y2, x3, y3, red, green, blue, alpha);   
}

bool ProHillClimbingEnergyMap::onTheSameLine(int x1, int y1, int x2, int y2, int x3, int y3) {
    int xa = x2-x1, ya = y2-y1;
    int xb = x3-x1, yb = y3-y1;
    return xa*yb - xb*ya == 0;
}

void ProHillClimbingEnergyMap::mutateColor(int i) {
    int r1 = randInt(0, 4);
    int r2 = randInt(0, 1);
    if (r1 % 4 == 0) {
        if (r2 % 2 == 0) {
            this->solution[i].alpha += randFloat(0.0, 0.1);
        } else {
            this->solution[i].alpha = randFloat(0.0, 1.0);
        }
    } else if (r1 % 4 == 1) {

    } else if (r1 % 4 == 2) {

    } else {

    }
}

void ProHillClimbingEnergyMap::mutateVertex(int i) {

}

void ProHillClimbingEnergyMap::draw() {
    this->drawer.DrawPolygons(this->solution);
}

int64 ProHillClimbingEnergyMap::getLoss() {
    return this->comparator.Loss(source);
}

int ProHillClimbingEnergyMap::randomChoice(vector<float> prob) {
    int n = int(prob.size());
    vector<float> pref(n);
    int r = randFloat(0.00, 1.00);
    for (int i = 0; i < n; i++) {
        pref[i] += prob[i];
        if (i > 0) {
            pref[i] += pref[i-1];
        }
        if (pref[i] >= r) {
            return i;
        }
    }
    return n-1;
} 

int ProHillClimbingEnergyMap::randInt(int left=0, int right=10000) {
    uniform_int_distribution<int> dist(left, right);
    return dist(this->gen);
}

float ProHillClimbingEnergyMap::randFloat(float left=0.5, float right=1.0) {
    uniform_real_distribution<float> dist(left, right);
    return dist(this->gen);
}
