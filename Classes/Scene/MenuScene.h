#pragma once
#include"cocos2d.h"
#include"music.h"
USING_NS_CC;
class MenuScene :public Scene
{
public:
	virtual bool init();

	
	CREATE_FUNC(MenuScene);
private:
	MusicManager* m_musicManager;

};