#pragma once
#include"NormalScene.h"
#include"Entity/Player.h"
#include"Player.h"
#include"Gate.h"
USING_NS_CC;
/*
* źŇ
@@ -14,8 +15,10 @@ class SafeScene : public NormalScene

	virtual bool init();
	virtual void update(float dt);
	bool isWall(float Px, float Py);
	CREATE_FUNC(SafeScene);
private:
	TMXTiledMap* map;
	Player* player;
	Gate* safeGate;
}; 
