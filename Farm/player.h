#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "winsgl.h"
#include "plant.h"
#include "animal.h"
#include "pool.h"
#include "fruit.h"
#include "garden.h"
#include "work.h"
#include "research.h"
#include "trade.h"
#include <cmath>

using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::pair;
using std::map;

extern vector<string>PLANT_NAME;
extern vector<string>ANIMAL_NAME;
extern vector<string>MEAT_NAME;
extern vector<string>PRODUCT_NAME;
extern vector<string>POOL_NAME;
extern vector<string>FRUIT_NAME;
extern vector<string>GARDEN_NAME;
extern vector<string>MANUAL_NAME;

class Player {
private:
	string archive;

	string name;
	int cash = 100, level = 1, exp = 0;
	map<string, int> pack;
	map<string, int> enable = {
		{ "plant", 0 },
		{ "plantNum", 0 },

		{ "animal", 0 },
		{ "animalChicken", 0 },
		{ "animalCow", 0 },
		{ "animalPig", 0 },
		{ "animalSheep", 0 },
		{ "animalDuck", 0 },

		{ "pool", 0 },
		{ "poolFish", 0 },
		{ "poolShrimp", 0 },
		{ "poolCrab", 0 },
		{ "poolShell", 0 },

		{ "fruit", 0 },
		{ "fruitApple", 0 },
		{ "fruitPeach", 0 },
		{ "fruitLemon", 0 },
		{ "fruitBanana", 0 },
		{ "fruitCherry", 0 },
		{ "fruitGrape", 0 },
		{ "fruitCoco", 0 },
		{ "fruitCoffee", 0 },
		{ "fruitLatex", 0 },

		{ "garden", 0 },
		{ "gardenBristle", 0 },
		{ "gardenDandelion", 0 },
		{ "gardenRose", 0 },
		{ "gardenOrchid", 0 },
		{ "gardenTolip", 0 },
		{ "gardenLavender", 0 },
		{ "gardenMoli", 0 },
		{ "gardenGold", 0 },

		{ "work", 0 },
		{ "workFirewood", 0 },
		{ "workWoodhouse", 0 },
		{ "workHoe", 0 },
		{ "workWoodPlane", 0 },
		{ "workPaper", 0 },
		{ "workBoat", 0 },
		{ "workFlower", 0 },
		{ "workBread", 0 },
		{ "workCookie", 0 },
		{ "workPuff", 0 },
		{ "workCake", 0 },
		{ "workPizza", 0 },
		{ "workStarch", 0 },
		{ "workFruitpie", 0 },
		{ "workChickenfeed", 0 },
		{ "workCowfeed", 0 },
		{ "workPigfeed", 0 },
		{ "workSheepfeed", 0 },
		{ "workDuckfeed", 0 },
		{ "workCream", 0 },
		{ "workCheese", 0 },
		{ "workButter", 0 },
		{ "workSalad", 0 },
		{ "workYogurt", 0 },
		{ "workVenegar", 0 },
		{ "workSoy", 0 },
		{ "workSugar", 0 },
		{ "workSyrup", 0 },
		{ "workPeppersauce", 0 },
		{ "workTomatosauce", 0 },
		{ "workPeanutsauce", 0 },
		{ "workCutton", 0 },
		{ "workWool", 0 },
		{ "workBandage", 0 },
		{ "workWeave", 0 },
		{ "workSilk", 0 },
		{ "workNet", 0 },
		{ "workRosebundle", 0 },
		{ "workPotted", 0 },
		{ "workMixbundle", 0 },
		{ "workPerfume", 0 },
		{ "workPetal", 0 },
		{ "workClothes", 0 },
		{ "workSweater", 0 },
		{ "workShoes", 0 },
		{ "workSuit", 0 },
		{ "workDown", 0 },
		{ "workTrainer", 0 },
		{ "workDress", 0 },
		{ "workBag", 0 },
		{ "workArmer", 0 },
		{ "workHelmet", 0 },
		{ "workStone", 0 },
		{ "workHouse", 0 },
		{ "workVilla", 0 },
		{ "workSand", 0 },
		{ "workArbor", 0 },
		{ "workAsphalt", 0 },
		{ "workPark", 0 },
		{ "workDepartment", 0 },
		{ "workBacon", 0 },
		{ "workBeaf", 0 },
		{ "workPopcorn", 0 },
		{ "workChocolate", 0 },
		{ "workIcecream", 0 },
		{ "workFruitplate", 0 },
		{ "workLantern", 0 },
		{ "workDoor", 0 },
		{ "workBasket", 0 },
		{ "workSantatree", 0 },
		{ "workStatue", 0 },
		{ "workBeer", 0 },
		{ "workLamonade", 0 },
		{ "workMixfruit", 0 },
		{ "workMelonade", 0 },
		{ "workUscoffee", 0 },
		{ "workMilktea", 0 },
		{ "workCoal", 0 },
		{ "workPlast", 0 },
		{ "workIron", 0 },
		{ "workCarbon", 0 },
		{ "workGoldbar", 0 },
		{ "workRocket", 0 },
		{ "workKnife", 0 },
		{ "workBow", 0 },
		{ "workBomb", 0 },
		{ "workPistol", 0 },
		{ "workAutogun", 0 },
		{ "workCannon", 0 },
		{ "workTank", 0 },
		{ "workFlight", 0 },
		{ "workRing", 0 },
		{ "workNecklace", 0 },
		{ "workBracelet", 0 },
		{ "workEarring", 0 },
		{ "workHairpin", 0 },

		{ "research", 0 },

		{ "truck", 0 },

		{ "train", 0 },

		{ "ship", 0 },

		{ "plane", 0 },

		{ "mine", 0 },

		{ "tower", 0 },

		{ "town", 0 },

		{ "construct", 0 },

		{ "law", 0 },

		{ "tour", 0 },
	};

