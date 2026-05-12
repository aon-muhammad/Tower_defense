#pragma once
#pragma once
#include<iostream>
#include "raylib.h"
#include"Tower.h"
#include"Enemy.h"
#include "Player.h"
class machineguntower :public tower {
public:
	machineguntower(float xcor, float ycor) : tower(xcor, ycor, 150, "Machine Gun", 80, 0, 1, 75, 0.2f, 10.0) {
		priceforupgrade = 75;
	}
	void takedamage(float damage)override {
		hp -=int( damage);
		if (hp < 0) {
			hp = 0;
		}
	}
	void attack(enemy* e)override {
		cout << "Machine Gun tower is attackin.\n";
		e->takedamage(damagerate);
	}
	bool enemeyinrange(enemy* e) override {
		float dx = e->getx() - x;
		float dy = e->gety() - y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance <= range;
	}
	void render() override {
		cout << "Machine Tower [" << name << "] at (" << x << ", " << y << ")\n";
	}

	bool canfire(float currentTime)override {
		return (currentTime - lasttimefire) >= firedelay;
	}
	void resetFireTime(float currentTime)override {
		lasttimefire = currentTime;
	}
	int getlevel() {
		return level;
	}
	void update(player& p1) override {
		if (level > 4) return;
		if (p1.getgold() >= priceforupgrade) {
			hp += 60;
			damagerate += 10;
			range += 5;
			level++;
			p1.spendgold(priceforupgrade);
			priceforupgrade += 30;
		}
	}
};