#include "winsgl.h"
#include "clock.h"
#include "text.h"
#include "player.h"
#include "gamble.h"
#include "tower.h"
#include "mine.h"

#define PLANT_HEIGHT PLANT_TYPES * 40
#define ANIMAL_HEIGHT ANIMAL_TYPES * 40
#define POOL_HEIGHT POOL_TYPES * 40
#define FRUIT_HEIGHT FRUIT_TYPES * 40
#define GARDEN_HEIGHT GARDEN_TYPES * 40
#define WORK_HEIGHT WORK_TYPES * 80
#define RESEARCH_HEIGHT RESEARCH_TYPES * 80

#define PURCHASE_HEIGHT PURCHASE_TYPES * 40

#define RELU(x) (((x)>=0)?(x):0)
#define NOREOPEN() static int opened = false; if(opened)return; opened = true;


enum MAIN_STATUS {
	MS_WELCOME,
	MS_ARCHIVE,
	MS_GAME
};
enum MAIN_STATUS status = MS_WELCOME;

Player *player;

void gameLayin() {
	deleteWidget("headIcon");
	deleteWidget("nameLabel");
	deleteWidget("nameContent");
	deleteWidget("levelLabel");
	deleteWidget("levelContent");
	deleteWidget("moneyLabel");
	deleteWidget("moneyContent");
	deleteWidget("dateContent");
	deleteWidget("timeContent");
	deleteWidget("velocityContent");
	deleteWidget("goalIcon");
	deleteWidget("warehouseIcon");
	deleteWidget("plantLabel");
	deleteWidget("plantContent");
	deleteWidget("plantButton");
	deleteWidget("animalLabel");
	deleteWidget("animalContent");
	deleteWidget("animalButton");
	deleteWidget("poolLabel");
	deleteWidget("poolContent");
	deleteWidget("poolButton");
	deleteWidget("fruitLabel");
	deleteWidget("fruitContent");
	deleteWidget("fruitButton");
	deleteWidget("gardenLabel");
	deleteWidget("gardenContent");
	deleteWidget("gardenButton");
	deleteWidget("workLabel");
	deleteWidget("workContent");
	deleteWidget("workButton");
	deleteWidget("researchLabel");
	deleteWidget("researchContent");
	deleteWidget("researchButton");
	deleteWidget("truckIcon");
	deleteWidget("trainIcon");
	deleteWidget("shipIcon");
	deleteWidget("planeIcon");
	deleteWidget("mineIcon");
	deleteWidget("towerIcon");
	deleteWidget("townButton");
	deleteWidget("constructButton");
	deleteWidget("lawButton");
	deleteWidget("tourButton");
}
void gameLayout() {
	registerWidget(easyWidget(SG_PIC, "headIcon", 10, 10, 80, 80, "source/head.bmp", NULL));
	registerWidget(easyWidget(SG_LABEL, "nameLabel", 100, 10, 40, 24, "姓名：", NULL));
	registerWidget(easyWidget(SG_LABEL, "nameContent", 140, 10, 100, 24, "玩家", NULL));
	registerWidget(easyWidget(SG_LABEL, "levelLabel", 100, 40, 40, 24, "等级：", NULL));
	registerWidget(easyWidget(SG_LABEL, "levelContent", 140, 40, 140, 24, "1(0/41)", NULL));
	registerWidget(easyWidget(SG_LABEL, "moneyLabel", 100, 70, 100, 24, "金钱：:", NULL));
	registerWidget(easyWidget(SG_LABEL, "moneyContent", 140, 70, 100, 24, "0", NULL));
	registerWidget(easyWidget(SG_LABEL, "dateContent", 280, 10, 120, 24, "2000年01月01日", NULL));
	registerWidget(easyWidget(SG_LABEL, "timeContent", 280, 40, 120, 24, "00:00:00", NULL));
	registerWidget(easyWidget(SG_BUTTON, "velocityContent", 280, 70, 100, 24, "1x", [](widget *obj) {
		static int rate = 1;
		if ((rate = rate * 2) > 128)rate = 1;
		sprintf((char *)getWidgetByName(obj->name)->content, "%dx", rate);
		refreshWidget(obj->name);
	}));

	registerWidget(easyWidget(SG_BUTTON, "goalIcon", getWidth(SG_CANVAS) - 190, 10, 80, 80, "", [](widget *obj) {
		NOREOPEN();
		createWindow(400, 400, "成就", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
		}, []() {});
	}));
	getWidgetByName("goalIcon")->bgImg = loadBmp("source/goal.bmp");
	refreshWidget("goalIcon");
	registerWidget(easyWidget(SG_BUTTON, "warehouseIcon", getWidth(SG_CANVAS) - 90, 10, 80, 80, "", [](widget *obj) {
		NOREOPEN();
		createWindow(400, 400, "仓库", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			static int page;
			page = 0;

			registerWidget(easyWidget(SG_LABEL, "warehousePage", 180, 320, 40, 20,
				(std::to_string(page + 1) + "  /  " + std::to_string(RELU((int)player->getPack().size() - 1) / 16 + 1)).data(), NULL));
			registerWidget(easyWidget(SG_BUTTON, "warehouseUpgrade", 0, 340, 400, 60, "升级", NULL));
			registerWidget(easyWidget(SG_BUTTON, "warehouseLeft", 0, 0, 20, 330, "<", [](widget *obj) {
				int iter;
				if (page>0)page--;
				strcpy((char *)getWidgetByName("warehousePage")->content,
					(std::to_string(page + 1) + "  /  " + std::to_string(RELU((int)player->getPack().size() - 1) / 16 + 1)).data());
				iter = 0;
				for (auto item : player->getPack()) {
					deleteWidget((string("ware") + std::to_string(iter)).data());
					iter++;
				}
				iter = 0;
				for (auto item : player->getPack()) {
					if (iter < page * 16 || iter >= page * 16 + 16) {
						iter++;
						continue;
					}
					registerWidget(easyWidget(SG_BUTTON, (string("ware") + std::to_string(iter)).data(),
						25 + (iter - page * 16) % 4 * 90, 10 + (iter - page * 16) / 4 * 80, 80, 70,
						(item.first + "\n" + std::to_string(item.second)).data(), NULL));
					iter++;
				}
			}));
			registerWidget(easyWidget(SG_BUTTON, "warehouseRight", 380, 0, 20, 330, ">", [](widget *obj) {
				int iter;
				if (page < ((int)player->getPack().size() - 1) / 16)page++;
				strcpy((char *)getWidgetByName("warehousePage")->content,
					(std::to_string(page + 1) + "  /  " + std::to_string(RELU((int)player->getPack().size() - 1) / 16 + 1)).data());
				iter = 0;
				for (auto item : player->getPack()) {
					deleteWidget((string("ware") + std::to_string(iter)).data());
					iter++;
				}
				iter = 0;
				for (auto item : player->getPack()) {
					if (iter < page * 16 || iter >= page * 16 + 16) {
						iter++;
						continue;
					}
					registerWidget(easyWidget(SG_BUTTON, (string("ware") + std::to_string(iter)).data(),
						25 + (iter - page * 16) % 4 * 90, 10 + (iter - page * 16) / 4 * 80, 80, 70,
						(item.first + "\n" + std::to_string(item.second)).data(), NULL));
					iter++;
				}
			}));
			int iter = 0;
			for (auto item : player->getPack()) {
				if (iter < page * 16 || iter >= page * 16 + 16) {
					iter++;
					continue;
				}
				registerWidget(easyWidget(SG_BUTTON, (string("ware") + std::to_string(iter)).data(),
					25 + (iter - page * 16) % 4 * 90, 10 + (iter - page * 16) / 4 * 80, 80, 70,
					(item.first + "\n" + std::to_string(item.second)).data(), NULL));
				iter++;
			}
		}, []() {});
	}));
	getWidgetByName("warehouseIcon")->bgImg = loadBmp("source/warehouse.bmp");
	refreshWidget("warehouseIcon");

	registerWidget(easyWidget(SG_LABEL, "plantLabel", 10, 122, 100, 24, "农场：", NULL));
	registerWidget(easyWidget(SG_LABEL, "plantContent", 100, 122, 200, 24, "空地0 成熟0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "plantButton", 300, 120, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("plant"))return;
		NOREOPEN();
		createWindow(400, 400, "农场", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			static string ids[] = {
				"plantFlower",
				"plantCorn",
				"plantCarrot",
				"plantBean",
				"plantSugar",
				"plantCutton",
				"plantPotato",
				"plantPepper",
				"plantPumpkin",
				"plantTomato",
				"plantWatermelon",
				"plantPeanut",
				"plantTea"
			};
			static int plantType;
			plantType = -1;
			static rgb selectColor, emptyColor;
			selectColor.r = 32, selectColor.g = 127, selectColor.b = 255;
			emptyColor.r = emptyColor.g = emptyColor.b = 0;
			registerWidget(easyWidget(SG_SCROLLVERT, "plantTypeScroll", 100, 0, 20, 400, "", NULL));
			getWidgetByName("plantTypeScroll")->extra = PLANT_HEIGHT - 400 + 1;
			getWidgetByName("plantTypeScroll")->drag = [](widget *obj, int x, int y) {
				moveWidget("plantAll", 0, -y);
				moveWidget("plantFlower", 0, -y);
				moveWidget("plantCorn", 0, -y);
				moveWidget("plantCarrot", 0, -y);
				moveWidget("plantBean", 0, -y);
				moveWidget("plantSugar", 0, -y);
				moveWidget("plantCutton", 0, -y);
				moveWidget("plantPotato", 0, -y);
				moveWidget("plantPepper", 0, -y);
				moveWidget("plantPumpkin", 0, -y);
				moveWidget("plantTomato", 0, -y);
				moveWidget("plantWatermelon", 0, -y);
				moveWidget("plantPeanut", 0, -y);
				moveWidget("plantTea", 0, -y);
			};
			refreshWidget("plantTypeScroll");

#define CHOOSE_PLANT(type) [](widget *obj) {\
	if (plantType == type) {\
		getWidgetByName(obj->name)->tf.color = emptyColor;\
		plantType = -1;\
	}\
	else {\
		if (plantType != -1) {\
			getWidgetByName(ids[plantType].data())->tf.color = emptyColor; \
			refreshWidget(ids[plantType].data());\
		}\
		getWidgetByName(obj->name)->tf.color = selectColor;\
		plantType = type;\
	}\
	refreshWidget(ids[type].data());\
}

			registerWidget(easyWidget(SG_LABEL, "plantFlower", 10, 10, 80, 24, "小麦", CHOOSE_PLANT(PLANT_FLOWER)));
			registerWidget(easyWidget(SG_LABEL, "plantCorn", 10, 50, 80, 24, "玉米", CHOOSE_PLANT(PLANT_CORN)));
			registerWidget(easyWidget(SG_LABEL, "plantCarrot", 10, 90, 80, 24, "萝卜", CHOOSE_PLANT(PLANT_CARROT)));
			registerWidget(easyWidget(SG_LABEL, "plantBean", 10, 130, 80, 24, "大豆", CHOOSE_PLANT(PLANT_BEAN)));
			registerWidget(easyWidget(SG_LABEL, "plantSugar", 10, 170, 80, 24, "甘蔗", CHOOSE_PLANT(PLANT_SUGAR)));
			registerWidget(easyWidget(SG_LABEL, "plantCutton", 10, 210, 80, 24, "棉花", CHOOSE_PLANT(PLANT_COTTON)));
			registerWidget(easyWidget(SG_LABEL, "plantPotato", 10, 250, 80, 24, "土豆", CHOOSE_PLANT(PLANT_POTATO)));
			registerWidget(easyWidget(SG_LABEL, "plantPepper", 10, 290, 80, 24, "辣椒", CHOOSE_PLANT(PLANT_PEPER)));
			registerWidget(easyWidget(SG_LABEL, "plantPumpkin", 10, 330, 80, 24, "南瓜", CHOOSE_PLANT(PLANT_PUMPKIN)));
			registerWidget(easyWidget(SG_LABEL, "plantTomato", 10, 370, 80, 24, "番茄", CHOOSE_PLANT(PLANT_TOMATO)));
			registerWidget(easyWidget(SG_LABEL, "plantWatermelon", 10, 410, 80, 24, "西瓜", CHOOSE_PLANT(PLANT_WATERMELON)));
			registerWidget(easyWidget(SG_LABEL, "plantPeanut", 10, 450, 80, 24, "花生", CHOOSE_PLANT(PLANT_PEANUT)));
			registerWidget(easyWidget(SG_LABEL, "plantTea", 10, 490, 80, 24, "茶叶", CHOOSE_PLANT(PLANT_TEA)));

#undef CHOOSE_PLANT
#define LAND_CLICK() [](widget *obj) {\
	if (obj->value == -1 && plantType != -1) {\
		if (player->useItem(PLANT_NAME[plantType], 1)) {\
			obj->value = plantType;\
			player->addPlant(atoi(obj->name + 4), plantType);\
		}\
	}\
	else if (obj->value >= 0 && player->plants[atoi(obj->name + 4)]->growString(player->clk) == "成熟") {\
		obj->value = -1;\
		player->addItem(PLANT_NAME[player->plants[atoi(obj->name + 4)]->getType()], 20);\
		player->addExp(PLANT_EXP[player->plants[atoi(obj->name + 4)]->getType()]);\
		delete player->plants[atoi(obj->name + 4)];\
		player->plants[atoi(obj->name + 4)] = NULL;\
	}\
}

			int i = 0;
			for (i = 0; i < player->plants.size(); i++) {
				registerWidget(easyWidget(SG_BUTTON, (string("land") + std::to_string(i)).data(),
					140 + i % 3 * 80, 10 + i / 3* 80, 70, 70, "", LAND_CLICK()));
				if (player->plants[i]) {
					getWidgetByName((string("land") + std::to_string(i)).data())->value = player->plants[i]->getType();
					refreshWidget((string("land") + std::to_string(i)).data());
				}
				else {
					getWidgetByName((string("land") + std::to_string(i)).data())->value = -1;
					refreshWidget((string("land") + std::to_string(i)).data());
				}
			}
			registerWidget(easyWidget(SG_BUTTON, "addLand", 140 + i % 3 * 80, 10 + i / 3 * 80, 70, 70, "+($20)",
				[](widget *obj) {
				if (player->plants.size() >= player->getEnable("plantNum"))return;
				if (!player->useCash(20))return;
				player->plants.push_back(NULL);
				int pos = player->plants.size() - 1;
				registerWidget(easyWidget(SG_BUTTON, (string("land") + std::to_string(pos)).data(),
					140 + pos % 3 * 80, 10 + pos / 3* 80 - getWidgetByName("landContentScroll")->value,
					70, 70, "空地", LAND_CLICK()));

#undef LAND_CLICK

				getWidgetByName((string("land") + std::to_string(pos)).data())->value = -1;
				refreshWidget((string("land") + std::to_string(pos)).data());
				if ((pos + 1) % 3 == 0) {
					moveWidget("addLand", -160, 80);
				}
				else moveWidget("addLand", 80, 0);
				getWidgetByName("landContentScroll")->extra = (player->plants.size() + 3) / 3 * 80 + 10 - 400 + 1;
				refreshWidget("landContentScroll");
			}));
			registerWidget(easyWidget(SG_SCROLLVERT, "landContentScroll", 380, 0, 20, 400, "", NULL));
			getWidgetByName("landContentScroll")->extra = (player->plants.size() + 3) / 3 * 80 + 10 - 400 + 1;
			getWidgetByName("landContentScroll")->drag = [](widget *obj, int x, int y) {
				for (int i = 0; i < player->plants.size(); i++) {
					moveWidget((string("land") + std::to_string(i)).data(), 0, -y);
				}
				moveWidget("addLand", 0, -y);
			};
			refreshWidget("landContentScroll");
		}, []() {
			for (int i = 0; i < player->plants.size(); i++) {
				if (!player->plants[i]) {
					strcpy((char *)getWidgetByName((string("land") + std::to_string(i)).data())->content, "空地");
					refreshWidget((string("land") + std::to_string(i)).data());
				}
				else {
					strcpy((char *)getWidgetByName((string("land") + std::to_string(i)).data())->content,
						(PLANT_NAME[player->plants[i]->getType()] + '\n' + player->plants[i]->growString(player->clk)).data());
					refreshWidget((string("land") + std::to_string(i)).data());
				}
			}

			if (biosMouse(1).z) {
				vec3i mouse = biosMouse(0);
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
					int previous = getWidgetByName("landContentScroll")->value;
					int extra = getWidgetByName("landContentScroll")->extra;
					if (extra > 0) {
						int value = previous + 20;
						if (value > extra - 1)value = extra - 1;
						getWidgetByName("landContentScroll")->value = value;
						refreshWidget("landContentScroll");
						getWidgetByName("landContentScroll")->drag(NULL, 0, value - previous);
					}
				}
				if (mouse.z == SG_MIDDLE_BUTTON_UP) {
					int previous = getWidgetByName("landContentScroll")->value;
					int value = previous - 20;
					if (value < 0)value = 0;
					getWidgetByName("landContentScroll")->value = value;
					refreshWidget("landContentScroll");
					getWidgetByName("landContentScroll")->drag(NULL, 0, value - previous);
				}
			}
		});
	}));
	registerWidget(easyWidget(SG_LABEL, "animalLabel", 10, 162, 100, 24, "牧场：", NULL));
	registerWidget(easyWidget(SG_LABEL, "animalContent", 100, 162, 200, 24, "空位0 成熟0 老年0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "animalButton", 300, 160, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("animal"))return;
		NOREOPEN();
		createWindow(400, 400, "牧场", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_LABEL, "animalChicken", 10, 10, 80, 24, "鸡舍", NULL));
			registerWidget(easyWidget(SG_LABEL, "animalCow", 10, 50, 80, 24, "牛圈", NULL));
			registerWidget(easyWidget(SG_LABEL, "animalPig", 10, 90, 80, 24, "猪圈", NULL));
			registerWidget(easyWidget(SG_LABEL, "animalSheep", 10, 130, 80, 24, "羊圈", NULL));
			registerWidget(easyWidget(SG_LABEL, "animalDuck", 10, 170, 80, 24, "鸭舍", NULL));

			for (int i = 0; i < player->houses.size(); i++) {
				registerWidget(easyWidget(SG_BUTTON, ("house" + std::to_string(i)).data(),
					140, 10 + i * 80, 170, 70,
					player->houses[i] ? HOUSE_NAME[player->houses[i]->getType()].data() : "空位", [](widget *obj) {
					static int pos;
					pos = obj->value;
					NOREOPEN();
					if (!player->houses[pos]) {
						static int chose;
						chose = 0;
						createWindow(640, 180, "窝棚", BIT_MAP, []() {
							windowFinish([]() {
								opened = false;
							});
							resizeFuntion(NULL);

							registerWidget(easyWidget(SG_BUTTON, "chooseChicken", 20, 40, 104, 100, "鸡舍", [](widget *obj) {
								if (!player->getEnable("animalChicken"))return;
								player->houses[pos] = new House(ANIMAL_CHICKEN);
								chose = 1;
							}));
							registerWidget(easyWidget(SG_BUTTON, "chooseCow", 144, 40, 104, 100, "牛圈", [](widget *obj) {
								if (!player->getEnable("animalCow"))return;
								player->houses[pos] = new House(ANIMAL_COW);
								chose = 1;
							}));
							registerWidget(easyWidget(SG_BUTTON, "choosePig", 268, 40, 104, 100, "猪圈", [](widget *obj) {
								if (!player->getEnable("animalPig"))return;
								player->houses[pos] = new House(ANIMAL_PIG);
								chose = 1;
							}));
							registerWidget(easyWidget(SG_BUTTON, "chooseSheep", 392, 40, 104, 100, "羊圈", [](widget *obj) {
								if (!player->getEnable("animalSheep"))return;
								player->houses[pos] = new House(ANIMAL_SHEEP);
								chose = 1;
							}));
							registerWidget(easyWidget(SG_BUTTON, "chooseDuck", 516, 40, 104, 100, "鸭舍", [](widget *obj) {
								if (!player->getEnable("animalDuck"))return;
									player->houses[pos] = new House(ANIMAL_DUCK);
								}));
						}, []() {
							if (chose) {
								closeWindow(-1);
								strcpy((char *)getWidgetByName(("house" + std::to_string(pos)).data())->content,
									HOUSE_NAME[player->houses[pos]->getType()].data());
								refreshWidget(("house" + std::to_string(pos)).data());
							}
						});
					}
					else {
						int window = createWindow(640, 180, "窝棚", BIT_MAP, []() {
							windowFinish([]() {
								opened = false;
							});
							resizeFuntion(NULL);

#define ANIMAL_CLICK() [](widget *obj) {\
	Animal* tmp = player->houses[pos]->getAnimal()[obj->value];\
	if (tmp == NULL) {\
		if(!player->useCash(2 * PURCHASE_PRICE[player->houses[pos]->getType() + PLANT_TYPES + ANIMAL_TYPES]))return;\
		player->houses[pos]->addAnimal(obj->value, player->clk);\
	}\
	else if (tmp->growString(player->clk) == PRODUCT_NAME[tmp->getType()]) {\
		player->addItem(PRODUCT_NAME[tmp->getType()], 1);\
		player->addExp(PRODUCT_EXP[tmp->getType()]);\
		tmp->charge();\
	}\
	else if (tmp->growString(player->clk) == "产仔") {\
		for (int i = 0; i < player->houses[pos]->getAnimal().size(); i++) {\
			if (player->houses[pos]->getAnimal()[i] == NULL) {\
				player->houses[pos]->addAnimal(i, player->clk);\
				break;\
			}\
		}\
		tmp->charge();\
	}\
	else if (tmp->growString(player->clk) == MEAT_NAME[tmp->getType()]) {\
		player->addItem(MEAT_NAME[tmp->getType()], 30);\
		player->addExp(ANIMAL_EXP[tmp->getType()]);\
		player->houses[pos]->deleteAnimal(obj->value);\
	}\
	else if (tmp->growString(player->clk) == "饥饿") {\
		if (player->useItem(ANIMAL_NAME[tmp->getType()] + "饲料", 1))\
			tmp->feed(player->clk);\
	}\
}
#define KILL_CLICK() [](widget *obj) {\
	Animal* tmp = player->houses[pos]->getAnimal()[obj->value];\
	if (!tmp)return;\
	int grow = tmp->charge();\
	player->addItem(MEAT_NAME[tmp->getType()], grow * (grow - 1) / 2);\
	player->addExp(ANIMAL_EXP[tmp->getType()] * grow);\
	player->houses[pos]->deleteAnimal(obj->value);\
}\

							for (int i = 0; i < player->houses[pos]->getAnimal().size(); i++) {
								registerWidget(easyWidget(SG_BUTTON, ("animal" + std::to_string(i)).data(),
									20 + i * 124, 30, 104, 80, "", ANIMAL_CLICK()));
								registerWidget(easyWidget(SG_BUTTON, ("kill" + std::to_string(i)).data(),
									20 + i * 124, 120, 104, 30, "宰杀", KILL_CLICK()));
								getWidgetByName(("animal" + std::to_string(i)).data())->value = i;
								getWidgetByName(("kill" + std::to_string(i)).data())->value = i;
								refreshWidget(("animal" + std::to_string(i)).data());
								refreshWidget(("kill" + std::to_string(i)).data());
							}
							if (player->houses[pos]->getAnimal().size() >= 5)return;
							registerWidget(easyWidget(SG_BUTTON, ("addAnimal" + std::to_string(pos)).data(),
								20 + player->houses[pos]->getAnimal().size() * 124, 30, 104, 120,
								("+($" + std::to_string(pos * 100) + ")").data(), [](widget *obj) {
								if (!player->useCash(pos * 100))return;
								player->houses[pos]->addAnimal();
								int index = player->houses[pos]->getAnimal().size() - 1;
								registerWidget(easyWidget(SG_BUTTON, ("animal" + std::to_string(index)).data(),
									20 + index * 124, 30, 104, 80, "", ANIMAL_CLICK()));
								registerWidget(easyWidget(SG_BUTTON, ("kill" + std::to_string(index)).data(),
									20 + index * 124, 120, 104, 30, "宰杀", KILL_CLICK()));
								getWidgetByName(("animal" + std::to_string(index)).data())->value = index;
								getWidgetByName(("kill" + std::to_string(index)).data())->value = index;
								refreshWidget(("animal" + std::to_string(index)).data());
								refreshWidget(("kill" + std::to_string(index)).data());
								if (player->houses[pos]->getAnimal().size() < 5)
									moveWidget(("addAnimal" + std::to_string(pos)).data(), 124, 0);
								else deleteWidget(("addAnimal" + std::to_string(pos)).data());
							}));
						}, []() {
							if (!player->houses[pos])return;
							for (int i = 0; i < player->houses[pos]->getAnimal().size(); i++) {
								if (!player->houses[pos]->getAnimal()[i]) {
									strcpy((char *)getWidgetByName(("animal" + std::to_string(i)).data())->content, "空位");
									refreshWidget(("animal" + std::to_string(i)).data());
								}
								else {
									strcpy((char *)getWidgetByName(("animal" + std::to_string(i)).data())->content,
										(ANIMAL_NAME[player->houses[pos]->getType()] + "\n" +
											player->houses[pos]->getAnimal()[i]->growString(player->clk)).data());
									refreshWidget(("animal" + std::to_string(i)).data());
								}
							}
						});
						getWidgetByName(("destruct" + std::to_string(pos)).data())->extra = window;
						refreshWidget(("destruct" + std::to_string(pos)).data());
					}
				}));
				getWidgetByName(("house" + std::to_string(i)).data())->value = i;
				refreshWidget(("house" + std::to_string(i)).data());
				registerWidget(easyWidget(SG_BUTTON, ("destruct" + std::to_string(i)).data(),
					320, 10 + i * 80, 40, 70, "拆除", [](widget *obj) {
					if (!player->houses[obj->value])return;
					else {
						delete player->houses[obj->value];
						player->houses[obj->value] = NULL;
						strcpy((char *)getWidgetByName(("house" + std::to_string(obj->value)).data())->content, "空闲");
						refreshWidget(("house" + std::to_string(obj->value)).data());
					}
				}));
				getWidgetByName(("destruct" + std::to_string(i)).data())->extra = -1;
				getWidgetByName(("destruct" + std::to_string(i)).data())->value = i;
				refreshWidget(("destruct" + std::to_string(i)).data());
			}
			registerWidget(easyWidget(SG_SCROLLVERT, "houseContentScroll", 380, 0, 20, 400, "", NULL));
			getWidgetByName("houseContentScroll")->extra = player->houses.size() * 80 + 10 - 400 + 1;
			getWidgetByName("houseContentScroll")->drag = [](widget *obj, int x, int y) {
				for (int i = 0; i < player->houses.size(); i++) {
					moveWidget((string("house") + std::to_string(i)).data(), 0, -y);
				}
			};
			refreshWidget("houseContentScroll");
		}, []() {});
	}));
	registerWidget(easyWidget(SG_LABEL, "poolLabel", 10, 202, 100, 24, "池塘：", NULL));
	registerWidget(easyWidget(SG_LABEL, "poolContent", 100, 202, 200, 24, "幼年0 成年0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "poolButton", 300, 200, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("pool"))return;
		NOREOPEN();
		createWindow(400, 400, "池塘", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_OUTPUT, "poolStat", 10, 10, 380, 80, "统计：\n"
				"幼鱼0 幼虾0 幼蟹0 幼贝0\n成鱼0 成虾0 成蟹0 成贝0", NULL));
			registerWidget(easyWidget(SG_BUTTON, "getFish", 10, 100, 80, 30, "钓鱼", [](widget *obj) {
				if (player->pool->fishBig > 0) {
					player->addItem("鱼", 1);
					player->pool->fishBig--;
				}
			}));
			registerWidget(easyWidget(SG_BUTTON, "getShrimp", 110, 100, 80, 30, "捕虾", [](widget *obj) {
				if (player->pool->shrimpBig > 0) {
					player->addItem("虾", 1);
					player->pool->shrimpBig--;
				}
			}));
			registerWidget(easyWidget(SG_BUTTON, "getCrab", 210, 100, 80, 30, "捕蟹", [](widget *obj) {
				if (player->pool->crabBig > 0) {
					player->addItem("蟹", 1);
					player->pool->crabBig--;
				}
			}));
			registerWidget(easyWidget(SG_BUTTON, "getShell", 310, 100, 80, 30, "拾贝", [](widget *obj) {
				if (player->pool->shellBig > 0) {
					player->addItem("贝", 1);
					player->pool->shellBig--;
				}
			}));
		}, []() {
			strcpy((char *)getWidgetByName("poolStat")->content, player->pool->statString().data());
			refreshWidget("poolStat");
		});
	}));
	registerWidget(easyWidget(SG_LABEL, "fruitLabel", 10, 242, 100, 24, "果园：", NULL));
	registerWidget(easyWidget(SG_LABEL, "fruitContent", 100, 242, 200, 24, "空位0 结果0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "fruitButton", 300, 240, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("fruit"))return;
		NOREOPEN();
		static int delId = -1;
		createWindow(400, 400, "果园", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_SCROLLVERT, "fruitScroll", 380, 0, 20, 400, "", NULL));
			getWidgetByName("fruitScroll")->extra = player->fruits.size() * 30 - 400 + 21;
			getWidgetByName("fruitScroll")->drag = [](widget *obj, int x, int y) {
				for (int i = 0; i < player->fruits.size(); i++) {
					moveWidget(("fruitLable" + std::to_string(player->fruits[i]->id)).data(), 0, -y);
					moveWidget(("fruitOperate" + std::to_string(player->fruits[i]->id)).data(), 0, -y);
				}
			};
			refreshWidget("fruitScroll");

#define ADD_FRUIT(type, idx)\
registerWidget(easyWidget(SG_LABEL, ("fruitLable" + std::to_string(player->fruits[idx]->id)).data(),\
	100, (idx) * 30 + 13 - getWidgetByName("fruitScroll")->value, 180, 24, FRUIT_NAME[type].data(), NULL));\
registerWidget(easyWidget(SG_BUTTON, ("fruitOperate" + std::to_string(player->fruits[idx]->id)).data(),\
	300, (idx) * 30 + 13 - getWidgetByName("fruitScroll")->value, 60, 24, "收获", [](widget *obj){\
	if(player->fruits[obj->value]->growString(player->clk)=="成熟") {\
		player->fruits[obj->value]->harvest(player->clk);\
		player->addItem(FRUIT_NAME[player->fruits[obj->value]->getType()], 10);\
	}\
	else if (player->fruits[obj->value]->growString(player->clk) == "枯萎") {\
		delId = player->fruits[obj->value]->id;\
		delete player->fruits[obj->value];\
		for(int i = obj->value + 1; i < player->fruits.size(); i++){\
			player->fruits[i - 1] = player->fruits[i];\
			moveWidget(("fruitLable" + std::to_string(player->fruits[i]->id)).data(), 0, -30);\
			moveWidget(("fruitOperate" + std::to_string(player->fruits[i]->id)).data(), 0, -30);\
			getWidgetByName(("fruitOperate" + std::to_string(player->fruits[i]->id)).data())->value--;\
			refreshWidget(("fruitOperate" + std::to_string(player->fruits[i]->id)).data());\
		}\
		player->fruits.pop_back();\
		getWidgetByName("fruitScroll")->extra = player->fruits.size() * 30 - 400 + 21; \
		refreshWidget("fruitScroll"); \
	}\
}));\
getWidgetByName(("fruitOperate" + std::to_string(player->fruits[idx]->id)).data())->value = idx;\
refreshWidget(("fruitOperate" + std::to_string(player->fruits[idx]->id)).data());\
getWidgetByName("fruitScroll")->extra = player->fruits.size() * 30 - 400 + 21;\
refreshWidget("fruitScroll");

			registerWidget(easyWidget(SG_BUTTON, "fruitApple", 10, 10, 80, 24,
				("苹果($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_APPLE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitApple"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_APPLE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_APPLE, player->clk));
				ADD_FRUIT(FRUIT_APPLE, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitPeach", 10, 50, 80, 24,
				("桃子($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_PEACH + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitPeach"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_PEACH + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_PEACH, player->clk));
				ADD_FRUIT(FRUIT_PEACH, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitLemon", 10, 90, 80, 24,
				("柠檬($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_LEMON + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitLemon"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_LEMON + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_LEMON, player->clk));
				ADD_FRUIT(FRUIT_LEMON, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitBanana", 10, 130, 80, 24,
				("香蕉($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_BANANA + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitBanana"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_BANANA + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_BANANA, player->clk));
				ADD_FRUIT(FRUIT_BANANA, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitCherry", 10, 170, 80, 24,
				("樱桃($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_CHERRY + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitCherry"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_CHERRY + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_CHERRY, player->clk));
				ADD_FRUIT(FRUIT_CHERRY, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitGrape", 10, 210, 80, 24,
				("葡萄($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_GRAPE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitGrape"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_GRAPE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_GRAPE, player->clk));
				ADD_FRUIT(FRUIT_GRAPE, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitCoco", 10, 250, 80, 24,
				("可可($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_COCO + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitCoco"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_COCO + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_COCO, player->clk));
				ADD_FRUIT(FRUIT_COCO, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitCoffee", 10, 290, 80, 24,
				("咖啡($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_COFFEE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitCoffee"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_COFFEE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_COFFEE, player->clk));
				ADD_FRUIT(FRUIT_COFFEE, player->fruits.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "fruitLatex", 10, 330, 80, 24,
				("橡胶($" + std::to_string(18 * PURCHASE_PRICE[FRUIT_LATEX + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("fruitLatex"))return;
				if (!player->useCash(18 * PURCHASE_PRICE[FRUIT_LATEX + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES]))return;
				player->fruits.push_back(new Fruit(FRUIT_LATEX, player->clk));
				ADD_FRUIT(FRUIT_LATEX, player->fruits.size() - 1);
			}));

			for (int i = 0; i < player->fruits.size(); i++) {
				ADD_FRUIT(player->fruits[i]->getType(), i);
			}

#undef ADD_FRUIT
			
		}, []() {
			if (delId >= 0) {
				deleteWidget(("fruitLable" + std::to_string(delId)).data());
				deleteWidget(("fruitOperate" + std::to_string(delId)).data());
				delId = -1;
			}

			for (int i = 0; i < player->fruits.size(); i++) {
				strcpy((char *)getWidgetByName(("fruitLable" + std::to_string(player->fruits[i]->id)).data())->content,
					(FRUIT_NAME[player->fruits[i]->getType()] + " " + player->fruits[i]->growString(player->clk)).data());
				refreshWidget(("fruitLable" + std::to_string(player->fruits[i]->id)).data());
			}

			if (biosMouse(1).z) {
				vec3i mouse = biosMouse(0);
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
					int previous = getWidgetByName("fruitScroll")->value;
					int extra = getWidgetByName("fruitScroll")->extra;
					if (extra > 0) {
						int value = previous + 20;
						if (value > extra - 1)value = extra - 1;
						getWidgetByName("fruitScroll")->value = value;
						refreshWidget("fruitScroll");
						getWidgetByName("fruitScroll")->drag(NULL, 0, value - previous);
					}
				}
				if (mouse.z == SG_MIDDLE_BUTTON_UP) {
					int previous = getWidgetByName("fruitScroll")->value;
					int value = previous - 20;
					if (value < 0)value = 0;
					getWidgetByName("fruitScroll")->value = value;
					refreshWidget("fruitScroll");
					getWidgetByName("fruitScroll")->drag(NULL, 0, value - previous);
				}
			}
		});
	}));
	registerWidget(easyWidget(SG_LABEL, "gardenLabel", 10, 282, 100, 24, "花园：", NULL));
	registerWidget(easyWidget(SG_LABEL, "gardenContent", 100, 282, 200, 24, "空位0 开花0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "gardenButton", 300, 280, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("garden"))return;
		NOREOPEN();
		static int delId = -1;
		createWindow(400, 400, "花园", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_SCROLLVERT, "gardenScroll", 380, 0, 20, 400, "", NULL));
			getWidgetByName("gardenScroll")->extra = player->gardens.size() * 30 - 400 + 21;
			getWidgetByName("gardenScroll")->drag = [](widget *obj, int x, int y) {
				for (int i = 0; i < player->gardens.size(); i++) {
					moveWidget(("gardenLable" + std::to_string(player->gardens[i]->id)).data(), 0, -y);
					moveWidget(("gardenOperate" + std::to_string(player->gardens[i]->id)).data(), 0, -y);
				}
			};
			refreshWidget("gardenScroll");

#define ADD_GARDEN(type, idx)\
registerWidget(easyWidget(SG_LABEL, ("gardenLable" + std::to_string(player->gardens[idx]->id)).data(),\
	100, (idx) * 30 + 13 - getWidgetByName("gardenScroll")->value, 180, 24, GARDEN_NAME[type].data(), NULL));\
registerWidget(easyWidget(SG_BUTTON, ("gardenOperate" + std::to_string(player->gardens[idx]->id)).data(),\
	300, (idx) * 30 + 13 - getWidgetByName("gardenScroll")->value, 60, 24, "收获", [](widget *obj){\
	if(player->gardens[obj->value]->growString(player->clk)=="成熟") {\
		player->gardens[obj->value]->harvest(player->clk);\
		player->addItem(GARDEN_NAME[player->gardens[obj->value]->getType()], 10);\
	}\
	else if (player->gardens[obj->value]->growString(player->clk) == "枯萎") {\
		delId = player->gardens[obj->value]->id;\
		delete player->gardens[obj->value];\
		for(int i = obj->value + 1; i < player->gardens.size(); i++){\
			player->gardens[i - 1] = player->gardens[i];\
			moveWidget(("gardenLable" + std::to_string(player->gardens[i]->id)).data(), 0, -30);\
			moveWidget(("gardenOperate" + std::to_string(player->gardens[i]->id)).data(), 0, -30);\
			getWidgetByName(("gardenOperate" + std::to_string(player->gardens[i]->id)).data())->value--;\
			refreshWidget(("gardenOperate" + std::to_string(player->gardens[i]->id)).data());\
		}\
		player->gardens.pop_back();\
		getWidgetByName("gardenScroll")->extra = player->gardens.size() * 30 - 400 + 21; \
		refreshWidget("gardenScroll"); \
	}\
}));\
getWidgetByName(("gardenOperate" + std::to_string(player->gardens[idx]->id)).data())->value = idx;\
refreshWidget(("gardenOperate" + std::to_string(player->gardens[idx]->id)).data());\
getWidgetByName("gardenScroll")->extra = player->gardens.size() * 30 - 400 + 21;\
refreshWidget("gardenScroll");

			registerWidget(easyWidget(SG_BUTTON, "gardenBristle", 10, 10, 80, 24,
				("狗尾草($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_BRISTLE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenBristle"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_BRISTLE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_BRISTLE, player->clk));
				ADD_GARDEN(GARDEN_BRISTLE, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenDandelion", 10, 50, 80, 24,
				("蒲公英($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_DANDELION + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenDandelion"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_DANDELION + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_DANDELION, player->clk));
				ADD_GARDEN(GARDEN_DANDELION, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenRose", 10, 90, 80, 24,
				("玫瑰($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_ROSE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenRose"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_ROSE + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_ROSE, player->clk));
				ADD_GARDEN(GARDEN_ROSE, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenOrchid", 10, 130, 80, 24,
				("兰花($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_ORCHID + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenOrchid"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_ORCHID + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_ORCHID, player->clk));
				ADD_GARDEN(GARDEN_ORCHID, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenTolip", 10, 170, 80, 24,
				("郁金香($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_TOLIP + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenTolip"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_TOLIP + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_TOLIP, player->clk));
				ADD_GARDEN(GARDEN_TOLIP, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenLavender", 10, 210, 80, 24,
				("薰衣草($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_LAVENDER + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenLavender"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_LAVENDER + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_LAVENDER, player->clk));
				ADD_GARDEN(GARDEN_LAVENDER, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenMoli", 10, 250, 80, 24,
				("茉莉($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_MOLI + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenMoli"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_MOLI + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_MOLI, player->clk));
				ADD_GARDEN(GARDEN_MOLI, player->gardens.size() - 1);
			}));
			registerWidget(easyWidget(SG_BUTTON, "gardenGold", 10, 290, 80, 24,
				("金银花($" + std::to_string(18 * PURCHASE_PRICE[GARDEN_GOLD + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]) + ")").data(), [](widget *obj) {
				if (!player->getEnable("gardenGold"))return;
				if (!player->useCash(12 * PURCHASE_PRICE[GARDEN_GOLD + PLANT_TYPES + 2 * ANIMAL_TYPES + POOL_TYPES + FRUIT_TYPES]))return;
				player->gardens.push_back(new Garden(GARDEN_GOLD, player->clk));
				ADD_GARDEN(GARDEN_GOLD, player->gardens.size() - 1);
			}));

			for (int i = 0; i < player->gardens.size(); i++) {
				ADD_GARDEN(player->gardens[i]->getType(), i);
			}

