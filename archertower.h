#pragma once
#include<iostream>
#include "raylib.h"
#include"Tower.h"
#include"Enemy.h"
#include "Player.h"
using namespace std;
class archertower :public tower {
public:
	archertower(float xcor, float ycor) : tower(xcor, ycor, 300, "ArcherTower", 90, 0, 1, 80, 0.3f, 30.0f) {
		priceforupgrade = 80;
	}
	void takedamage(float damage)override {
		hp -= int(damage);
		if (hp < 0) {
			hp = 0;
		}
	}
	void attack(enemy* e)override {
		cout << "Archer tower is attackin.\n";
		e->takedamage(damagerate);
	}
	bool enemeyinrange(enemy* e) override {
		float dx = e->getx() - x;
		float dy = e->gety() - y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance <= range;
	}
	void render() override {
		cout << "Archer Tower [" << name << "] at (" << x << ", " << y << ")\n";
	}

	bool canfire(float currenttime)override {
		return (currenttime - lasttimefire) >= firedelay;
	}
	void resetFireTime(float currentTime)override {
		lasttimefire = currentTime;
	}
	void update(player& p1) override {
		if (level > 4) { 
			return;
		}
		if (p1.getgold() >= priceforupgrade) {
			hp += 70;
			damagerate += 8;
			range += 10;
			level++;
			p1.spendgold(priceforupgrade);
			priceforupgrade += 25;
		}
	}
};