#pragma once
#include"Item.h"
//Ѫƿ
USING_NS_CC;
class HealingVial :public Item
{
public :
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact(int mode);
	
	CREATE_FUNC(HealingVial);
private:

};