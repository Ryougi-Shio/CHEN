#include"PitchForkAmmo.h"
#include<ctime>
USING_NS_CC;
bool PitchForkAmmo::init()
{

	bindSprite(Sprite::create("Weapon/Ammo/spear_action1.png"));
	Animation* animation = Animation::create();
	for (int i = 1; i <= 5; i++)
	{
		char s[50];
		sprintf(s, "Weapon/Ammo/spear_action%d.png", i);
		animation->addSpriteFrameWithFile(s);
	}
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);

	return 1;
}


