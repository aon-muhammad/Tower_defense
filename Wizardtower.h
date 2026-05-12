#pragma once
#pragma once
#include<iostream>
#include "raylib.h"
#include"Tower.h"
#include"Enemy.h"
class wizardtower :public tower {
public:
	wizardtower(float xcor, float ycor) : tower(xcor, ycor, 150, "WizardTower", 120, 0, 1, 150, 0.8f, 60.0) {
		priceforupgrade = 120;
	}
	void takedamage(float damage)override {
		hp -= int(damage);
		if (hp < 0) {
			hp = 0;
		}
	}
	void attack(enemy* e)override {
		cout << "Wizard tower is attackin.\n";
		e->takedamage(damagerate);
	}
	bool enemeyinrange(enemy* e) override {
		float dx = e->getx() - x;
		float dy = e->gety() - y;
		float distance = sqrt(dx * dx + dy * dy);
		return distance <= range;
	}
	void render() override {
		cout << "Wizard Tower [" << name << "] at (" << x << ", " << y << ")\n";
	}

	bool canfire(float currentTime)override {
		return (currentTime - lasttimefire) >= firedelay;
	}
	void resetFireTime(float currentTime)override {
		lasttimefire = currentTime;
	}
	void update(player& p1) override {
		if (level > 4) return;
		if (p1.getgold() >= priceforupgrade) {
			hp += 40;
			damagerate += 15;
			range += 5;
			level++;
			p1.spendgold(priceforupgrade);
			priceforupgrade += 40;
		}
	}
};