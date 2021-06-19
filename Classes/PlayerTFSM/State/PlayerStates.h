#pragma once
#include"State.h"
class Player;
//ÒÆ¶¯×´Ì¬£¬ÏòÓÒ
class RunState : public State
{
public:
	virtual void execute(Player* player);
private:

};

//ÐÝÏ¢×´Ì¬
class RestState :public State
{
public:
	virtual void execute(Player* player);

private:

};
class FrozenState :public State
{
public:
	virtual void execute(Player* player);

private:

};



