#pragma once
#include"Entity.h"
USING_NS_CC;
class NPC :public Entity
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void interact(int mode);
	void changeNpcName(char s[]);
	char* getNpcName();
	void AnimateFrameCache_init();
	CREATE_FUNC(NPC);
protected:
	char NpcName[30];
	SpriteFrameCache* m_frameCache;
};