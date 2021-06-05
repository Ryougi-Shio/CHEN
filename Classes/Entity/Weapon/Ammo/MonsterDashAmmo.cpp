#include"MonsterDashAmmo.h"
bool MonsterDashAmmo::init()
{

	bindSprite(Sprite::create("Weapon/Ammo/effect_dash1.png"));
	Animation* animation = Animation::create();
	for (int i = 1; i <= 3; i++)
	{
		char s[50];
		sprintf(s, "Weapon/Ammo/effect_dash%d.png", i);
		animation->addSpriteFrameWithFile(s);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);
	auto* action = Animate::create(animation);
	this->getSprite()->runAction(action);
	return 1;
}		