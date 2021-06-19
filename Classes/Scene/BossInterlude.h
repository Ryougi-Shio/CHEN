#pragma once
#include"cocos2d.h"
USING_NS_CC;
class Player;
class Monster;
class BossInterlude : public Scene
{
public:
	virtual bool init();
	void playInterlude(Player* _player, Monster* _boss);
	void remove(float dt);
	CREATE_FUNC(BossInterlude);
private:
};