#pragma once
#include"Entity.h"
#define NORMAL 2
class Weapon;
class PlayerAttribute;
class PlayerTFSM;
class PlayerMove;
USING_NS_CC;
/*
* 玩家类
* 包含
* 初始化
* 移动
* 动画状态函数
* 血量，护甲，金钱管理
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
	PlayerAttribute* getPlayerAttribute();
	PlayerMove* getplayermove();
	virtual void update(float delta);
	void AnimateFrameCache_init();
	void trueMouseMap(EventMouse::MouseButton key);
	void flaseMouseMap(EventMouse::MouseButton key);
	void PistolInit();
	void changeMouseLocation(Vec2 location);
	Vec2 getMouseLocation();
	bool getIsFlip();
	std::map<EventMouse::MouseButton, bool> getMouseMap();
	Weapon* getWeapon1();
	void dead();
	void deadNotice();

	CREATE_FUNC(Player);
	friend class PlayerMove;
private:
	PlayerTFSM* TFSM;
	PlayerMove* PLAYERMOVE;
	PlayerAttribute* playerAttribute;
	SpriteFrameCache* m_frameCache;

	static Weapon* weapon1;
	std::map<EventMouse::MouseButton, bool> mouseMap;
	Vec2 mouseLocation;
};
