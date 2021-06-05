#include"Item.h"
#include"cocos2d.h"
#include"Player.h"

USING_NS_CC;
bool Item::init()
{
	return 1;
}
void Item::Interact()
{
	;
}
void Item::update(float dt)
{
	;
}

void Item::bindPlayer(Player* player)
{
	mPlayer = player;
}
void Item::bindScene(Scene* scene)
{
	mScene = scene;
}
void Item::bindMap(BattleMap* map)
{
	mMap = map;
}
void Item::setIsCanSee(bool can)
{
	isCanSee = can;
}
bool Item::isAround()
{
	float Px = mPlayer->getPositionX();
	float Py = mPlayer->getPositionY();
	float x = this->getPositionX();
	float y = this->getPositionY();

	if (sqrt((Px - x) * (Px - x) + (Py - y) * (Py - y)) <= 100)//°ë¾¶100ÂëÒÔÄÚ
		return true;
	else
		return false;
}