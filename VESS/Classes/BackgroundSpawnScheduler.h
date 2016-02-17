#pragma once

#ifndef __BACKGROUND_SPAWN_SCHEDULER_H__
#define __BACKGROUND_SPAWN_SCHEDULER_H__
#include <vector>
#include "BackgroundObject.h"
#include <stdlib.h>
using namespace std;

class FightLayer;

class EnumBackground {
public:
	enum OBJECT {TREE, MOUNTAIN};
};

class BackgroundSpawnSchedulerTimer{
private:
	EnumBackground::OBJECT object;
	float timer; //ì§„ì§œ ?€?´ë¨¸
	float monsterSpawnInterval; //timeWhenObjectSpawn    ?¤ë¸Œ?íŠ¸ ?ì„±???¼ë§ˆ ?„ì— ?¤ìŒ ?¤ë¸Œ?íŠ¸ë¥??ì„±??ì§€ ê²°ì •?˜ëŠ” ê²?/ê¸°ë³¸ ?°ì‚° ë¡œì§??targetTImerScale??ê³±í•´ ê°„ê²© ë²”ìœ„ë¥?ì¡°ì ˆ 
	float monsterSpawnIntervalScaling; //0~1ê¹Œì? ?¼ë§ˆ??ë²Œë¦´ì§€.->?¬ê¸° ì»¤ì§ˆ?˜ë¡ ?¤ë¸Œ?íŠ¸ê°€ ?ì„±?˜ëŠ” ê°„ê²©??ì»¤ì§
	FightLayer* field;
public:
	void update(float deltaTime);//deltaTimeTime->?„ë ˆ???¬ì´ ê°„ê²©
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EnumBackground::OBJECT object, FightLayer* layer, float scale);// ?´ë–¤?¤ë¸Œ?íŠ¸ ?ì„±? ì?, ?ì„±??ê±??´ë–¤?ˆì´?´ì— addchild ? ì?, ?¤ë¸Œ?íŠ¸ ?ì„± ê°„ê²© 
};

class BackgroundSpawnScheduler{ //fightlayer?ì„œ ???˜ë‚˜ ?ì„±. ê°ê°???¤ë¸Œ?íŠ¸?¤ì„ ?°ë¡œ?°ë¡œ ?ì„±,?´ìš©(ê°™ì´ ?€ì§ì´ì§€ ?ŠëŠ”??
private:
	BackgroundSpawnSchedulerTimer mountain;
	BackgroundSpawnSchedulerTimer tree;
	FightLayer* field;
public:
	BackgroundSpawnScheduler();
	BackgroundSpawnScheduler(FightLayer* layer);
	void update(float deltaTime); 
};



#endif