#pragma once
#include"cocos2d.h"
#define NORMAL 4
class Player;
USING_NS_CC;
/*
* 负责玩家的移动，需绑定一个Player
* 把所有和移动相关的都封在这里面
*/
class PlayerMove:public Node
{
public:

	void bindPlayer(Player* player);//绑定玩家
	void Move();//负责移动的函数
	void playerMove();//进行runAction并改变状态机的函数
	void startmoveX(float x);//改变X方向的速度
	void startmoveY(float y);//改变Y方向的速度
	void stopmoveX();
	void stopmoveY();
	bool getismoveX();
	bool getismoveY();
	float getspeedX();
	float getspeedY();
	float getSpeed();
	bool getIsFlip();

	//判断传入的坐标在地图上对应的点是不是墙壁

	bool isWall(float Px, float Py);
	void bindMap(TMXTiledMap* aMap);
	void TrueKeyCode(EventKeyboard::KeyCode keycode);
	void FalseKeyCode(EventKeyboard::KeyCode keycode);
	std::map<cocos2d::EventKeyboard::KeyCode, bool> getkeyMap();
	void FlipToMouse();
	Player* getPlayer();

	CREATE_FUNC(PlayerMove);
private:
	Player* mPlayer;	//PlayerMove绑的Player
	TMXTiledMap* map;	//PlayerMove绑的地图
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;//存贮键码的状态，按下为true
	float movespeedX, movespeedY;
	float Speed = NORMAL;//速度宏定义可调
	bool ismoveX=0;
	bool ismoveY=0;
	bool isFlip = 0;//记录是否翻转，人物朝向左为0，人物朝向右为1

};