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
	bool isAround(int Range);	//判断场景里的玩家是否在周围
	bool getIsCanSee();//0不可见，1可见
	bool getIsUsed();//0不可用，1可用
	void setIsCanSee(bool can);
	void setIsUsed(bool used);
	void bindScene(Scene* scene);
	void bindMap(BattleMap* map);
	void bindPlayer(Player* player);

	CREATE_FUNC(Item);
protected:
	BattleMap* mMap;
	Scene* mScene;
	Player* mPlayer;
	bool isCanSee = 0;
	bool isUsed=0;
	long startTime = 0;
};