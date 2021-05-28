#pragma once
#include"Entity.h"
class Player;
class NormalScene;
USING_NS_CC;
/*
*Gate传送门
* 玩家靠近门时进行响应
* 弹出一个窗口
*   开  始  战  斗
*   【是】  【否】
*/
class Gate :public Entity
{
public:
	virtual bool init();
	virtual void update(float delta);
	bool isAround(float Px,float Py);//检测玩家是否在门周围
	void transferMenu(NormalScene* start, NormalScene* destination);//传送菜单显示，内含两个按钮
	void bindPlayer(Player* mPlayer);
	void bindStart(NormalScene* mScene);
	void bindDestination(NormalScene* mScene);
	NormalScene* getStart();
	NormalScene* getDestination();
	CREATE_FUNC(Gate);
private:
	Player* player;
	NormalScene* start;
	NormalScene* destination;
};