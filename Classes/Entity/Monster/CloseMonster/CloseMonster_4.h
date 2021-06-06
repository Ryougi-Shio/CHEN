#pragma once
#include"Monster.h"
class CloseMonster_4 :public Monster
{
public:
	virtual bool init();
	virtual void rest();

	virtual void run();

	virtual void dead();

	CREATE_FUNC(CloseMonster_4);
private:

};