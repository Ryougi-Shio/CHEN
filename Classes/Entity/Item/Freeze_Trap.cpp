#include "Freeze_Trap.h"
#include"Player.h"
#include"PlayerMove.h"
#include"BattleMap.h"
#include"PlayerAttribute.h"
bool Freeze_Trap::init()
{
	this->bindSprite(Sprite::create("Items/freeze_trap.png"));
	return true;
}

void Freeze_Trap::Interact(int mode)
{
	isUsed = 1;
	IsTrapping = 1;
	startTime = clock();					//计时器开始
	mPlayer->getplayermove()->setFrozen(1);//玩家状态Frozen开启

	this->scheduleUpdate();

}

void Freeze_Trap::update(float dt)
{
	if (IsTrapping && clock() - startTime > 2000)//2s后解冻
	{
		mPlayer->getplayermove()->setFrozen(0);
		this->unscheduleUpdate();
		this->getSprite()->setOpacity(0);
	}
}

void Freeze_Trap::notice(char s[])
{
}
