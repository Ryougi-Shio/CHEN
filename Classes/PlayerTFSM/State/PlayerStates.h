#pragma once
#include"State.h"
class Player;
//移动状态，向右
class RunState : public State
{
public:
	virtual void execute(Player* player);
private:

};
//移动，向左 Flip意为翻转
class RunState_Flip : public State
{
public:
	virtual void execute(Player* player);
private:

};
//休息状态
class RestState :public State
{
public:
	virtual void execute(Player* player);

private:

};
//休息，向左
class RestState_Flip :public State
{
public:
	virtual void execute(Player* player);

private:

};


