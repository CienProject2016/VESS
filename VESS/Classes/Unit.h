#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

USING_NS_CC;

class Unit: public Node{
protected:
	CC_SYNTHESIZE(int, hp_, HP);
};
#endif