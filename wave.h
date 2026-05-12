#pragma once
#include<iostream>
#include "raylib.h"
#include <cmath>
#include"Entity.h"
#include"Player.h"
#include"Path.h"
#include"Enemy.h"
#include"Basicenemy.h"
#include"fastenemy.h"
#include"peka.h"
#include"Tankenemy.h"
#include"map.h"
class wave {
private:
    int wavecount;
    enemy** e;
    int total;
    int spawnIndex;
    float lastSpawn;
    float spawnDelay;
    Map* map;
public:
    wave(Map* m) {
        map = m;
        wavecount = 0;
        total = 5;
        spawnIndex = 0;
        spawnDelay = 1.0f;
        lastSpawn = GetTime();
        e = new enemy * [total];
        for (int i = 0; i < total; i++)
            e[i] = nullptr;
    }
    void spawnEnemy() {
        if (spawnIndex >= total) {
            return;
        }
        if (GetTime() - lastSpawn < spawnDelay) {
            return;
        }
        Path& p = map->getpath();
        enemy* newenemy = nullptr;
        if (wavecount == 0) {
            newenemy = new basicenemy(&p);
        }
        else if (wavecount == 1) {
            newenemy = new fastenemy(&p);
        }
        else if (wavecount == 2) {
            newenemy = new tankenemy(&p);
        }
        else if (wavecount == 3) {
            newenemy = new peka(&p);
        }
        else if (wavecount == 4) {
            int type = rand() % 4;
            if (type == 0) {
                newenemy = new basicenemy(&p); 
            }
            if (type == 1){ 
                newenemy = new fastenemy(&p);
            }
            if (type == 2){ 
                newenemy = new tankenemy(&p);
            }
            if (type == 3){ 
                 newenemy = new peka(&p);     }
        }

        e[spawnIndex] = newenemy;
        spawnIndex++;
        lastSpawn = GetTime();
    }
    void update() {
        spawnEnemy();
        bool allDead = true;
        for (int i = 0; i < total; i++) {
            if (e[i] != nullptr && e[i]->isalive()) {
                allDead = false;
            }
        }
        if (spawnIndex >= total && allDead) {
            wavecount++;
            if (wavecount > 4) {
                return; 
            }
            for (int i = 0; i < total; i++) {
                delete e[i];
                e[i] = nullptr;
            }
            delete[] e;

            total += 3;
            e = new enemy * [total];

            for (int i = 0; i < total; i++)
                e[i] = nullptr;

            spawnIndex = 0;
            lastSpawn = GetTime();
        }
    }
    enemy** getEnemies() {
        return e;
    }
    int getTotal() {
        return total;
    }
    int getWave() {
        return wavecount;
    }
    ~wave() {
        for (int i = 0; i < total; i++)
            delete e[i];
        delete[] e;
    }
};