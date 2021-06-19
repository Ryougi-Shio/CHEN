#include"PlayerMove.h"
#include"Player.h"
#include"PlayerStates.h"
#include"PlayerTFSM/PlayerTFSM.h"
#include"PlayerAttribute.h"
#define PX 52
#define PY 60
USING_NS_CC;
bool PlayerMove::init()
{
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerMove::FrozenUpdate), 0.1f);

	return 1;
}
void PlayerMove::bindPlayer(Player* player)
{
	mPlayer = player;
}
Player* PlayerMove::getPlayer()
{
	return mPlayer;
}
bool PlayerMove::getIsFrozen()
{
	return isFrozen;
}
void PlayerMove::setFrozen(bool frozen)
{
	isFrozen = frozen;
}
void PlayerMove::FrozenUpdate(float dt)
{
	if (isFrozen)
	{
		mPlayer->TFSM->changeState(new FrozenState());//�ı�״̬��
	}
	else
	{
		;
	}
}
bool PlayerMove::getIsFlip()
{
	return isFlip;
}

void PlayerMove::playerMove()
{
	if (!isFrozen)
	{
		auto move = MoveBy::create(0, Vec2(movespeedX, movespeedY));
		this->getPlayer()->runAction(move);//����ʵ���ƶ�


		if (movespeedX)
		{
			mPlayer->TFSM->changeState(new RunState());//�ı�״̬��

		}


		if ((!movespeedX) && (!movespeedY))
			mPlayer->TFSM->changeState(new RestState());

		if (movespeedY)
		{
			mPlayer->TFSM->changeState(new RunState());

		}

	}
	
	
}
void PlayerMove::startmoveX(float x)
{
	movespeedX = x;
	ismoveX = 1;
}
void PlayerMove::startmoveY(float y)
{
	movespeedY = y;
	ismoveY = 1;
}
void PlayerMove::stopmoveX()
{
	movespeedX = 0;
	ismoveX = 0;
}
void PlayerMove::stopmoveY()
{
	movespeedY = 0;
	ismoveY = 0;
}
bool PlayerMove::getismoveX()
{
	return ismoveX;
}
bool PlayerMove::getismoveY()
{
	return ismoveY;
}
float PlayerMove::getspeedX()
{
	return movespeedX;
}
float PlayerMove::getspeedY()
{
	return movespeedY;
}
float PlayerMove::getSpeed()
{
	return Speed;
}
void PlayerMove::setSpeed(float s)
{
	Speed = s;
}
std::map<cocos2d::EventKeyboard::KeyCode, bool> PlayerMove::getkeyMap()
{
	return keyMap;
}
void PlayerMove::TrueKeyCode(EventKeyboard::KeyCode keycode)//���̰��£���Ӧkeycode��true
{
	keyMap[keycode] = true;
}
void PlayerMove::FalseKeyCode(EventKeyboard::KeyCode keycode)//�����ɿ�����Ӧkeycode��false
{

	keyMap[keycode] = false;
}
void PlayerMove::setSpeed(int spee)
{
	Speed = spee;
}
bool PlayerMove::isWall(float Px, float Py)
{
	int mapX = (int)(Px / 64);
	int mapY = (int)(11 - int(Py / 64));
	int tileGid = map->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));
//	CCLOG("%d,%d",mapX,mapY);
//	CCLOG("%f,%f",Px,Py);
	if (tileGid)
	{
		//CCLOG("TTTTTTT");//��ǽ��������
		return false;
	}

	else
	{
		//CCLOG("FFFFFFF");//����ǽ������
		return true;
	}

	
}
void PlayerMove::bindMap(TMXTiledMap* aMap)
{
	map = aMap;
}

void PlayerMove::Move()
{
	//Player�˶�
	/*����ƶ�ԭ��
	* keyMap�������룬�簴��Wʱ����W������true���ɿ�W����W������false������keyMap�м����״̬�����ƶ�
	* �ƶ��󣬽��ƶ��ٶ���0
	*/
	auto right = (EventKeyboard::KeyCode)127;
	auto left = (EventKeyboard::KeyCode)124;
	auto up = (EventKeyboard::KeyCode)146;
	auto down = (EventKeyboard::KeyCode)142;
	auto E = EventKeyboard::KeyCode::KEY_E;
	float x = mPlayer->getPositionX();
	float y = mPlayer->getPositionY();

	if (keyMap[up])
	{

		if(isWall(x,y+PY*0.3))
			startmoveY(Speed);
	}
	if (keyMap[down])
	{
		if (isWall(x, y-PY*0.5))
		startmoveY(-Speed);
	}
	if (keyMap[left])
	{
		if (isWall(x-PX*0.5, y))
		startmoveX(-Speed);
	}
	if (keyMap[right])
	{
		if (isWall(x+PX*0.5, y))
		startmoveX(Speed);
	}
	playerMove();
	stopmoveX();
	stopmoveY();
}
void PlayerMove::FlipToMouse()
{
	float Mouse_X =mPlayer->getMouseLocation().x;
	float Player_X = mPlayer->getPositionX();

	if (Mouse_X > Player_X)
	{
		isFlip = 0;

	}

	else
	{
		isFlip = 1;

	}

}