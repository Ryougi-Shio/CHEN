#pragma once
#include"Monster.h"
class Ammo;
class MonsterDashAmmo;
class MonsterShockAmmo;
/*��ս��
* ���ݶ�������־��廯
*/
class CloseMonster :public Monster
{
public:
	virtual bool init();
	virtual Ammo* MonsterAttack();
	virtual void update(float dt);
	void stopAttack();//ֹͣ����

	void DashAttack();	//��ײ����
	void ShockAttack();	//���ع���
	bool isAttack();	//�����Ƿ��ڹ���
	void DashUpdate(float dt);	
	void ShockUpdate(float dt);
	CREATE_FUNC(CloseMonster);
private:

	MonsterDashAmmo* DashAmmo;
	MonsterShockAmmo* ShockAmmo;
};