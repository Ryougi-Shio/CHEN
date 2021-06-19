#include"Sword.h"
#include"Player/Player.h"
#include"SwordAmmo.h"
#include"AllTag.h"
#define PI 3.1415926;


bool Sword::init()
{
	notice(" ");
	bindSprite(Sprite::create("Weapon/sword_1.png"));
	setWeaponSpeed(800);
	this->setTag(AllTag::PlayerWeapon_Sword_TAG);
	return 1;
}

Ammo* Sword::Attack()
{
	return SwordAmmo::create();
}
void Sword::update(float dt)
{
	if (getPlayer()->getIsFlip())
	{

		getSprite()->setFlippedX(1);
		setPositionX(-getPlayer()->getSprite()->getContentSize().width);
	}
	else
	{
		getSprite()->setFlippedX(0);
		setPositionX(getPlayer()->getSprite()->getContentSize().width);
	}
	
	if (getPlayer()->getMouseLocation().y >= getPlayer()->getPositionY())
		setPositionY(-getPlayer()->getSprite()->getContentSize().height * 0.5);
	else
		setPositionY(-getPlayer()->getSprite()->getContentSize().height * 0.1);

		
}