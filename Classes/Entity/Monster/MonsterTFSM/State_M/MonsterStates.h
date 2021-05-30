#pragma once
#include"State_M.h"
class Monster;
//移动状态，向右
class RunState_M : public State_M
{
public:
	virtual void execute(Monster*monster);
private:

};
//移动，向左 Flip意为翻转
class RunState_Flip_M : public State_M
{
public:
	virtual void execute(Monster*monster);
private:

};
//休息状态
class RestState_M :public State_M
{
public:
	virtual void execute(Monster*monster);

private:

};
//休息，向左
class RestState_Flip_M :public State_M
{
public:
	virtual void execute(Monster*monster);

private:

};


