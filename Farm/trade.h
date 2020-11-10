#pragma once
#include "clock.h"
#include <string>
#include <vector>
#include <deque>

#define PURCHASE_TYPES 140
#define TRUCK_HEIGHT 400

static vector<int> PURCHASE_PRICE = {
	10,//小麦
	18,//玉米
	36,//萝卜
	60,//大豆
	102,//甘蔗
	172,//棉花
	96,//土豆
	64,//辣椒
	192,//南瓜
	180,//番茄
	300,//西瓜
	166,//花生
	888,//茶叶
	15,//鸡肉
	40,//牛肉
	82,//猪肉
	74,//羊肉
	280,//鸭肉
	8,//鸡蛋
	14,//牛奶
	60,//蘑菇
	64,//羊毛
	800,//鸭绒
	72,//鱼
	170,//虾
	420,//蟹
	1200,//贝
	12,//苹果
	16,//桃子
	20,//柠檬
	40,//香蕉
	35,//樱桃
	54,//葡萄
	92,//可可
	44,//咖啡
	80,//橡胶
	2,//狗尾草
	7,//蒲公英
	18,//玫瑰
	16,//兰花
	88,//郁金香
	110,//薰衣草
	192,//茉莉
	1320,//金银花
	4,//木柴
	28,//木棚
	3,//锄头
	5,//木板
	22,//纸
	142,//木筏
	10,//面粉
	22,//面包
	15,//饼干
	32,//泡芙
	168,//蛋糕
	180,//披萨
	220,//土豆粉
	104,//水果派
	12,//鸡饲料
	19,//牛饲料
	53,//猪饲料
	42,//羊饲料
	60,//鸭饲料
	18,//奶油
	70,//奶酪
	34,//黄油
	148,//沙拉酱
	40,//酸奶
	21,//醋
	68,//酱油
	120,//白糖
	510,//糖浆
	72,//辣酱
	200,//番茄酱
	182,//花生酱
	190,//棉布
	98,//毛线
	86,//绷带
	154,//织布
	272,//丝绸
	324,//渔网
	180,//玫瑰束
	36,//盆栽
	320,//混合花束
	600,//香水
	35000,//金银花瓣
	410,//衬衣
	208,//毛衣
	500,//布鞋
	420,//西装
	2800,//羽绒服
	520,//运动鞋
	38400,//晚礼服
	460,//背包
	400,//铠甲
	320,//头盔
	14,//石块
	320,//平房
	600,//别墅
	55,//砂砾
	160,//凉亭
	64,//沥青
	3000,//公园
	4800,//公寓
	62,//培根
	28,//牛排
	82,//爆米花
	210,//巧克力
	168,//冰淇淋
	174,//鲜果捞
	404,//南瓜灯
	1200,//拱门
	1040,//花篮
	36000,//圣诞树
	98,//雕像
	80,//啤酒
	176,//柠檬水
	150,//混合果汁
	640,//西瓜汁
	188,//美式咖啡
	1080,//奶茶
	40,//煤炭
	90,//塑料
	80,//铁锭
	40,//金刚石
	360000,//金条
	8000000,//火箭
	198,//匕首
	84,//弓箭
	330,//手雷
	300,//手枪
	288,//冲锋枪
	648,//意大利炮
	2600,//坦克
	4800,//飞行器
	800,//钻石戒指
	14000,//项链
	212,//手镯
	384000,//耳环
	1200000//金钗
};

using std::vector;
using std::pair;

