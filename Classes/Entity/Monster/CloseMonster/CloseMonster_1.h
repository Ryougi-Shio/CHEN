#pragma once
#include"Monster.h"
class CloseMonster_1 :public Monster
{
public:
	virtual bool init();
	virtual void rest();
	virtual void rest_flip();
	virtual void run();
	virtual void run_flip();
	virtual void dead();
	virtual void dead_flip();
	CREATE_FUNC(CloseMonster_1);
private:
	
};