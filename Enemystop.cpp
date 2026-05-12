#include "Enemy.h"
#include "Tower.h"
#include "raylib.h"

void enemy::stop(tower* t) {

    if (t==nullptr|| !t->isalive()) {
        speed = originalspeed;
        isstopped = false;
        return;
    }
    if (towerinrange(t)) {
        speed = 0.0f;
        isstopped = true;
        float currenttime = GetTime();
        if (currenttime - lasttimefire >= delay) {
            attack(t);
            lasttimefire = currenttime;
        }
    }
    else {
        speed = originalspeed;
        isstopped = false;
    }
}