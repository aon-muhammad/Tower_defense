#pragma once
#include<iostream>
#include "raylib.h"
#include <cmath>
#include"Tower.h"
#include "Enemy.h"
class fastenemy :public enemy {
public:
	fastenemy(Path* p2) : enemy(5.0f, 0, 0, 100, "HOGRIDER", 3.0f, 80, p2, 0.0, 0.7f, 100) {
		reward = 3;
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
	void attack(tower* t)override {
		cout << "Hogrider is attacking.\n";
		t->takedamage(damagerate);
	}
	void takedamage(float damage)override {
		hp -= int(damage);
		if (hp < 0) {
			hp = 0;
		}
	}
	void render() override {
		cout << "FastEnemy [" << name << "] at (" << x << ", " << y << ") HP: " << hp << "\n";
	}
	bool towerinrange(tower* t)override {
		float dx = t->getx() - x;
		float dy = t->gety() - y;
		float distance = sqrt((dx * dx) + (dy * dy));
		return distance <= range;
	}
};