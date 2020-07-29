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
	"С��",
	"����",
	"�ܲ�",
	"��",
	"����",
	"�޻�",
	"����",
	"����",
	"�Ϲ�",
	"����",
	"����",
	"����",
	"��Ҷ"
};
static vector<int> PLANT_TIME = {
	10 * 24 * 3600,//С��
	15 * 24 * 3600,//����
	25 * 24 * 3600,//�ܲ�
	36 * 24 * 3600,//��
	50 * 24 * 3600,//����
	80 * 24 * 3600,//�޻�
	40 * 24 * 3600,//����
	20 * 24 * 3600,//����
	50 * 24 * 3600,//�Ϲ�
	40 * 24 * 3600,//����
	64 * 24 * 3600,//����
	30 * 24 * 3600,//����
	120 * 24 * 3600,//��Ҷ
};
static vector<int> PLANT_EXP = {
	1,//С��
	2,//����
	4,//�ܲ�
	8,//��
	15,//����
	25,//�޻�
	28,//����
	30,//����
	64,//�Ϲ�
	72,//����
	108,//����
	120,//����
	600,//��Ҷ
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
		if (period <= 0)return "����";
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