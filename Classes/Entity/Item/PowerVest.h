#pragma once
#include"Item.h"
//力量药水，加伤害
USING_NS_CC;
class PowerVest :public Item
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact(int mode);

	CREATE_FUNC(PowerVest);
private:

};