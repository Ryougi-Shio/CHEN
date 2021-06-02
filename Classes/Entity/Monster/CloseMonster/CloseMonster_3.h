#pragma once
#include"Monster.h"
class CloseMonster_3 :public Monster
{
public:
	virtual bool init();
	virtual void rest();

	virtual void run();


	virtual void dead();

	CREATE_FUNC(CloseMonster_3);
private:

};