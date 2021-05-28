#pragma once
#include"cocos2d.h"
class Player;
USING_NS_CC;
/*
* 负责玩家的移动，需绑定一个Player
* Player的update调用这里的移动函数，让update清爽了些？
*/
class PlayerMove:public Node
{
public:
	void bindPlayer(Player* player);//绑定玩家
	void Move();//负责移动的函数
	Player* getPlayer();

	CREATE_FUNC(PlayerMove);
private:
	Player* mPlayer;
};