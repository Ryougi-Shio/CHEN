#include"Pistol.h"
#include"Player/Player.h"
#include<cmath>
#include"PistolAmmo.h"
#define PI 3.14159


bool Pistol::init()
{
	bindSprite(Sprite::create("Weapon/Pistol.png"));
	setShootSpeed(0.3f);
	return 1;
}

Ammo* Pistol::Attack()
{
	return PistolAmmo::create();
}
void Pistol::update(float dt)
{
	if (!getIsGround())
	{
		float x = getPlayer()->getMouseLocation().x;
		float y = Director::getInstance()->getVisibleSize().height-getPlayer()->getMouseLocation().y;
		float Px = getPlayer()->getPositionX();
		float Py = getPlayer()->getPositionY();	
		float r = atan((y - Py) / (x - Px))*180/PI;

		if (x <= Px)
			r = 180 + r;

			
		getSprite()->setRotation(-r);
	}
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