	void born() {
		clk = new Clock();
		process(1);
	}
	void unpackage(JSON *json) {
		clk = new Clock(getContent(json, "clock")->data.json_int);
		name = getContent(json, "name")->data.json_string;
		cash = getContent(json, "cash")->data.json_int;
		level = getContent(json, "level")->data.json_int;
		exp = getContent(json, "exp")->data.json_int;
		strcpy((char *)getWidgetByName("nameContent")->content, name.data());
		refreshWidget("nameContent");
		strcpy((char *)getWidgetByName("levelContent")->content,
			(std::to_string(level) + "(" + std::to_string(exp) + "/" + std::to_string(upexp(level)) + ")").data());
		refreshWidget("levelContent");
		strcpy((char *)getWidgetByName("moneyContent")->content, std::to_string(cash).data());
		refreshWidget("moneyContent");

		JSON *packList = getContent(json, "pack")->data.json_array;
		JSON_Item *ij;
		for (int idx = 0; ij = getElement(packList, idx); idx++) {
			string name = getContent(ij->data.json_object, "name")->data.json_string;
			int num = getContent(ij->data.json_object, "num")->data.json_int;
			pack[name] = num;
		}

		JSON *enableList = getContent(json, "enable")->data.json_array;
		JSON_Item *ej;
		for (int idx = 0; ej = getElement(enableList, idx); idx++) {
			string name = getContent(ej->data.json_object, "name")->data.json_string;
			int value = getContent(ej->data.json_object, "value")->data.json_int;
			enable[name] = value;
		}

		JSON *plantList = getContent(json, "plants")->data.json_array;
		JSON_Item *pj;
		for (int idx = 0; pj = getElement(plantList, idx); idx++) {
			bool empty = getContent(pj->data.json_object, "empty")->data.json_bool;
			if (empty) {
				plants.push_back(NULL);
			}
			else {
				int type = getContent(pj->data.json_object, "type")->data.json_int;
				int time = getContent(pj->data.json_object, "time")->data.json_int;
				plants.push_back(new Plant((PLANT_TYPE)type, time));
			}
		}

		JSON *houseList = getContent(json, "houses")->data.json_array;
		JSON_Item *hj;
		for (int idx = 0; hj = getElement(houseList, idx); idx++) {
			bool empty = getContent(hj->data.json_object, "empty")->data.json_bool;
			if (empty) {
				houses.push_back(NULL);
			}
			else {
				int type = getContent(hj->data.json_object, "type")->data.json_int;
				houses.push_back(new House((ANIMAL_TYPE)type));
				JSON *animalList = getContent(hj->data.json_object, "animals")->data.json_array;
				JSON_Item *aj;
				for (int pos = 0; aj = getElement(animalList, pos); pos++) {
					bool empty = getContent(aj->data.json_object, "empty")->data.json_bool;
					if (empty) {
						houses[idx]->addAnimal();
					}
					else {
						int time = getContent(aj->data.json_object, "time")->data.json_int;
						int grow = getContent(aj->data.json_object, "grow")->data.json_int;
						int produce = getContent(aj->data.json_object, "produce")->data.json_int;
						houses[idx]->addAnimal();
						houses[idx]->addAnimal(pos, time, grow, produce);
					}
				}
			}
		}

		JSON * poolObj = getContent(json, "pool")->data.json_object;
		pool->fishSmall = getContent(poolObj, "fishSmall")->data.json_int;
		pool->fishBig = getContent(poolObj, "fishBig")->data.json_int;
		pool->shrimpSmall = getContent(poolObj, "shrimpSmall")->data.json_int;
		pool->shrimpBig = getContent(poolObj, "shrimpBig")->data.json_int;
		pool->crabSmall = getContent(poolObj, "crabSmall")->data.json_int;
		pool->crabBig = getContent(poolObj, "crabBig")->data.json_int;
		pool->shellSmall = getContent(poolObj, "shellSmall")->data.json_int;
		pool->shellBig = getContent(poolObj, "shellBig")->data.json_int;

		JSON *fruitList = getContent(json, "fruits")->data.json_array;
		JSON_Item *fj;
		for (int idx = 0; fj = getElement(fruitList, idx); idx++) {
			int type = getContent(fj->data.json_object, "type")->data.json_int;
			int time = getContent(fj->data.json_object, "time")->data.json_int;
			int age = getContent(fj->data.json_object, "age")->data.json_int;
			fruits.push_back(new Fruit((FRUIT_TYPE)type, time, age, idx));
		}

		JSON *gardenList = getContent(json, "gardens")->data.json_array;
		JSON_Item *gj;
		for (int idx = 0; gj = getElement(gardenList, idx); idx++) {
			int type = getContent(gj->data.json_object, "type")->data.json_int;
			int time = getContent(gj->data.json_object, "time")->data.json_int;
			int age = getContent(gj->data.json_object, "age")->data.json_int;
			gardens.push_back(new Garden((GARDEN_TYPE)type, time, age, idx));
		}

		JSON *workshopList = getContent(json, "workshops")->data.json_array;
		JSON_Item *wj;
		for (int idx = 0; wj = getElement(workshopList, idx); idx++) {
			bool empty = getContent(wj->data.json_object, "empty")->data.json_bool;
			if (empty) {
				workshops[idx] = NULL;
			}
			else {
				workshops[idx] = new Workshop((WORK_TYPE)idx);
				JSON *currentObj = getContent(wj->data.json_object, "current")->data.json_object;
				int type = getContent(currentObj, "type")->data.json_int;
				int time = getContent(currentObj, "time")->data.json_int;
				workshops[idx]->setCurrent((MANUAL_TYPE)type, time);
				int len = getContent(wj->data.json_object, "len")->data.json_int;
				workshops[idx]->queueLen = len;
				JSON *queueArray = getContent(wj->data.json_object, "queue")->data.json_array;
				JSON_Item *qj;
				for (int pos = 0; qj = getElement(queueArray, pos); pos++) {
					workshops[idx]->addWork((MANUAL_TYPE)qj->data.json_int);
				}
			}
		}

		JSON *truckList = getContent(json, "truck")->data.json_array;
		JSON_Item *tj;
		for (int idx = 0; tj = getElement(truckList, idx); idx++) {
			string description = getContent(tj->data.json_object, "description")->data.json_string;
			int price = getContent(tj->data.json_object, "price")->data.json_int;
			JSON * postList = getContent(tj->data.json_object, "post")->data.json_array;
			JSON_Item *pj;
			map<string, int>post;
			for (int idx = 0; pj = getElement(postList, idx); idx++) {
				string name = getContent(pj->data.json_object, "name")->data.json_string;
				int num = getContent(pj->data.json_object, "num")->data.json_int;
				post[name] = num;
			}
			truck.addItem(description, price, post);
		}

		JSON *trainObj = getContent(json, "train")->data.json_object;
		JSON *trainList = getContent(trainObj, "list")->data.json_array;
		JSON_Item *lj;
		for (int idx = 0; lj = getElement(trainList, idx); idx++) {
			string name = getContent(lj->data.json_object, "name")->data.json_string;
			float prob = getContent(lj->data.json_object, "prob")->data.json_float;
			train.addItem(name, prob);
		}
		JSON *trainCurrent = getContent(trainObj, "current")->data.json_array;
		JSON_Item *cj;
		for (int idx = 0; cj = getElement(trainCurrent, idx); idx++) {
			string name = getContent(cj->data.json_object, "name")->data.json_string;
			int price = getContent(cj->data.json_object, "price")->data.json_int;
			train.addCurrent(name, price);
		}

	}
	JSON *package() {
		JSON *ret = createJson();
		setIntContent(ret, "clock", clk->getPast());
		setStringContent(ret, "name", name.data());
		setIntContent(ret, "cash", cash);
		setIntContent(ret, "level", level);
		setIntContent(ret, "exp", exp);

		JSON *packList = createJsonArray();
		for (auto item : pack) {
			if (item.second == 0)continue;
			JSON *ij = createJson();
			setStringContent(ij, "name", item.first.data());
			setIntContent(ij, "num", item.second);
			setObjectElement(packList, INT_MAX, ij);
		}
		setArrayContent(ret, "pack", packList);

		JSON *enableList = createJsonArray();
		for (auto e : enable) {
			JSON *ej = createJson();
			setStringContent(ej, "name", e.first.data());
			setIntContent(ej, "value", e.second);
			setObjectElement(enableList, INT_MAX, ej);
		}
		setArrayContent(ret, "enable", enableList);

		JSON * plantList= createJsonArray();
		for (auto plant : plants) {
			JSON *pj = createJson();
			setBoolContent(pj, "empty", plant == NULL);
			if (plant) {
				setIntContent(pj, "type", plant->getType());
				setIntContent(pj, "time", plant->getTime());
			}
			setObjectElement(plantList, INT_MAX, pj);
		}
		setArrayContent(ret, "plants", plantList);

		JSON * houseList = createJsonArray();
		for (auto h : houses) {
			JSON *hj = createJson();
			setBoolContent(hj, "empty", h == NULL);
			if (h) {
				setIntContent(hj, "type", h->getType());
				JSON *animalList = createJsonArray();
				for (auto a : h->getAnimal()) {
					JSON *aj = createJson();
					setBoolContent(aj, "empty", a == NULL);
					if (a) {
						setIntContent(aj, "time", a->getTime());
						setIntContent(aj, "grow", a->getGrow());
						setIntContent(aj, "produce", a->getProduce());
					}
					setObjectElement(animalList, INT_MAX, aj);
				}
				setArrayContent(hj, "animals", animalList);
			}
			setObjectElement(houseList, INT_MAX, hj);
		}
		setArrayContent(ret, "houses", houseList);

		JSON * poolObj = createJson();
		setIntContent(poolObj, "fishSmall", pool->fishSmall);
		setIntContent(poolObj, "fishBig", pool->fishBig);
		setIntContent(poolObj, "shrimpSmall", pool->shrimpSmall);
		setIntContent(poolObj, "shrimpBig", pool->shrimpBig);
		setIntContent(poolObj, "crabSmall", pool->crabSmall);
		setIntContent(poolObj, "crabBig", pool->crabBig);
		setIntContent(poolObj, "shellSmall", pool->shellSmall);
		setIntContent(poolObj, "shellBig", pool->shellBig);
		setObjectContent(ret, "pool", poolObj);

		JSON * fruitList = createJsonArray();
		for (auto fruit : fruits) {
			JSON *fj = createJson();
			setIntContent(fj, "type", fruit->getType());
			setIntContent(fj, "time", fruit->getTime());
			setIntContent(fj, "age", fruit->age);
			setObjectElement(fruitList, INT_MAX, fj);
		}
		setArrayContent(ret, "fruits", fruitList);

		JSON * gardenList = createJsonArray();
		for (auto garden : gardens) {
			JSON *gj = createJson();
			setIntContent(gj, "type", garden->getType());
			setIntContent(gj, "time", garden->getTime());
			setIntContent(gj, "age", garden->age);
			setObjectElement(gardenList, INT_MAX, gj);
		}
		setArrayContent(ret, "gardens", gardenList);

		JSON * workshopList = createJsonArray();
		for (auto w : workshops) {
			JSON *wj = createJson();
			setBoolContent(wj, "empty", w == NULL);
			if (w) {
				JSON *wjc = createJson();
				setIntContent(wjc, "type", w->getCurrent());
				setIntContent(wjc, "time", w->getTime());
				setObjectContent(wj, "current", wjc);
				setIntContent(wj, "len", w->queueLen);
				JSON *wjq = createJsonArray();
				for (int i = 0; w->getQueuer(i) != -1; i++) {
					setIntElement(wjq, INT_MAX, w->getQueuer(i));
				}
				setArrayContent(wj, "queue", wjq);
			}
			setObjectElement(workshopList, INT_MAX, wj);
		}
		setArrayContent(ret, "workshops", workshopList);

		JSON * truckList = createJsonArray();
		for (auto l : truck.getList()) {
			JSON *tj = createJson();
			setStringContent(tj, "description", l.first.data());
			setIntContent(tj, "price", l.second.second);
			JSON * postList = createJsonArray();
			for (auto p : l.second.first) {
				JSON *pj = createJson();
				setStringContent(pj, "name", p.first.data());
				setIntContent(pj, "num", p.second);
				setObjectElement(postList, INT_MAX, pj);
			}
			setArrayContent(tj, "post", postList);
			setObjectElement(truckList, INT_MAX, tj);
		}
		setObjectContent(ret, "truck", truckList);

		JSON * trainObj = createJson();
		JSON * trainList = createJsonArray();
		for (auto l : train.getList()) {
			JSON *item = createJson();
			setStringContent(item, "name", l.first.data());
			setFloatContent(item, "prob", l.second);
			setObjectElement(trainList, INT_MAX, item);
		}
		setArrayContent(trainObj, "list", trainList);
		JSON * trainCurrent = createJsonArray();
		for (auto l : train.getCurrent()) {
			JSON *item = createJson();
			setStringContent(item, "name", l.first.data());
			setIntContent(item, "price", l.second);
			setObjectElement(trainCurrent, INT_MAX, item);
		}
		setArrayContent(trainObj, "current", trainCurrent);
		setObjectContent(ret, "train", trainObj);

		return ret;
	}
	int upexp(int i) {
		return 20 * pow(1.2, i) - 10 * sqrt(i) * pow(1.1, i) + 18 * i + 10 * i * i;
	}
	void process(int level) {
		switch (level) {
		case 1: {
			plants.push_back(NULL);
			plants.push_back(NULL);
			plants.push_back(NULL);
			plants.push_back(NULL);
			plants.push_back(NULL);
			plants.push_back(NULL);
			enable["plant"] = 1;
			enable["plantNum"] = 6;
			pack["小麦"] = 3;
			train.addItem("小麦", 1.0f);

			workshops[WORK_WOOD] = new Workshop(WORK_WOOD);
			enable["work"] = 1;
			enable["workFirewood"] = 1;

			enable["town"] = 1;
			break;
		}
		case 2: {
			enable["plantNum"] += 3;
			pack["玉米"] = 3;
			train.addItem("玉米", 0.8f);

			workshops[WORK_BAKERY] = new Workshop(WORK_BAKERY);
			enable["workFlower"] = 1;
			break;
		}
		case 3: {
			enable["plantNum"] += 3;

			enable["workWoodhouse"] = 1;
			enable["workBread"] = 1;
			break;
		}
		case 4: {
			enable["plantNum"] += 3;

			houses.push_back(NULL);
			enable["animal"] = 1;
			enable["animalChicken"] = 1;

			workshops[WORK_FEED] = new Workshop(WORK_FEED);
			enable["workChickenfeed"] = 1;
			break;
		}
		case 5: {
			enable["plantNum"] += 3;

			enable["workHoe"] = 1;
			enable["workCookie"] = 1;

			enable["truck"] = 1;
			for (int i = 0; i < 6; i++) {
				truck.addItem(level);
			}
			break;
		}
		case 6: {
			enable["plantNum"] += 3;

			houses.push_back(NULL);
			enable["animalCow"] = 1;

			enable["workCowfeed"] = 1;
			break;
		}
		case 7: {
			enable["plantNum"] += 3;

			workshops[WORK_MILK] = new Workshop(WORK_MILK);
			enable["workCream"] = 1;
			enable["workPuff"] = 1;
			break;
		}
		case 8: {
			enable["plantNum"] += 3;
			train.addItem("萝卜", 0.4f);

			enable["workCheese"] = 1;

			enable["train"] = 1;
			train.refreshList();
			break;
		}
		case 9: {
			enable["plantNum"] += 3;

			houses.push_back(NULL);
			enable["animalPig"] = 1;

			enable["workPigfeed"] = 1;
			break;
		}
		case 10: {
			enable["plantNum"] += 3;
			train.addItem("大豆", 0.3f);

			workshops[WORK_FLAVOR] = new Workshop(WORK_FLAVOR);
			enable["workVenegar"] = 1;
			break;
		}
		case 11: {
			enable["plantNum"] += 3;
			train.addItem("甘蔗", 0.15f);

			enable["workSoy"] = 1;
			break;
		}
		case 12: {
			enable["plantNum"] += 3;

			enable["workButter"] = 1;
			enable["workSugar"] = 1;
			break;
		}
		case 13: {
			enable["plantNum"] += 3;
			train.addItem("棉花", 0.08f);

			enable["workCake"] = 1;
			break;
		}
		case 14: {
			enable["plantNum"] += 3;

			workshops[WORK_SPIN] = new Workshop(WORK_SPIN);
			enable["workPizza"] = 1;
			enable["workCutton"] = 1;
			break;
		}
		case 15: {
			enable["plantNum"] += 3;
			train.addItem("土豆", 0.05f);

			houses.push_back(NULL);

			enable["pool"] = 1;
			enable["poolFish"] = 1;
			break;
		}
		case 16: {
			enable["plantNum"] += 3;

			enable["fruit"] = 1;
			enable["fruitApple"] = 1;

			enable["workStarch"] = 1;
			break;
		}
		case 17: {
			enable["plantNum"] += 3;
			train.addItem("辣椒", 0.03f);

			enable["workSyrup"] = 1;
			break;
		}
		case 18: {
			enable["plantNum"] += 3;

			enable["garden"] = 1;
			enable["gardenBristle"] = 1;

			enable["workPeppersauce"] = 1;
			break;
		}
		case 19: {
			enable["plantNum"] += 3;

			enable["fruitPeach"] = 1;

			enable["gardenDandelion"] = 1;
			break;
		}
		case 20: {
			enable["plantNum"] += 3;

			houses.push_back(NULL);
			enable["animalSheep"] = 1;

			enable["workSheepfeed"] = 1;
			break;
		}
		case 21: {
			enable["plantNum"] += 3;

			enable["fruitLemon"] = 1;

			enable["workWool"] = 1;
			break;
		}
		case 22: {
			enable["plantNum"] += 3;

			enable["poolShrimp"] = 1;

			enable["gardenRose"] = 1;
			break;
		}
		case 23: {
			enable["plantNum"] += 3;

			workshops[WORK_FLOWER] = new Workshop(WORK_FLOWER);
			enable["workRosebundle"] = 1;
			workshops[WORK_CLOTH] = new Workshop(WORK_CLOTH);
			enable["workClothes"] = 1;
			break;
		}
		case 24: {
			enable["plantNum"] += 3;

			enable["fruitBanana"] = 1;

			enable["workSweater"] = 1;
			break;
		}
		case 25: {
			enable["plantNum"] += 3;

			houses.push_back(NULL);

			enable["gardenOrchid"] = 1;

			enable["workPotted"] = 1;
			break;
		}
		case 26: {
			enable["plantNum"] += 3;

			workshops[WORK_CONSTRUCT] = new Workshop(WORK_CONSTRUCT);
			enable["workBadage"] = 1;
			enable["workStone"] = 1;
			break;
		}
		case 27: {
			enable["plantNum"] += 3;

			enable["fruitCherry"] = 1;

			enable["workShoes"] = 1;
			break;
		}
		case 28: {
			enable["plantNum"] += 3;

			enable["fruitGrape"] = 1;

			enable["gardenTolip"] = 1;
			break;
		}
		case 29: {
			enable["plantNum"] += 3;

			houses.push_back(NULL);

			enable["gardenLavender"] = 1;

			workshops[WORK_MEAT] = new Workshop(WORK_MEAT);
			enable["workBacon"] = 1;
			break;
		}
		case 30: {
			enable["plantNum"] += 3;
			train.addItem("南瓜", 0.02f);

			enable["poolCrab"] = 1;
			break;
		}
		case 31: {
			enable["plantNum"] += 2;

			workshops[WORK_DECORATE] = new Workshop(WORK_DECORATE);
			enable["workHouse"] = 1;
			enable["workLantern"] = 1;
			break;
		}
		case 32: {
			enable["plantNum"] += 2;
			train.addItem("番茄", 0.015f);

			enable["workMixbundle"] = 1;
			break;
		}
		case 33: {
			enable["plantNum"] += 2;

			houses.push_back(NULL);

			enable["workTomatosauce"] = 1;
			enable["workBeaf"] = 1;
			break;
		}
		case 34: {
			enable["plantNum"] += 2;

			enable["workSalad"] = 1;
			enable["workWeave"] = 1;
			break;
		}
		case 35: {
			enable["plantNum"] += 2;

			houses.push_back(NULL);

			enable["workSuit"] = 1;
			enable["workVilla"] = 1;
			break;
		}
		case 36: {
			enable["plantNum"] += 2;

			workshops[WORK_DRINK] = new Workshop(WORK_DRINK);
			enable["workBeer"] = 1;
			enable["workDoor"] = 1;
			break;
		}
		case 37: {
			enable["plantNum"] += 2;

			enable["fruitCoco"] = 1;

			enable["workPopcorn"] = 1;
			break;
		}
		case 38: {
			enable["plantNum"] += 2;

			houses.push_back(NULL);

			enable["workSand"] = 1;
			enable["workChocolate"] = 1;
			break;
		}
		case 39: {
			enable["plantNum"] += 2;

			workshops[WORK_INDUSTRY] = new Workshop(WORK_INDUSTRY);
			enable["workLamonade"] = 1;
			enable["workCoal"] = 1;
			break;
		}
		case 40: {
			enable["plantNum"] += 2;

			enable["gardenMoli"] = 1;

			enable["workBasket"] = 1;
			break;
		}
		case 41: {
			enable["plantNum"] += 2;

			houses.push_back(NULL);

			enable["workWoodPlane"] = 1;
			enable["workMixfruit"] = 1;
			enable["workPlast"] = 1;
			break;
		}
		case 42: {
			enable["plantNum"] += 2;

			enable["workArbor"] = 1;
			enable["workPerfume"] = 1;
			enable["workIron"] = 1;
			break;
		}
		case 43: {
			enable["plantNum"] += 2;
			train.addItem("西瓜", 0.01f);

			workshops[WORK_FIRE] = new Workshop(WORK_FIRE);
			enable["workPaper"] = 1;
			enable["workKnife"] = 1;
			break;
		}
		case 44: {
			enable["plantNum"] += 2;

			houses.push_back(NULL);
			enable["animalDuck"] = 1;

			enable["workDuckfeed"] = 1;
			enable["workMelonade"] = 1;
			break;
		}
		case 45: {
			enable["plantNum"] += 2;

			enable["workCarbon"] = 1;
			enable["workFruitpie"] = 1;
			enable["workDown"] = 1;
			break;
		}
		case 46: {
			enable["plantNum"] += 2;
			train.addItem("花生", 0.06f);

			workshops[WORK_DIAMOND] = new Workshop(WORK_DIAMOND);
			enable["workRing"] = 1;
			enable["workBow"] = 1;
			break;
		}
		case 47: {
			enable["plantNum"] += 2;
			train.addItem("咖啡", 0.04f);

			houses.push_back(NULL);

			enable["workPeanutsauce"] = 1;
			enable["workSantatree"] = 1;
			break;
		}
		case 48: {
			enable["plantNum"] += 2;

			enable["workAsphalt"] = 1;
			enable["workBomb"] = 1;
			enable["workUscoffee"] = 1;
			break;
		}
		case 49: {
			enable["plantNum"] += 2;

			enable["workYogurt"] = 1;
			enable["workSilk"] = 1;
			enable["workIcecream"] = 1;
			break;
		}
		case 50: {
			enable["plantNum"] += 2;
			train.addItem("茶叶", 0.03f);

			houses.push_back(NULL);

			enable["workNet"] = 1;
			enable["workFruitplate"] = 1;
			break;
		}
		case 51: {
			enable["plantNum"] += 1;

			enable["workBoat"] = 1;
			enable["workStatue"] = 1;
			enable["workMilktea"] = 1;
			break;
		}
		case 52: {
			enable["plantNum"] += 1;
			
			houses.push_back(NULL);

			enable["fruitLatex"] = 1;

			enable["gardenGold"] = 1;

			enable["workPetal"] = 1;
			break;
		}
		case 53: {
			enable["plantNum"] += 1;

			enable["poolShell"] = 1;

			enable["workPistol"] = 1;
			enable["workTrainer"] = 1;
			break;
		}
		case 54: {
			enable["plantNum"] += 1;

			enable["workDress"] = 1;
			enable["workAutogun"] = 1;
			enable["workNecklace"] = 1;
			break;
		}
		case 55: {
			enable["plantNum"] += 1;

			enable["workBag"] = 1;
			enable["workPark"] = 1;
			enable["workCannon"] = 1;
			break;
		}
		case 56: {
			enable["plantNum"] += 1;

			enable["workBracelet"] = 1;
			enable["workGoldbar"] = 1;
			break;
		}
		case 57: {
			enable["plantNum"] += 1;

			enable["workArmer"] = 1;
			enable["workDepartment"] = 1;
			break;
		}
		case 58: {
			enable["plantNum"] += 1;

			enable["workEarring"] = 1;
			enable["workHelmet"] = 1;
			break;
		}
		case 59: {
			enable["plantNum"] += 1;

			enable["workTank"] = 1;
			enable["workHairpin"] = 1;
			break;
		}
		case 60: {
			enable["plantNum"] += 1;

			enable["workFlight"] = 1;
			enable["workRocket"] = 1;
			break;
		}
		default:
			break;
		}
	}

public:
	Clock *clk;
	vector<Plant*> plants;
	vector<House*> houses;
	Pool *pool;
	vector<Fruit*> fruits;
	vector<Garden*> gardens;

