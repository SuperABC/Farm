#pragma once
#include <string>
#include <vector>
#include "clock.h"

#define GARDEN_TYPES 6

using std::vector;

enum GARDEN_TYPE {
	GARDEN_BRISTLE,
	GARDEN_DANDELION,
	GARDEN_ROSE,
	GARDEN_ORCHID,
	GARDEN_TOLIP,
	GARDEN_LAVENDER,
	GARDEN_MOLI,
	GARDEN_GOLD
};
static vector<string>GARDEN_NAME = {
	"��β��",
	"�ѹ�Ӣ",
	"õ��"
	"����",
	"������",
	"޹�²�",
	"����",
	"������"
};
static vector<int>GARDEN_TIME = {
	1 * 24 * 3600,//��β��
	2 * 24 * 3600,//�ѹ�Ӣ
	4 * 24 * 3600,//õ��
	3 * 24 * 3600,//����
	9 * 24 * 3600,//������
	10 * 24 * 3600,//޹�²�
	14 * 24 * 3600,//����
	120 * 24 * 3600,//������
};

class Garden {
private:
	GARDEN_TYPE type;
	Time time;

public:
	int age = 0;
	int id;
	static int maxId;

	Garden(GARDEN_TYPE type, Clock *clk) : type(type) {
		time = *clk + GARDEN_TIME[type];
		id = maxId;
		maxId = maxId + 1;
	}
	Garden(GARDEN_TYPE type, int time, int age, int id) : type(type), time(Time() + time), age(age), id(id) {}
	~Garden() {}

	string growString(Clock *tmp) {
		int period = time - *tmp;
		if (period <= 0) {
			if (age < 4)
				return "����";
			else
				return "��ή";
		}
		else return Time(period).toString(false);
	}
	void harvest(Clock *clk) {
		time = *clk + GARDEN_TIME[type];
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
int Garden::maxId = 0;