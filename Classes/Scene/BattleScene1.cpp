#include"BattleScene1.h"
#include"music/music.h"
#include"Map/BattleMap.h"
#include"Player.h"
#include"PlayerMove.h"
#include"PlayerAttribute.h"
#include"Pistol.h"
#include"PistolAmmo.h"
#include"Monster.h"
#include"RemoteMonster.h"
#include"MonsterDashAmmo.h"
#include"TreasureBoxes.h"
#include"miniMapTab.h"
#include"SafeScene.h"
#include"HealingVial.h"
#include"WeaponManager.h"
#include"Coin.h"
#include"PitchForkAmmo.h"
#include"StartScene.h"
#include"Freeze_Trap.h"
#include"BossInterlude.h"
#include"MenuScene.h"
#include"DieScene.h"
#include"json.h"
#include<direct.h>
#define PI 3.1415926f
static long long SwordEnd;
static long long SwordStart;
static long long PistolEnd;
static long long PistolStart;
static long long MonsterHurt;
//记录上一颗子弹消失和产生的时刻，后续在生成子弹时，需起码与此间隔0.3s
bool BattleScene1::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	char* currentPath;
	currentPath = getcwd(NULL, 0);
	if (level==NULL)
	{
		level=UserDefault::getInstance()->getIntegerForKey("BattleLevel");
		if (!level)
		{
			UserDefault::getInstance()->setIntegerForKey("BattleLevel", 1);
			level=UserDefault::getInstance()->getIntegerForKey("BattleLevel");
			UserDefault::getInstance()->flush();
		}
	}
	if (levelLabel == NULL)
	{
		char s[10];
		sprintf(s, "%d", level);
		levelLabel = Label::createWithTTF(s, "fonts/Marker Felt.ttf", 64);
		levelLabel->setColor(Color3B(255, 255, 255));
		levelLabel->setPosition(visibleSize.width / 2, visibleSize.height - levelLabel->getContentSize().height / 2);
		addChild(levelLabel,3);
	}
	srand((unsigned)time(NULL));//根据时间取随机种子
	
	if (initWithPhysics()) {
		getPhysicsWorld()->setGravity(Vec2::ZERO);
		getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		getPhysicsWorld()->setSubsteps(20);
	}
	Mapinit();
	getmusicManager()->changeMusic("bgm/BattleScene.mp3");
	//设置按钮
	auto settings = MenuItemImage::create("ui/settings.png", "ui/settings.png", [&](Ref* sender) {
		getmusicManager()->effectPlay("effect/button.mp3");
		getmusicManager()->menu(this);
	});
	//位置位于左上角
	settings->setPosition(visibleSize.width - settings->getContentSize().width / 2, visibleSize.height - settings->getContentSize().height / 2);
	//菜单
	auto menu = Menu::create(settings, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 3);

	//玩家创建
	auto physicsBody = PhysicsBody::createBox(Size(40.0f, 40.0f),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	bindPlayer(Player::create());
	getPlayer()->setTag(AllTag::Player_TAG);
	getPlayer()->addComponent(physicsBody);
	getPlayer()->getPhysicsBody()->setCategoryBitmask(0x0010);
	getPlayer()->getPhysicsBody()->setCollisionBitmask(0x0010);
	getPlayer()->getPhysicsBody()->setContactTestBitmask(0x0010);
	getPlayer()->setPosition(64 * 2 + 32, 64 * 2 + 32);
	getPlayer()->getplayermove()->bindMap(parentMap->getBattleMap());//PlayerMove跟这个地图绑定
	getPlayer()->getPlayerAttribute()->setPosition(getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().width / 2,
		visibleSize.height - getPlayer()->getPlayerAttribute()->getSprite()->getContentSize().height / 2);//属性UI位置设置
	this->addChild(getPlayer()->getPlayerAttribute(), 4);
	this->addChild(getPlayer(), 2);
	//宝箱创建,血瓶创建
	if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
	{
		parentMap->BoxInit();
		parentMap->getBox().back()->bindScene(this);
		parentMap->BoxCreate();
		int i = rand() % 3 + 1;
		parentMap->getBox().back()->BoxBirth(i);

		parentMap->ItemInit();//宝箱里的物品创建
		parentMap->getItems().back()->bindScene(this);
		parentMap->ItemCreate();

		parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);
	}
	else if (parentMap->getBattleMap()->getTag() == BossRoom_TAG)
	{
		for (int i = 1; i <= 3; i++)
		{
			parentMap->BoxInit();
			parentMap->getBox().back()->bindScene(this);
			parentMap->BoxCreate();
			parentMap->getBox().back()->BoxBirth(i);

			parentMap->ItemInit();//宝箱里的物品创建
			parentMap->getItems().back()->bindScene(this);
			parentMap->ItemCreate();
			
		}
		parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::ItemInBoxUpdate), 0.1f);


	}
	if (parentMap->getBattleMap()->getTag() == ShopRoom_TAG)
	{
		parentMap->getWeapon()->bindPlayer(getPlayer());
	}

	if (parentMap->getBattleMap()->getTag() != BossRoom_TAG)
	{
		parentMap->DropsInit();//打怪的掉落物
		for (int i = 0; i < parentMap->getDrops().size(); i++)
		{
			parentMap->getDrops().at(i)->bindScene(this);
		}
		parentMap->DropsCreate(0);
	
	}	
	parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::DropsUpdate), 0.1f);

	//小地图创建
	MiniMap = miniMapTab::create();
	MiniMap->bindBattleScene(this);
	this->addChild(MiniMap, 10);
	MiniMap->setScale(1);
	MiniMap->setPosition(Vec2(visibleSize.width-MiniMap->getSprite()->getContentSize().width/2
	, MiniMap->getSprite()->getContentSize().height / 2));

	//陷阱创建
	int TrapsNum = rand() % 5 + 1;
	for (int i = 1; i <= TrapsNum; i++)
	{
		parentMap->TrapsInit();
		parentMap->getTraps().back()->bindScene(this);
		parentMap->getTraps().back()->setScale(1.5);
		parentMap->TrapsCreate(i);
		parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::TrapsUpdate), 0.1f);
	}
	//parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::TrapsUpdate), 0.1f);
	//祈祷雕像创建
	if (parentMap->getBattleMap()->getTag()==NormalRoom_TAG)
	{
		if (rand() % 2)
		{
			parentMap->StatueInit();
			parentMap->getStatue().back()->bindScene(this);
			parentMap->StatueCreate();
			parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::StatueUpdate), 0.1f);

		}
			
		

	}
	else if (parentMap->getBattleMap()->getTag() == ShopRoom_TAG)
	{
		parentMap->StatueInit();
		parentMap->getStatue().back()->bindScene(this);
		parentMap->StatueCreate();
		parentMap->schedule(CC_SCHEDULE_SELECTOR(BattleMap::StatueUpdate), 0.1f);
	}
	
	
	////eventlistener,键盘监听，用于移动人物
	auto myKeyListener = EventListenerKeyboard::create();
	myKeyListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘按下时响应
	{
		{
			bool ischeats = 0;
			const std::array < EventKeyboard::KeyCode, 4 > yyds =
			{ EventKeyboard::KeyCode::KEY_Y,EventKeyboard::KeyCode::KEY_Y,EventKeyboard::KeyCode::KEY_D,EventKeyboard::KeyCode::KEY_S };
			std::vector<EventKeyboard::KeyCode> vec;
			if (cheats.size() >= 10)
			{
				cheats.pop();
			}
			cheats.push(keycode);
			for (int i = 0; i < cheats.size(); i++)
			{
				cheats.push(cheats.front());
				vec.push_back(cheats.front());
				cheats.pop();
			}
			if (vec.size() >= yyds.size())
			{
				for (int i = 0; i < vec.size(); i++)
				{
					int j;
					if (vec.at(i) == yyds.at(0))
					{
						if ((i + 1) == vec.size())
						{
							break;
						}
						for (j = i + 1; j < vec.size() && (j - i) < yyds.size(); j++)
						{
							if (vec.at(j) == yyds.at(j - i))
							{
								continue;
							}
							else
							{
								break;
							}
						}
						if (j - i == 4)
						{
							ischeats = 1;
							break;
						}
					}
				}
			}
			else
			{
				ischeats = 0;
			}
			if (ischeats)
			{
				int length = cheats.size();
				for (int i = 0; i < length; i++)
				{
					cheats.pop();
				}
				getPlayer()->getPlayerAttribute()->changeAp(9999999);
			}
		}


		getPlayer()->getplayermove()->TrueKeyCode(keycode);//PlayerMove里keyMap的对应键码置true
		if (keycode==EventKeyboard::KeyCode::KEY_E)//按E交互
		{
			bool clear = true;//怪物清完
			for (auto ix : parentMap->getMonster())
			{
				if (!ix->getIsDead())
					clear = false;
			}

			inGate();
			for (int i = 0; i < parentMap->getBox().size(); i++)
			{
				if (parentMap->getBox().at(i)->getIsCanSee())
				{
					if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG
						|| parentMap->getBattleMap()->getTag() == BossRoom_TAG)
						parentMap->getBox().at(i)->Interact(" ");
					else if (parentMap->getBattleMap()->getTag() == ShopRoom_TAG)
						parentMap->getBox().at(i)->Interact("$30");

				}
			
			}	

	//		bool f=parentMap->getWeapon()->getCanUse();
			if (clear&&parentMap->getWeapon()!=nullptr && parentMap->getWeapon()->getCanUse()
				&& parentMap->getWeapon()->getPlayer()!=nullptr && parentMap->getWeapon()->isAround())
			{
				auto PlayerWeapon1Tag = getPlayer()->getWeapon1()->getTag();					
				if ((parentMap->getWeapon()->getIsBought())||(getPlayer()->getPlayerAttribute()->getMoney()>=100
					&& !parentMap->getWeapon()->getIsBought()) )
				{
					parentMap->getWeapon()->NoticeOnorOff(0);
					if (getPlayer()->pickWeapon(parentMap->getWeapon()->getTag()))
					{

						parentMap->getWeapon()->removeFromParentAndCleanup(0);
						parentMap->WeaponCreate(PlayerWeapon1Tag);
						parentMap->getWeapon()->setPosition(getPlayer()->getPosition());
						parentMap->getWeapon()->bindPlayer(getPlayer());
					}
					else
					{
						parentMap->getWeapon()->removeFromParentAndCleanup(1);
						parentMap->getWeapon()->bindPlayer(nullptr);
					}
					if (parentMap->getWeapon()->getIsBought() == false)
					{
						getPlayer()->getPlayerAttribute()->CutMoney(100);
						parentMap->getWeapon()->setIsBought(true);
					}
						

				}
				
				
			}
		}
		if (keycode == EventKeyboard::KeyCode::KEY_Q)//按Q切换武器
		{
			
			if (getPlayer()->getWeapon2()!=nullptr)
			{
				getPlayer()->swapWeapon();
			}

			

		}
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE)//按空格开技能
		{
			getPlayer()->HeroSkill(0);
		}
	};
	
	myKeyListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event* event)//键盘松开时响应
	{
		getPlayer()->getplayermove()->FalseKeyCode(keycode);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);

	//鼠标监听
	auto myMouseListener = EventListenerMouse::create();
	myMouseListener->onMouseMove = [=](cocos2d::Event* event)//移动
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->changeMouseLocation(e->getLocation());


	};
	myMouseListener->onMouseDown = [=](cocos2d::Event* event)//按下
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->trueMouseMap(e->getMouseButton());

	};
	myMouseListener->onMouseUp = [=](cocos2d::Event* event)//松开
	{
		EventMouse* e = (EventMouse*)event;
		getPlayer()->flaseMouseMap(e->getMouseButton());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene1::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
//	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::test), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::DeleteAmmo), 0.001f);
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::Ammoupdate), 0.01f);//每0.01s检测玩家子弹是否需要生成
	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::AmmoUpdate_Monster), 0.3f);//怪物子弹
	if (parentMap->getBattleMap()->getTag() != HiddenRoom_TAG)
	{
		this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::LandDamageUpdate), 0.5f);//地形伤害
		this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::LandSlowUpdate), 0.01f);//地形减速
		this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::LandBurningUpdate), 0.5f);//地形灼烧
	}

	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene1::PlayerDeatheUpdate), 1.0f);//
	MapGateInit();
	return 1;
}
void BattleScene1::MapGateInit()//地图门的初始化
{
	for (int i = 1; i <= 5; i++)
	{
		m_mapgate.pushBack(MapGate::create());
		m_mapgate.back()->bindPlayer(getPlayer());
		this->addChild(m_mapgate.back(), 5);
		m_mapgate.back()->IsAble(false);//初始默认该门不可用
	}

	//上
	m_mapgate.at(0)->setPosition(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height - m_mapgate.back()->getSprite()->getContentSize().height * 0.5 - 64);
	//下
	m_mapgate.at(1)->setPosition(Director::getInstance()->getVisibleSize().width / 2, m_mapgate.back()->getSprite()->getContentSize().height * 0.5 + 64);

	//左
	m_mapgate.at(2)->setPosition(m_mapgate.back()->getSprite()->getContentSize().width/2+64, Director::getInstance()->getVisibleSize().height / 2);
	//右
	m_mapgate.at(3)->setPosition(Director::getInstance()->getVisibleSize().width- m_mapgate.back()->getSprite()->getContentSize().width / 2-64,
		Director::getInstance()->getVisibleSize().height / 2);
	m_mapgate.at(4)->setPosition(Director::getInstance()->getVisibleSize()/2);//Boos房
}
void BattleScene1::inGate()//进门的判断和传送的实现
{
	for (int i = 0; i < 5; i++)
	{
		if (m_mapgate.at(i)->getAble())//获取该门是否可用
		{
			if (m_mapgate.at(i)->isAround(getPlayer()->getPositionX(), getPlayer()->getPositionY()) )//判断玩家在周围
			{

				MusicManager::effectPlay("effect/tp.mp3");
				switch (i)
				{
				case 0://改变地图并改变玩家位置，即传送
					DeleteAllAmmo();
					changeMap(parentMap->getNumber() + 4);
					getPlayer()->setPosition(Director::getInstance()->getVisibleSize().width / 2, m_mapgate.back()->getSprite()->getContentSize().height * 0.5 + 64);
					break;
				case 1:
					DeleteAllAmmo();
					changeMap(parentMap->getNumber() - 4);
					getPlayer()->setPosition(Director::getInstance()->getVisibleSize().width / 2,
						Director::getInstance()->getVisibleSize().height - m_mapgate.back()->getSprite()->getContentSize().height * 0.5 - 64);
					break;
				case 2:
					DeleteAllAmmo();
					changeMap(parentMap->getNumber() - 1);
					getPlayer()->setPosition(Director::getInstance()->getVisibleSize().width - m_mapgate.back()->getSprite()->getContentSize().width / 2 - 64,
						Director::getInstance()->getVisibleSize().height / 2);
					break;
				case 3:
					DeleteAllAmmo();
					changeMap(parentMap->getNumber() + 1);
					getPlayer()->setPosition(m_mapgate.back()->getSprite()->getContentSize().width / 2 + 64,
						Director::getInstance()->getVisibleSize().height / 2);
					break;
				case 4:
				{
					DeleteAllAmmo();
					char* currentPath;
					currentPath = getcwd(NULL, 0);
					level++;

					UserDefault::getInstance()->setIntegerForKey("BattleLevel", level);
					UserDefault::getInstance()->flush();
					Director::getInstance()->replaceScene(BattleScene1::create());
					break;
				}

				
				default:
					break;
				}
				
				break;


			}
			
		}
	}
}
void BattleScene1::update(float dt)
{
	int able = 1;
	for (int i = 0; i < parentMap->getMonster().size(); i++)
	{
		if (parentMap->getMonster().at(i)->getIsDead()==0)//但凡这张图里有一只怪没死，就置为不可用 able=0
			able = 0;
	}
	int x = parentMap->getNumber()%4+1;
	int y = parentMap->getNumber() / 4+1;
	//初始把四扇门都置为不可用，再依次判断是否开门
	for (int i = 0; i < 5; i++)
	{
		m_mapgate.at(i)->IsAble(0);
	
	}
	//根据地图的编号位置选择传送门的开启，例如最左侧地图不会开左门
	if (x<=3 && m_battleMap.at(parentMap->getNumber()+1)->getName()!="no")
	{
		m_mapgate.at(3)->IsAble(able);
		if (parentMap->getNumber() + 1 == getHidRoom())
		{
			int chaos_1 = rand() % 255 + 1;
			int chaos_2 = rand() % 255 + 1;
			int chaos_3 = rand() % 255 + 1;
			m_mapgate.at(3)->getSprite()->setColor(Color3B(chaos_1, chaos_2, chaos_3));
		}
		else
			m_mapgate.at(3)->getSprite()->setColor(Color3B(255, 255, 255));
	}
	if (x>=2 && m_battleMap.at(parentMap->getNumber() - 1)->getName() != "no")
	{
		m_mapgate.at(2)->IsAble(able);
		if (parentMap->getNumber() - 1 == getHidRoom())//隐藏房间，霓虹の传送门
		{
			int chaos_1 = rand() % 255 + 1;
			int chaos_2 = rand() % 255 + 1;
			int chaos_3 = rand() % 255 + 1;
			m_mapgate.at(2)->getSprite()->setColor(Color3B(chaos_1, chaos_2, chaos_3));
		}
		else
			m_mapgate.at(2)->getSprite()->setColor(Color3B(255, 255, 255));
	}
	if (y>=2 && m_battleMap.at(parentMap->getNumber() - 4)->getName() != "no")
	{
		m_mapgate.at(1)->IsAble(able);
		if (parentMap->getNumber() - 4 == getHidRoom())
		{
			int chaos_1 = rand() % 255 + 1;
			int chaos_2 = rand() % 255 + 1;
			int chaos_3 = rand() % 255 + 1;
			m_mapgate.at(1)->getSprite()->setColor(Color3B(chaos_1, chaos_2, chaos_3));
		}
		else
			m_mapgate.at(1)->getSprite()->setColor(Color3B(255, 255, 255));
	}
	if (y<=3 && m_battleMap.at(parentMap->getNumber() + 4)->getName() != "no")
	{
		m_mapgate.at(0)->IsAble(able);
		if (parentMap->getNumber() + 4 == getHidRoom())
		{
			int chaos_1 = rand() % 255 + 1;
			int chaos_2 = rand() % 255 + 1;
			int chaos_3 = rand() % 255 + 1;
			m_mapgate.at(0)->getSprite()->setColor(Color3B(chaos_1, chaos_2, chaos_3));
		}
		else
			m_mapgate.at(0)->getSprite()->setColor(Color3B(255, 255, 255));
	}
	if (parentMap->getNumber() == getBossRoom())
		m_mapgate.at(4)->IsAble(able);
	for (int i = 0; i < parentMap->getBox().size(); i++)
		parentMap->getBox().at(i)->setIsCanSee(able);
}

