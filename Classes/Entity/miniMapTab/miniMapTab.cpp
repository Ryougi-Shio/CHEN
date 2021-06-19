#include"miniMapTab.h"
#include"BattleScene1.h"
#include"NormalBattleScene.h"
#include"AllTag.h"
#include"Entity.h"
#include"Monster.h"
#include"MapGate.h"
bool miniMapTab::init()
{	//迷你地图块的初始化
	this->bindSprite(Sprite::create("UI/miniMapTab.png"));
	this->getSprite()->setOpacity(150);
	for (int i = 0; i < 16; i++)
	{
		RoomTab.push_back(Sprite::create("UI/WitheSpot.png"));

		int x = i % 4 - 1;
		int y = i / 4 - 1;
		//位置
		RoomTab.back()->setPositionX((this->getSprite()->getContentSize().width / 4) * (x)-20);
		RoomTab.back()->setPositionY((this->getSprite()->getContentSize().height / 4) * (y)-25);

		this->addChild(RoomTab.back());

	}
	//初始化皆为未访问
	for (int i = 0; i < 16; i++)
	{
		hasVisited[i] = false;
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
	//玩家当前所在地图编号0~15
	int n = mScene->getParentMap()->getNumber();
	if(n!=mScene->getHidRoom())
		hasVisited[n] = true;
	for (int i = 0; i < 16; i++)
	{



		//对于访问过的房间
		if(hasVisited[i] == true)
		{
			removeChild(RoomTab.at(i));
			RoomTab.erase(RoomTab.begin() + i);
			if(i==mScene->getStartRoom())
				RoomTab.insert(RoomTab.begin() + i, Sprite::create("UI/StartSpot.png"));
			else if(i==mScene->getShopRoom())
				RoomTab.insert(RoomTab.begin() + i, Sprite::create("UI/SpecialSpot.png"));
			else if(i == mScene->getBossRoom())
				RoomTab.insert(RoomTab.begin() + i, Sprite::create("UI/BossSpot.png"));
			else
			{
				RoomTab.insert(RoomTab.begin() + i, Sprite::create("UI/WitheSpot.png"));
			}
			if (i == n)//当前人物所在非隐藏房间 高亮提示
			{
				if(i!=mScene->getHidRoom())
					RoomTab.at(i)->setColor(Color3B(255, 255, 255));//白色 
			}
				
			else//其他非隐藏房间 灰色显示
			{
				if (i != mScene->getHidRoom())
					RoomTab.at(i)->setColor(Color3B(128, 138, 135));// 灰色
			}
			//设置图块位置
			int x = i % 4 - 1;
			int y = i / 4 - 1;
			RoomTab.at(i)->setPositionX((this->getSprite()->getContentSize().width / 4) * (x)-20);
			RoomTab.at(i)->setPositionY((this->getSprite()->getContentSize().height / 4) * (y)-25);
			this->addChild(RoomTab.at(i));
		}
		else//如果是没访问过的房间
		{
			//商店房或Boss房更换成其他图标
			if (i == mScene->getShopRoom()|| i == mScene->getBossRoom())
			{
				removeChild(RoomTab.at(i));
				RoomTab.erase(RoomTab.begin() + i);
				if(i == mScene->getShopRoom())
				RoomTab.insert(RoomTab.begin() + i, Sprite::create("UI/SpecialSpot.png"));
				else if(i == mScene->getBossRoom())
					RoomTab.insert(RoomTab.begin() + i, Sprite::create("UI/BossSpot.png"));
				int x = i % 4 - 1;
				int y = i / 4 - 1;

				RoomTab.at(i)->setPositionX((this->getSprite()->getContentSize().width / 4) * (x)-20);
				RoomTab.at(i)->setPositionY((this->getSprite()->getContentSize().height / 4) * (y)-25);
				this->addChild(RoomTab.at(i));
				RoomTab.at(i)->setColor(Color3B(128, 138, 135));// 灰色

			}
		
			else
				RoomTab.at(i)->setColor(Color3B(0, 0, 0));

			RoomTab.at(i)->setOpacity(0);//透明

			

		}


		bool Clean = 1;
		for (int im = 0; im < mScene->getBattleMap().at(n)->getMonster().size(); im++)
		{
			if (mScene->getParentMap()->getMonster().at(im)->getIsDead() == 0)//有怪没死 
				Clean = 0;
		}
		if (Clean)//当前房间清完了，
		{
			for (int i = 0; i < 4; i++)
			{
				//特殊房间可以直接看到，隐藏房间永远不会在地图显示
				if (mScene->getMapGate().at(i)->getAble())
				{
					if (i == 0)
					{
						if (n + 4 != mScene->getHidRoom())
						{
							RoomTab.at(n + 4)->setOpacity(255);
							if (n + 4 == mScene->getShopRoom() || n + 4 == mScene->getBossRoom())
								hasVisited[n + 4] = true;
						}
					
					}

					else if (i == 1)
					{
						if (n - 4 != mScene->getHidRoom())
						{
							RoomTab.at(n - 4)->setOpacity(255);
							if (n - 4 == mScene->getShopRoom() || n - 4 == mScene->getBossRoom())
								hasVisited[n - 4] = true;
						}
						
					}

					else if (i == 2)
					{
						if (n - 1 != mScene->getHidRoom())
						{
							RoomTab.at(n - 1)->setOpacity(255);
							if (n - 1 == mScene->getShopRoom() || n - 1 == mScene->getBossRoom())
								hasVisited[n - 1] = true;
						}
						
					}

					else if (i == 3)
					{
						if (n + 1 != mScene->getHidRoom())
						{
							RoomTab.at(n + 1)->setOpacity(255);
							if (n + 1 == mScene->getShopRoom() || n + 1 == mScene->getBossRoom())
								hasVisited[n + 1] = true;
						}
						
					}

				}
			}
		}
		

	}

}

