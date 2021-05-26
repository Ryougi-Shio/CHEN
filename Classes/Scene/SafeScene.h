#pragma once
#include"NormalScene.h"
#include"Entity/Player.h"
USING_NS_CC;
/*
* 家
* 包含
* 传送门
* 玩家
*/
class SafeScene : public NormalScene
{
public:
	
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(SafeScene);
private:
	TMXTiledMap* map;
	Player* player;
};