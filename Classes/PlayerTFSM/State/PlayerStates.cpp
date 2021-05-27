#include"PlayerStates.h"
#include"Entity/Player.h"
USING_NS_CC;
void RunState::execute(Player* player)
{
	player->run();
}
void RunState_Flip::execute(Player* player)
{
	player->run_flip();
}
void RestState::execute(Player* player)
{
	player->rest();
}
void RestState_Flip::execute(Player* player)
{
	player->rest_flip();
}