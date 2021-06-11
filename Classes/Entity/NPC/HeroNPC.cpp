#include "HeroNPC.h"

bool HeroNPC::init()
{
	if (strlen(NpcName) == 0)
	{
		changeNpcName("knight");
	}
	char s[40];
	sprintf(s, "Player/%s_rest1.png", NpcName);
	bindSprite(Sprite::create(s));
	this->scheduleUpdate();
	AnimateFrameCache_init();
	return true;
}

void HeroNPC::update(float dt)
{

}

void HeroNPC::interact(int mode)
{
	if (mode == 0)
	{
		changeNpcName("knight");


	}
	else if (mode == 1)
	{
		changeNpcName("ranger");

	}		
	this->removeAllChildren();
	char s[40];
	sprintf(s, "Player/%s_rest1.png", NpcName);
	bindSprite(Sprite::create(s));
	AnimateFrameCache_init();
}


