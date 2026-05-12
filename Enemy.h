#pragma once
#include <iostream>
#include <cmath>
#include "raylib.h"
#include "Entity.h"
#include "Path.h"
using namespace std;
class tower;
class enemy : public entity {
protected:
    float speed;
    float damagerate;
    int range;
    float originalspeed;
    bool isstopped;
    Path* path;
    int index;              // current waypoint index
    float lasttimefire;
    float delay;
    int reward;
    int maxhp;
public:
    enemy(){
        speed = 0;
        damagerate = 0;
        range = 0;
        originalspeed = 0;
        isstopped = false;
        path = nullptr;
        index = 0;
        lasttimefire = 0;
        delay = 0;
        reward = 0;
        maxhp = 0;
    }
    enemy(float s, float xcor, float ycor, int h, string n, float dr, int r, Path* p1, float l, float d, int re): entity(xcor, ycor, h, n) {
        speed = s;
        damagerate = dr;
        range = r;
        originalspeed = s;
        isstopped = false;
        path = p1;
        index = 1; // To make it move towrds second waypoint
        lasttimefire = l;
        delay = d;
        reward = re;
        maxhp = h;
        if (path != nullptr ) {
            x = path->get(0).getxaxis();//get the 0th coor x and y axis
            y = path->get(0).getyaxis();
        }
    }

    virtual void move() = 0; 
    bool hasreachedend()  {
        return (path != nullptr && index >= path->size());
    }
    virtual void attack(tower* t) = 0;
    virtual bool towerinrange(tower* t) = 0;
    int getreward() {
        return reward; 
    }
    int getrange() { 
        return range;
    }
    int gethp() {
        return hp;
    }
    int getmaxhp() {
        return maxhp; 
    }
    void setstop() {
        if (isstopped) {//a setter to resume the movement
            speed = originalspeed;
            isstopped = false;
        }
    }
    void stop(tower* t);
    //my code was stuck in circular dependencies so i made a seperate cpp file forr thiss
};