void BattleScene1::AmmoUpdate_Monster(float dt)
{
	//怪物Pistol子弹
	//获取玩家坐标
	float Px = getPlayer()->getPositionX() - getPlayer()->getContentSize().width / 2;
	float Py = getPlayer()->getPositionY() - getPlayer()->getContentSize().height / 2;
	for (int i = 0; i < parentMap->getMonster().size(); i++)
	{
		bool CanShoot = 0;
		float Mx = parentMap->getMonster().at(i)->getPositionX();//获取怪物坐标
		float My = parentMap->getMonster().at(i)->getPositionY();
		Vec2 m = Vec2(Vec2(Px - Mx, Py - My) / sqrt((Px - Mx) * (Px - Mx) + (Py - My) * (Py - My)));
//		CCLOG("%d", parentMap->getMonster().at(i)->getTag());
		if (parentMap->getMonster().at(i)->getIsDead() == 0 && //没死
			parentMap->getMonster().at(i)->CanSee()&&			//看见玩家
			((parentMap->getMonster().at(i)->getTag()==AllTag::O_small_monster_TAG)
			||(parentMap->getMonster().at(i)->getTag() == AllTag::Y_craw_monster_TAG)
				|| parentMap->getMonster().at(i)->getTag()==Chaos_monster_TAG)
			||(parentMap->getMonster().at(i)->getIsDead() == 0 && parentMap->getMonster().at(i)->CanSee()&& parentMap->getMonster().at(i)->getTag() == AllTag::CthulhuEye_Monster_TAG&& parentMap->getMonster().at(i)->getHp()> parentMap->getMonster().at(i)->getMaxHp()/2) )
				
		{
			if (parentMap->getMonster().at(i)->getTag() == AllTag::CthulhuEye_Monster_TAG)
			{
				float Ax, Ay;
				if (parentMap->getMonster().at(i)->getIsFlip() == 0)
				{
					Ax = parentMap->getMonster().at(i)->getPosition().x +
						parentMap->getMonster().at(i)->getSprite()->getContentSize().width;
				}
				else
				{
					Ax = parentMap->getMonster().at(i)->getPosition().x;
				}
				Ay = parentMap->getMonster().at(i)->getPosition().y
					+ parentMap->getMonster().at(i)->getSprite()->getContentSize().height / 2;
				if (Ax<0 || Ax>Director::getInstance()->getVisibleSize().width || Ay<0 || Ay>Director::getInstance()->getVisibleSize().height)
					continue;
			}
			
			m_monsterAmmoList.push_back(parentMap->getMonster().at(i)->MonsterAttack());//生成子弹
			m_monsterAmmoList.back()->start = clock();									//标记出生时间
			m_monsterAmmoList.back()->setTag(AllTag::MonsterAmmo_PistolTAG);
			this->addChild(m_monsterAmmoList.back(), 3);
			auto physicBody = PhysicsBody::createBox(Size(28.0f, 28.0f), PhysicsMaterial(0, 0, 0));//添加刚体
			m_monsterAmmoList.back()->addComponent(physicBody);
			m_monsterAmmoList.back()->getPhysicsBody()->setDynamic(false);
		
			if (parentMap->getMonster().at(i)->getIsFlip() == 0)
				m_monsterAmmoList.back()->setPosition(Vec2(parentMap->getMonster().at(i)->getPosition().x+ 
					parentMap->getMonster().at(i)->getSprite()->getContentSize().width,
					parentMap->getMonster().at(i)->getPosition().y
				+ parentMap->getMonster().at(i)->getSprite()->getContentSize().height/2));
			else
				m_monsterAmmoList.back()->setPosition(Vec2(parentMap->getMonster().at(i)->getPosition().x,
					parentMap->getMonster().at(i)->getPosition().y
					+ parentMap->getMonster().at(i)->getSprite()->getContentSize().height/2));
			

			m_monsterAmmoList.back()->getPhysicsBody()->setVelocity(m * 500);

			m_monsterAmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0010);//掩码，怪物子弹和玩家相同
			m_monsterAmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0010);
			m_monsterAmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0010);
		}
	}
	//怪物Laser子弹
	for (int i = 0; i < parentMap->getMonster().size(); i++)
	{
		bool CanShoot = 0;
		float Mx = parentMap->getMonster().at(i)->getPositionX();//获取怪物坐标
		float My = parentMap->getMonster().at(i)->getPositionY();
		Vec2 m = Vec2(Vec2(Px - Mx, Py - My) / sqrt((Px - Mx) * (Px - Mx) + (Py - My) * (Py - My)));
	
		if (parentMap->getMonster().at(i)->getIsDead() == 0 && //没死
			parentMap->getMonster().at(i)->CanSee() &&			//看见玩家
			((parentMap->getMonster().at(i)->getTag() == AllTag::LittleEye_monster_TAG)))
				
		{

			m_monsterAmmoList.push_back(parentMap->getMonster().at(i)->MonsterAttack());//生成子弹
			m_monsterAmmoList.back()->start = clock();									//标记出生时间
			m_monsterAmmoList.back()->setTag(AllTag::MonsterAmmo_PistolTAG);
			this->addChild(m_monsterAmmoList.back(), 3);
			auto physicBody = PhysicsBody::createBox(Size(2.0f, 40.0f), PhysicsMaterial(0, 0, 0));//添加刚体
			m_monsterAmmoList.back()->addComponent(physicBody);
			m_monsterAmmoList.back()->getPhysicsBody()->setDynamic(false);

			if (parentMap->getMonster().at(i)->getIsFlip() == 0)
				m_monsterAmmoList.back()->setPosition(Vec2(parentMap->getMonster().at(i)->getPosition().x +
					parentMap->getMonster().at(i)->getSprite()->getContentSize().width,
					parentMap->getMonster().at(i)->getPosition().y
					+ parentMap->getMonster().at(i)->getSprite()->getContentSize().height / 2));
			else
				m_monsterAmmoList.back()->setPosition(Vec2(parentMap->getMonster().at(i)->getPosition().x,
					parentMap->getMonster().at(i)->getPosition().y
					+ parentMap->getMonster().at(i)->getSprite()->getContentSize().height / 2));


			m_monsterAmmoList.back()->getPhysicsBody()->setVelocity(m * 500);

			float angele;
			angele = atan(m.x/m.y) * 180 / PI;
			m_monsterAmmoList.back()->setRotation(angele);

			/*
				float x = getPlayer()->getMouseLocation().x;
				float y = Director::getInstance()->getVisibleSize().height-getPlayer()->getMouseLocation().y;
				float Px = getPlayer()->getPositionX();
				float Py = getPlayer()->getPositionY();	
				float r = atan((y - Py) / (x - Px))*180/PI;

					if (x <= Px)
							r = 180 + r;

		
	getSprite()->setRotation(-r);*/

			m_monsterAmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0010);//掩码，怪物子弹和玩家相同
			m_monsterAmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0010);
			m_monsterAmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0010);
		}
	}
	if (parentMap->getMonster().size()&&parentMap->getMonster().back()->getTag() == Chaos_monster_TAG)
	{
		for (auto ix : m_monsterAmmoList)
		{
			int chaos_1 = rand() % 255 + 1;
			int chaos_2 = rand() % 255 + 1;
			int chaos_3 = rand() % 255 + 1;
			ix->getSprite()->setColor(Color3B(chaos_1, chaos_2, chaos_3));
		}
	}
}
//玩家子弹的生成
void BattleScene1::Ammoupdate(float dt)
{
	if (getPlayer()->getplayermove()->getIsFrozen() == 0)
	{
		float x = getPlayer()->getMouseLocation().x;
		float y = Director::getInstance()->getVisibleSize().height - getPlayer()->getMouseLocation().y;
		float Px = getPlayer()->getPositionX() - getPlayer()->getContentSize().width / 2;
		float Py = getPlayer()->getPositionY() - getPlayer()->getContentSize().height / 2;
		float Wx = (Px + getPlayer()->getWeapon1()->getPositionX() + getPlayer()->getWeapon1()->getContentSize().width / 2);
		float Wy = (Py + getPlayer()->getWeapon1()->getPositionY());
		Vec2 v = Vec2(Vec2(x - Wx, y - Wy) / sqrt((x - Wx) * (x - Wx) + (y - Wy) * (y - Wy)));//从人物指向鼠标位置的单位向量

		//玩家Pistol子弹
		if (getPlayer()->getMouseMap()[EventMouse::MouseButton::BUTTON_LEFT]		//鼠标左键按下
			&& getPlayer()->getPlayerAttribute()->getHp() > 0							//Player没死
			&& (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Pistol_TAG
				|| getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Shotgun_TAG))//Weapon是枪
		{

			bool CanShoot = 0;


			if (AmmoList.size() == 0)
			{
				
				if (clock() - PistolEnd >
					getPlayer()->getWeapon1()->getWeaponSpeed()
					+ getPlayer()->getPlayerAttribute()->getShootSpeed()
					- getPlayer()->getPlayerAttribute()->getShootSpeed_Buff())
				{
					CanShoot = 1;
				}

			}
			
			else if (clock() - AmmoList.back()->start >
				getPlayer()->getWeapon1()->getWeaponSpeed()
				+ getPlayer()->getPlayerAttribute()->getShootSpeed()
				- getPlayer()->getPlayerAttribute()->getShootSpeed_Buff()
				&& (clock() - PistolStart >
					getPlayer()->getWeapon1()->getWeaponSpeed()
					+ getPlayer()->getPlayerAttribute()->getShootSpeed()
					- getPlayer()->getPlayerAttribute()->getShootSpeed_Buff()))
			{
				long t1 = clock();
				long t2 = PistolStart;
				CCLOG("%ld,%ld", t1, t2);
				CanShoot = 1;
			}


			if (AmmoList.size() == 0)
			{

			}
			if (CanShoot)
			{
				if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Pistol_TAG)
					MusicManager::effectPlay("effect/pistol.mp3");
				else if(getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Shotgun_TAG)
					MusicManager::effectPlay("effect/shotgun.mp3");
				int Num = 1;
				if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Shotgun_TAG)//霰弹则三连发
					Num = 5;
				for (int i = 1; i <= Num; i++)
				{
					AmmoList.push_back(getPlayer()->getWeapon1()->Attack());


					AmmoList.back()->setTag(AllTag::PlayerAmmo_Pistol_TAG);
					AmmoList.back()->start = clock();//每个子弹内部的start负责记录出生时刻
					PistolStart = clock();
					addChild(AmmoList.back(), 3);
					auto physicBody = PhysicsBody::createBox(Size(20.0f, 20.0f), PhysicsMaterial(0, 0, 0));
					AmmoList.back()->addComponent(physicBody);
					AmmoList.back()->getPhysicsBody()->setDynamic(false);
					AmmoList.back()->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
					if (i == 1)
						AmmoList.back()->getPhysicsBody()->setVelocity(v * 500);
					else if (i == 2)
					{
						float ang_v = v.getAngle() + 4 * (PI / 180);
						Vec2 v2 = Vec2(cos(ang_v), sin(ang_v));

						AmmoList.back()->getPhysicsBody()->setVelocity(v2 * 500);
					}
					else if (i == 3)
					{
						float ang_v = v.getAngle() - 4 * (PI / 180);
						Vec2 v2 = Vec2(cos(ang_v), sin(ang_v));

						AmmoList.back()->getPhysicsBody()->setVelocity(v2 * 500);
					}
					else if (i == 4)
					{
						float ang_v = v.getAngle() - 8 * (PI / 180);
						Vec2 v2 = Vec2(cos(ang_v), sin(ang_v));

						AmmoList.back()->getPhysicsBody()->setVelocity(v2 * 500);
					}
					else if (i == 5)
					{
						float ang_v = v.getAngle() - 8 * (PI / 180);
						Vec2 v2 = Vec2(cos(ang_v), sin(ang_v));

						AmmoList.back()->getPhysicsBody()->setVelocity(v2 * 500);
					}
					AmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0001);//0001
					AmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
					AmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0001);
				}

			}

		}
		//玩家Sword子弹 &PitchFor子弹
		if (getPlayer()->getMouseMap()[EventMouse::MouseButton::BUTTON_LEFT] &&
			getPlayer()->getPlayerAttribute()->getHp() > 0 &&
			(getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Sword_TAG
				|| getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapn_PitchFork_TAG))
		{
			bool CanShoot = 0;


			if (AmmoList.size() == 0)
			{
				if (clock() - SwordStart >
					getPlayer()->getWeapon1()->getWeaponSpeed()
					+ getPlayer()->getPlayerAttribute()->getShootSpeed()
					- getPlayer()->getPlayerAttribute()->getShootSpeed_Buff())
				{
					long t1 = clock();
					long t2 = SwordStart;
					CCLOG("%ld,%ld", t1,t2);
					CanShoot = 1;
				}

			}


			if (CanShoot)
			{
				if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Sword_TAG)
					MusicManager::effectPlay("effect/sword.mp3");
				else if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapn_PitchFork_TAG)
					MusicManager::effectPlay("effect/fork.mp3");
				AmmoList.push_back(getPlayer()->getWeapon1()->Attack());
				AmmoList.back()->start = clock();
				SwordStart = clock();
				AmmoList.back()->setTag(AllTag::PlayerAmmo_Sword_TAG);
				addChild(AmmoList.back(), 3);
				auto physicBody = PhysicsBody::createBox(Size(120.0f, 120.0f), PhysicsMaterial(0, 0, 0));
				AmmoList.back()->addComponent(physicBody);
				AmmoList.back()->getPhysicsBody()->setDynamic(false);
				AmmoList.back()->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
				AmmoList.back()->getPhysicsBody()->setVelocity(v * 1500);
				AmmoList.back()->getPhysicsBody()->setCategoryBitmask(0x0001);//0001
				AmmoList.back()->getPhysicsBody()->setCollisionBitmask(0x0001);//0001
				AmmoList.back()->getPhysicsBody()->setContactTestBitmask(0x0001);
				if (getPlayer()->getIsFlip() && getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Sword_TAG)
					AmmoList.back()->getSprite()->setFlippedX(1);
				if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapn_PitchFork_TAG)
				{
					AmmoList.back()->getSprite()->setRotation(getPlayer()->getWeapon1()->getSprite()->getRotation());
				}
			}

		}
	}
	
	
	
}

