#pragma once
#include <iostream>
#include <cmath>
#include "raylib.h"
#include "Tower.h"
#include "Enemy.h"
#include "Player.h"
using namespace std;
class canontower :public tower {
public:
	canontower(float xcor, float ycor) :tower(xcor, ycor, 200, "Canons", 100, 0, 1, 100, 0.5f, 40.0) {
		priceforupgrade = 100;
	};
	void takedamage(float damage)override {
		hp -= int(damage);
		if (hp < 0) {
			hp = 0;
		}
	}
	void attack(enemy* e)override {
		cout << "Canon tower is attacking.\n";
		e->takedamage(damagerate);
	}
	bool enemeyinrange(enemy* e) override {
		float dx = e->getx() - x;
		float dy = e->gety() - y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance <= range;
	}
	void render() override {
		cout << "Canon Tower [" << name << "] at (" << x << ", " << y << ")\n";
	}
	bool canfire(float currentTime)override {
		return (currentTime - lasttimefire) >= firedelay;
	}
	void resetFireTime(float currentTime)override {
		lasttimefire = currentTime;
	}
	void update(player& p1)override {
		if (level > 4) {
			return;
		}
		if (p1.getgold() >= priceforupgrade) {
			hp += 50;
			damagerate += 10;
			range += 5;
			level++;
			p1.spendgold(priceforupgrade);
			priceforupgrade += 30;
		}
	}
	int getlevel() {
		return level;
	}
};