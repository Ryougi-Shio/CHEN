#pragma once
#include"Monster.h"
class Ammo;
/*Զ�̹���
* ���ݶ�������־��廯
*/
class RemoteMonster :public Monster
{
public:
	virtual bool init();
	virtual Ammo* MonsterAttack();
	CREATE_FUNC(RemoteMonster);
private:


};