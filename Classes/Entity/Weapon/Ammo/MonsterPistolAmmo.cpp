#include"MonsterPistolAmmo.h"

bool MonsterPistolAmmo::init()
{
	bindSprite(Sprite::create("Weapon/Ammo/monster_bullet_2.png"));

	return 1;
}