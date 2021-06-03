#include"Sword.h"
#include"Player/Player.h"
#include"SwordAmmo.h"
#define PI 3.1415926;


bool Sword::init()
{
	bindSprite(Sprite::create("Weapon/sword_1.png"));
	setShootSpeed(0.3f);
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
		setPositionX(-getPlayer()->getSprite()->getContentSize().width / 2);
	}
	else
	{
		getSprite()->setFlippedX(0);
		setPositionX(getPlayer()->getSprite()->getContentSize().width / 2);
	}
	if (getPlayer()->getMouseLocation().y >= getPlayer()->getPositionY())
		setPositionY(5);
	else
		setPositionY(0);


}