class Truck {
private:
	vector<pair<string, pair<map<string, int>, int>>> list;
	vector<vector<pair<string, pair<map<string, int>, int>>>> library = {
		{
			{ "这些天麻雀吃坏了我的麦田，我需要小麦。",{ { { "小麦", 40 } }, 240 } },
			{ "我生病了，没有力气下地，希望买一些小麦。",{ { { "小麦", 12 } }, 96 } },
			{ "我的车队途经此地，看到大片麦田，不知是否有卖。",{ { { "小麦", 300 } }, 2460 } },
			{ "你好，今天我们家房子漏雨了，需要一些木柴来修补。",{ { { "木柴", 8 } }, 20 } },
			{ "柴火用完了，现在需要木柴急用，能帮帮我吗？",{ { { "木柴", 4 } }, 8 } },
		},//1
		{
			{ "磨玉米面的时候材料不够了，能帮我一下吗？",{ { { "小麦", 4 },{ "玉米", 8 } }, 156 } },
			{ "我的磨坊被昨天大风吹塌了，急需帮助。",{ { { "木柴", 4 },{ "面粉", 10 } }, 100 } },
			{ "我一天没吃饭了，饥肠辘辘，能否买一些面粉？",{ { { "面粉", 15 } }, 108 } },
			{ "我们刷墙队的浆糊用完了，需要买一些面粉。",{ { { "面粉", 28 } }, 210 } },
			{ "我的车队途经此地，看到大片玉米地，不知是否有卖。",{ { { "玉米", 400 } }, 6000 } },
		},//2
		{
			{ "我闻到香味了，香喷喷的面包哟~",{ { { "面包", 3 } }, 50 } },
			{ "哈喽，我的麦田收割完毕，要盖一座磨坊，请求物资支援。",{ { { "木棚", 2 } }, 44 } },
			{ "在面包中加入玉米粒一定有很好的口感。",{ { { "面包", 2 },{ "玉米", 1 } }, 46 } },
			{ "我的新家要装修，需要大量木头。",{ { { "木柴", 4 },{ "木棚", 1 } }, 35 } },
		},//3
		{
			{ "老八蜜汁小汉堡，面包鸡肉美汁汁！",{ { { "面包", 2 },{ "鸡肉", 1 } }, 44 } },
			{ "早餐店来进货了。",{ { { "面粉", 12 },{ "面包", 6 },{ "鸡蛋", 20 },{ "鸡肉", 4 } }, 360 } },
			{ "开了一家正新鸡排，烤鸡翅炸鸡排鸡肉肠都很美味！",{ { { "鸡肉", 40 } }, 420 } },
			{ "面条厂需要鸡蛋和面粉。",{ { { "鸡蛋", 4 },{ "面粉", 20 } }, 180 } },
		},//4
		{
			{ "我要出门旅游了，需要准备随身干粮。",{ { { "饼干", 10 },{ "面包", 8 } }, 270 } },
			{ "最近阴雨不断，家里的锄头都生锈了，我要买一些新的。",{ { { "锄头", 4 } }, 118 } },
			{ "我要准备一些水煮蛋和饼干当零食。",{ { { "饼干", 6 },{ "鸡蛋", 10 } }, 140 } },
			{ "在吗，我要下地干活了，但是忘了带东西出门。",{ { { "锄头", 1 },{ "面包", 1 } }, 18 } },
		},//5
		{
			{ "帅哥，我今天晚上要来一次牛奶浴，你应该有吧？",{ { { "牛奶", 30 } }, 320 } },
			{ "明天早饭我要吃牛奶泡饼干，求买。",{ { { "牛奶", 2 },{ "饼干", 4 } }, 56 } },
			{ "美国加州牛肉面大王来进货了。",{ { { "面粉", 20 },{ "牛肉", 10 } }, 400 } },
		},//6
		{
			{ "干面包不好吃，我要做一点奶油夹心面包。",{ { { "奶油", 2 },{ "面包", 2 } }, 56 } },
			{ "夹心饼干一直是我最爱吃的零食",{ { { "奶油", 2 },{ "饼干", 4 } }, 70 } },
			{ "你这泡芙看起来很香啊，我买一些回去卖给邻居。",{ { { "泡芙", 40 } }, 780 } },
		},//7
		{
			{ "社区食堂，来采购一些蔬菜。",{ { { "玉米", 10 },{ "萝卜", 20 } }, 610 } },
			{ "我来给我的骆驼买一些食物。",{ { { "萝卜", 30 } }, 720 } },
			{ "我想试试做一些好利来的半熟芝士。",{ { { "奶酪", 2 },{ "面粉", 3 } }, 102 } },
		},//8
		{
			{ "陕西肉夹馍，采购原材料。",{ { { "面粉", 10 },{ "猪肉", 4 } }, 260 } },
			{ "要买一些肉做灌肠。",{ { { "猪肉", 12 } }, 600 } },
			{ "好吃不如饺子，好玩不如…",{ { { "猪肉", 3 },{ "蘑菇", 4 },{ "玉米", 2 },{ "面粉", 6 } }, 340 } },
		},//9
		{
			{ "我的女神官宣了，我真的…",{ { { "醋", 40 } }, 540 } },
			{ "金龙鱼大豆油来进货了。",{ { { "大豆", 300 } }, 1100 } },
			{ "家里做饭要做点醋溜排骨。",{ { { "猪肉", 3 },{ "醋", 1 } }, 160 } },
		},//10
		{
			{ "孩子这次又没及格，我要几根甘蔗，打一顿完了还可以吃。",{ { { "甘蔗", 4 } }, 250 } },
			{ "买一些食材做糖饼。",{ { { "甘蔗", 1 },{ "面粉", 2 } }, 70 } },
			{ "我来打酱油了。",{ { { "酱油", 3 } }, 140 } },
		},//11
		{
			{ "煎牛排要掌握好配料和火候。",{ { { "牛肉", 4 },{ "黄油", 3 } }, 188 } },
			{ "我要自己尝试做一做奶油蛋糕了。",{ { { "面粉", 10 },{ "奶油", 6 },{ "白糖", 5 } }, 480 } },
			{ "你希望看到自己的庄稼变成又白又软的棉花糖吗？",{ { { "白糖", 20 } }, 1400 } },
		},//12
		{
			{ "冬天来了，需要准备棉被了。",{ { { "棉花", 18 } }, 2000 } },
			{ "今天是我生日，马老师能跟我说一句春节快乐吗？",{ { { "蛋糕", 2 } }, 200 } },
			{ "我需要一个贴心小棉袄。",{ { { "棉花", 6 } }, 600 } },
		},//13
		{
			{ "我看到了香喷喷的披萨饼。",{ { { "披萨", 2 } }, 200 } },
			{ "我们需要一些棉布来生产家装用品。",{ { { "棉布", 12 } }, 1500 } },
			{ "你这披萨种类太少了，让我来加工。",{ { { "披萨", 10 } }, 960 } },
		},//14
		{
			{ "今天我们要吃黄焖鸡。",{ { { "鸡肉", 2 },{ "土豆", 3 } }, 172 } },
			{ "这么大的鱼呀，卖给我回去做鱼汤行吗？",{ { { "鱼", 5 } }, 208 } },
			{ "麦当劳来进货，汉堡和薯条没原料了。",{ { { "土豆", 18 },{ "面包", 10 },{ "鸡肉", 4 } }, 1080 } },
		},//15
	};

public:
	Truck() {}

