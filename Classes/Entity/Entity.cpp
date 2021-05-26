#include"Entity.h"
USING_NS_CC;
Sprite* Entity::getSprite()
{
	return this->m_sprite;
}

void Entity::bindSprite(Sprite* sprite)
{
	m_sprite = sprite;
	addChild(m_sprite);
}