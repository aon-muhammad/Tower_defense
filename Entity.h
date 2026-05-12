#pragma once
#include<iostream>
#include "raylib.h"
#include <cmath>
using namespace std;
class entity {
protected:
	float x, y;
	string name;
	int hp;
public:
	entity() {
		x = 0;
		y = 0;
		hp = 0;
		name = "N/R";
	}
	entity(float xcor, float ycor, int h, string n)
		: x(xcor), y(ycor), hp(h), name(n) {}
	void setposition(float newx, float newy) {
		x = newx;
		y = newy;
	}
	virtual void render() = 0;
	virtual void takedamage(float damage) = 0;
	string getname() {
		return name;
	}
	int gethp() {
		return hp;
	}
	float getx() {
		return x;
	}
	float gety() {
		return y;
	}
	bool isalive() {
		if (hp <= 0) {
			return false;
		}
		return true;
	}
	virtual ~entity() {}
};