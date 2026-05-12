#pragma once
#include "raylib.h"
#include "Enemy.h"

class Projectile {
private:
    float  x, y;
    float  speed;
    int    damage;
    Color  color;
    float  radius;
    enemy* target;
    bool   active;

public:
    Projectile() {
        x = 0; y = 0;
        speed = 0; damage = 0;
        radius = 4.0f;
        target = nullptr;
        active = false;
        color = WHITE;
    }

    void init(float startX, float startY, enemy* tgt, int dmg, Color col, float spd, float rad) {
        x = startX;
        y = startY;
        target = tgt;
        damage = dmg;
        color = col;
        speed = spd;
        radius = rad;
        active = true;
    }

    void update() {
        if (!active) {
            return;
        }
        if (!target || !target->isalive()) {
            active = false;
            return;
        }
        float tx = target->getx();
        float ty = target->gety();
        float dx = tx - x;
        float dy = ty - y;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist <= speed + radius) {
            target->takedamage(damage);
            active = false;
            return;
        }

        x += (dx / dist) * speed;
        y += (dy / dist) * speed;
    }
    void draw() {
        if (!active) {
            return;
        }
        DrawCircle((int)x, (int)y, radius, color);
    }
    bool isactive() { 
        return active; 
    }
};