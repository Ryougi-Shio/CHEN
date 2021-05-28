#include"PlayerMove.h"
#include"Player.h"
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
void PlayerMove::Move()
{
	//PlayerÔË¶¯
	float Speed = mPlayer->getSpeed();
	auto right = (EventKeyboard::KeyCode)127;
	auto left = (EventKeyboard::KeyCode)124;
	auto up = (EventKeyboard::KeyCode)146;
	auto down = (EventKeyboard::KeyCode)142;
	float x = mPlayer->getPositionX();
	float y = mPlayer->getPositionY();
	if (mPlayer->getkeyMap()[up])
	{
		if(mPlayer->isWall(x,y+PY*0.3))
			mPlayer->startmoveY(Speed);
	}
	if (mPlayer->getkeyMap()[down])
	{
		if (mPlayer->isWall(x, y-PY*0.5))
		mPlayer->startmoveY(-Speed);
	}
	if (mPlayer->getkeyMap()[left])
	{
		if (mPlayer->isWall(x-PX*0.5, y))
		mPlayer->startmoveX(-Speed);
	}
	if (mPlayer->getkeyMap()[right])
	{
		if (mPlayer->isWall(x+PX*0.5, y))
		mPlayer->startmoveX(Speed);
	}
	if (mPlayer->getkeyMap()[right] && mPlayer->getkeyMap()[up])
	{
		if (mPlayer->isWall(x+PX*0.5, y+PY*0.3))
		{
			mPlayer->startmoveX(Speed);
			mPlayer->startmoveY(Speed);
		}

	}
	if (mPlayer->getkeyMap()[left] && mPlayer->getkeyMap()[up])
	{
		if (mPlayer->isWall(x-PX*0.5, y+PY*0.3))
		{
			mPlayer->startmoveX(-Speed);
			mPlayer->startmoveY(Speed);
		}

	}
	if (mPlayer->getkeyMap()[left] && mPlayer->getkeyMap()[down])
	{
		if (mPlayer->isWall(x-PX*0.5, y-PY*0.5))
		{
			mPlayer->startmoveX(-Speed);
			mPlayer->startmoveY(-Speed);
		}

	}
	if (mPlayer->getkeyMap()[right] && mPlayer->getkeyMap()[down])
	{
		if (mPlayer->isWall(x+PX*0.5, y-PY*0.5))
		{
			mPlayer->startmoveX(Speed);
			mPlayer->startmoveY(-Speed);
		}

	}
	mPlayer->playerMove();
	mPlayer->stopmoveX();
	mPlayer->stopmoveY();
}
