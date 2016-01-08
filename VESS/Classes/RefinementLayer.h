#pragma once
#ifndef __REFINEMENT_LAYER_H__
#define __REFINEMENT_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class RefinementLayer : public Layer
{
public :
	virtual bool init();
	CREATE_FUNC(RefinementLayer);

};

#endif