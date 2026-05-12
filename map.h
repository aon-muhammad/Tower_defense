#pragma once
#include "Path.h"
class Map {
private:
    Path  p;
    int   maptype;
public:
    Map() : maptype(1) {
        loadmap(1);
    }
    Map(int type) : maptype(type) {
        loadmap(type);
    }
    void loadmap(int type) {
        if (type == 1) {
            //s shaped 
            coor waypoints[] = {
                coor(400,   0),
                coor(400, 200),
                coor(150, 200),
                coor(150, 400),
                coor(400, 400),
                coor(400, 600)
            };
            p.set(waypoints, 6);
        }
        else if (type == 2) {
            //zig zag
            coor waypoints[] = {
                coor(100,   0),
                coor(100, 150),
                coor(650, 150),
                coor(650, 300),
                coor(150, 300),
                coor(150, 450),
                coor(650, 450),
                coor(650, 600)
            };
            p.set(waypoints, 8);
        }
        else {
            //spiral
            coor waypoints[] = {
                coor(100,   0),
                coor(100, 100),
                coor(700, 100),
                coor(700, 500),
                coor(200, 500),
                coor(200, 200),
                coor(600, 200),
                coor(600, 400),
                coor(300, 400),
                coor(300, 300),
                coor(500, 300),
                coor(500, 600)
            };
            p.set(waypoints, 12);
        }
    }
    Path& getpath() { 
        return p;
    }
    Path& getpath(int i) {
        return p; 
    }
    int   getmaptype() { 
        return maptype; 
    }
    int getcount() {
        return 1;
    }
    ~Map() {}
};