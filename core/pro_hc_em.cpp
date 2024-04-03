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

#define LIMIT 50

ProHillClimbingEnergyMap::ProHillClimbingEnergyMap(int m_, int maxFE_, Mat _source, Drawer _drawer, Compare _comparator): m(m_), maxFE(maxFE_), source(_source), drawer(_drawer), comparator(_comparator) {
    this->H = this->source.rows;
    this->W = this->source.cols;

    this->img = Mat::zeros(H, W, CV_8UC3);
    this->gen.seed(this->rd());
}

void ProHillClimbingEnergyMap::Solve() {
    solution.resize(0);
    solution.push_back(generatePolygon());
    
    int64 best = getLoss();
    int cnt = 0;
    int64 fitness = best;
    vector<float> pr = {1.00000};
    int k = 0;
    initEnergyMap();
    for (int t = 0; t < maxFE; t++) {
        cout << "iteration " << t << ":" << endl;
        int i = randomChoice(pr);
        int r = randInt(0, 3);
        auto prev = solution;
        if (r % 3 == 0) {
            cout << "Mutating color" << endl;
            mutateColor(i);
        } else if (r % 3 == 1) {
            cout << "Mutating vertex" << endl;
            mutateVertex(i);
        } else {
            cout << "Trying something else..." << endl;
        }
        int64 current = getLoss();
        if (current < best) {
            best = current;
            cnt = 0;
        } else {
            solution = prev;
            cnt++;
        }
        cout << "cnt: " << cnt << ", " << "k: " << k << endl;
        if (cnt > LIMIT && k < m) {
            cout << "current: " << current << ", " << "fitness: " << fitness << endl;
            if (current < fitness) { 
                initEnergyMap();
                auto p = generatePolygon();
                initPolygon(p);
                solution.push_back(p);

                // p[k-1] = 1/2, p[k-2] = 1/4 ... p[0] = 1/2**k
                pr.push_back(0);
                float currentProbability = 1/2;
                for (int i = k-1; i >= 0; i--) {
                    pr[i] = currentProbability;
                    currentProbability /= 2;
                }

                fitness = current;
                k++;
                cnt = 0;
            } else {
                initPolygon(solution[k-1]);
                cnt++;
            }
        }
        if (cnt > LIMIT && k == m) {
            cout << "FOUND:" << endl;
            cout << "cnt > LIMIT && k == m" << endl;
            for (int i = 0; i < m; i++) {
                pr[i] = float(1/m);
            }
        }
    }

    draw();
}

void ProHillClimbingEnergyMap::initPolygon(Polygon &p) {
    cout << "init polygon" << endl;
    p.red = randInt(0, 255);
    p.green = randInt(0, 255);
    p.blue = randInt(0, 255);
    p.alpha = randFloat(0.1, 1.000);

    vector<vector<float>> pr(W, vector<float>(H));
    float total = 0.0;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            total += this->energyMap[i][j];
        }
    }
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            pr[i][j] = this->energyMap[i][j] / total;
        }
    }
    vector<vector<float>> pref(W, vector<float>(H));
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            pref[i][j] += pr[i][j];
            if (i > 0) {
                pref[i][j] += pref[i-1][j];
            } 
            if (j > 0) {
                pref[i][j] += pref[i][j-1];
            }
            if (i > 0 && j > 0) {
                pref[i][j] -= pref[i-1][j-1];
            }
        }
    }

    auto getSum = [&](int xl, int xr, int yl, int yr) -> float {
        float result = pref[xr][yr];
        if (xl > 0) {
            result -= pref[xl-1][yr];
        }
        if (yl > 0) {
            result -= pref[xr][yl-1];
        }
        if (xl > 0 && yl > 0) {
            result += pref[xl-1][yl-1];
        }
        return result;
    };
    
    vector<vector<float>> mx(W, vector<float>(H));
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            float left = getSum(0, max(0, i-1), 0, H);
            float right = getSum(i, i, 0, j);
            mx[i][j] = left + right;
            // float total = 0;
            // for (int k = 0; k < i; k++) {
            //     for (int l = 0; l < H; l++) {
            //         total += pr[k][l];
            //     }
            // }
            // for (int l = 0; l < j; l++) {
            //     total += pr[i][l];
            // }
            // mx[i][j] = total;
        }
    }
    if (p.xCoord.size() < 3) {
        p = generatePolygon();
    }
    for (int k = 0; k < 3; k++) {
        float r = randFloat(0.0, 1.00);

        bool fl = false;
        for (int i = 0; i < W; i++) {
            if (fl) {
                break;
            }
            for (int j = 0; j < H; j++) {
                if (mx[i][j] >= r) {
                    p.xCoord[k] = i;
                    p.yCoord[k] = j;
                    fl = true;
                    break;
                }
            }
        }
    }
}

void ProHillClimbingEnergyMap::initEnergyMap() {
    cout << "init energy map" << endl;
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
    cout << "generate polygon" << endl;
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
        if (r2 % 2 == 0) {
            int64 newVal = min(255, this->solution[i].red + randInt(0, 128));
            this->solution[i].red = newVal;
        } else {
            this->solution[i].red = randInt(0, 255);
        }
    } else if (r1 % 4 == 2) {
        if (r2 % 2 == 0) {
            int64 newVal = min(255, this->solution[i].green + randInt(0, 128));
            this->solution[i].green = newVal;
        } else {
            this->solution[i].green = randInt(0, 255);
        }
    } else {
        if (r2 % 2 == 0) {
            int64 newVal = min(255, this->solution[i].blue + randInt(0, 128));
            this->solution[i].blue = newVal;
        } else {
            this->solution[i].blue = randInt(0, 255);
        }
    }
}

void ProHillClimbingEnergyMap::mutateVertex(int i) {
    int j = randInt(0, 3);
    int r1 = randInt(0, 1);
    int r2 = randInt(0, 1);
    if (r1 % 2 == 0) {
        if (r2 % 2 == 0) {
            this->solution[i].xCoord[j] += randInt(0, 0.1 * W);
        } else {
            this->solution[i].xCoord[j] = randInt(0, W);
        }
    } else {
        if (r2 % 2 == 0) {
            this->solution[i].yCoord[j] += randInt(0, 0.1 * H);
        } else {
            this->solution[i].yCoord[j] = randInt(0, H);
        }
    }
}

void ProHillClimbingEnergyMap::draw() {
    this->drawer.DrawPolygons(this->solution);
}

int64 ProHillClimbingEnergyMap::getLoss() {
    draw();
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
