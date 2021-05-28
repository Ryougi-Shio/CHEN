#include"PlayerMove.h"
#include"Player.h"
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
	if (mPlayer->getkeyMap()[up])
	{
		mPlayer->startmoveY(Speed);
	}
	if (mPlayer->getkeyMap()[down])
	{
		mPlayer->startmoveY(-Speed);
	}
	if (mPlayer->getkeyMap()[left])
	{
		mPlayer->startmoveX(-Speed);
	}
	if (mPlayer->getkeyMap()[right])
	{
		mPlayer->startmoveX(Speed);
	}
	if (mPlayer->getkeyMap()[right] && mPlayer->getkeyMap()[up])
	{
		mPlayer->startmoveX(Speed);
		mPlayer->startmoveY(Speed);
	}
	if (mPlayer->getkeyMap()[left] && mPlayer->getkeyMap()[up])
	{
		mPlayer->startmoveX(-Speed);
		mPlayer->startmoveY(Speed);
	}
	if (mPlayer->getkeyMap()[left] && mPlayer->getkeyMap()[down])
	{
		mPlayer->startmoveX(-Speed);
		mPlayer->startmoveY(-Speed);
	}
	if (mPlayer->getkeyMap()[right] && mPlayer->getkeyMap()[down])
	{
		mPlayer->startmoveX(Speed);
		mPlayer->startmoveY(-Speed);
	}
	mPlayer->playerMove();
	mPlayer->stopmoveX();
	mPlayer->stopmoveY();
}