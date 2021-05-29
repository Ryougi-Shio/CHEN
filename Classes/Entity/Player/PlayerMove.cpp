#include"PlayerMove.h"
#include"Player.h"
#include"PlayerStates.h"

#define PX 52
#define PY 60
USING_NS_CC;
void PlayerMove::bindPlayer(Player* player)
{
	mPlayer = player;
}
Player* PlayerMove::getPlayer()
{
	return mPlayer;
}
void PlayerMove::playerMove()
{
	auto move = MoveBy::create(0, Vec2(movespeedX, movespeedY));
	this->getPlayer()->runAction(move);//����ʵ���ƶ�


	if (movespeedX > 0)
	{
		mPlayer->TFSM->changeState(new RunState());//�ı�״̬��
		isFlip = 0;

	}
	if (movespeedX < 0)
	{
		mPlayer->TFSM->changeState(new RunState_Flip());
		isFlip = 1;
	}

	if ((!movespeedX) && (!movespeedY))
	{
		if (!isFlip)
			mPlayer->TFSM->changeState(new RestState());
		else
			mPlayer->TFSM->changeState(new RestState_Flip());
	}
	if (movespeedY)
	{
		if (!isFlip)
			mPlayer->TFSM->changeState(new RunState());
		else
			mPlayer->TFSM->changeState(new RunState_Flip());
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
bool PlayerMove::isWall(float Px, float Py)
{
	int mapX = (int)(Px / 64);
	int mapY = (int)(12 - Py / 64);
	//CCLOG("X:%d    Y:%d", mapX, mapY);
	int tileGid = map->getLayer("wall")->getTileGIDAt(Vec2(mapX, mapY));
	//CCLOG("%d", tileGid);
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
	if (keyMap[right] && keyMap[up])
	{
		if (isWall(x+PX*0.5, y+PY*0.3))
		{
			startmoveX(Speed);
			startmoveY(Speed);
		}

	}
	if (keyMap[left] && keyMap[up])
	{
		if (isWall(x-PX*0.5, y+PY*0.3))
		{
			startmoveX(-Speed);
			startmoveY(Speed);
		}

	}
	if (keyMap[left] && keyMap[down])
	{
		if (isWall(x-PX*0.5, y-PY*0.5))
		{
			startmoveX(-Speed);
			startmoveY(-Speed);
		}

	}
	if (keyMap[right] && keyMap[down])
	{
		if (isWall(x+PX*0.5, y-PY*0.5))
		{
			startmoveX(Speed);
			startmoveY(-Speed);
		}

	}
	playerMove();
	stopmoveX();
	stopmoveY();
}
