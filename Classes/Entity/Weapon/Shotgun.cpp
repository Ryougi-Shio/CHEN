#include"Shotgun.h"
#include"Player/Player.h"
#include<cmath>
#include"PistolAmmo.h"
#include"AllTag.h"
#define PI 3.14159


bool Shotgun::init()
{
	bindSprite(Sprite::create("Weapon/Shotgun.png"));
	this->setTag(AllTag::PlayerWeapon_Shotgun_TAG);
	setWeaponSpeed(1000);
	return 1;
}

Ammo* Shotgun::Attack()
{
	return PistolAmmo::create();
}
void Shotgun::update(float dt)
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

