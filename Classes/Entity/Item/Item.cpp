#include"Item.h"
#include"cocos2d.h"
#include"Player.h"
#include"AllTag.h"
#include"BattleMap.h"
USING_NS_CC;
bool Item::init()
{
	return 1;
}
void Item::Interact(int mode)
{
	;
}
void Item::update(float dt)
{
	;
}

void Item::notice(char s[])
{
	;
}

void Item::ChangeNotice(char s[])
{
	noticeLabel->setString(s);
}

void Item::NoticeOnorOff(bool able)
{
	if (noticeLabel != nullptr)
	{
		if (able)
			noticeLabel->setOpacity(255);
		else
			noticeLabel->setOpacity(0);
	}
	
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
bool Item::isAround(int Range)
{
	float Px = mPlayer->getPositionX();
	float Py = mPlayer->getPositionY();
	float x = this->getPositionX();
	float y = this->getPositionY();

	if (sqrt((Px - x) * (Px - x) + (Py - y) * (Py - y)) <= Range)//°ë¾¶100ÂëÒÔÄÚ
		return true;
	else
		return false;
}
bool Item::getIsCanSee()
{
	return isCanSee;
}
bool Item::getIsUsed()
{
	return isUsed;
}
void Item::setIsUsed(bool used)
{
	isUsed = used;
}