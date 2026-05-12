#pragma once
#include<iostream>
#include "raylib.h"
#include <cmath>
#include"Tower.h"
#include"Enemy.h"
class basicenemy :public enemy {
public:
	basicenemy(Path* p2) : enemy(2.0f, 0, 0, 100, "BARBARIAN", 10, 100, p2, 0.0, 1.0f, 50) {
		reward = 2;
	}
	void move() override {
		if (path == nullptr || index >= path->size()) {
			return;
		}
		coor target = path->get(index);
		coor me((int)x, (int)y);
		coor diff = target - me;
		float dx = (float)diff.getxaxis();
		float dy = (float)diff.getyaxis();
		//distance formula 
		float dist = sqrt(dx * dx + dy * dy);
		if (dist < 5.0f || me == target) {
			index++;
			return;
		}

		x += (dx / dist) * speed;
		y += (dy / dist) * speed;
	}
	void attack(tower* t)override {
		cout << "Barbarian is attacking.\n";
		t->takedamage(damagerate);
	}
	void takedamage(float damage)override {
		hp -= int(damage);
		if (hp < 0) {
			hp = 0;
		}
	}
	void render() override {
		cout << "BasicEnemy [" << name << "] at (" << x << ", " << y << ") HP: " << hp << "\n";
	}
	bool towerinrange(tower* t)override {
		float dx = t->getx() - x;
		float dy = t->gety() - y;
		float distance = sqrt((dx * dx) + (dy * dy));
		return (distance <= range);
	}
};