#include"NPC.h"
USING_NS_CC;
bool NPC::init()
{
	return 1;
}


void NPC::changeNpcName(char s[])
{
	strcpy(NpcName, s);
}

char* NPC::getNpcName()
{
	return NpcName;
}

void NPC::AnimateFrameCache_init()
{
	m_frameCache = SpriteFrameCache::getInstance();//获取动画缓存实例对象
	char plist[40], png[40];
	sprintf(plist, "NPC/%s_animate.plist", NpcName);
	sprintf(png, "NPC/%s_animate.png", NpcName);
	m_frameCache->addSpriteFramesWithFile(plist, png);//添加帧动画文件到缓存


	Vector<SpriteFrame*>frameArray;//创建序列备用
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "%s_rest%d.png", NpcName, i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//将帧加入到序列中
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//创建动画
	animation->setLoops(-1);//-1表示无限播放
	animation->setDelayPerUnit(0.1f);//每两张图片的间隔时间
	auto* action = Animate::create(animation);
	getSprite()->runAction(action);
}
void NPC::update(float dt)
{
	;
}

void NPC::interact(int mode)
{
	;
}
