#pragma once
#include"Monster.h"
class Ammo;
/*远程镭射怪物
* 根据读入的名字具体化
*/
class RemoteMonster_Laser :public Monster
{
public:
	virtual bool init();
	virtual Ammo* MonsterAttack();
	CREATE_FUNC(RemoteMonster_Laser);
private:


};