#pragma once
#include"State_M.h"
class Monster;
//ÒÆ¶¯×´Ì¬£¬ÏòÓÒ
class RunState_M : public State_M
{
public:
	virtual void execute(Monster*monster);
private:

};

//ĞİÏ¢×´Ì¬
class RestState_M :public State_M
{
public:
	virtual void execute(Monster*monster);

private:

};



