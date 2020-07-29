#pragma once
#include <string>
#include <vector>
#include "clock.h"

#define FRUIT_TYPES 9

using std::vector;

enum FRUIT_TYPE {
	FRUIT_APPLE,
	FRUIT_PEACH,
	FRUIT_LEMON,
	FRUIT_BANANA,
	FRUIT_CHERRY,
	FRUIT_GRAPE,
	FRUIT_COCO,
	FRUIT_COFFEE,
	FRUIT_LATEX
};
static vector<string>FRUIT_NAME = {
	"Æ»¹û",
	"ÌÒ×Ó",
	"ÄûÃÊ",
	"Ïã½¶",
	"Ó£ÌÒ",
	"ÆÏÌÑ",
	"¿É¿É",
	"¿§·È",
	"Ïð½º"
};
static vector<int>FRUIT_TIME = {
	9 * 24 * 3600,//Æ»¹û
	14 * 24 * 3600,//ÌÒ×Ó
	20 * 24 * 3600,//ÄûÃÊ
	42 * 24 * 3600,//Ïã½¶
	40 * 24 * 3600,//Ó£ÌÒ
	64 * 24 * 3600,//ÆÏÌÑ
	100 * 24 * 3600,//¿É¿É
	51 * 24 * 3600,//¿§·È
	96 * 24 * 3600,//Ïð½º
};
static vector<int>SEED_PRICE = {

};

class Fruit {
private:
	FRUIT_TYPE type;
	Time time;

public:
	int age = 0;
	int id;
	static int maxId;

	Fruit(FRUIT_TYPE type, Clock *clk) : type(type) {
		time = *clk + FRUIT_TIME[type];
		id = maxId;
		maxId = maxId + 1;
	}
	Fruit(FRUIT_TYPE type, int time, int age, int id) : type(type), time(Time() + time), age(age), id(id) {}
	~Fruit() {}

	string growString(Clock *tmp) {
		int period = time - *tmp;
		if (period <= 0) {
			if (age <8)
				return "³ÉÊì";
			else
				return "¿ÝÎ®";
		}
		else return Time(period).toString(false);
	}
	void harvest(Clock *clk) {
		time = *clk + FRUIT_TIME[type];
		age++;
	}

	int getType() {
		return type;
	}
	int getTime() {
		Time start;
		return time - start;
	}
};
int Fruit::maxId = 0;