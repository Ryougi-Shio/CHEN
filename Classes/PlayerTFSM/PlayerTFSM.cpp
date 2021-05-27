#include"PlayerTFSM.h"
#include"PlayerStates.h"
#include"Entity/Player.h"
bool PlayerTFSM::init()
{
	changeState(new RestState());//Ä¬ÈÏÐÝÏ¢×´Ì¬
	return 1;
}

void PlayerTFSM::changeState(State* state)
{
	mCurState = state;
}

void PlayerTFSM::bindPlayer(Player* player)
{
	mplayer = player;
}

void PlayerTFSM::update(float dt)
{
	mCurState->execute(mplayer);
}
State* PlayerTFSM::getmCurState()
{
	return mCurState;
}