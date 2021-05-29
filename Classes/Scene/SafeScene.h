<<<<<<< main
#pragma once
#include"NormalScene.h"
#include"Player.h"
#include"Gate.h"
USING_NS_CC;
/*
* ��
* ��
* ������
* ���
*/
class SafeScene : public NormalScene
{
public:
	
	virtual bool init();
	virtual void update(float dt);
	bool isWall(float Px, float Py);
	CREATE_FUNC(SafeScene);
private:
	TMXTiledMap* map;
	Player* player;
	Gate* safeGate;
};
=======

>>>>>>> main

