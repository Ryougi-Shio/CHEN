#include"PlayerStates.h"
#include"Player.h"
USING_NS_CC;
void RunState::execute(Player* player)
{
	player->run();
}

void RestState::execute(Player* player)
{
	player->rest();
}

