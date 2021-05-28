#pragma once
#include"Entity.h"
#include"PlayerTFSM.h"
#include"PlayerMove.h"
#define NORMAL 2
USING_NS_CC;
/*
* 玩家类
* 包含
* 初始化
* 移动
* 动画状态函数
*/
class Player : public Entity
{
public:
	virtual bool init();
	void rest();//待机动画函数
	void rest_flip();
	void run();//跑步动画函数
	void run_flip();
	void TFSMupdate(float dt);//动画状态机专用update，每0.4f一次调用
	PlayerMove* getplayermove();




	virtual void update(float delta);

	CREATE_FUNC(Player);
	friend class PlayerMove;
private:
	PlayerTFSM* TFSM;
	PlayerMove* PLAYERMOVE;
	int Health;//血量
	int Armor;//护甲
	int Mana;//法力



};
