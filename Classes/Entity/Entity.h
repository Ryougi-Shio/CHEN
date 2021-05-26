#pragma once
#include"cocos2d.h"
USING_NS_CC;
/*
* 基础实体类，不生成实例
* 包含
* 绑定精灵
*/
class Entity : public cocos2d::Node
{
public:
	Sprite* getSprite();
	void bindSprite(Sprite* sprite);
private:
	Sprite* m_sprite;
};