	vector<Workshop *> workshops;

	Truck truck;
	Train train;
	Ship ship;
	Plane plane;

	Player() {
		name = "玩家";
		for (int i = 0; i < PLANT_NAME.size(); i++) {
			pack[PLANT_NAME[i]] = 0;
		}
		for (int i = 0; i < MEAT_NAME.size(); i++) {
			pack[MEAT_NAME[i]] = 0;
		}
		for (int i = 0; i < PRODUCT_NAME.size(); i++) {
			pack[PRODUCT_NAME[i]] = 0;
		}
		for (int i = 0; i < POOL_NAME.size(); i++) {
			pack[POOL_NAME[i]] = 0;
		}
		for (int i = 0; i < FRUIT_NAME.size(); i++) {
			pack[FRUIT_NAME[i]] = 0;
		}
		for (int i = 0; i < GARDEN_NAME.size(); i++) {
			pack[GARDEN_NAME[i]] = 0;
		}
		for (int i = 0; i < MANUAL_NAME.size(); i++) {
			pack[MANUAL_NAME[i]] = 0;
		}
		pool = new Pool();
		workshops = vector<Workshop *>(WORK_TYPES, NULL);
	}
	~Player() {
		delete clk;
		for (auto p : plants)delete p;
		for (auto h : houses)delete h;
		for (auto w : workshops)delete w;
	}

