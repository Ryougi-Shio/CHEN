#pragma once
#include"cocos2d.h"
USING_NS_CC;
enum hero_direction
{
	RIGHT_DOWN = 1,
	LEFT_DOWN = 2,
	LEFT_UP = 3,
	RIGHT_UP = 4,
	DOWN = 5,
	LEFT = 6,
	UP = 7,
	RIGHT = 8
};
class Hero :public Node//类hero的定义
{
public:
	int direction;			//人物方向
	Point position;			//人物坐标
	Sprite* sprite;

	void initHeroSprite(int direction, Point position);//人物初始化
	void heroMove(int direction);						//人物移动到
	
	Animate* createAnimate(int direction, const char* action, int num);		//获取动画
	CREATE_FUNC(Hero);
};