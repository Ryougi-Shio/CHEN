#pragma once
#include"Item.h"

USING_NS_CC;
class HealingVial :public Item
{
public :
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact();
	
	CREATE_FUNC(HealingVial);
private:

};