#pragma once
#include <iostream>
#include <cmath>
#include "raylib.h"
#include "Tower.h"
#include "Enemy.h"
#include "Map.h"

class player {
private:
    int gold;
    int lives;
    tower** t;
    int towercount;
    int maxtowers;
    Map* map;
public:
    player(Map* m ) {
        gold = 1000;
        lives = 10;
        map = m;
        towercount = 0;
        maxtowers = 20;
        t = new tower * [maxtowers];
        for (int i = 0; i < maxtowers; i++) {
            t[i] = nullptr;
        }
        m = nullptr;
    }
    
    bool isonpath(float px, float py) {
        if (!map) {
            return false;
        }
        Path& p = map->getpath(0);
        const int HALF = 35;
        for (int j = 0; j < p.size() - 1; j++) {
            int ax = p.get(j).getxaxis(), ay = p.get(j).getyaxis();
            int bx = p.get(j + 1).getxaxis(), by = p.get(j + 1).getyaxis();
            bool nearHorizontal = false;
            if (ay == by) {
                int left = ax;
                int right = bx;

                if (left > right) {
                    int temp = left;
                    left = right;
                    right = temp;
                }

                nearHorizontal =
                    (int)px >= left && (int)px <= right &&
                    (int)py >= ay - HALF && (int)py <= ay + HALF;
            }

            bool nearVertical = false;
            if (ax == bx) {
                int top = ay;
                int bottom = by;

                if (top > bottom) {
                    int temp = top;
                    top = bottom;
                    bottom = temp;
                }

                nearVertical =
                    (int)py >= top && (int)py <= bottom &&
                    (int)px >= ax - HALF && (int)px <= ax + HALF;
            }

            if (nearHorizontal || nearVertical) return true;
        }

        return false;
    }

    
    bool overlapping(float x, float y) {

        for (int i = 0; i < towercount; i++) {
            if (t[i]!=nullptr) {
                float dx = t[i]->getx() - x;
                float dy = t[i]->gety() - y;
                if (sqrt(dx * dx + dy * dy) < 40)
                    return true;
            }
        }
        return false;
    }
    bool isoutofbounds(float x, float y) {
        return (x < 0 || x > 800 || y < 40 || y > 600);
    }
    void addgold(int amount) {
        gold += amount;
    }

    bool spendgold(int amount) {
        if (gold >= amount) {
            gold -= amount;
            return true;
        }
        return false;
    }

    void resizearray() {
        tower** newArr = new tower * [maxtowers * 2];
        for (int i = 0; i < maxtowers; i++)
            newArr[i] = t[i];
        for (int i = maxtowers; i < maxtowers * 2; i++)
            newArr[i] = nullptr;
        delete[] t;
        t = newArr;
        maxtowers *= 2;
    }
    bool placetower(float x, float y, tower* t1) {
        if (isonpath(x, y) || isoutofbounds(x, y) || overlapping(x, y)) {
            return false;
        }
        if (!spendgold(t1->getmoney())) {
            return false;
        }
        if (towercount >= maxtowers) {
            resizearray();
        }
        t[towercount] = t1;
        t[towercount]->setx(x);
        t[towercount]->sety(y);
        towercount++;
        return true;
    }

    
    void update(enemy** e, int total) {
        float currenttime = GetTime();
        for (int i = 0; i < towercount; i++) {

            if (!t[i] || !t[i]->isalive()) { 
                continue;
            }
            for (int j = 0; j < total; j++) {
                if (!e[j] || !e[j]->isalive()) {
                    continue;
                }
                if (t[i]->enemeyinrange(e[j]) && t[i]->canfire(currenttime)) {

                    t[i]->attack(e[j]);
                    t[i]->resetFireTime(currenttime);

                    if (!e[j]->isalive())
                        addgold(e[j]->getreward());

                    break;
                }
            }
        }
    }
    bool enemypos(enemy* e) {
        return (e->gety() >= 600);
    }
    void loselife() {
        lives--;
    }
    bool gameover() {
        return lives <= 0;
    }
    int getgold() {
        return gold;
    }
    int getlives() { 
        return lives; 
    }

    tower** gettower() {
        return t; 
    }
    int gettowercount() { 
        return towercount; 
    }

    ~player() {
        for (int i = 0; i < maxtowers; i++) {
            delete t[i];
        }
        delete[] t;
    }
};