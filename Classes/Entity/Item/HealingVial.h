#pragma once
#include"Item.h"
//血瓶
USING_NS_CC;
class HealingVial :public Item
{
public :
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact(int mode);
	virtual void notice(char s[]);
	CREATE_FUNC(HealingVial);
private:

};