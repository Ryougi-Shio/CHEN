#include"WeaponManager.h"
#include"AllTag.h"
#include"Player.h"
USING_NS_CC;

bool WeaponManager::getWeapon(Weapon* Weapon1, Weapon* Weapon2)
{

	return 1;
}

void WeaponManager::WeaponSwap()
{
	if (isBagfull())
	{
		Weapon* Weapon_swap = m_player->getWeapon1();
		
		Weapon_sub = Weapon_swap;
	}
}

void WeaponManager::bindPlayer(Player* player)
{
	m_player = player;
}
bool WeaponManager::isBagfull()
{
	if (!Weapon_main && !Weapon_sub)
		return true;
	else
		return false;
}
Weapon* WeaponManager::pickUp(Weapon* Weapon_target)
{
	if (isBagfull())
	{
		Weapon* Weapon_swap = Weapon_main;
		Weapon_main = Weapon_target;
		return Weapon_swap;
	}
	else
	{
		Weapon_sub = Weapon_main;
		Weapon_main = Weapon_target;
		return NULL;
	};
}