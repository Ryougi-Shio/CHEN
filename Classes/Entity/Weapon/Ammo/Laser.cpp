#include "Laser.h"

bool Laser::init()
{
	bindSprite(Sprite::create("Weapon/Ammo/Laser.png"));

	return 1;
}
