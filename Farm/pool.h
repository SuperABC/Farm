#pragma once
#include <string>
#include <vector>
#include "clock.h"

#define POOL_TYPES 4
#define FISH_INIT 60
#define SHRIMP_INIT 28
#define CRAB_INIT 13
#define SHELL_INIT 6
#define FISH_MAX 800
#define SHRIMP_MAX 400
#define CRAB_MAX 200
#define SHELL_MAX 100

using std::vector;

enum POOL_TYPE{
	POOL_FISH,
	POOL_SHRIMP,
	POOL_CRAB,
	POOL_SHELL,
};
static vector<string>POOL_NAME = {
	"”„",
	"œ∫",
	"–∑",
	"±¥"
};

int probRound(float prob) {
	float p = prob - (int)prob;
	if (random(1000) < p * 1000)return (int)prob + 1;
	else return (int)prob;
}

class Pool {
public:
	int fishSmall, fishBig;
	int shrimpSmall, shrimpBig;
	int crabSmall, crabBig;
	int shellSmall, shellBig;

	Pool() : fishSmall(FISH_INIT), fishBig(0),
		shrimpSmall(SHRIMP_INIT), shrimpBig(0),
		crabSmall(CRAB_INIT), crabBig(0),
		shellSmall(SHELL_INIT), shellBig(0) {}

	void overnight() {
		int fishGrow = probRound(fishSmall * random(1000) / 5000.f);
		fishSmall += probRound(sqrt(fishBig) * sqrt(FISH_MAX - fishBig - fishSmall) * random(1000) / (FISH_MAX * 100.f));
		fishBig += fishGrow;
		fishSmall -= fishGrow;
		int shrimpGrow = probRound(shrimpSmall * random(1000) / 10000.f);
		shrimpSmall += probRound(sqrt(shrimpBig) * sqrt(SHRIMP_MAX - shrimpBig - shrimpSmall) * random(1000) / (SHRIMP_MAX * 300.f));
		shrimpBig += shrimpGrow;
		shrimpSmall -= shrimpGrow;
		int crabGrow = probRound(crabSmall * random(1000) / 20000.f);
		crabSmall += probRound(sqrt(crabBig) * sqrt(CRAB_MAX - crabBig - crabSmall) * random(1000) / (CRAB_MAX * 900.f));
		crabBig += crabGrow;
		crabSmall -= crabGrow;
		int shellGrow = probRound(shellSmall * random(1000) / 40000.f);
		shellSmall += probRound(sqrt(shellBig) * sqrt(SHELL_MAX - shellBig - shellSmall) * random(1000) / (SHELL_MAX * 2700.f));
		shellBig += shellGrow;
		shellSmall -= shellGrow;
	}
	int bigNum() {
		return fishBig + shrimpBig + crabBig + shellBig;
	}
	int smallNum() {
		return fishSmall + shrimpSmall + crabSmall + shellSmall;
	}
	string statString() {
		return string() + "Õ≥º∆£∫\n"
			"”◊”„" + std::to_string(fishSmall) +
			" ”◊œ∫" + std::to_string(shrimpSmall) +
			" ”◊–∑" + std::to_string(crabSmall) +
			" ”◊±¥" + std::to_string(shellSmall) +
			"\n≥…”„" + std::to_string(fishBig) +
			" ≥…œ∫" + std::to_string(shrimpBig) +
			" ≥…–∑" + std::to_string(crabBig) +
			" ≥…±¥" + std::to_string(shellBig);
	}
};