#include"miniMapTab.h"
#include"BattleScene1.h"
#include"NormalBattleScene.h"
#include"AllTag.h"
#include"Entity.h"
#include"Monster.h"
#include"MapGate.h"
bool miniMapTab::init()
{	//�����ͼ��ĳ�ʼ��
	this->bindSprite(Sprite::create("UI/miniMapTab.png"));
	this->getSprite()->setOpacity(150);
	for (int i = 0; i < 16; i++)
	{
		RoomTab.push_back(Sprite::create("UI/WitheSpot.png"));

		int x = i % 4 - 1;
		int y = i / 4 - 1;
		//λ��
		RoomTab.back()->setPositionX((this->getSprite()->getContentSize().width / 4) * (x)-20);
		RoomTab.back()->setPositionY((this->getSprite()->getContentSize().height / 4) * (y)-25);

		this->addChild(RoomTab.back());

	}
	//��ʼ����Ϊδ����
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
	//��ҵ�ǰ���ڵ�ͼ���0~15
	int n = mScene->getParentMap()->getNumber();
	if(n!=mScene->getHidRoom())
		hasVisited[n] = true;
	for (int i = 0; i < 16; i++)
	{



		//���ڷ��ʹ��ķ���
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
			if (i == n)//��ǰ�������ڷ����ط��� ������ʾ
			{
				if(i!=mScene->getHidRoom())
					RoomTab.at(i)->setColor(Color3B(255, 255, 255));//��ɫ 
			}
				
			else//���������ط��� ��ɫ��ʾ
			{
				if (i != mScene->getHidRoom())
					RoomTab.at(i)->setColor(Color3B(128, 138, 135));// ��ɫ
			}
			//����ͼ��λ��
			int x = i % 4 - 1;
			int y = i / 4 - 1;
			RoomTab.at(i)->setPositionX((this->getSprite()->getContentSize().width / 4) * (x)-20);
			RoomTab.at(i)->setPositionY((this->getSprite()->getContentSize().height / 4) * (y)-25);
			this->addChild(RoomTab.at(i));
		}
		else//�����û���ʹ��ķ���
		{
			//�̵귿��Boss������������ͼ��
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
				RoomTab.at(i)->setColor(Color3B(128, 138, 135));// ��ɫ

			}
		
			else
				RoomTab.at(i)->setColor(Color3B(0, 0, 0));

			RoomTab.at(i)->setOpacity(0);//͸��

			

		}


		bool Clean = 1;
		for (int im = 0; im < mScene->getBattleMap().at(n)->getMonster().size(); im++)
		{
			if (mScene->getParentMap()->getMonster().at(im)->getIsDead() == 0)//�й�û�� 
				Clean = 0;
		}
		if (Clean)//��ǰ���������ˣ�
		{
			for (int i = 0; i < 4; i++)
			{
				//���ⷿ�����ֱ�ӿ��������ط�����Զ�����ڵ�ͼ��ʾ
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

