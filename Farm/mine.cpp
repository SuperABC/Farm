#include "mine.h"
#include "player.h"

extern Player *player;

void mineSetup() {
	registerWidget(easyWidget(SG_LABEL, "level", 20, 20, 160, 40, "第层", [](widget *obj) {}));
	sprintf((char *)getWidgetByName("level")->content, "第%d层", player->mine.level);
	getWidgetByName("level")->tf.size = 32;
	refreshWidget("level");
	registerWidget(easyWidget(SG_BUTTON, "downstair", 300, 20, 80, 40, "下挖一层", [](widget *obj) {}));
	registerWidget(easyWidget(SG_PROCESS, "digging", 100, 100, 200, 100, "…挖掘中…", [](widget *obj) {}));
}
void mineLoop() {

}