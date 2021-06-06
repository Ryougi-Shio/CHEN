#pragma once
#include"Entity.h"
class NormalBattleScene;
USING_NS_CC;
class miniMapTab :public Entity
{
public:
	virtual bool init();
	virtual void update(float dt);

	void bindBattleScene(NormalBattleScene*scene);
	CREATE_FUNC(miniMapTab);
private:
	NormalBattleScene* mScene;
	std::vector<Sprite*> RoomTab;
	int x;
	int y;
};