	vector<pair<string, int>> getPack() {
		vector<pair<string, int>> ret;
		for (auto m : pack) {
			if(m.second > 0)ret.push_back(m);
		}
		std::sort(ret.begin(), ret.end(), [](pair<string, int>item1, pair<string, int>item2) {
			if (item1.first == item2.first)return false;
			for (unsigned int i = 0; i < PLANT_NAME.size(); i++) {
				if (item1.first == PLANT_NAME[i])return true;
				if (item2.first == PLANT_NAME[i])return false;
			}
			for (unsigned int i = 0; i < MEAT_NAME.size(); i++) {
				if (item1.first == MEAT_NAME[i])return true;
				if (item2.first == MEAT_NAME[i])return false;
			}
			for (unsigned int i = 0; i < PRODUCT_NAME.size(); i++) {
				if (item1.first == PRODUCT_NAME[i])return true;
				if (item2.first == PRODUCT_NAME[i])return false;
			}
			for (unsigned int i = 0; i < POOL_NAME.size(); i++) {
				if (item1.first == POOL_NAME[i])return true;
				if (item2.first == POOL_NAME[i])return false;
			}
			for (unsigned int i = 0; i < FRUIT_NAME.size(); i++) {
				if (item1.first == FRUIT_NAME[i])return true;
				if (item2.first == FRUIT_NAME[i])return false;
			}
			for (unsigned int i = 0; i < GARDEN_NAME.size(); i++) {
				if (item1.first == GARDEN_NAME[i])return true;
				if (item2.first == GARDEN_NAME[i])return false;
			}
			for (unsigned int i = 0; i < MANUAL_NAME.size(); i++) {
				if (item1.first == MANUAL_NAME[i])return true;
				if (item2.first == MANUAL_NAME[i])return false;
			}
			return item1.second < item2.second;
		});
		return ret;
	}
	int getNum(string item) { return pack[item]; }
	int mainLoop() {
		clk->pass(atoi((char *)getWidgetByName("velocityContent")->content));
		clk->getDate((char *)getWidgetByName("dateContent")->content);
		clk->getTime((char *)getWidgetByName("timeContent")->content);
		refreshWidget("dateContent");
		refreshWidget("timeContent");
		strcpy((char *)getWidgetByName("moneyContent")->content, std::to_string(cash).data());
		refreshWidget("moneyContent");
		if (clk->overnight) {
			pool->overnight();
			truck.overnight(level);
			train.refreshList();
			save();
		}

		int count0, count1, count2;
		count0 = count1 = count2 = 0;
		for (auto p : plants) {
			if (p == NULL)count0++;
			else if (p->growString(clk) == "成熟")count1++;
		}
		strcpy((char *)getWidgetByName("plantContent")->content, ("空地" + std::to_string(count0) +
			" 成熟" + std::to_string(count1)).data());
		refreshWidget("plantContent");
		count0 = count1 = count2 = 0;
		for (auto h : houses) {
			if (!h)continue;
			for (auto a : h->getAnimal()) {
				if (a == NULL)count0++;
				else if ((Time() + a->getTime()) < *clk && a->getProduce() == 1) {
					if(a->getGrow() <= 6)count1++;
					else count2++;
				}
			}
		}
		strcpy((char *)getWidgetByName("animalContent")->content, ("空位" + std::to_string(count0) +
			" 成熟" + std::to_string(count1) + " 老年" + std::to_string(count2)).data());
		refreshWidget("animalContent");
		count0 = count1 = count2 = 0;
		count0 = pool->smallNum();
		count1 = pool->bigNum();
		strcpy((char *)getWidgetByName("poolContent")->content, ("幼年" + std::to_string(count0) +
			" 成年" + std::to_string(count1)).data());
		refreshWidget("poolContent");
		count0 = count1 = count2 = 0;
		for (auto w : workshops) {
			if (w == NULL)break;
			if (w->getCurrent() == -1)count0++;
			else count1++;
		}
		strcpy((char *)getWidgetByName("workContent")->content, ("空位" + std::to_string(count0) +
			" 工作" + std::to_string(count1)).data());
		refreshWidget("workContent");

		for (auto ws : workshops) {
			if (ws) {
				ws->refreshResult(clk);
				if (ws->ready.size() > 0) {
					for (auto r : ws->ready) {
						pack[MANUAL_NAME[r]]++;
						addExp(MANUAL_EXP[r]);
					}
					ws->ready.clear();
				}
			}
		}

		if (biosKey(1)) {
			int key = biosKey(0);
			if (key == SG_ESC)return 1;
		}
		return 0;
	}

