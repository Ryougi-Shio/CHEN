#pragma once
#include"Monster.h"
class Ammo;
/*远程怪物
* 根据读入的名字具体化
*/
class RemoteMonster :public Monster
{
public:
	virtual bool init();
	virtual Ammo* MonsterAttack();


	CREATE_FUNC(RemoteMonster);
private:


};