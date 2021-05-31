#include"PistolAmmo.h"
#include"Player/Player.h"
bool PistolAmmo::init()
{
	bindSprite(Sprite::create("Weapon/Ammo/shotgunbullet.png"));
	
	return 1;
}