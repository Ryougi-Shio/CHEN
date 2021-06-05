#include"Item.h"
USING_NS_CC;
class TreasureBox :public Item
{
public:
	virtual bool init();
	virtual void update(float dt);
	virtual void Interact();

private:
	bool isOpen = 0;
};