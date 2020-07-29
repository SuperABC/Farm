#pragma once
#include <string>
#include <vector>
#include "clock.h"

#define PLANT_TYPES 13

using std::vector;

enum PLANT_TYPE {
	PLANT_FLOWER,
	PLANT_CORN,
	PLANT_CARROT,
	PLANT_BEAN,
	PLANT_SUGAR,
	PLANT_COTTON,
	PLANT_POTATO,
	PLANT_PEPER,
	PLANT_PUMPKIN,
	PLANT_TOMATO,
	PLANT_WATERMELON,
	PLANT_PEANUT,
	PLANT_TEA
};
static vector<string>PLANT_NAME = {
	"小麦",
	"玉米",
	"萝卜",
	"大豆",
	"甘蔗",
	"棉花",
	"土豆",
	"辣椒",
	"南瓜",
	"番茄",
	"西瓜",
	"花生",
	"茶叶"
};
static vector<int> PLANT_TIME = {
	10 * 24 * 3600,//小麦
	15 * 24 * 3600,//玉米
	25 * 24 * 3600,//萝卜
	36 * 24 * 3600,//大豆
	50 * 24 * 3600,//甘蔗
	80 * 24 * 3600,//棉花
	40 * 24 * 3600,//土豆
	20 * 24 * 3600,//辣椒
	50 * 24 * 3600,//南瓜
	40 * 24 * 3600,//番茄
	64 * 24 * 3600,//西瓜
	30 * 24 * 3600,//花生
	120 * 24 * 3600,//茶叶
};
static vector<int> PLANT_EXP = {
	1,//小麦
	2,//玉米
	4,//萝卜
	8,//大豆
	15,//甘蔗
	25,//棉花
	28,//土豆
	30,//辣椒
	64,//南瓜
	72,//番茄
	108,//西瓜
	120,//花生
	600,//茶叶
};

class Plant {
private:
	PLANT_TYPE type;
	Time time;

public:
	Plant(PLANT_TYPE type, Clock *clk) : type(type) {
		time = *clk + PLANT_TIME[type];
	}
	Plant(PLANT_TYPE type, int time) : type(type), time(Time()+time) {}
	~Plant() {

	}

	string growString(Clock *tmp) {
		int period = time - *tmp;
		if (period <= 0)return "成熟";
		else return Time(period).toString();
	}

	int getType() {
		return type;
	}
	int getTime() {
		Time start;
		return time - start;
	}
};