#pragma once
#include"Entity.h"
class Player;
class MapGate : public Entity
{
public:
	virtual bool init();
	virtual void update(float delta);
	bool isAround(float Px, float Py);//检测玩家是否在门周围
	void bindPlayer(Player* mPlayer);
	void notice();//提示按'E'
	void  IsAble(bool able);
	bool getAble();
	CREATE_FUNC(MapGate);
private:
	Player* player;
	Label* noticeLabel;
	bool Able=1;
};