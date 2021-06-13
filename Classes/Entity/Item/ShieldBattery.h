#pragma once
#include"Item.h"
//»¤¶Üµç³Ø
USING_NS_CC;
class ShieldBattery :public Item
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact(int mode);
	virtual void notice(char s[]);
	CREATE_FUNC(ShieldBattery);
private:

};