#undef ADD_GARDEN

		}, []() {
			if (delId >= 0) {
				deleteWidget(("gardenLable" + std::to_string(delId)).data());
				deleteWidget(("gardenOperate" + std::to_string(delId)).data());
				delId = -1;
			}

			for (int i = 0; i < player->gardens.size(); i++) {
				strcpy((char *)getWidgetByName(("gardenLable" + std::to_string(player->gardens[i]->id)).data())->content,
					(GARDEN_NAME[player->gardens[i]->getType()] + " " + player->gardens[i]->growString(player->clk)).data());
				refreshWidget(("gardenLable" + std::to_string(player->gardens[i]->id)).data());
			}

			if (biosMouse(1).z) {
				vec3i mouse = biosMouse(0);
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
					int previous = getWidgetByName("gardenScroll")->value;
					int extra = getWidgetByName("gardenScroll")->extra;
					if (extra > 0) {
						int value = previous + 20;
						if (value > extra - 1)value = extra - 1;
						getWidgetByName("gardenScroll")->value = value;
						refreshWidget("gardenScroll");
						getWidgetByName("gardenScroll")->drag(NULL, 0, value - previous);
					}
				}
				if (mouse.z == SG_MIDDLE_BUTTON_UP) {
					int previous = getWidgetByName("gardenScroll")->value;
					int value = previous - 20;
					if (value < 0)value = 0;
					getWidgetByName("gardenScroll")->value = value;
					refreshWidget("gardenScroll");
					getWidgetByName("gardenScroll")->drag(NULL, 0, value - previous);
				}
			}
		});
	}));
	registerWidget(easyWidget(SG_LABEL, "workLabel", 10, 322, 100, 24, "劳动：", NULL));
	registerWidget(easyWidget(SG_LABEL, "workContent", 100, 322, 200, 24, "空位0 工作0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "workButton", 300, 320, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("work"))return;
		NOREOPEN();
		createWindow(400, 400, "工作室", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_SCROLLVERT, "workScroll", 380, 0, 20, 400, "", NULL));
			getWidgetByName("workScroll")->extra = WORK_HEIGHT - 400 + 1;
			getWidgetByName("workScroll")->drag = [](widget *obj, int x, int y) {
				moveWidget("workWood", 0, -y);
				moveWidget("workBakery", 0, -y);
				moveWidget("workFeed", 0, -y);
				moveWidget("workMilk", 0, -y);
				moveWidget("workFlavor", 0, -y);
				moveWidget("workSpin", 0, -y);
				moveWidget("workFlower", 0, -y);
				moveWidget("workCloth", 0, -y);
				moveWidget("workConstruct", 0, -y);
				moveWidget("workMeat", 0, -y);
				moveWidget("workDecorate", 0, -y);
				moveWidget("workDrink", 0, -y);
				moveWidget("workIndustry", 0, -y);
				moveWidget("workFire", 0, -y);
				moveWidget("workDiamond", 0, -y);
			};
			refreshWidget("workScroll");

#define SHOW_DESCRIBE(widgetName, descName, idx)\
getWidgetByName(widgetName)->move = [](widget *obj, int x, int y) {\
	string description = MANUAL_NAME[idx] + '\n';\
	for(auto prev : MANUAL_PREV[idx]){\
		description += prev.first + ":" + std::to_string(prev.second) +\
			"(" + std::to_string(player->getNum(prev.first)) + ")" + '\n';\
	}\
	strcpy((char *)getWidgetByName(descName)->content, description.data());\
	refreshWidget(descName);\
};\
refreshWidget(widgetName);

#define REFRESH_WORKITEM(widgetName, workname)\
	tmp = (char *)getWidgetByName(widgetName)->content;\
	if(player->getEnable(workname)){\
		rgb color = {0, 0, 0};\
		getWidgetByName(widgetName)->tf.color = color;\
		refreshWidget(widgetName);\
	}\
	else{\
		rgb color = {127, 127, 127};\
		getWidgetByName(widgetName)->tf.color = color;\
		refreshWidget(widgetName);\
	}

			registerWidget(easyWidget(SG_BUTTON, "workWood", 10, 10, 360, 60, "木材采集与加工\n", [](widget *obj) {
				if (!player->workshops[WORK_WOOD])return;
				NOREOPEN();
				createWindow(800, 180, "木材采集与加工", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "woodDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "woodFirewood", 10, 120, 50, 50, "木柴", [](widget *obj) {
						if (!player->getEnable("workFirewood"))return;
						player->addWork(MANUAL_FIREWOOD);
					}));
					SHOW_DESCRIBE("woodFirewood", "woodDescribe", MANUAL_FIREWOOD);
					registerWidget(easyWidget(SG_BUTTON, "woodWoodhouse", 70, 120, 50, 50, "木棚", [](widget *obj) {
						if (!player->getEnable("workWoodhouse"))return;
						player->addWork(MANUAL_WOODHOUSE);
					}));
					SHOW_DESCRIBE("woodWoodhouse", "woodDescribe", MANUAL_WOODHOUSE);
					registerWidget(easyWidget(SG_BUTTON, "woodHoe", 130, 120, 50, 50, "锄头", [](widget *obj) {
						if (!player->getEnable("workHoe"))return;
						player->addWork(MANUAL_HOE);
					}));
					SHOW_DESCRIBE("woodHoe", "woodDescribe", MANUAL_HOE);
					registerWidget(easyWidget(SG_BUTTON, "woodWoodplane", 190, 120, 50, 50, "木板", [](widget *obj) {
						if (!player->getEnable("workWoodplane"))return;
						player->addWork(MANUAL_WOODPLANE);
					}));
					SHOW_DESCRIBE("woodWoodplane", "woodDescribe", MANUAL_WOODPLANE);
					registerWidget(easyWidget(SG_BUTTON, "woodPaper", 250, 120, 50, 50, "纸", [](widget *obj) {
						if (!player->getEnable("workPaper"))return;
						player->addWork(MANUAL_PAPER);
					}));
					SHOW_DESCRIBE("woodPaper", "woodDescribe", MANUAL_PAPER);
					registerWidget(easyWidget(SG_BUTTON, "woodBoat", 310, 120, 50, 50, "木筏", [](widget *obj) {
						if (!player->getEnable("workBoat"))return;
						player->addWork(MANUAL_BOAT);
					}));
					SHOW_DESCRIBE("woodBoat", "woodDescribe", MANUAL_BOAT);
					registerWidget(easyWidget(SG_BUTTON, "woodCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_WOOD]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("woodQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_WOOD]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "woodAdd",
						130 + 80 * player->workshops[WORK_WOOD]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_WOOD]->queueLen * (WORK_WOOD + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_WOOD]->queueLen * (WORK_WOOD + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("woodQueue") + std::to_string(player->workshops[WORK_WOOD]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_WOOD]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_WOOD]->addQueue()) {
							moveWidget("woodAdd", 80, 0);
							strcpy((char *)getWidgetByName("woodAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_WOOD]->queueLen * (WORK_WOOD + 1) * 50) + ")").data());
						}
						else deleteWidget("woodAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("woodCurrent")->content,
						player->workshops[WORK_WOOD]->currentString(player->clk).data());
					refreshWidget("woodCurrent");
					for (int i = 0; i < player->workshops[WORK_WOOD]->queueLen; i++) {
						int type = player->workshops[WORK_WOOD]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("woodQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("woodQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("woodQueue") + std::to_string(i)).data());

						char *tmp;
						REFRESH_WORKITEM("woodFirewood", "workFirewood");
						REFRESH_WORKITEM("woodWoodhouse", "workWoodhouse");
						REFRESH_WORKITEM("woodHoe", "workHoe");
						REFRESH_WORKITEM("woodWoodplane", "workWoodplane");
						REFRESH_WORKITEM("woodPaper", "workPaper");
						REFRESH_WORKITEM("woodBoat", "workBoat");
					}
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workBakery", 10, 90, 360, 60, "磨坊与烘焙坊\n", [](widget *obj) {
				if (!player->workshops[WORK_BAKERY])return;
				NOREOPEN();
				createWindow(800, 180, "磨坊与烘焙坊", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "bakeryDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "bakeryFlower", 10, 120, 50, 50, "面粉", [](widget *obj) {
						if (!player->getEnable("workFlower"))return;
						player->addWork(MANUAL_FLOWER);
					}));
					SHOW_DESCRIBE("bakeryFlower", "bakeryDescribe", MANUAL_FLOWER);
					registerWidget(easyWidget(SG_BUTTON, "bakeryBread", 70, 120, 50, 50, "面包", [](widget *obj) {
						if (!player->getEnable("workBread"))return;
						player->addWork(MANUAL_BREAD);
					}));
					SHOW_DESCRIBE("bakeryBread", "bakeryDescribe", MANUAL_BREAD);
					registerWidget(easyWidget(SG_BUTTON, "bakeryCookie", 130, 120, 50, 50, "饼干", [](widget *obj) {
						if (!player->getEnable("workCookie"))return;
						player->addWork(MANUAL_COOKIE);
					}));
					SHOW_DESCRIBE("bakeryCookie", "bakeryDescribe", MANUAL_COOKIE);
					registerWidget(easyWidget(SG_BUTTON, "bakeryPuff", 190, 120, 50, 50, "泡芙", [](widget *obj) {
						if (!player->getEnable("workPuff"))return;
						player->addWork(MANUAL_PUFF);
					}));
					SHOW_DESCRIBE("bakeryPuff", "bakeryDescribe", MANUAL_PUFF);
					registerWidget(easyWidget(SG_BUTTON, "bakeryCake", 250, 120, 50, 50, "蛋糕", [](widget *obj) {
						if (!player->getEnable("workCake"))return;
						player->addWork(MANUAL_CAKE);
					}));
					SHOW_DESCRIBE("bakeryCake", "bakeryDescribe", MANUAL_CAKE);
					registerWidget(easyWidget(SG_BUTTON, "bakeryPizza", 310, 120, 50, 50, "披萨", [](widget *obj) {
						if (!player->getEnable("workPizza"))return;
						player->addWork(MANUAL_PIZZA);
					}));
					SHOW_DESCRIBE("bakeryPizza", "bakeryDescribe", MANUAL_PIZZA);
					registerWidget(easyWidget(SG_BUTTON, "bakeryStarch", 370, 120, 50, 50, "土豆粉", [](widget *obj) {
						if (!player->getEnable("workStarch"))return;
						player->addWork(MANUAL_STARCH);
					}));
					SHOW_DESCRIBE("bakeryStarch", "bakeryDescribe", MANUAL_STARCH);
					registerWidget(easyWidget(SG_BUTTON, "bakeryFruitPie", 430, 120, 50, 50, "水果馅饼", [](widget *obj) {
						if (!player->getEnable("workFruitPie"))return;
						player->addWork(MANUAL_FRUITPIE);
					}));
					SHOW_DESCRIBE("bakeryFruitPie", "bakeryDescribe", MANUAL_FRUITPIE);
					registerWidget(easyWidget(SG_BUTTON, "bakeryCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_BAKERY]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("bakeryQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_BAKERY]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "bakeryAdd",
						130 + 80 * player->workshops[WORK_BAKERY]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_BAKERY]->queueLen * (WORK_BAKERY + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_BAKERY]->queueLen * (WORK_BAKERY + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("bakeryQueue") + std::to_string(player->workshops[WORK_BAKERY]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_BAKERY]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_BAKERY]->addQueue()) {
							moveWidget("bakeryAdd", 80, 0);
							strcpy((char *)getWidgetByName("bakeryAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_BAKERY]->queueLen * (WORK_BAKERY + 1) * 50) + ")").data());
						}
						else deleteWidget("bakeryAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("bakeryCurrent")->content,
						player->workshops[WORK_BAKERY]->currentString(player->clk).data());
					refreshWidget("bakeryCurrent");
					for (int i = 0; i < player->workshops[WORK_BAKERY]->queueLen; i++) {
						int type = player->workshops[WORK_BAKERY]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("bakeryQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("bakeryQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("bakeryQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("bakeryFlower", "workFlower");
					REFRESH_WORKITEM("bakeryBread", "workBread");
					REFRESH_WORKITEM("bakeryCookie", "workCookie");
					REFRESH_WORKITEM("bakeryPuff", "workPuff");
					REFRESH_WORKITEM("bakeryCake", "workCake");
					REFRESH_WORKITEM("bakeryPizza", "workPizza");
					REFRESH_WORKITEM("bakeryStarch", "workStarch");
					REFRESH_WORKITEM("bakeryFruitPie", "workFruitPie");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workFeed", 10, 170, 360, 60, "动物饲料厂\n", [](widget *obj) {
				if (!player->workshops[WORK_FEED])return;
				NOREOPEN();
				createWindow(800, 180, "动物饲料厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "feedDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "feedChickenfeed", 10, 120, 50, 50, "鸡饲料", [](widget *obj) {
						if (!player->getEnable("workChickenfeed"))return;
						player->addWork(MANUAL_CHICKENFEED);
					}));
					SHOW_DESCRIBE("feedChickenfeed", "feedDescribe", MANUAL_CHICKENFEED);
					registerWidget(easyWidget(SG_BUTTON, "feedCowfeed", 70, 120, 50, 50, "牛饲料", [](widget *obj) {
						if (!player->getEnable("workCowfeed"))return;
						player->addWork(MANUAL_COWFEED);
					}));
					SHOW_DESCRIBE("feedCowfeed", "feedDescribe", MANUAL_COWFEED);
					registerWidget(easyWidget(SG_BUTTON, "feedPigfeed", 130, 120, 50, 50, "猪饲料", [](widget *obj) {
						if (!player->getEnable("workPigfeed"))return;
						player->addWork(MANUAL_PIGFEED);
					}));
					SHOW_DESCRIBE("feedPigfeed", "feedDescribe", MANUAL_PIGFEED);
					registerWidget(easyWidget(SG_BUTTON, "feedSheepfeed", 190, 120, 50, 50, "羊饲料", [](widget *obj) {
						if (!player->getEnable("workSheepfeed"))return;
						player->addWork(MANUAL_SHEEPFEED);
					}));
					SHOW_DESCRIBE("feedSheepfeed", "feedDescribe", MANUAL_SHEEPFEED);
					registerWidget(easyWidget(SG_BUTTON, "feedDuckfeed", 250, 120, 50, 50, "鸭饲料", [](widget *obj) {
						if (!player->getEnable("workDuckfeed"))return;
						player->addWork(MANUAL_DUCKFEED);
					}));
					SHOW_DESCRIBE("feedDuckfeed", "feedDescribe", MANUAL_DUCKFEED);
					registerWidget(easyWidget(SG_BUTTON, "feedCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_FEED]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("feedQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_FEED]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "feedAdd",
						130 + 80 * player->workshops[WORK_FEED]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_FEED]->queueLen * (WORK_FEED + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_FEED]->queueLen * (WORK_FEED + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("feedQueue") + std::to_string(player->workshops[WORK_FEED]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_FEED]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_FEED]->addQueue()) {
							moveWidget("feedAdd", 80, 0);
							strcpy((char *)getWidgetByName("feedAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_FEED]->queueLen * (WORK_FEED + 1) * 50) + ")").data());
						}
						else deleteWidget("feedAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("feedCurrent")->content,
						player->workshops[WORK_FEED]->currentString(player->clk).data());
					refreshWidget("feedCurrent");
					for (int i = 0; i < player->workshops[WORK_FEED]->queueLen; i++) {
						int type = player->workshops[WORK_FEED]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("feedQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("feedQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("feedQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("feedChickenfeed", "workChickenfeed");
					REFRESH_WORKITEM("feedCowfeed", "workCowfeed");
					REFRESH_WORKITEM("feedPigfeed", "workPigfeed");
					REFRESH_WORKITEM("feedSheepfeed", "workSheepfeed");
					REFRESH_WORKITEM("feedDuckfeed", "workDuckfeed");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workMilk", 10, 250, 360, 60, "乳制品厂\n", [](widget *obj) {
				if (!player->workshops[WORK_MILK])return;
				NOREOPEN();
				createWindow(800, 180, "乳制品厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "milkDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "milkCream", 10, 120, 50, 50, "奶油", [](widget *obj) {
						if (!player->getEnable("workCream"))return;
						player->addWork(MANUAL_CREAM);
					}));
					SHOW_DESCRIBE("milkCream", "milkDescribe", MANUAL_CREAM);
					registerWidget(easyWidget(SG_BUTTON, "milkCheese", 70, 120, 50, 50, "奶酪", [](widget *obj) {
						if (!player->getEnable("workCheese"))return;
						player->addWork(MANUAL_CHEESE);
					}));
					SHOW_DESCRIBE("milkCheese", "milkDescribe", MANUAL_CHEESE);
					registerWidget(easyWidget(SG_BUTTON, "milkButter", 130, 120, 50, 50, "黄油", [](widget *obj) {
						if (!player->getEnable("workButter"))return;
						player->addWork(MANUAL_BUTTER);
					}));
					SHOW_DESCRIBE("milkButter", "milkDescribe", MANUAL_BUTTER);
					registerWidget(easyWidget(SG_BUTTON, "milkSalad", 190, 120, 50, 50, "沙拉酱", [](widget *obj) {
						if (!player->getEnable("workSalad"))return;
						player->addWork(MANUAL_SALAD);
					}));
					SHOW_DESCRIBE("milkSalad", "milkDescribe", MANUAL_SALAD);
					registerWidget(easyWidget(SG_BUTTON, "milkYogurt", 250, 120, 50, 50, "酸奶", [](widget *obj) {
						if (!player->getEnable("workYogurt"))return;
						player->addWork(MANUAL_YOGURT);
					}));
					SHOW_DESCRIBE("milkYogurt", "milkDescribe", MANUAL_YOGURT);
					registerWidget(easyWidget(SG_BUTTON, "milkCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_MILK]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("milkQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_MILK]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "milkAdd",
						130 + 80 * player->workshops[WORK_MILK]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_MILK]->queueLen * (WORK_MILK + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_MILK]->queueLen * (WORK_MILK + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("milkQueue") + std::to_string(player->workshops[WORK_MILK]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_MILK]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_MILK]->addQueue()) {
							moveWidget("milkAdd", 80, 0);
							strcpy((char *)getWidgetByName("milkAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_MILK]->queueLen * (WORK_MILK + 1) * 50) + ")").data());
						}
						else deleteWidget("milkAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("milkCurrent")->content,
						player->workshops[WORK_MILK]->currentString(player->clk).data());
					refreshWidget("milkCurrent");
					for (int i = 0; i < player->workshops[WORK_MILK]->queueLen; i++) {
						int type = player->workshops[WORK_MILK]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("milkQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("milkQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("milkQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("milkCream", "workCream");
					REFRESH_WORKITEM("milkCheese", "workCheese");
					REFRESH_WORKITEM("milkButter", "workButter");
					REFRESH_WORKITEM("milkSalad", "workSalad");
					REFRESH_WORKITEM("milkYogurt", "workYogurt");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workFlavor", 10, 330, 360, 60, "调料厂\n", [](widget *obj) {
				if (!player->workshops[WORK_FLAVOR])return;
				NOREOPEN();
				createWindow(800, 180, "调料厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "flavorDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "flavorVenegar", 10, 120, 50, 50, "醋", [](widget *obj) {
						if (!player->getEnable("workVenegar"))return;
						player->addWork(MANUAL_VENEGAR);
					}));
					SHOW_DESCRIBE("flavorVenegar", "flavorDescribe", MANUAL_VENEGAR);
					registerWidget(easyWidget(SG_BUTTON, "flavorSoy", 70, 120, 50, 50, "酱油", [](widget *obj) {
						if (!player->getEnable("workSoy"))return;
						player->addWork(MANUAL_SOY);
					}));
					SHOW_DESCRIBE("flavorSoy", "flavorDescribe", MANUAL_SOY);
					registerWidget(easyWidget(SG_BUTTON, "flavorSugar", 130, 120, 50, 50, "白糖", [](widget *obj) {
						if (!player->getEnable("workSugar"))return;
						player->addWork(MANUAL_SUGAR);
					}));
					SHOW_DESCRIBE("flavorSugar", "flavorDescribe", MANUAL_SUGAR);
					registerWidget(easyWidget(SG_BUTTON, "flavorSyrup", 190, 120, 50, 50, "糖浆", [](widget *obj) {
						if (!player->getEnable("workSyrup"))return;
						player->addWork(MANUAL_SYRUP);
					}));
					SHOW_DESCRIBE("flavorSyrup", "flavorDescribe", MANUAL_SYRUP);
					registerWidget(easyWidget(SG_BUTTON, "flavorPeppersauce", 250, 120, 50, 50, "辣酱", [](widget *obj) {
						if (!player->getEnable("workPeppersauce"))return;
						player->addWork(MANUAL_PEPPERSAUCE);
					}));
					SHOW_DESCRIBE("flavorPeppersauce", "flavorDescribe", MANUAL_PEPPERSAUCE);
					registerWidget(easyWidget(SG_BUTTON, "flavorTomatosauce", 310, 120, 50, 50, "番茄酱", [](widget *obj) {
						if (!player->getEnable("workTomatosauce"))return;
						player->addWork(MANUAL_TOMATOSAUCE);
					}));
					SHOW_DESCRIBE("flavorTomatosauce", "flavorDescribe", MANUAL_TOMATOSAUCE);
					registerWidget(easyWidget(SG_BUTTON, "flavorPeanutsauce", 370, 120, 50, 50, "花生酱", [](widget *obj) {
						if (!player->getEnable("workPeanutsauce"))return;
						player->addWork(MANUAL_PEANUTSAUCE);
					}));
					SHOW_DESCRIBE("flavorPeanutsauce", "flavorDescribe", MANUAL_PEANUTSAUCE);
					registerWidget(easyWidget(SG_BUTTON, "flavorCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_FLAVOR]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("flavorQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_FLAVOR]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "flavorAdd",
						130 + 80 * player->workshops[WORK_FLAVOR]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_FLAVOR]->queueLen * (WORK_FLAVOR + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_FLAVOR]->queueLen * (WORK_FLAVOR + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("flavorQueue") + std::to_string(player->workshops[WORK_FLAVOR]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_FLAVOR]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_FLAVOR]->addQueue()) {
							moveWidget("flavorAdd", 80, 0);
							strcpy((char *)getWidgetByName("flavorAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_FLAVOR]->queueLen * (WORK_FLAVOR + 1) * 50) + ")").data());
						}
						else deleteWidget("flavorAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("flavorCurrent")->content,
						player->workshops[WORK_FLAVOR]->currentString(player->clk).data());
					refreshWidget("flavorCurrent");
					for (int i = 0; i < player->workshops[WORK_FLAVOR]->queueLen; i++) {
						int type = player->workshops[WORK_FLAVOR]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("flavorQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("flavorQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("flavorQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("flavorVenegar", "workVenegar");
					REFRESH_WORKITEM("flavorSoy", "workSoy");
					REFRESH_WORKITEM("flavorSugar", "workSugar");
					REFRESH_WORKITEM("flavorSyrup", "workSyrup");
					REFRESH_WORKITEM("flavorPeppersauce", "workPeppersauce");
					REFRESH_WORKITEM("flavorTomatosauce", "workTomatosauce");
					REFRESH_WORKITEM("flavorPeanutsauce", "workPeanutsauce");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workSpin", 10, 410, 360, 60, "纺织厂\n", [](widget *obj) {
				if (!player->workshops[WORK_SPIN])return;
				NOREOPEN();
				createWindow(800, 180, "纺织厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "spinDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "spinCutton", 10, 120, 50, 50, "棉布", [](widget *obj) {
						if (!player->getEnable("workCutton"))return;
						player->addWork(MANUAL_CUTTON);
					}));
					SHOW_DESCRIBE("spinCutton", "spinDescribe", MANUAL_CUTTON);
					registerWidget(easyWidget(SG_BUTTON, "spinWool", 70, 120, 50, 50, "毛线", [](widget *obj) {
						if (!player->getEnable("workWool"))return;
						player->addWork(MANUAL_WOOL);
					}));
					SHOW_DESCRIBE("spinWool", "spinDescribe", MANUAL_WOOL);
					registerWidget(easyWidget(SG_BUTTON, "spinBandage", 130, 120, 50, 50, "绷带", [](widget *obj) {
						if (!player->getEnable("workBandage"))return;
						player->addWork(MANUAL_BANDAGE);
					}));
					SHOW_DESCRIBE("spinBandage", "spinDescribe", MANUAL_BANDAGE);
					registerWidget(easyWidget(SG_BUTTON, "spinWeave", 190, 120, 50, 50, "织布", [](widget *obj) {
						if (!player->getEnable("workWeave"))return;
						player->addWork(MANUAL_WEAVE);
					}));
					SHOW_DESCRIBE("spinWeave", "spinDescribe", MANUAL_WEAVE);
					registerWidget(easyWidget(SG_BUTTON, "spinSilk", 250, 120, 50, 50, "丝绸", [](widget *obj) {
						if (!player->getEnable("workSilk"))return;
						player->addWork(MANUAL_SILK);
					}));
					SHOW_DESCRIBE("spinSilk", "spinDescribe", MANUAL_SILK);
					registerWidget(easyWidget(SG_BUTTON, "spinNet", 310, 120, 50, 50, "渔网", [](widget *obj) {
						if (!player->getEnable("workNet"))return;
						player->addWork(MANUAL_NET);
					}));
					SHOW_DESCRIBE("spinNet", "spinDescribe", MANUAL_NET);
					registerWidget(easyWidget(SG_BUTTON, "spinCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_SPIN]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("spinQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_SPIN]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "spinAdd",
						130 + 80 * player->workshops[WORK_SPIN]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_SPIN]->queueLen * (WORK_SPIN + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_SPIN]->queueLen * (WORK_SPIN + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("spinQueue") + std::to_string(player->workshops[WORK_SPIN]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_SPIN]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_SPIN]->addQueue()) {
							moveWidget("spinAdd", 80, 0);
							strcpy((char *)getWidgetByName("spinAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_SPIN]->queueLen * (WORK_SPIN + 1) * 50) + ")").data());
						}
						else deleteWidget("spinAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("spinCurrent")->content,
						player->workshops[WORK_SPIN]->currentString(player->clk).data());
					refreshWidget("spinCurrent");
					for (int i = 0; i < player->workshops[WORK_SPIN]->queueLen; i++) {
						int type = player->workshops[WORK_SPIN]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("spinQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("spinQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("spinQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("spinCutton", "workCutton");
					REFRESH_WORKITEM("spinWool", "workWool");
					REFRESH_WORKITEM("spinBandage", "workBandage");
					REFRESH_WORKITEM("spinWeave", "workWeave");
					REFRESH_WORKITEM("spinSilk", "workSilk");
					REFRESH_WORKITEM("spinNet", "workNet");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workFlower", 10, 490, 360, 60, "花束加工厂\n", [](widget *obj) {
				if (!player->workshops[WORK_FLOWER])return;
				NOREOPEN();
				createWindow(800, 180, "花束加工厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "flowerDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "flowerRosebundle", 10, 120, 50, 50, "玫瑰束", [](widget *obj) {
						if (!player->getEnable("workRosebundle"))return;
						player->addWork(MANUAL_ROSEBUNDLE);
					}));
					SHOW_DESCRIBE("flowerRosebundle", "flowerDescribe", MANUAL_ROSEBUNDLE);
					registerWidget(easyWidget(SG_BUTTON, "flowerPotted", 70, 120, 50, 50, "盆栽", [](widget *obj) {
						if (!player->getEnable("workPotted"))return;
						player->addWork(MANUAL_POTTED);
					}));
					SHOW_DESCRIBE("flowerPotted", "flowerDescribe", MANUAL_POTTED);
					registerWidget(easyWidget(SG_BUTTON, "flowerMixbundle", 130, 120, 50, 50, "混合花束", [](widget *obj) {
						if (!player->getEnable("workMixbundle"))return;
						player->addWork(MANUAL_MIXBUNDLE);
					}));
					SHOW_DESCRIBE("flowerMixbundle", "flowerDescribe", MANUAL_MIXBUNDLE);
					registerWidget(easyWidget(SG_BUTTON, "flowerPerfume", 190, 120, 50, 50, "香水", [](widget *obj) {
						if (!player->getEnable("workPerfume"))return;
						player->addWork(MANUAL_PERFUME);
					}));
					SHOW_DESCRIBE("flowerPerfume", "flowerDescribe", MANUAL_PERFUME);
					registerWidget(easyWidget(SG_BUTTON, "flowerPetal", 250, 120, 50, 50, "金银花瓣", [](widget *obj) {
						if (!player->getEnable("workPetal"))return;
						player->addWork(MANUAL_PETAL);
					}));
					SHOW_DESCRIBE("flowerPetal", "flowerDescribe", MANUAL_PETAL);
					registerWidget(easyWidget(SG_BUTTON, "flowerCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_FLOWER]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("flowerQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_FLOWER]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "flowerAdd",
						130 + 80 * player->workshops[WORK_FLOWER]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_FLOWER]->queueLen * (WORK_FLOWER + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_FLOWER]->queueLen * (WORK_FLOWER + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("flowerQueue") + std::to_string(player->workshops[WORK_FLOWER]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_FLOWER]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_FLOWER]->addQueue()) {
							moveWidget("flowerAdd", 80, 0);
							strcpy((char *)getWidgetByName("flowerAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_FLOWER]->queueLen * (WORK_FLOWER + 1) * 50) + ")").data());
						}
						else deleteWidget("flowerAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("flowerCurrent")->content,
						player->workshops[WORK_FLOWER]->currentString(player->clk).data());
					refreshWidget("flowerCurrent");
					for (int i = 0; i < player->workshops[WORK_FLOWER]->queueLen; i++) {
						int type = player->workshops[WORK_FLOWER]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("flowerQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("flowerQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("flowerQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("flowerRosebundle", "workRosebundle");
					REFRESH_WORKITEM("flowerPotted", "workPotted");
					REFRESH_WORKITEM("flowerMixbundle", "workMixbundle");
					REFRESH_WORKITEM("flowerflowerPerfume", "workflowerPerfume");
					REFRESH_WORKITEM("flowerPetal", "workPetal");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workCloth", 10, 570, 360, 60, "服装厂\n", [](widget *obj) {
				if (!player->workshops[WORK_CLOTH])return;
				NOREOPEN();
				createWindow(800, 180, "服装厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "clothDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "clothClothes", 10, 120, 50, 50, "衬衣", [](widget *obj) {
						if (!player->getEnable("workClothes"))return;
						player->addWork(MANUAL_CLOTHES);
					}));
					SHOW_DESCRIBE("clothClothes", "clothDescribe", MANUAL_CLOTHES);
					registerWidget(easyWidget(SG_BUTTON, "clothSweater", 70, 120, 50, 50, "毛衣", [](widget *obj) {
						if (!player->getEnable("workSweater"))return;
						player->addWork(MANUAL_SWEATER);
					}));
					SHOW_DESCRIBE("clothSweater", "clothDescribe", MANUAL_SWEATER);
					registerWidget(easyWidget(SG_BUTTON, "clothShoes", 130, 120, 50, 50, "布鞋", [](widget *obj) {
						if (!player->getEnable("workShoes"))return;
						player->addWork(MANUAL_SHOES);
					}));
					SHOW_DESCRIBE("clothShoes", "clothDescribe", MANUAL_SHOES);
					registerWidget(easyWidget(SG_BUTTON, "clothSuit", 190, 120, 50, 50, "西装", [](widget *obj) {
						if (!player->getEnable("workSuit"))return;
						player->addWork(MANUAL_SUIT);
					}));
					SHOW_DESCRIBE("clothSuit", "clothDescribe", MANUAL_SUIT);
					registerWidget(easyWidget(SG_BUTTON, "clothDown", 250, 120, 50, 50, "羽绒服", [](widget *obj) {
						if (!player->getEnable("workDown"))return;
						player->addWork(MANUAL_DOWN);
					}));
					SHOW_DESCRIBE("clothDown", "clothDescribe", MANUAL_DOWN);
					registerWidget(easyWidget(SG_BUTTON, "clothTrainer", 310, 120, 50, 50, "运动鞋", [](widget *obj) {
						if (!player->getEnable("workTrainer"))return;
						player->addWork(MANUAL_TRAINER);
					}));
					SHOW_DESCRIBE("clothTrainer", "clothDescribe", MANUAL_TRAINER);
					registerWidget(easyWidget(SG_BUTTON, "clothDress", 370, 120, 50, 50, "晚礼服", [](widget *obj) {
						if (!player->getEnable("workDress"))return;
						player->addWork(MANUAL_DRESS);
					}));
					SHOW_DESCRIBE("clothDress", "clothDescribe", MANUAL_DRESS);
					registerWidget(easyWidget(SG_BUTTON, "clothBag", 430, 120, 50, 50, "背包", [](widget *obj) {
						if (!player->getEnable("workBag"))return;
						player->addWork(MANUAL_BAG);
					}));
					SHOW_DESCRIBE("clothBag", "clothDescribe", MANUAL_BAG);
					registerWidget(easyWidget(SG_BUTTON, "clothArmer", 490, 120, 50, 50, "铠甲", [](widget *obj) {
						if (!player->getEnable("workArmer"))return;
						player->addWork(MANUAL_ARMER);
					}));
					SHOW_DESCRIBE("clothArmer", "clothDescribe", MANUAL_ARMER);
					registerWidget(easyWidget(SG_BUTTON, "clothHelmet", 550, 120, 50, 50, "头盔", [](widget *obj) {
						if (!player->getEnable("workHelmet"))return;
						player->addWork(MANUAL_HELMET);
					}));
					SHOW_DESCRIBE("clothHelmet", "clothDescribe", MANUAL_HELMET);
					registerWidget(easyWidget(SG_BUTTON, "clothCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_CLOTH]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("clothQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_CLOTH]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "clothAdd",
						130 + 80 * player->workshops[WORK_CLOTH]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_CLOTH]->queueLen * (WORK_CLOTH + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_CLOTH]->queueLen * (WORK_CLOTH + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("clothQueue") + std::to_string(player->workshops[WORK_CLOTH]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_CLOTH]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_CLOTH]->addQueue()) {
							moveWidget("clothAdd", 80, 0);
							strcpy((char *)getWidgetByName("clothAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_CLOTH]->queueLen * (WORK_CLOTH + 1) * 50) + ")").data());
						}
						else deleteWidget("clothAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("clothCurrent")->content,
						player->workshops[WORK_CLOTH]->currentString(player->clk).data());
					refreshWidget("clothCurrent");
					for (int i = 0; i < player->workshops[WORK_CLOTH]->queueLen; i++) {
						int type = player->workshops[WORK_CLOTH]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("clothQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("clothQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("bakeryQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("clothClothes", "workClothes");
					REFRESH_WORKITEM("clothSweater", "workSweater");
					REFRESH_WORKITEM("clothShoes", "workShoes");
					REFRESH_WORKITEM("clothSuit", "workSuit");
					REFRESH_WORKITEM("clothDown", "workDown");
					REFRESH_WORKITEM("clothTrainer", "workTrainer");
					REFRESH_WORKITEM("clothDress", "workDress");
					REFRESH_WORKITEM("clothBag", "workBag");
					REFRESH_WORKITEM("clothArmer", "workArmer");
					REFRESH_WORKITEM("clothHelmet", "workHelmet");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workConstruct", 10, 650, 360, 60, "建筑工厂\n", [](widget *obj) {
				if (!player->workshops[WORK_CONSTRUCT])return;
				NOREOPEN();
				createWindow(800, 180, "建筑工厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "constructDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "constructStone", 10, 120, 50, 50, "石块", [](widget *obj) {
						if (!player->getEnable("workStone"))return;
						player->addWork(MANUAL_STONE);
					}));
					SHOW_DESCRIBE("constructStone", "constructDescribe", MANUAL_STONE);
					registerWidget(easyWidget(SG_BUTTON, "constructHouse", 70, 120, 50, 50, "平房", [](widget *obj) {
						if (!player->getEnable("workHouse"))return;
						player->addWork(MANUAL_HOUSE);
					}));
					SHOW_DESCRIBE("constructHouse", "constructDescribe", MANUAL_HOUSE);
					registerWidget(easyWidget(SG_BUTTON, "constructVilla", 130, 120, 50, 50, "别墅", [](widget *obj) {
						if (!player->getEnable("workVilla"))return;
						player->addWork(MANUAL_VILLA);
					}));
					SHOW_DESCRIBE("constructVilla", "constructDescribe", MANUAL_VILLA);
					registerWidget(easyWidget(SG_BUTTON, "constructSand", 190, 120, 50, 50, "砂砾", [](widget *obj) {
						if (!player->getEnable("workSand"))return;
						player->addWork(MANUAL_SAND);
					}));
					SHOW_DESCRIBE("constructSand", "constructDescribe", MANUAL_SAND);
					registerWidget(easyWidget(SG_BUTTON, "constructArbor", 250, 120, 50, 50, "凉亭", [](widget *obj) {
						if (!player->getEnable("workArbor"))return;
						player->addWork(MANUAL_ARBOR);
					}));
					SHOW_DESCRIBE("constructArbor", "constructDescribe", MANUAL_ARBOR);
					registerWidget(easyWidget(SG_BUTTON, "constructAsphalt", 310, 120, 50, 50, "沥青", [](widget *obj) {
						if (!player->getEnable("workAsphalt"))return;
						player->addWork(MANUAL_ASPHALT);
					}));
					SHOW_DESCRIBE("constructAsphalt", "constructDescribe", MANUAL_ASPHALT);
					registerWidget(easyWidget(SG_BUTTON, "constructPark", 370, 120, 50, 50, "公园", [](widget *obj) {
						if (!player->getEnable("workPark"))return;
						player->addWork(MANUAL_PARK);
					}));
					SHOW_DESCRIBE("constructPark", "constructDescribe", MANUAL_PARK);
					registerWidget(easyWidget(SG_BUTTON, "constructDepartment", 430, 120, 50, 50, "公寓", [](widget *obj) {
						if (!player->getEnable("workDepartment"))return;
						player->addWork(MANUAL_DEPARTMENT);
					}));
					SHOW_DESCRIBE("constructDepartment", "constructDescribe", MANUAL_DEPARTMENT);
					registerWidget(easyWidget(SG_BUTTON, "constructCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_CONSTRUCT]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("constructQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_CONSTRUCT]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "constructAdd",
						130 + 80 * player->workshops[WORK_CONSTRUCT]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_CONSTRUCT]->queueLen * (WORK_CONSTRUCT + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_CONSTRUCT]->queueLen * (WORK_CONSTRUCT + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("constructQueue") + std::to_string(player->workshops[WORK_CONSTRUCT]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_CONSTRUCT]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_CONSTRUCT]->addQueue()) {
							moveWidget("constructAdd", 80, 0);
							strcpy((char *)getWidgetByName("constructAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_CONSTRUCT]->queueLen * (WORK_CONSTRUCT + 1) * 50) + ")").data());
						}
						else deleteWidget("constructAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("constructCurrent")->content,
						player->workshops[WORK_CONSTRUCT]->currentString(player->clk).data());
					refreshWidget("constructCurrent");
					for (int i = 0; i < player->workshops[WORK_CONSTRUCT]->queueLen; i++) {
						int type = player->workshops[WORK_CONSTRUCT]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("constructQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("constructQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("constructQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("constructStone", "workStone");
					REFRESH_WORKITEM("constructHouse", "workHouse");
					REFRESH_WORKITEM("constructVilla", "workVilla");
					REFRESH_WORKITEM("constructSand", "workSand");
					REFRESH_WORKITEM("constructArbor", "workArbor");
					REFRESH_WORKITEM("constructAsphalt", "workAsphalt");
					REFRESH_WORKITEM("constructPark", "workPark");
					REFRESH_WORKITEM("constructDepartment", "workDepartment");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workMeat", 10, 730, 360, 60, "熟食品加工厂\n", [](widget *obj) {
				if (!player->workshops[WORK_MEAT])return;
				NOREOPEN();
				createWindow(800, 180, "熟食品加工厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "meatDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "meatBacon", 10, 120, 50, 50, "培根", [](widget *obj) {
						if (!player->getEnable("workBacon"))return;
						player->addWork(MANUAL_BACON);
					}));
					SHOW_DESCRIBE("meatBacon", "meatDescribe", MANUAL_BACON);
					registerWidget(easyWidget(SG_BUTTON, "meatBeaf", 70, 120, 50, 50, "牛排", [](widget *obj) {
						if (!player->getEnable("workBeaf"))return;
						player->addWork(MANUAL_BEAF);
					}));
					SHOW_DESCRIBE("meatBeaf", "meatDescribe", MANUAL_BEAF);
					registerWidget(easyWidget(SG_BUTTON, "meatPopcorn", 130, 120, 50, 50, "爆米花", [](widget *obj) {
						if (!player->getEnable("workPopcorn"))return;
						player->addWork(MANUAL_POPCORN);
					}));
					SHOW_DESCRIBE("meatPopcorn", "meatDescribe", MANUAL_POPCORN);
					registerWidget(easyWidget(SG_BUTTON, "meatChocolate", 190, 120, 50, 50, "巧克力", [](widget *obj) {
						if (!player->getEnable("workChocolate"))return;
						player->addWork(MANUAL_CHOCOLATE);
					}));
					SHOW_DESCRIBE("meatChocolate", "meatDescribe", MANUAL_CHOCOLATE);
					registerWidget(easyWidget(SG_BUTTON, "meatIcecream", 250, 120, 50, 50, "冰淇淋", [](widget *obj) {
						if (!player->getEnable("workIcecream"))return;
						player->addWork(MANUAL_ICECREAM);
					}));
					SHOW_DESCRIBE("meatIcecream", "meatDescribe", MANUAL_ICECREAM);
					registerWidget(easyWidget(SG_BUTTON, "meatFruitplate", 310, 120, 50, 50, "鲜果捞", [](widget *obj) {
						if (!player->getEnable("workFruitplate"))return;
						player->addWork(MANUAL_FRUITPLATE);
					}));
					SHOW_DESCRIBE("meatFruitplate", "meatDescribe", MANUAL_FRUITPLATE);
					registerWidget(easyWidget(SG_BUTTON, "meatCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_MEAT]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("meatQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_MEAT]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "meatAdd",
						130 + 80 * player->workshops[WORK_MEAT]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_MEAT]->queueLen * (WORK_MEAT + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_MEAT]->queueLen * (WORK_MEAT + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("meatQueue") + std::to_string(player->workshops[WORK_MEAT]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_MEAT]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_MEAT]->addQueue()) {
							moveWidget("meatAdd", 80, 0);
							strcpy((char *)getWidgetByName("meatAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_MEAT]->queueLen * (WORK_MEAT + 1) * 50) + ")").data());
						}
						else deleteWidget("meatAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("meatCurrent")->content,
						player->workshops[WORK_MEAT]->currentString(player->clk).data());
					refreshWidget("meatCurrent");
					for (int i = 0; i < player->workshops[WORK_MEAT]->queueLen; i++) {
						int type = player->workshops[WORK_MEAT]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("meatQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("meatQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("meatQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("meatBacon", "workBacon");
					REFRESH_WORKITEM("meatBeaf", "workBeaf");
					REFRESH_WORKITEM("meatPopcorn", "workPopcorn");
					REFRESH_WORKITEM("meatChocolate", "workChocolate");
					REFRESH_WORKITEM("meatIcecream", "workIcecream");
					REFRESH_WORKITEM("meatFruitplate", "workFruitplate");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workDecorate", 10, 810, 360, 60, "装饰品作坊\n", [](widget *obj) {
				if (!player->workshops[WORK_DECORATE])return;
				NOREOPEN();
				createWindow(800, 180, "装饰品作坊", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "decorateDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "decorateLantern", 10, 120, 50, 50, "南瓜灯", [](widget *obj) {
						if (!player->getEnable("workLantern"))return;
						player->addWork(MANUAL_LANTERN);
					}));
					SHOW_DESCRIBE("decorateLantern", "decorateDescribe", MANUAL_LANTERN);
					registerWidget(easyWidget(SG_BUTTON, "decorateDoor", 70, 120, 50, 50, "拱门", [](widget *obj) {
						if (!player->getEnable("workDoor"))return;
						player->addWork(MANUAL_DOOR);
					}));
					SHOW_DESCRIBE("decorateDoor", "decorateDescribe", MANUAL_DOOR);
					registerWidget(easyWidget(SG_BUTTON, "decorateBasket", 130, 120, 50, 50, "花篮", [](widget *obj) {
						if (!player->getEnable("workBasket"))return;
						player->addWork(MANUAL_BASKET);
					}));
					SHOW_DESCRIBE("decorateBasket", "decorateDescribe", MANUAL_BASKET);
					registerWidget(easyWidget(SG_BUTTON, "decorateSantatree", 190, 120, 50, 50, "圣诞树", [](widget *obj) {
						if (!player->getEnable("workSantatree"))return;
						player->addWork(MANUAL_SANTATREE);
					}));
					SHOW_DESCRIBE("decorateSantatree", "decorateDescribe", MANUAL_SANTATREE);
					registerWidget(easyWidget(SG_BUTTON, "decorateStatue", 250, 120, 50, 50, "雕像", [](widget *obj) {
						if (!player->getEnable("workStatue"))return;
						player->addWork(MANUAL_STATUE);
					}));
					SHOW_DESCRIBE("decorateStatue", "decorateDescribe", MANUAL_STATUE);
					registerWidget(easyWidget(SG_BUTTON, "decorateCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_DECORATE]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("decorateQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_DECORATE]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "decorateAdd",
						130 + 80 * player->workshops[WORK_DECORATE]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_DECORATE]->queueLen * (WORK_DECORATE + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_DECORATE]->queueLen * (WORK_DECORATE + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("decorateQueue") + std::to_string(player->workshops[WORK_DECORATE]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_DECORATE]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_DECORATE]->addQueue()) {
							moveWidget("decorateAdd", 80, 0);
							strcpy((char *)getWidgetByName("decorateAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_DECORATE]->queueLen * (WORK_DECORATE + 1) * 50) + ")").data());
						}
						else deleteWidget("decorateAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("decorateCurrent")->content,
						player->workshops[WORK_DECORATE]->currentString(player->clk).data());
					refreshWidget("decorateCurrent");
					for (int i = 0; i < player->workshops[WORK_DECORATE]->queueLen; i++) {
						int type = player->workshops[WORK_DECORATE]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("decorateQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("decorateQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("decorateQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("decorateLantern", "workLantern");
					REFRESH_WORKITEM("decorateDoor", "workDoor");
					REFRESH_WORKITEM("decorateBasket", "workBasket");
					REFRESH_WORKITEM("decorateSantatree", "workSantatree");
					REFRESH_WORKITEM("decorateStatue", "workStatue");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workDrink", 10, 890, 360, 60, "饮料厂\n", [](widget *obj) {
				if (!player->workshops[WORK_DRINK])return;
				NOREOPEN();
				createWindow(800, 180, "饮料厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "drinkDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "drinkBeer", 10, 120, 50, 50, "啤酒", [](widget *obj) {
						if (!player->getEnable("workBeer"))return;
						player->addWork(MANUAL_BEER);
					}));
					SHOW_DESCRIBE("drinkBeer", "drinkDescribe", MANUAL_BEER);
					registerWidget(easyWidget(SG_BUTTON, "drinkLamonade", 70, 120, 50, 50, "柠檬水", [](widget *obj) {
						if (!player->getEnable("workLamonade"))return;
						player->addWork(MANUAL_LAMONADE);
					}));
					SHOW_DESCRIBE("drinkLamonade", "drinkDescribe", MANUAL_LAMONADE);
					registerWidget(easyWidget(SG_BUTTON, "drinkMixfruit", 130, 120, 50, 50, "混合果汁", [](widget *obj) {
						if (!player->getEnable("workMixfruit"))return;
						player->addWork(MANUAL_MIXFRUIT);
					}));
					SHOW_DESCRIBE("drinkMixfruit", "drinkDescribe", MANUAL_MIXFRUIT);
					registerWidget(easyWidget(SG_BUTTON, "drinkMelonade", 190, 120, 50, 50, "西瓜汁", [](widget *obj) {
						if (!player->getEnable("workMelonade"))return;
						player->addWork(MANUAL_MELONADE);
					}));
					SHOW_DESCRIBE("drinkMelonade", "drinkDescribe", MANUAL_MELONADE);
					registerWidget(easyWidget(SG_BUTTON, "drinkUscoffee", 250, 120, 50, 50, "美式咖啡", [](widget *obj) {
						if (!player->getEnable("workUscoffee"))return;
						player->addWork(MANUAL_USCOFFEE);
					}));
					SHOW_DESCRIBE("drinkUscoffee", "drinkDescribe", MANUAL_USCOFFEE);
					registerWidget(easyWidget(SG_BUTTON, "drinkMilktea", 310, 120, 50, 50, "奶茶", [](widget *obj) {
						if (!player->getEnable("workMilktea"))return;
						player->addWork(MANUAL_MILKTEA);
					}));
					SHOW_DESCRIBE("drinkMilktea", "drinkDescribe", MANUAL_MILKTEA);
					registerWidget(easyWidget(SG_BUTTON, "drinkCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_DRINK]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("drinkQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_DRINK]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "drinkAdd",
						130 + 80 * player->workshops[WORK_DRINK]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_DRINK]->queueLen * (WORK_DRINK + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_DRINK]->queueLen * (WORK_DRINK + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("drinkQueue") + std::to_string(player->workshops[WORK_DRINK]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_DRINK]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_DRINK]->addQueue()) {
							moveWidget("drinkAdd", 80, 0);
							strcpy((char *)getWidgetByName("drinkAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_DRINK]->queueLen * (WORK_DRINK + 1) * 50) + ")").data());
						}
						else deleteWidget("drinkAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("drinkCurrent")->content,
						player->workshops[WORK_DRINK]->currentString(player->clk).data());
					refreshWidget("drinkCurrent");
					for (int i = 0; i < player->workshops[WORK_DRINK]->queueLen; i++) {
						int type = player->workshops[WORK_DRINK]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("drinkQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("drinkQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("drinkQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("drinkBeer", "workBeer");
					REFRESH_WORKITEM("drinkLamonade", "workLamonade");
					REFRESH_WORKITEM("drinkMixfruit", "workMixfruit");
					REFRESH_WORKITEM("drinkMelonade", "workMelonade");
					REFRESH_WORKITEM("drinkUscoffee", "workUscoffee");
					REFRESH_WORKITEM("drinkMilktea", "workMilktea");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workIndustry", 10, 970, 360, 60, "重工业加工厂\n", [](widget *obj) {
				if (!player->workshops[WORK_INDUSTRY])return;
				NOREOPEN();
				createWindow(800, 180, "重工业加工厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "industryDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "industryCoal", 10, 120, 50, 50, "煤炭", [](widget *obj) {
						if (!player->getEnable("workCoal"))return;
						player->addWork(MANUAL_COAL);
					}));
					SHOW_DESCRIBE("industryCoal", "industryDescribe", MANUAL_COAL);
					registerWidget(easyWidget(SG_BUTTON, "industryPlast", 70, 120, 50, 50, "塑料", [](widget *obj) {
						if (!player->getEnable("workPlast"))return;
						player->addWork(MANUAL_PLAST);
					}));
					SHOW_DESCRIBE("industryPlast", "industryDescribe", MANUAL_PLAST);
					registerWidget(easyWidget(SG_BUTTON, "industryIron", 130, 120, 50, 50, "铁锭", [](widget *obj) {
						if (!player->getEnable("workIron"))return;
						player->addWork(MANUAL_IRON);
					}));
					SHOW_DESCRIBE("industryIron", "industryDescribe", MANUAL_IRON);
					registerWidget(easyWidget(SG_BUTTON, "industryCarbon", 190, 120, 50, 50, "金刚石", [](widget *obj) {
						if (!player->getEnable("workCarbon"))return;
						player->addWork(MANUAL_CARBON);
					}));
					SHOW_DESCRIBE("industryCarbon", "industryDescribe", MANUAL_CARBON);
					registerWidget(easyWidget(SG_BUTTON, "industryGoldbar", 250, 120, 50, 50, "金条", [](widget *obj) {
						if (!player->getEnable("workGoldbar"))return;
						player->addWork(MANUAL_GOLDBAR);
					}));
					SHOW_DESCRIBE("industryGoldbar", "industryDescribe", MANUAL_GOLDBAR);
					registerWidget(easyWidget(SG_BUTTON, "industryRocket", 310, 120, 50, 50, "火箭", [](widget *obj) {
						if (!player->getEnable("workRocket"))return;
						player->addWork(MANUAL_ROCKET);
					}));
					SHOW_DESCRIBE("industryRocket", "industryDescribe", MANUAL_ROCKET);
					registerWidget(easyWidget(SG_BUTTON, "industryCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_INDUSTRY]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("industryQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_INDUSTRY]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "industryAdd",
						130 + 80 * player->workshops[WORK_INDUSTRY]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_INDUSTRY]->queueLen * (WORK_INDUSTRY + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_INDUSTRY]->queueLen * (WORK_INDUSTRY + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("industryQueue") + std::to_string(player->workshops[WORK_INDUSTRY]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_INDUSTRY]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_INDUSTRY]->addQueue()) {
							moveWidget("industryAdd", 80, 0);
							strcpy((char *)getWidgetByName("industryAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_INDUSTRY]->queueLen * (WORK_INDUSTRY + 1) * 50) + ")").data());
						}
						else deleteWidget("industryAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("industryCurrent")->content,
						player->workshops[WORK_INDUSTRY]->currentString(player->clk).data());
					refreshWidget("industryCurrent");
					for (int i = 0; i < player->workshops[WORK_INDUSTRY]->queueLen; i++) {
						int type = player->workshops[WORK_INDUSTRY]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("industryQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("industryQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("industryQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("industryCoal", "workCoal");
					REFRESH_WORKITEM("industryPlast", "workPlast");
					REFRESH_WORKITEM("industryIron", "workIron");
					REFRESH_WORKITEM("industryCarbon", "workCarbon");
					REFRESH_WORKITEM("industryGoldbar", "workGoldbar");
					REFRESH_WORKITEM("industryRocket", "workRocket");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workFire", 10, 1050, 360, 60, "军工厂\n", [](widget *obj) {
				if (!player->workshops[WORK_FIRE])return;
				NOREOPEN();
				createWindow(800, 180, "军工厂", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "fireDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "fireKnife", 10, 120, 50, 50, "匕首", [](widget *obj) {
						if (!player->getEnable("workKnife"))return;
						player->addWork(MANUAL_KNIFE);
					}));
					SHOW_DESCRIBE("fireKnife", "fireDescribe", MANUAL_KNIFE);
					registerWidget(easyWidget(SG_BUTTON, "fireBow", 70, 120, 50, 50, "弓箭", [](widget *obj) {
						if (!player->getEnable("workBow"))return;
						player->addWork(MANUAL_BOW);
					}));
					SHOW_DESCRIBE("fireBow", "fireDescribe", MANUAL_BOW);
					registerWidget(easyWidget(SG_BUTTON, "fireBomb", 130, 120, 50, 50, "手雷", [](widget *obj) {
						if (!player->getEnable("workBomb"))return;
						player->addWork(MANUAL_BOMB);
					}));
					SHOW_DESCRIBE("fireBomb", "fireDescribe", MANUAL_BOMB);
					registerWidget(easyWidget(SG_BUTTON, "firePistol", 190, 120, 50, 50, "手枪", [](widget *obj) {
						if (!player->getEnable("workPistol"))return;
						player->addWork(MANUAL_PISTOL);
					}));
					SHOW_DESCRIBE("firePistol", "fireDescribe", MANUAL_PISTOL);
					registerWidget(easyWidget(SG_BUTTON, "fireAutogun", 250, 120, 50, 50, "冲锋枪", [](widget *obj) {
						if (!player->getEnable("workAutogun"))return;
						player->addWork(MANUAL_AUTOGUN);
					}));
					SHOW_DESCRIBE("fireAutogun", "fireDescribe", MANUAL_AUTOGUN);
					registerWidget(easyWidget(SG_BUTTON, "fireCannon", 310, 120, 50, 50, "意大利炮", [](widget *obj) {
						if (!player->getEnable("workCannon"))return;
						player->addWork(MANUAL_CANNON);
					}));
					SHOW_DESCRIBE("fireCannon", "fireDescribe", MANUAL_CANNON);
					registerWidget(easyWidget(SG_BUTTON, "fireTank", 370, 120, 50, 50, "坦克", [](widget *obj) {
						if (!player->getEnable("workTank"))return;
						player->addWork(MANUAL_TANK);
					}));
					SHOW_DESCRIBE("fireTank", "fireDescribe", MANUAL_TANK);
					registerWidget(easyWidget(SG_BUTTON, "fireCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_FIRE]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("fireQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_FIRE]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "fireAdd",
						130 + 80 * player->workshops[WORK_FIRE]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_FIRE]->queueLen * (WORK_FIRE + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_FIRE]->queueLen * (WORK_FIRE + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("fireQueue") + std::to_string(player->workshops[WORK_FIRE]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_FIRE]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_FIRE]->addQueue()) {
							moveWidget("fireAdd", 80, 0);
							strcpy((char *)getWidgetByName("fireAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_FIRE]->queueLen * (WORK_FIRE + 1) * 50) + ")").data());
						}
						else deleteWidget("fireAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("fireCurrent")->content,
						player->workshops[WORK_FIRE]->currentString(player->clk).data());
					refreshWidget("fireCurrent");
					for (int i = 0; i < player->workshops[WORK_FIRE]->queueLen; i++) {
						int type = player->workshops[WORK_FIRE]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("fireQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("fireQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("fireQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("fireKnife", "workKnife");
					REFRESH_WORKITEM("fireBow", "workBow");
					REFRESH_WORKITEM("fireBomb", "workBomb");
					REFRESH_WORKITEM("firePistol", "workPistol");
					REFRESH_WORKITEM("fireAutogun", "workAutogun");
					REFRESH_WORKITEM("fireCannon", "workCannon");
					REFRESH_WORKITEM("fireTank", "workTank");
				});
			}));
			registerWidget(easyWidget(SG_BUTTON, "workDiamond", 10, 1130, 360, 60, "首饰作坊\n", [](widget *obj) {
				if (!player->workshops[WORK_DIAMOND])return;
				NOREOPEN();
				createWindow(800, 180, "首饰作坊", BIT_MAP, []() {
					windowFinish([]() {
						opened = false;
					});
					registerWidget(easyWidget(SG_OUTPUT, "diamondDescribe", 650, 10, 140, 160, "", [](widget *obj) {}));
					registerWidget(easyWidget(SG_BUTTON, "diamondRing", 10, 120, 50, 50, "钻石戒指", [](widget *obj) {
						if (!player->getEnable("workRing"))return;
						player->addWork(MANUAL_RING);
					}));
					SHOW_DESCRIBE("diamondRing", "diamondDescribe", MANUAL_RING);
					registerWidget(easyWidget(SG_BUTTON, "diamondNecklace", 70, 120, 50, 50, "项链", [](widget *obj) {
						if (!player->getEnable("workNecklace"))return;
						player->addWork(MANUAL_NECKLACE);
					}));
					SHOW_DESCRIBE("diamondNecklace", "diamondDescribe", MANUAL_NECKLACE);
					registerWidget(easyWidget(SG_BUTTON, "diamondBracelet", 130, 120, 50, 50, "手镯", [](widget *obj) {
						if (!player->getEnable("workBracelet"))return;
						player->addWork(MANUAL_BRACELET);
					}));
					SHOW_DESCRIBE("diamondBracelet", "diamondDescribe", MANUAL_BRACELET);
					registerWidget(easyWidget(SG_BUTTON, "diamondEarring", 190, 120, 50, 50, "耳环", [](widget *obj) {
						if (!player->getEnable("workEarring"))return;
						player->addWork(MANUAL_EARRING);
					}));
					SHOW_DESCRIBE("diamondEarring", "diamondDescribe", MANUAL_EARRING);
					registerWidget(easyWidget(SG_BUTTON, "diamondHairpin", 250, 120, 50, 50, "金钗", [](widget *obj) {
						if (!player->getEnable("workHairpin"))return;
						player->addWork(MANUAL_HAIRPIN);
					}));
					SHOW_DESCRIBE("diamondHairpin", "diamondDescribe", MANUAL_HAIRPIN);
					registerWidget(easyWidget(SG_BUTTON, "diamondCurrent", 10, 10, 100, 100, "", [](widget *obj) {}));
					for (int i = 0; i < player->workshops[WORK_DIAMOND]->queueLen; i++) {
						registerWidget(easyWidget(SG_BUTTON, (string("diamondQueue") + std::to_string(i)).data(),
							130 + 80 * i, 40, 70, 70, "", [](widget *obj) {}));
					}
					if (player->workshops[WORK_DIAMOND]->queueLen >= 6)return;
					registerWidget(easyWidget(SG_BUTTON, "diamondAdd",
						130 + 80 * player->workshops[WORK_DIAMOND]->queueLen, 40, 70, 70,
						("+($" + std::to_string(player->workshops[WORK_DIAMOND]->queueLen * (WORK_DIAMOND + 1) * 50) + ")").data(),
						[](widget *obj) {
						if (!player->useCash(player->workshops[WORK_DIAMOND]->queueLen * (WORK_DIAMOND + 1) * 50))return;
						registerWidget(easyWidget(SG_BUTTON,
							(string("diamondQueue") + std::to_string(player->workshops[WORK_DIAMOND]->queueLen)).data(),
							130 + 80 * player->workshops[WORK_DIAMOND]->queueLen, 40, 70, 70, "", NULL));
						if (player->workshops[WORK_DIAMOND]->addQueue()) {
							moveWidget("diamondAdd", 80, 0);
							strcpy((char *)getWidgetByName("diamondAdd")->content,
								("+($" + std::to_string(player->workshops[WORK_DIAMOND]->queueLen * (WORK_DIAMOND + 1) * 50) + ")").data());
						}
						else deleteWidget("diamondAdd");
					}));
				}, []() {
					strcpy((char *)getWidgetByName("diamondCurrent")->content,
						player->workshops[WORK_DIAMOND]->currentString(player->clk).data());
					refreshWidget("diamondCurrent");
					for (int i = 0; i < player->workshops[WORK_DIAMOND]->queueLen; i++) {
						int type = player->workshops[WORK_DIAMOND]->getQueuer(i);
						if (type >= 0) {
							strcpy((char *)getWidgetByName((string("diamondQueue") + std::to_string(i)).data())->content,
								MANUAL_NAME[type].data());
						}
						else {
							strcpy((char *)getWidgetByName((string("diamondQueue") + std::to_string(i)).data())->content,
								"无");
						}
						refreshWidget((string("diamondQueue") + std::to_string(i)).data());
					}

					char *tmp;
					REFRESH_WORKITEM("diamondRing", "workRing");
					REFRESH_WORKITEM("diamondNecklace", "workNecklace");
					REFRESH_WORKITEM("diamondBracelet", "workBracelet");
					REFRESH_WORKITEM("diamondEarring", "workEarring");
					REFRESH_WORKITEM("diamondHairpin", "workHairpin");
				});
			}));

#undef SHOW_DESCRIBE

		}, []() {

#define REFRESH_WORKSHOP(widgetName, idx)\
	tmp = (char *)getWidgetByName(widgetName)->content;\
	if(player->workshops[idx]){\
		current = player->workshops[idx]->getCurrent(); \
		strcpy(tmp, (string(tmp).substr(0, \
			string(tmp).find('\n')) + '\n' + (current == -1 ? \
			"空闲" : MANUAL_NAME[current] + "生产中")).data());\
		rgb color = {0, 0, 0};\
		getWidgetByName(widgetName)->tf.color = color;\
		refreshWidget(widgetName);\
	}\
	else{\
		strcpy(tmp, (string(tmp).substr(0, \
			string(tmp).find('\n')) + '\n' + "未解锁").data());\
		rgb color = {127, 127, 127};\
		getWidgetByName(widgetName)->tf.color = color;\
		refreshWidget(widgetName);\
	}

			int current;
			char *tmp;
			REFRESH_WORKSHOP("workWood", 0);
			REFRESH_WORKSHOP("workBakery", 1);
			REFRESH_WORKSHOP("workFeed", 2);
			REFRESH_WORKSHOP("workMilk", 3);
			REFRESH_WORKSHOP("workFlavor", 4);
			REFRESH_WORKSHOP("workSpin", 5);
			REFRESH_WORKSHOP("workFlower", 6);
			REFRESH_WORKSHOP("workCloth", 7);
			REFRESH_WORKSHOP("workConstruct", 8);
			REFRESH_WORKSHOP("workMeat", 9);
			REFRESH_WORKSHOP("workDecorate", 10);
			REFRESH_WORKSHOP("workDrink", 11);
			REFRESH_WORKSHOP("workIndustry", 12);
			REFRESH_WORKSHOP("workFire", 13);
			REFRESH_WORKSHOP("workDiamond", 14);

#undef REFRESH_WORKSHOP

			if (biosMouse(1).z) {
				vec3i mouse = biosMouse(0);
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
					int previous = getWidgetByName("workScroll")->value;
					int extra = getWidgetByName("workScroll")->extra;
					int value = previous + 20;
					if (value > extra - 1)value = extra - 1;
					getWidgetByName("workScroll")->value = value;
					refreshWidget("workScroll");
					getWidgetByName("workScroll")->drag(NULL, 0, value - previous);
				}
				if (mouse.z == SG_MIDDLE_BUTTON_UP) {
					int previous = getWidgetByName("workScroll")->value;
					int value = previous - 20;
					if (value < 0)value = 0;
					getWidgetByName("workScroll")->value = value;
					refreshWidget("workScroll");
					getWidgetByName("workScroll")->drag(NULL, 0, value - previous);
				}
			}
		});
	}));
	registerWidget(easyWidget(SG_LABEL, "researchLabel", 10, 362, 100, 24, "科研：", NULL));
	registerWidget(easyWidget(SG_LABEL, "researchContent", 100, 362, 200, 24, "空位0 研究0", NULL));
	registerWidget(easyWidget(SG_BUTTON, "researchButton", 300, 360, 100, 24, "详情", [](widget *obj) {
		if (!player->getEnable("research"))return;
		NOREOPEN();
		createWindow(400, 400, "研究院", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_SCROLLVERT, "researchScroll", 380, 0, 20, 400, "", NULL));
			getWidgetByName("researchScroll")->extra = RESEARCH_HEIGHT - 400 + 1;
			getWidgetByName("researchScroll")->drag = [](widget *obj, int x, int y) {
				moveWidget("researchPlant", 0, -y);
				moveWidget("researchWork", 0, -y);
				moveWidget("researchConstruct", 0, -y);
				moveWidget("researchTrade", 0, -y);
				moveWidget("researchWar", 0, -y);
				moveWidget("researchContract", 0, -y);
			};
			refreshWidget("researchScroll");
			registerWidget(easyWidget(SG_BUTTON, "researchPlant", 10, 10, 360, 60, "种植技术", NULL));
			registerWidget(easyWidget(SG_BUTTON, "researchWork", 10, 90, 360, 60, "养殖技术", NULL));
			registerWidget(easyWidget(SG_BUTTON, "researchConstruct", 10, 170, 360, 60, "建设技术", NULL));
			registerWidget(easyWidget(SG_BUTTON, "researchTrade", 10, 250, 360, 60, "战斗技术", NULL));
			registerWidget(easyWidget(SG_BUTTON, "researchWar", 10, 330, 360, 60, "贸易技术", NULL));
		}, []() {
			if (biosMouse(1).z) {
				vec3i mouse = biosMouse(0);
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
					int previous = getWidgetByName("researchScroll")->value;
					int extra = getWidgetByName("researchScroll")->extra;
					int value = previous + 20;
					if (value > extra - 1)value = extra - 1;
					getWidgetByName("researchScroll")->value = value;
					refreshWidget("researchScroll");
					getWidgetByName("researchScroll")->drag(NULL, 0, value - previous);
				}
				if (mouse.z == SG_MIDDLE_BUTTON_UP) {
					int previous = getWidgetByName("researchScroll")->value;
					int value = previous - 20;
					if (value < 0)value = 0;
					getWidgetByName("researchScroll")->value = value;
					refreshWidget("researchScroll");
					getWidgetByName("researchScroll")->drag(NULL, 0, value - previous);
				}
			}
		});
	}));

	registerWidget(easyWidget(SG_BUTTON, "truckIcon", getWidth(SG_CANVAS) - 340, 120, 140, 140, "", [](widget *obj) {
		if (!player->getEnable("truck"))return;
		NOREOPEN();
		createWindow(400, 600, "卡车", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyCombinedWidget("truckList", 0, 0, 0, 0, 0));
			vector<pair<string, pair<map<string, int>, int>>> list = player->truck.getList();
			for (int i = 0; i < list.size(); i++) {
				insertSubWidget("truckList", easyCombinedWidget((string("p") + std::to_string(i)).data(),
					20 + (i % 3) * 120, (i / 3) * 300, 120, 400, 3,
					easyWidget(SG_OUTPUT, "description", 10, 10, 100, 240, "", NULL),
					easyWidget(SG_BUTTON, "submit", 10, 260, 50, 20, "提交", [](widget *obj) {
					bool enough = true;
					auto post = player->truck.getList()[obj->value];
					for (auto p : post.second.first) {
						if (player->getNum(p.first) < p.second) {
							enough = false;
							break;
						}
					}
					if (enough) {
						for (auto p : post.second.first) {
							player->useItem(p.first, p.second);
						}
						player->addCash(post.second.second);
						player->truck.remove(obj->value);
					}
				}),
					easyWidget(SG_BUTTON, "delete", 60, 260, 50, 20, "删除", [](widget *obj) {
					player->truck.remove(obj->value);
				})), INT_MAX);
				getWidgetByName(("truckList/p" + std::to_string(i) + "/submit").data())->value = i;
				getWidgetByName(("truckList/p" + std::to_string(i) + "/delete").data())->value = i;
				refreshWidget(("truckList/p" + std::to_string(i) + "/submit").data());
				refreshWidget(("truckList/p" + std::to_string(i) + "/delete").data());
			}
		}, []() {
			vector<pair<string, pair<map<string, int>, int>>> list = player->truck.getList();
			for (int i = 0; i < list.size(); i++) {
				string text;
				if (list[i].first == "none") {
					text = "空";
				}
				else {
					text = list[i].first + '\n';
					for (auto req : list[i].second.first) {
						text += req.first + ':' +
							std::to_string(req.second) + '(' + std::to_string(player->getNum(req.first)) +')' + '\n';
					}
					text += '$' + std::to_string(list[i].second.second);
				}
				strcpy((char *)getWidgetByName(("truckList/p" + std::to_string(i) + "/description").data())->content, text.data());
				refreshWidget(("truckList/p" + std::to_string(i) + "/description").data());
			}
		});
	}));
	getWidgetByName("truckIcon")->bgImg = loadBmp("source/truck.bmp");
	refreshWidget("truckIcon");
	registerWidget(easyWidget(SG_BUTTON, "trainIcon", getWidth(SG_CANVAS) - 180, 120, 140, 140, "", [](widget *obj){
		if (!player->getEnable("train"))return;
		NOREOPEN();
		createWindow(400, 400, "火车", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_BUTTON, "purchase", 100, 340, 200, 40, "出发", [](widget *obj) {
				int iter = 0;
				int sum = 0;
				while (true) {
					widget *tmp = getWidgetByName(("trainList/p" + std::to_string(iter)).data());
					if (!tmp)break;
					int price = atoi((char *)getWidgetByName(("trainList/p" + std::to_string(iter) + "/price").data())->content + 1);
					int num = atoi((char *)getWidgetByName(("trainList/p" + std::to_string(iter) + "/num").data())->content);
					sum += price * num;
					iter++;
				}
				if (player->useCash(sum)) {
					iter = 0;
					while (true) {
						widget *tmp = getWidgetByName(("trainList/p" + std::to_string(iter)).data());
						if (!tmp)break;
						string name = (char *)getWidgetByName(("trainList/p" + std::to_string(iter) + "/name").data())->content;
						int num = atoi((char *)getWidgetByName(("trainList/p" + std::to_string(iter) + "/num").data())->content);
						player->addItem(name, num);
						iter++;
					}
				}
			}));

			registerWidget(easyCombinedWidget("trainList", 0, 0, 400, 320, 0));
			vector<pair<string, int>> list = player->train.getCurrent();
			for (int i = 0; i < list.size(); i++) {
				insertSubWidget("trainList", easyCombinedWidget((string("p") + std::to_string(i)).data(),
					20 + (i %3) * 120, (i/3) * 80, 120, 80, 5,
					easyWidget(SG_LABEL, "name", 10, 10, 80, 20, list[i].first.data(), NULL),
					easyWidget(SG_LABEL, "price", 10, 30, 80, 20, ("$" + std::to_string(list[i].second)).data(), NULL),
					easyWidget(SG_INPUT, "num", 10, 50, 80, 20, "0", NULL),
					easyWidget(SG_BUTTON, "inc", 100, 10, 20, 30, "+", [](widget *obj) {
						int origin = atoi((char *)getWidgetByName(("trainList/p" + std::to_string(obj->value) + "/num").data())->content);
						origin++;
						strcpy((char *)getWidgetByName(("trainList/p" + std::to_string(obj->value) + "/num").data())->content, std::to_string(origin).data());
						refreshWidget(("trainList/p" + std::to_string(obj->value) + "/num").data());
					}),
					easyWidget(SG_BUTTON, "dec", 100, 40, 20, 30, "-", [](widget *obj) {
						int origin = atoi((char *)getWidgetByName(("trainList/p" + std::to_string(obj->value) + "/num").data())->content);
						if(origin)origin--;
						strcpy((char *)getWidgetByName(("trainList/p" + std::to_string(obj->value) + "/num").data())->content, std::to_string(origin).data());
						refreshWidget(("trainList/p" + std::to_string(obj->value) + "/num").data());
					})), INT_MAX);
				getWidgetByName(("trainList/p" + std::to_string(i) + "/inc").data())->value = i;
				getWidgetByName(("trainList/p" + std::to_string(i) + "/dec").data())->value = i;
				refreshWidget(("trainList/p" + std::to_string(i) + "/inc").data());
				refreshWidget(("trainList/p" + std::to_string(i) + "/dec").data());
			}

		}, []() {});
	}));
	getWidgetByName("trainIcon")->bgImg = loadBmp("source/train.bmp");
	refreshWidget("trainIcon");
	registerWidget(easyWidget(SG_BUTTON, "shipIcon", getWidth(SG_CANVAS) - 340, 260, 140, 140, "", [](widget *obj) {
		if (!player->getEnable("ship"))return;
		NOREOPEN();
		createWindow(400, 400, "轮船", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
		}, []() {});
	}));
	getWidgetByName("shipIcon")->bgImg = loadBmp("source/ship.bmp");
	refreshWidget("shipIcon");
	registerWidget(easyWidget(SG_BUTTON, "planeIcon", getWidth(SG_CANVAS) - 180, 260, 140, 140, "", [](widget *obj) {
		if (!player->getEnable("plane"))return;
		NOREOPEN();
		createWindow(400, 400, "飞机", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
		}, []() {});
	}));
	getWidgetByName("planeIcon")->bgImg = loadBmp("source/plane.bmp");
	refreshWidget("planeIcon");

	registerWidget(easyWidget(SG_BUTTON, "mineIcon", 20, getHeight(SG_CANVAS) - 200, 240, 160, "", [](widget *obj) {
		if (!player->getEnable("mine"))return;
		NOREOPEN();
		createWindow(400, 400, "矿山", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
			mineSetup();
		}, mineLoop);
	}));
	getWidgetByName("mineIcon")->bgImg = loadBmp("source/mine.bmp");
	refreshWidget("mineIcon");
	registerWidget(easyWidget(SG_BUTTON, "towerIcon", 300, getHeight(SG_CANVAS) - 200, 240, 160, "", [](widget *obj) {
		if (!player->getEnable("tower"))return;
		NOREOPEN();
		createWindow(400, 400, "尼尔拉塔", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
			towerSetup();
		}, towerLoop);
	}));
	getWidgetByName("towerIcon")->bgImg = loadBmp("source/tower.bmp");
	refreshWidget("towerIcon");

	registerWidget(easyWidget(SG_BUTTON, "townButton",
		getWidth(SG_CANVAS) - 220, getHeight(SG_CANVAS) - 180, 200, 24, "镇中心", [](widget *obj) {
		if (!player->getEnable("town"))return;
		NOREOPEN();
		static int chose;
		chose = 0;
		createWindow(400, 320, "小镇", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_BUTTON, "townGamble", 10, 10, 380, 60, "赌场", [](widget *obj) {
				chose = 1;
				createWindow(640, 480, "赌场", BIT_MAP, gambleSetup, gambleLoop);
			}));
			registerWidget(easyWidget(SG_BUTTON, "townVideo", 10, 90, 380, 60, "广播电台", [](widget *obj) {
				chose = 1;
			}));
			registerWidget(easyWidget(SG_BUTTON, "townCulture", 10, 170, 380, 60, "文化广场", [](widget *obj) {
				chose = 1;
			}));
			registerWidget(easyWidget(SG_BUTTON, "townStock", 10, 250, 380, 60, "股票交易所", [](widget *obj) {
				chose = 1;
			}));
		}, []() {
			if (chose)closeWindow(-1);
		});
	}));
	registerWidget(easyWidget(SG_BUTTON, "constructButton",
		getWidth(SG_CANVAS) - 220, getHeight(SG_CANVAS) - 140, 200, 24, "基础建设", [](widget *obj) {
		if (!player->getEnable("construct"))return;
		NOREOPEN();
		createWindow(400, 400, "基础建设", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
		}, []() {});
	}));
	registerWidget(easyWidget(SG_BUTTON, "lawButton",
		getWidth(SG_CANVAS) - 220, getHeight(SG_CANVAS) - 100, 200, 24, "法律", [](widget *obj) {
		if (!player->getEnable("law"))return;
		NOREOPEN();
		createWindow(400, 400, "法律", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
		}, []() {});
	}));
	registerWidget(easyWidget(SG_BUTTON, "tourButton",
		getWidth(SG_CANVAS) - 220, getHeight(SG_CANVAS) - 60, 200, 24, "旅游业", [](widget *obj) {
		if (!player->getEnable("tour"))return;
		NOREOPEN();
		createWindow(400, 400, "旅游业", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);
		}, []() {});
	}));
}
void archiveLayin() {
	deleteWidget("newGame1");
	deleteWidget("newGame2");
	deleteWidget("newGame3");
	deleteWidget("newGame4");
	deleteWidget("deleteGame1");
	deleteWidget("deleteGame2");
	deleteWidget("deleteGame3");
	deleteWidget("deleteGame4");
}
void archiveLayout() {
	registerWidget(easyWidget(SG_BUTTON, "newGame1",
		getWidth(SG_CANVAS) / 2 - 380, getHeight(SG_CANVAS) / 2 - 120, 160, 200, "存档1\n空存档", [](widget *obj) {
		archiveLayin();
		gameLayout();
		makePath("存档");
		player = new Player();
		player->load("存档/存档1.sgl");
		status = MS_GAME;
		clearKeyBuffer();
	}));
	if (fileExist("存档/存档1.sgl")) {
		sprintf((char *)getWidgetByName("newGame1")->content, "存档1\n开始");
		refreshWidget("newGame1");
	}
	registerWidget(easyWidget(SG_BUTTON, "deleteGame1",
		getWidth(SG_CANVAS) / 2 - 380, getHeight(SG_CANVAS) / 2 + 100, 160, 40, "删除", [](widget *obj) {
		remove("存档/存档1.sgl");
		sprintf((char *)getWidgetByName("newGame1")->content, "存档1\n空存档");
		refreshWidget("newGame1");
	}));
	registerWidget(easyWidget(SG_BUTTON, "newGame2",
		getWidth(SG_CANVAS) / 2 - 180, getHeight(SG_CANVAS) / 2 - 120, 160, 200, "存档2\n空存档", [](widget *obj) {
		archiveLayin();
		gameLayout();
		makePath("存档");
		player = new Player();
		player->load("存档/存档2.sgl");
		status = MS_GAME;
		clearKeyBuffer();
	}));
	if (fileExist("存档/存档2.sgl")) {
		sprintf((char *)getWidgetByName("newGame2")->content, "存档2\n开始");
		refreshWidget("newGame2");
	}
	registerWidget(easyWidget(SG_BUTTON, "deleteGame2",
		getWidth(SG_CANVAS) / 2 - 180, getHeight(SG_CANVAS) / 2 + 100, 160, 40, "删除", [](widget *obj) {
		remove("存档/存档2.sgl");
		sprintf((char *)getWidgetByName("newGame2")->content, "存档2\n空存档");
		refreshWidget("newGame2");
	}));
	registerWidget(easyWidget(SG_BUTTON, "newGame3",
		getWidth(SG_CANVAS) / 2 + 20, getHeight(SG_CANVAS) / 2 - 120, 160, 200, "存档3\n空存档", [](widget *obj) {
		archiveLayin();
		gameLayout();
		makePath("存档");
		player = new Player();
		player->load("存档/存档3.sgl");
		status = MS_GAME;
		clearKeyBuffer();
	}));
	if (fileExist("存档/存档3.sgl")) {
		sprintf((char *)getWidgetByName("newGame3")->content, "存档3\n开始");
		refreshWidget("newGame3");
	}
	registerWidget(easyWidget(SG_BUTTON, "deleteGame3",
		getWidth(SG_CANVAS) / 2 + 20, getHeight(SG_CANVAS) / 2 + 100, 160, 40, "删除", [](widget *obj) {
		remove("存档/存档3.sgl");
		sprintf((char *)getWidgetByName("newGame3")->content, "存档3\n空存档");
		refreshWidget("newGame3");
	}));
	registerWidget(easyWidget(SG_BUTTON, "newGame4",
		getWidth(SG_CANVAS) / 2 + 220, getHeight(SG_CANVAS) / 2 - 120, 160, 200, "存档4\n空存档", [](widget *obj) {
		archiveLayin();
		gameLayout();
		makePath("存档");
		player = new Player();
		player->load("存档/存档4.sgl");
		status = MS_GAME;
		clearKeyBuffer();
	}));
	if (fileExist("存档/存档4.sgl")) {
		sprintf((char *)getWidgetByName("newGame4")->content, "存档4\n开始");
		refreshWidget("newGame4");
	}
	registerWidget(easyWidget(SG_BUTTON, "deleteGame4",
		getWidth(SG_CANVAS) / 2 + 220, getHeight(SG_CANVAS) / 2 + 100, 160, 40, "删除", [](widget *obj) {
		remove("存档/存档4.sgl");
		sprintf((char *)getWidgetByName("newGame4")->content, "存档4\n空存档");
		refreshWidget("newGame4");
	}));
}
void welcomeLayin() {
	deleteWidget("enterInst");
	deleteWidget("enterGame");
	deleteWidget("exitGame");
}
void welcomeLayout() {
	registerWidget(easyWidget(SG_BUTTON, "enterInst",
		getWidth(SG_CANVAS) / 2 - 120, getHeight(SG_CANVAS) / 2 - 120, 240, 60, "帮 助", [](widget *obj) {
		NOREOPEN();
		createWindow(400, 400, "帮助", BIT_MAP, []() {
			windowFinish([]() {
				opened = false;
			});
			resizeFuntion(NULL);

			registerWidget(easyWidget(SG_OUTPUT, "instContent",20, 20, 360, 360, instruction_text, [](widget *obj) {}));
		}, []() {
			if (biosMouse(1).z) {
				vec3i mouse = biosMouse(0);
				if (mouse.z == SG_MIDDLE_BUTTON_DOWN) {
					int previous = getWidgetByName("instContent")->value;
					int extra = getWidgetByName("instContent")->extra;
					if (extra > 0) {
						int value = previous + 3;
						if (value > extra - 1)value = extra - 1;
						getWidgetByName("instContent")->value = value;
						refreshWidget("instContent");
					}
				}
				if (mouse.z == SG_MIDDLE_BUTTON_UP) {
					int previous = getWidgetByName("instContent")->value;
					int value = previous - 3;
					if (value < 0)value = 0;
					getWidgetByName("instContent")->value = value;
					refreshWidget("instContent");
				}
			}
		});
	}));
	registerWidget(easyWidget(SG_BUTTON, "enterGame",
		getWidth(SG_CANVAS) / 2 - 200, getHeight(SG_CANVAS) / 2, 400, 120, "进 入 游 戏", [](widget *obj) {
		welcomeLayin();
		archiveLayout();
		status = MS_ARCHIVE;
	}));
	getWidgetByName("enterGame")->tf.size = 40;
	refreshWidget("enterGame");
	registerWidget(easyWidget(SG_BUTTON, "exitGame",
		getWidth(SG_CANVAS) - 160, 20, 120, 40, "退出", [](widget *obj) {
		exit(0);
	}));
}

void sgSetup() {
	initWindow(800, 600, "Farm", BIT_MAP);
	resizeFuntion(NULL);

	welcomeLayout();
}
void sgLoop() {
	static int first = 1;
	if (first) {
		first = 0;
		maximizeWindow();
		hideCaption();
	}
	switch (status) {
	case MS_WELCOME:
		break;
	case MS_ARCHIVE:
		break;
	case MS_GAME: 
		if (player->mainLoop()) {
			gameLayin();
			welcomeLayout();
			delete player;
			status = MS_WELCOME;
		}
		break;
	}
}
