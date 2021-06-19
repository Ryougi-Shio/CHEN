#pragma once
#include"NPC.h"
/*长得跟玩家一样的NPC  负责人物切换
*/
class HeroNPC :public NPC
{
public:	
	virtual bool init();
	virtual void update(float dt);
	virtual void interact(int mode);

	CREATE_FUNC(HeroNPC);
private:
	
};