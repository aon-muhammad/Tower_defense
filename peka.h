#pragma once
#include <iostream>
#include "Enemy.h"
#include "Tower.h"
using namespace std;

class peka : public enemy {
public:
    peka(Path* p2)
        : enemy(1.5f, 0, 0, 250, "PEKA", 15.0f, 120, p2, 0.0f, 0.8f, 200) {
        reward = 11;
    }

    void attack(tower* t) override {
        cout << "PEKA is attacking.\n";
        t->takedamage(damagerate);
    }
    void move() override {
        if (path == nullptr || index >= path->size()) return;

        coor target = path->get(index);
        coor me((int)x, (int)y);

        // operator- gives direction vector from me to target
        coor diff = target - me;
        float dx = (float)diff.getxaxis();
        float dy = (float)diff.getyaxis();
        float dist = sqrt(dx * dx + dy * dy);

        // operator== checks if we have arrived at the waypoint
        if (dist < 5.0f || me == target) {
            index++;
            return;
        }

        x += (dx / dist) * speed;
        y += (dy / dist) * speed;
    }
    void takedamage(float damage) override {
        hp -= (int)damage;
        if (hp < 0) hp = 0;
    }

    void render() override {
        cout << "PEKA [" << name << "] at ("
            << x << ", " << y << ") HP: " << hp << "\n";
    }

    bool towerinrange(tower* t) override {
        float dx = t->getx() - x;
        float dy = t->gety() - y;
        return sqrt(dx * dx + dy * dy) <= range;
    }
};