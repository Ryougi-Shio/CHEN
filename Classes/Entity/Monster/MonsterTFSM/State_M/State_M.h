#pragma once
#include"Monster.h"
/*
* 基类
* 无实例，无实现
*/
class State_M
{
public:
	virtual void execute(Monster* monster) = 0;
private:	

};