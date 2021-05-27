#pragma once
#include"State.h"
class Player;
//ÒÆ¶¯×´Ì¬
class RunState : public State
{
public:
	virtual void execute(Player* player);
private:

};

class RunState_Flip : public State
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
class RestState_Flip :public State
{
public:
	virtual void execute(Player* player);

private:

};


