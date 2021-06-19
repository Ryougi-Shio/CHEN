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
	m_frameCache = SpriteFrameCache::getInstance();//��ȡ��������ʵ������
	char plist[40], png[40];
	sprintf(plist, "NPC/%s_animate.plist", NpcName);
	sprintf(png, "NPC/%s_animate.png", NpcName);
	m_frameCache->addSpriteFramesWithFile(plist, png);//���֡�����ļ�������


	Vector<SpriteFrame*>frameArray;//�������б���
	for (int i = 1; i <= 4; i++)
	{
		char s[40];
		sprintf(s, "%s_rest%d.png", NpcName, i);
		auto frame = m_frameCache->getSpriteFrameByName(s);
		frameArray.pushBack(frame);//��֡���뵽������
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);//��������
	animation->setLoops(-1);//-1��ʾ���޲���
	animation->setDelayPerUnit(0.1f);//ÿ����ͼƬ�ļ��ʱ��
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

char NPC::NpcName[30];