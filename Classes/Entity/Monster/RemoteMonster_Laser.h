#pragma once
#include"Monster.h"
class Ammo;
/*Զ���������
* ���ݶ�������־��廯
*/
class RemoteMonster_Laser :public Monster
{
public:
	virtual bool init();
	virtual Ammo* MonsterAttack();
	CREATE_FUNC(RemoteMonster_Laser);
private:


};