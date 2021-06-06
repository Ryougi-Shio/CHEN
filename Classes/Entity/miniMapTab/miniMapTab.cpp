#include"miniMapTab.h"
#include"BattleScene1.h"
#include"NormalBattleScene.h"
#include"AllTag.h"
bool miniMapTab::init()
{
	this->bindSprite(Sprite::create("UI/miniMapTab.png"));
	for (int i = 0; i < 9; i++)
	{
		RoomTab.push_back(Sprite::create("UI/WitheSpot.png"));
	
		int x = i % 3 - 1;
		int y = i / 3 - 1;

		RoomTab.back()->setPositionX((this->getSprite()->getContentSize().width / 3) * (x));
		RoomTab.back()->setPositionY((this->getSprite()->getContentSize().height / 3) * (y));

		this->addChild(RoomTab.back());
		if(i==0)
		RoomTab.back()->setTag(MiniMapRoom_TAG);
	}


	this->schedule(CC_SCHEDULE_SELECTOR(miniMapTab::update), 0.1f);
	return 1;
}
void miniMapTab::bindBattleScene(NormalBattleScene* scene)
{
	mScene = scene;
}
void miniMapTab::update(float dt)
{
	
	int n = mScene->getParentMap()->getNumber();//玩家当前所在地图编号0~8
	for (int i = 0; i < 9; i++)
	{
		if(i==n)
			RoomTab.at(i)->setColor(Color3B(255, 0, 0));
		else
			RoomTab.at(i)->setColor(Color3B(255, 255, 255));
	}

}
