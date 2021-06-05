#pragma once
#include"Entity.h"
USING_NS_CC;
class Player;
class BattleMap;
class Item :public Entity
{
public:
	virtual bool init();
	virtual void Interact();
	virtual void update(float dt);
	bool isAround();	//判断场景里的玩家是否在周围
	void bindScene(Scene* scene);
	void bindMap(BattleMap* map);
	void bindPlayer(Player* player);
	void setIsCanSee(bool can);
	CREATE_FUNC(Item);
protected:
	BattleMap* mMap;
	Scene* mScene;
	Player* mPlayer;
	bool isCanSee = 0;
	bool isUsed=0;
	long startTime = 0;
};