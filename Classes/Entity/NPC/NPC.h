#pragma once
#include"Entity.h"
USING_NS_CC;
class NPC :public Entity
{
public:
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(NPC);
private:

};