	vector<pair<string, pair<map<string, int>, int>>> getList() {
		return list;
	}
	pair<string, pair<map<string, int>, int>> refresh(int level) {
		vector<pair<string, pair<map<string, int>, int>>> tmp;
		for (int i = 0; i < level; i++) {
			if (i >= library.size())break;
			tmp.insert(tmp.end(), library[i].begin(), library[i].end());
		}
		return tmp[random(tmp.size())];
	}
	void addItem(string description, int price, map<string, int>post) {
		list.push_back({ description, { post, price} });
	}
	void addItem(int level) {
		list.push_back(refresh(level));
	}
	void remove(int pos) {
		list[pos] = { "none", {{}, 0} };
	}
	void overnight(int level) {
		for (auto &p : list) {
			if (p.first == "none" && random(4) >= 3)
				p = refresh(level);
		}
	}
};
class Train {
private:
	vector<pair<string, float>> list;
	vector<pair<string, int>> current;
public:
	void addItem(string name, float prob) {
		list.push_back(pair<string, float>(name, prob));
	}
	vector<pair<string, float>> getList() {
		return list;
	}
	void addCurrent(string name, int price) {
		current.push_back(pair<string, int>(name, price));
	}
	vector<pair<string, int>> getCurrent() {
		return current;
	}
	void refreshList() {
		current.clear();
		float together = 0.f;
		for (auto p : list) {
			together += p.second;
		}
		for (int i = 0; i < 12; i++) {
			float r = together * random(RAND_MAX) / RAND_MAX;
			int idx = 0;
			for (auto p : list) {
				if (r < p.second) {
					current.push_back(pair<string, int>(p.first, PURCHASE_PRICE[idx]));
					break;
				}
				else {
					r -= p.second;
					idx++;
					continue;
				}
			}
		}
	}
};
class Ship {

};
class Plane {

};
