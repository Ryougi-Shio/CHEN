#pragma once
#include"Monster.h"
class Ammo;
class MonsterDashAmmo;
class MonsterShockAmmo;
/*近战怪
* 根据读入的名字具体化
*/
class CloseMonster :public Monster
{
public:
	virtual bool init();
	virtual Ammo* MonsterAttack();
	virtual void update(float dt);
	void stopAttack();//停止攻击

	void DashAttack();	//冲撞攻击
	void ShockAttack();	//撼地攻击
	bool isAttack();	//返回是否在攻击
	void DashUpdate(float dt);	
	void ShockUpdate(float dt);
	CREATE_FUNC(CloseMonster);
private:

	MonsterDashAmmo* DashAmmo;
	MonsterShockAmmo* ShockAmmo;
};