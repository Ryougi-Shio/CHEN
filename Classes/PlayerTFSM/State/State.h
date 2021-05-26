#pragma once
#include"Entity/Player.h"
/*
* 基类
* 无实例，无实现
*/
class State
{
public:
	virtual void execute(Player* player) = 0;
private:

};