#pragma once
#include"cocos2d.h"
#include"Entity/Entity.h"
/*
* 玩家属性管理类
* 包含
* UI
* HP,护甲，金钱的初始化以及变动
*/
class Player;
USING_NS_CC;
class PlayerAttribute :public Entity
{
public:
	void hpApMoneyinit(int hp, int ap);//初始化三个属性
	virtual bool init();
	int getHp();
	int getAp();
	int getMoney();
	void takeDamage(int damage);//收到伤害
	void ApHealingStart(float dt);//开始恢复护甲
	void ApHealing(float dt);//护甲回复
	void bindPlayer(Player* player);
	virtual void update(float dt);
	CREATE_FUNC(PlayerAttribute);
private:
	static int mhp;
	static int map;
	static int mmoney;
	Player* mplayer;
	bool isDamaged;
	Label* moneyLabel;
	Label* apLabel;
	Label* hpLabel;
	
};
