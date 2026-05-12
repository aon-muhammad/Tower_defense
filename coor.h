#pragma once
#include <iostream>
using namespace std;

class coor {
private:
    int xaxis;
    int yaxis;
public:
    coor() : xaxis(0), yaxis(0) {}
    coor(int xa, int ya) : xaxis(xa), yaxis(ya) {}

    int getxaxis() { 
        return xaxis;
    }
    int getyaxis() { 
        return yaxis; 
    }

    void setx(int h) {
        xaxis = h; 
    }
    void sety(int h) { 
        yaxis = h; 
    }
    void setxy(int h, int l) { 
        xaxis = h; yaxis = l;
    }

    // Operator overloading
    //this will be used to compare two coordinates 
    bool operator==(const coor& other) const {
        return xaxis == other.xaxis && yaxis == other.yaxis;
    }
    //this will be used to getthe difference bw two points
    coor operator-(const coor& other) const {
        return coor(xaxis - other.xaxis, yaxis - other.yaxis);
    }
};