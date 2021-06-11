#include"SwordAmmo.h"
#include<ctime>
USING_NS_CC;
bool SwordAmmo::init()
{

	bindSprite(Sprite::create("Weapon/Ammo/sword_action1.png"));
	Animation* animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "Weapon/Ammo/sword_action%d.png", i);
		animation->addSpriteFrameWithFile(s);
	}
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	return 1;
}


