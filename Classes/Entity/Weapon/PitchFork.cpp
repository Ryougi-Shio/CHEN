#include"PitchFork.h"
#include"Player/Player.h"
#include"PitchForkAmmo.h"
#include"AllTag.h"
#define PI 3.1415926;


bool PitchFork::init()
{
	notice(" ");
	bindSprite(Sprite::create("Weapon/PitchFork.png"));
	setWeaponSpeed(500);
	this->setTag(AllTag::PlayerWeapn_PitchFork_TAG);
	return 1;
}

Ammo* PitchFork::Attack()
{
	return PitchForkAmmo::create();
}
void PitchFork::update(float dt)
{
	float x = getPlayer()->getMouseLocation().x;
	float y = Director::getInstance()->getVisibleSize().height - getPlayer()->getMouseLocation().y;
	float Px = getPlayer()->getPositionX();
	float Py = getPlayer()->getPositionY();
	float r = atan((y - Py) / (x - Px)) * 180 / PI;

	if (x <= Px)
		r = 180 + r;


	getSprite()->setRotation(-r);
	if (getPlayer()->getIsFlip())
	{
		getSprite()->setFlippedY(1);
		setPositionX(-getPlayer()->getSprite()->getContentSize().width / 2);

	}
	else
	{
		getSprite()->setFlippedY(0);
		setPositionX(getPlayer()->getSprite()->getContentSize().width / 2);
	}
}