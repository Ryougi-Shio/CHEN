#pragma once
#include"NPC.h"
/*���ø����һ����NPC  ���������л�
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