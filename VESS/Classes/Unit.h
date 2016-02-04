
#include "cocos2d.h"
#include "EVENT.h"
#ifndef __UNIT_H__
#define __UNIT_H__

USING_NS_CC;

class Unit: public Node{
protected:
	CC_SYNTHESIZE(int, hp_, HP);
	CC_SYNTHESIZE(int, fullHp_, FullHp);
public:	
	Unit();
	~Unit();
};
#endif // __UNIT_H__