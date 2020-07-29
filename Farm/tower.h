#pragma once
#include "winsgl.h"

struct Block {
	int id;

	Block(int i) : id(i) {}
};
vector<vector<vector<Block>>> world;

void loadMap() {
	world.push_back({ 
		{ 3, 3, 3, 3, 1, 9, 1, 3 },
		{ 3, 3, 3, 3, 1, 9, 1, 3 },
		});
}

void towerSetup() {

}
void towerLoop() {

}