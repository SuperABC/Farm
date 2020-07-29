#pragma once
#include <string>
#include <vector>
#include "clock.h"

#define ANIMAL_TYPES 5

using std::vector;

enum ANIMAL_TYPE {
	ANIMAL_CHICKEN,
	ANIMAL_COW,
	ANIMAL_PIG,
	ANIMAL_SHEEP,
	ANIMAL_DUCK
};
static vector<string>HOUSE_NAME = {
	"º¶…·",
	"≈£»¶",
	"÷Ì»¶",
	"—Ú»¶",
	"—º…·"
};
static vector<string>ANIMAL_NAME = {
	"º¶",
	"≈£",
	"÷Ì",
	"—Ú",
	"—º"
};
static vector<string>MEAT_NAME = {
	"º¶»‚",
	"≈£»‚",
	"÷Ì»‚",
	"—Ú»‚",
	"—º»‚"
};
static vector<string>PRODUCT_NAME = {
	"º¶µ∞",
	"≈£ƒÃ",
	"ƒ¢πΩ",
	"—Ú√´",
	"—º»ﬁ"
};
static vector<int> ANIMAL_TIME = {
	24 * 3600,
	48 * 3600,
	96 * 3600,
	48 * 3600,
	360 * 3600
};
static vector<int> ANIMAL_EXP = {
	2,
	6,
	18,
	16,
	210
};
static vector<int> PRODUCT_EXP = {
	1,
	2,
	9,
	10,
	112
};

class Animal {
protected:
	ANIMAL_TYPE type;
	Time time;
	int grow = 0, produce = 1;

public:
	Animal(ANIMAL_TYPE type, Clock *clk) : type(type) {
		time = *clk + 2 * ANIMAL_TIME[type];
	}
	Animal(ANIMAL_TYPE type, int time, int grow, int produce) :
		type(type), time(Time() + time), grow(grow), produce(produce) {}

	string growString(Clock *tmp) {
		int period = time - *tmp;
		if (period <= 0) {
			if (grow < 6)
				if (produce) {
					return PRODUCT_NAME[type];
				}
				else {
					return "º¢∂ˆ";
				}
			else if (grow == 6)
				if (produce) {
					return "≤˙◊–";
				}
				else {
					return "º¢∂ˆ";
				}
			else
				if (produce) {
					return MEAT_NAME[type];
				}
				else {
					return "º¢∂ˆ";
				}
		}
		else {
			if(grow < 6)
				return "≥…≥§÷–\n" + Time(period).toString();
			else if(grow == 6)
				return "…˙”˝÷–\n" + Time(period).toString();
			else
				return "º¥Ω´À¿Õˆ\n" + Time(period).toString();
		}
	}
	int charge() {
		produce = 0;
		grow++;
		return grow;
	}
	void feed(Clock *clk) {
		produce = 1;
		if(grow<6)
			time = *clk + ANIMAL_TIME[type];
		else if (grow == 6)
			time = *clk + 2 * ANIMAL_TIME[type];
		else
			time = *clk + ANIMAL_TIME[type];
	}

	int getType() {
		return type;
	}
	int getTime() {
		Time start;
		return time - start;
	}
	int getGrow() {
		return grow;
	}
	int getProduce() {
		return produce;
	}
};

class House {
private:
	ANIMAL_TYPE type;
	vector<Animal *> animals;

public:
	House(ANIMAL_TYPE type) : type(type) {}
	~House() {
		for (auto a : animals)delete a;
	}

	int getType() {
		return type;
	}
	vector<Animal *> getAnimal() { return animals; }
	void addAnimal() {
		animals.push_back(NULL);
	}
	void addAnimal(int pos, Clock *clk) {
		animals[pos] = new Animal(type, clk);
	}
	void addAnimal(int pos, int time, int grow, int produce) {
		animals[pos] = new Animal(type, time, grow, produce);
	}
	void deleteAnimal(int pos) {
		delete animals[pos];
		animals[pos] = NULL;
	}
};