bool BattleScene1::isWall(float x, float y)//判断传入的这个坐标对应在地图上是不是墙体
{
	int mapX = (int)(x / 64);
	int mapY = (int)(11 - int(y / 64));
	int tileGid = parentMap->getBattleMap()->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));
	if (tileGid)
		return true;	//是墙

	else
		return false;	//不是墙
}
bool BattleScene1::isDamagingLand(float x, float y)
{
	if (parentMap->getBattleMap()->getTag() == NormalRoom_TAG)
	{
		int mapX = (int)(x / 64);
		int mapY = (int)(11 - int(y / 64));
		int tileGid = parentMap->getBattleMap()->getLayer("DamagingLand")->getTileGIDAt(Vec2(mapX, mapY));
		if (tileGid)
			return true;

		else
			return false;
	}
	else
		return false;

}
//清除子弹
void BattleScene1::DeleteAmmo(float dt)
{
	if (AmmoList.size() != 0)
	{
		int i = 0;
		auto ix = AmmoList.begin();
		int size = AmmoList.size();
		//Sword&&PitchFork的子弹回收
		if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Sword_TAG
			|| getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapn_PitchFork_TAG)
		{

			
			for (; i < size; ix++, i++)
			{
				
				if (AmmoList[i]->getTag() == AllTag::PlayerAmmo_Sword_TAG)
				{
					AmmoList[i]->setPosition(getPlayer()->getPosition() + getPlayer()->getWeapon1()->getPosition());
					long NowTime = clock();

					if (NowTime - AmmoList[i]->start >= 
						getPlayer()->getWeapon1()->getWeaponSpeed()
						+getPlayer()->getPlayerAttribute()->getShootSpeed()
						- getPlayer()->getPlayerAttribute()->getShootSpeed_Buff())
					{
						removeChild(AmmoList[i]);
						AmmoList.erase(ix);
						SwordEnd = clock();
						break;
					}
				}

			}
		}
		i = 0;
		ix = AmmoList.begin();
		size = AmmoList.size();
//子弹撞墙回收
			for (; i < size; ix++, i++)
			{

				if (isWall((*ix)->getPositionX(), (*ix)->getPositionY()))
				{
					removeChild(AmmoList[i]);
					AmmoList.erase(ix);
					PistolEnd = clock();
					break;
				}
				


			}
		

	}
	//怪物手枪子弹的撞墙回收 
	if (m_monsterAmmoList.size() != 0)
	{
		int i = 0;
		auto ix = m_monsterAmmoList.begin();
		int size = m_monsterAmmoList.size();
		for (; i < size; ix++, i++)
		{
			if (isWall((*ix)->getPositionX(), (*ix)->getPositionY()))
			{
				removeChild(m_monsterAmmoList[i]);
				m_monsterAmmoList.erase(ix);
				break;
			}

		}
	}
	if (getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapon_Sword_TAG
		|| getPlayer()->getWeapon1()->getTag() == AllTag::PlayerWeapn_PitchFork_TAG)
	{
		if (AmmoList.size())
			getPlayer()->getWeapon1()->getSprite()->setOpacity(0);
		else
			getPlayer()->getWeapon1()->getSprite()->setOpacity(255);
	}

}
void BattleScene1::DeleteAllAmmo()
{
	for (auto ix : AmmoList)
	{
		removeChild(ix);
	}
	AmmoList.clear();
}
//碰撞检测
bool BattleScene1::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		Ammo* ammo;
		MonsterPistolAmmo* ammo_M;
		MonsterDashAmmo* dash_M;
		Monster* monster;
		Player* player;

		int TagA = nodeA->getTag();
		int TagB = nodeB->getTag();

		if (TagA == AllTag::PlayerAmmo_Pistol_TAG || TagA == AllTag::PlayerAmmo_Sword_TAG)
			ammo = dynamic_cast<Ammo*>(nodeA);
		else if (TagA>AllTag::CloseMonster_TAG&&TagA<AllTag::RemoteMonster_TAG)
			monster = dynamic_cast<Monster*>(nodeA);
		else if (TagA == 0)
			player = dynamic_cast<Player*>(nodeA);
		else if (TagA == AllTag::MonsterAmmo_PistolTAG)
			ammo_M = dynamic_cast<MonsterPistolAmmo*>(nodeA);
		else if (TagA == AllTag::MonsterAmmo_CloseTAG)
			dash_M = dynamic_cast<MonsterDashAmmo*>(nodeA);



		if (TagB == AllTag::PlayerAmmo_Pistol_TAG || TagB == AllTag::PlayerAmmo_Sword_TAG)
			ammo = dynamic_cast<Ammo*>(nodeB);
		else if (TagB > AllTag::CloseMonster_TAG && TagB < AllTag::RemoteMonster_TAG)
			monster = dynamic_cast<Monster*>(nodeB);
		else if (TagB == 0)
			player = dynamic_cast<Player*>(nodeB);
		else if (TagB == AllTag::MonsterAmmo_PistolTAG)
			ammo_M = dynamic_cast<MonsterPistolAmmo*>(nodeB);
		else if (TagB == AllTag::MonsterAmmo_CloseTAG)
			dash_M = dynamic_cast<MonsterDashAmmo*>(nodeB);
		//怪物撞玩家手枪子弹
		if ((TagA > AllTag::CloseMonster_TAG && TagA < AllTag::RemoteMonster_TAG) &&(TagB==AllTag::PlayerAmmo_Pistol_TAG)||
			(TagB > AllTag::CloseMonster_TAG && TagB < AllTag::RemoteMonster_TAG) && (TagA == AllTag::PlayerAmmo_Pistol_TAG))
		{
			int i = 0;
			auto ix = AmmoList.begin();
			int size = AmmoList.size();
			for (; i < size; ix++, i++)
			{
				if (*ix == ammo)
				{
					removeChild(AmmoList[i]);
					AmmoList.erase(ix);
					PistolEnd = clock();
					break;
				}
			}
			monster->takingDamage(getPlayer()->getPlayerAttribute()->getDamage()
			+ getPlayer()->getPlayerAttribute()->getDamage_Buff());
		}
		//怪物撞玩家刀剑子弹
		if ((TagA > AllTag::CloseMonster_TAG && TagA < AllTag::RemoteMonster_TAG) && (TagB == AllTag::PlayerAmmo_Sword_TAG) ||
			(TagB > AllTag::CloseMonster_TAG && TagB < AllTag::RemoteMonster_TAG) && (TagA == AllTag::PlayerAmmo_Sword_TAG))
		{

			int i = 0;
			auto ix = AmmoList.begin();
			int size = AmmoList.size();
			for (; i < size; ix++, i++)
			{
				if (*ix == ammo&&clock()-(*ix)->start>400)
				{
					removeChild(AmmoList[i]);
					AmmoList.erase(ix);
					SwordEnd = clock();	
					break;
				}
			}
			if (clock() - MonsterHurt > 300)
			{
				MonsterHurt = clock();
				monster->takingDamage(getPlayer()->getPlayerAttribute()->getDamage()
					+ getPlayer()->getPlayerAttribute()->getDamage_Buff());
			}
		
		}
		//玩家撞怪物Pistol子弹
		if ((TagA==AllTag::Player_TAG&&TagB==AllTag::MonsterAmmo_PistolTAG)||
			(TagB == AllTag::Player_TAG && TagA == AllTag::MonsterAmmo_PistolTAG))
		{
			int i = 0;
			auto ix = m_monsterAmmoList.begin();
			int size = m_monsterAmmoList.size();
			for (; i < size; ix++, i++)
			{
				if (*ix == ammo_M)
				{
					removeChild(m_monsterAmmoList[i]);
					m_monsterAmmoList.erase(ix);
					break;
				}
			}
			getPlayer()->getPlayerAttribute()->takeDamage(level);
		}
		//玩家撞怪物Close子弹
		if ((TagA == AllTag::Player_TAG && TagB == AllTag::MonsterAmmo_CloseTAG) ||
			(TagB == AllTag::Player_TAG && TagA == AllTag::MonsterAmmo_CloseTAG))
		{
			getPlayer()->getPlayerAttribute()->takeDamage(1+level);
		}
		//玩家撞有碰撞伤害的怪物
		if ((TagA == AllTag::Player_TAG && TagB == AllTag::MonsterAmmo_ImmortalTAG) ||
			(TagB == AllTag::Player_TAG && TagA == AllTag::MonsterAmmo_ImmortalTAG))
		{
			getPlayer()->getPlayerAttribute()->takeDamage(3 + level );
		}
		return 1;
	}
	return 0;
}
void BattleScene1::LandDamageUpdate(float dt)
{
	
	if (isDamagingLand(getPlayer()->getPositionX(), getPlayer()->getPositionY()))
	{
		getPlayer()->getPlayerAttribute()->takeDamage(1);
	}
}
void BattleScene1::LandSlowUpdate(float dt)
{
	float x = getPlayer()->getPositionX();
	float y = getPlayer()->getPositionY();

	int mapX = (int)(x / 64);
	int mapY = (int)(11 - int(y / 64));
	int tileGid = parentMap->getBattleMap()->getLayer("SlowingLand")->getTileGIDAt(Vec2(mapX, mapY));
	if (tileGid)
		getPlayer()->getplayermove()->setSpeed(2);

	else
		getPlayer()->getplayermove()->setSpeed(NORMAL);

}
void BattleScene1::LandBurningUpdate(float dt)
{
	float x = getPlayer()->getPositionX();
	float y = getPlayer()->getPositionY();

	int mapX = (int)(x / 64);
	int mapY = (int)(11 - int(y / 64));
	int tileGid = parentMap->getBattleMap()->getLayer("BurningLand")->getTileGIDAt(Vec2(mapX, mapY));
	if (tileGid)
		getPlayer()->getPlayerAttribute()->setIsBurnging(1);

	else
		getPlayer()->getPlayerAttribute()->setIsBurnging(0);
}
void BattleScene1::PlayerDeatheUpdate(float dt)
{
	int Hp=getPlayer()->getPlayerAttribute()->getHp();
	if (Hp <= 0&&!getPlayer()->getIsdead())
	{	
	
		;
	}
}
