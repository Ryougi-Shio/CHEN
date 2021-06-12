#pragma once
#include"Item.h"
USING_NS_CC;
class Coin :public Item
{
public :
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact(int mode);
	virtual void notice(char s[]);
	CREATE_FUNC(Coin);
private:

};