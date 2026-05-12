#pragma once
#include <iostream>
#include <cmath>
#include "raylib.h"
#include "Entity.h"
#include "Path.h"
class player;
class enemy;
class tower : public entity {
protected:
    int range;
    float lasttimefire;
    int level;
    int money;
    float firedelay;
    float damagerate;
    int priceforupgrade;
    int maxhp;
public:
    tower(float xcor, float ycor, int h, string n,
        int r, float fr, int l, int m,
        float delay, float dr)
        : entity(xcor, ycor, h, n) {
        range = r;
        lasttimefire = fr;
        level = l;
        money = m;
        firedelay = delay;
        damagerate = dr;
        priceforupgrade = 0;
        maxhp = h;
    }
    virtual void update(player& p1) = 0;
    virtual void attack(enemy* e) = 0;
    virtual bool enemeyinrange(enemy* e) = 0;
    virtual bool canfire(float current) = 0;
    virtual void resetFireTime(float currentTime) = 0;
    virtual void takedamage(float damage) = 0;
    int getmoney() {
          return money; 
    }
    int getrange() {
          return range;
    }
    int getlevel() {
         return level; 
    }
    void setx(float xcor) { x = xcor; }
    void sety(float ycor) { y = ycor; }
    bool inplace(int x, int y) {
        Vector2 mouse = GetMousePosition();
        int grid = 30;
        int snappedX = ((int)(mouse.x) / grid) * grid;
        int snappedY = ((int)(mouse.y) / grid) * grid;
        return (x == snappedX && y == snappedY);
    }
    int getmaxhp() {
        return maxhp;
    }
    int getdamage() { 
        return damagerate;
    }
    void color(Path& p, player& pla);
};