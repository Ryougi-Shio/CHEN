#pragma once
#include"Item.h"
class Statue :public Item
{
public:
	virtual bool init();
	virtual void Interact(int mode);
	virtual void update(float dt);
	virtual void notice(char s[]);
	void setType(int type);
	int getType();
	
	CREATE_FUNC(Statue);
private:
	int StatueType;
	//0 伤害增加
	//1 血量恢复
	//2 金钱增加
};