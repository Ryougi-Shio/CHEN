#include"PistolAmmo.h"

bool PistolAmmo::init()
{
	bindSprite(Sprite::create("Weapon/Ammo/shotgunbullet.png"));
	
	return 1;
}