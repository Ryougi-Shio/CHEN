#pragma once
#include"AudioEngine.h"
#include"cocos2d.h"
USING_NS_CC;
/*
* 音乐播放器
* 包含
* 更改当前bgm
* 初次播放音乐，包括初始化音量
* 菜单界面，包括更改音量
* 播放音效。
*/
class MusicManager : public Node
{
public:
	virtual bool init();
	static void changeMusic(char* filename);
	static void startPlay(char* filename);
	static void changeMusicVolume(float Volume);
	static void menu(Scene* p);
	static void changeEffectVolume(float Volume);
	static void effectPlay(char* filename);

	static float getMusicVolume();
	static int getEffect();
	static float getEffectVolume();
	static int getBgm();

	static void setMusicVolume(float volume);
	static void setEffect(int effect);
	static void setEffectVolume(float _effectvolume);
	static void setBgm(int _bgm);
	CREATE_FUNC(MusicManager);
private:
	static int bgm;
	static float musicVolume;
	static int effect;
	static float effectVolume;
	static AudioEngine* manager;
	
};