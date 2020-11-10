#include "mine.h"
#include "player.h"

extern Player *player;

void mineSetup() {
	registerWidget(easyWidget(SG_LABEL, "level", 20, 20, 160, 40, "�ڲ�", [](widget *obj) {}));
	sprintf((char *)getWidgetByName("level")->content, "��%d��", player->mine.level);
	getWidgetByName("level")->tf.size = 32;
	refreshWidget("level");
	registerWidget(easyWidget(SG_BUTTON, "downstair", 300, 20, 80, 40, "����һ��", [](widget *obj) {}));
	registerWidget(easyWidget(SG_PROCESS, "digging", 100, 100, 200, 100, "���ھ��С�", [](widget *obj) {}));
}
void mineLoop() {

}