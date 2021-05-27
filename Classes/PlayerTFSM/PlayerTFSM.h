#pragma once
#include"cocos2d.h"
class State;
class Player;
USING_NS_CC;
/*
* 动画状态机
* 负责提供人物动画状态的切换和调用
*/
class PlayerTFSM :public Node
{
public:
	virtual bool init();
	virtual void update(float dt);
	void changeState(State* mCurState);
	void bindPlayer(Player* player);
	State* getmCurState();
	CREATE_FUNC(PlayerTFSM);
private:
	State* mCurState;
	Player* mplayer;
};