#pragma once
#include"Monster.h"
#include"MonsterPistolAmmo.h"
class CloseMonster_1 :public Monster
{
public:
	virtual bool init();
	virtual void rest();

	virtual void run();

	virtual void dead();

	MonsterPistolAmmo* MonsterAttack();
	CREATE_FUNC(CloseMonster_1);
private:
	
};