#pragma once
#include "winsgl.h"

class DexManager {
private:

public:
	DexManager() {}
};
class BillionairManager {
private:

public:
	BillionairManager() {}
};

void gambleLayout();
void dexLayin() {
	deleteWidget("dexStart");
	deleteWidget("dexQuit");
}
void dexLayout() {
	registerWidget(easyWidget(SG_BUTTON, "dexStart", 20, 20, 160, 60, "重新开始", [](widget *obj) {

	}));
	registerWidget(easyWidget(SG_BUTTON, "dexQuit", 560, 20, 60, 20, "退出", [](widget *obj) {
		dexLayin();
		gambleLayout();
	}));
}
void billionairLayin() {
	deleteWidget("billionairStart");
	deleteWidget("billionairQuit");
}
void billionairLayout() {
	registerWidget(easyWidget(SG_BUTTON, "billionairStart", 20, 20, 160, 60, "重新开始", [](widget *obj) {

	}));
	registerWidget(easyWidget(SG_BUTTON, "billionairQuit", 560, 20, 60, 20, "退出", [](widget *obj) {
		billionairLayin();
		gambleLayout();
	}));
}
void gambleLayin() {
	deleteWidget("dex");
	deleteWidget("billionair");
}
void gambleLayout() {
	registerWidget(easyWidget(SG_BUTTON, "dex", 40, 40, 560, 160, "德州扑克", [](widget *obj) {
		gambleLayin();
		dexLayout();
	}));
	registerWidget(easyWidget(SG_BUTTON, "billionair", 40, 280, 560, 160, "大富翁", [](widget *obj) {
		gambleLayin();
		billionairLayout();
	}));
}


auto gambleSetup = []() {
	gambleLayout();
};
auto gambleLoop = []() {

};