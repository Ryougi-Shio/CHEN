#pragma once
#include"cocos2d.h"
class State_M;
class Monster;
USING_NS_CC;
/*
* 动画状态机
* 负责提供怪物动画状态的切换和调用
*/
class MonsterTFSM :public Node
{
public:
	virtual bool init();
	virtual void update(float dt);
	void changeState(State_M* mCurState);
	void bindMonster(Monster* monster);
	State_M* getmCurState();
	CREATE_FUNC(MonsterTFSM);
private:
	State_M* mCurState;
	Monster* mmonster;
};