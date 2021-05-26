#pragma once
#include"Entity.h"
#include"PlayerTFSM/PlayerTFSM.h"
USING_NS_CC;
/*
* 玩家类
* 包含
* 初始化
* 移动
* 动画状态函数（目前只有休息状态）
*/
class Player : public Entity
{
public:
	virtual bool init();
	virtual void update(float delta);
	void rest();//待机动画函数
	void TFSMupdate(float dt);//动画状态机专用update，每0.4f一次调用
	void playerMove();//移动函数
	void startmoveX(float x);
	void startmoveY(float y);
	void stopmoveX();
	void stopmoveY();
	bool getismoveX();
	bool getismoveY();
	float getspeedX();
	float getspeedY();
	CREATE_FUNC(Player);

private:
	PlayerTFSM* TFSM;
	float movespeedX, movespeedY;
	bool ismoveX;
	bool ismoveY;
};
