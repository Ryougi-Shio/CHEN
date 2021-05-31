#pragma once
#include"NormalScene.h"
#include"Player.h"
#include"Gate.h"
#include"Ammo/PistolAmmo.h"

class CloseMonster_1;

USING_NS_CC;
/*
*ս���ĵ�ͼ
* ����
*���������ͼ����
*�������������
*��ɹؿ�����ִ����Ž�����һ��
*�ɽ������������塢ǿ��ҩ����������Ʒ������
*/
class BattleScene:public NormalScene
{
public:
	virtual bool init();
	virtual void update(float dt);
	void test(float dt);
	void Ammoupdate(float dt);
	bool isWall(float x, float y);
	void DeleteAmmo(float dt);
	bool onContactBegin(PhysicsContact& contact);
	CREATE_FUNC(BattleScene);
private:
	TMXTiledMap* map;
	Gate* safeGate;
	CloseMonster_1* Monster_1;
	std::vector<PistolAmmo*> AmmoList;
};