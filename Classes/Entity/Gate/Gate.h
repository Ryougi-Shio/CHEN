#pragma once
#include"Entity.h"
class Player;
class NormalScene;
USING_NS_CC;
/*
*Gate传送门
* 玩家靠近门时进行响应
* 提示按E进行传送
* 
*/
class Gate :public Entity
{
public:
	virtual bool init();
	virtual void update(float delta);
	bool isAround(float Px,float Py);//检测玩家是否在门周围
	void bindPlayer(Player* mPlayer);
	void bindStart(NormalScene* mScene);//初始地
	void bindDestination(NormalScene* mScene);//目的地
	void notice();//提示按'E'
	NormalScene* getStart();
	NormalScene* getDestination();
	CREATE_FUNC(Gate);
private:
	Player* player;
	NormalScene* start;
	NormalScene* destination;
	Label* noticeLabel;
	std::string Content;
	bool isOn=0;
};