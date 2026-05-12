#pragma once
#include<iostream>
#include "raylib.h"
#include <cmath>
#include "coor.h"
using namespace std;
class Path {
private:
    coor* waypoints;
    int total;//total number of waypoints
public:
    Path() {
        waypoints = nullptr;
        total = 0;
    }
    void set(coor* arr, int size) {
        //deep copying
        delete[] waypoints;
        total = size;
        waypoints = new coor[size];
        for (int i = 0; i < size; i++) {
            waypoints[i] = arr[i];
        }
    }
    coor get(int i) {
        return waypoints[i];//to get the next coors
    }
    int size() {
        return total;
    }
    ~Path() {
        delete[] waypoints;
    }
};