	void load(string filename) {
		archive = filename;
		ifstream fin(filename, std::ios::binary);
		int length;
		if (!fin.is_open()) {
			born();
		}
		else {
			fin.seekg(0, std::ios::end);
			length = (int)fin.tellg();
			fin.seekg(0, std::ios::beg);
			char *buffer = new char[length];
			fin.read(buffer, length);
			vector<char> plain(length);
			DESDecrypt(buffer, length, "SGL-Farm", plain.data());
			delete[] buffer;
			fin.close();
			JSON *json = readJson(plain.data());
			unpackage(json);
			freeJson(json);
		}
	}
	void save() {
		ofstream fout(archive, std::ios::binary);
		if (!fout.is_open())return;
		JSON *json = package();
		char *data = writeJson(json);
		freeJson(json);
		vector<char> cipher(strlen(data) + 8);
		int len = DESEncrypt(data, strlen(data), "SGL-Farm", cipher.data());
		fout.write(cipher.data(), len);
		free(data);
	}

	void setEnable(string name, int value) {
		enable[name] = value;
	}
	int getEnable(string name) {
		return enable[name];
	}
	bool useItem(string name, int num) {
		if (pack[name] >= num) {
			pack[name] -= num;
			return true;
		}
		return false;
	}
	void addItem(string name, int num) {
		pack[name] += num;
	}
	void addCash(int amount) {
		cash += amount;
	}
	bool useCash(int amount) {
		if (amount <= cash)cash -= amount;
		else return false;
		return true;
	}
	void addExp(int amount) {
		exp += amount;
		if (exp >= upexp(level)) {
			exp -= upexp(level);
			level++;
			process(level);
			alertInfo("升级", ("您已升级至" + std::to_string(level) + "级\n" + upgrade_text[level-1]).data(), 0, NULL);
		}
		strcpy((char *)getWidgetByName("levelContent")->content,
			(std::to_string(level) + "(" + std::to_string(exp) + "/" + std::to_string(upexp(level)) + ")").data());
		refreshWidget("levelContent");

	}
	void addPlant(int pos, int type) {
		plants[pos] = new Plant((PLANT_TYPE)type, clk);
	}
	void addWork(int type) {
		for (auto p : MANUAL_PREV[type]) {
			if (pack[p.first] < p.second)return;
		}
		for (auto p : MANUAL_PREV[type]) {
			pack[p.first] -= p.second;
		}
		workshops[MANUAL_CLASS[type]]->addWork((MANUAL_TYPE)type);
	}
};
