#pragma once
#include"Entity/Entity.h"
#include"cocos2d.h"
USING_NS_CC;
//近战怪物类
class CloseMonster : public Entity
{
public:
	void move();
	bool isaround(float Px, float Py);//判断玩家是否在附近
	void bindScene(Scene* scene);
	void takingDamage(int damage);//怪物收到伤害
	void iswall();

private:
	int mhp;
	Scene* mscene;
};