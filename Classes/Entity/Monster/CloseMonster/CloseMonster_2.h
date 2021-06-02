#pragma once
#include"Monster.h"
class CloseMonster_2 :public Monster
{
public:
	virtual bool init();
	virtual void rest();

	virtual void run();

	virtual void dead();

	CREATE_FUNC(CloseMonster_2);
private:

};