#include"MonsterShockAmmo.h"
bool MonsterShockAmmo::init()
{

	bindSprite(Sprite::create("Weapon/Ammo/shock_1.png"));
	Animation* animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		char s[50];
		sprintf(s, "Weapon/Ammo/shock_%d.png", i);
		animation->addSpriteFrameWithFile(s);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);
	return 1;
}