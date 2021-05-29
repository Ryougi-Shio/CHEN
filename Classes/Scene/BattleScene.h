#pragma once
#include"NormalScene.h"
#include"Player.h"
#include"Gate.h"
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
	CREATE_FUNC(BattleScene);
private:
	TMXTiledMap* map;
	Player* player;
	Gate* safeGate;
};