#pragma once
#include <vector>
#include "BackgroundObject.h"
#include <stdlib.h>
#ifndef __BACKGROUND_SPAWN_SCHEDULER_H__
#define __BACKGROUND_SPAWN_SCHEDULER_H__

using namespace std;

class FightLayer;

class EnumBackground {
public:
	enum Object {tree, mountain};
};

class BackgroundSpawnSchedulerTimer{
private:
	EnumBackground::Object object;
	float timer; //��¥ Ÿ�̸�
	float monsterSpawnInterval; //timeWhenObjectSpawn    ������Ʈ ������ �� �Ŀ� ���� ������Ʈ�� ������ �� �����ϴ� ��//�⺻ ���� ������ targetTImerScale�� ���� ���� ������ ���� 
	float monsterSpawnIntervalScaling; //0~1���� �󸶳� ������.->ũ�� Ŀ������ ������Ʈ�� �����Ǵ� ������ Ŀ��
	FightLayer* field;
public:
	void update(float deltaTime);//deltaTimeTime->������ ���� ����
	BackgroundSpawnSchedulerTimer();
	BackgroundSpawnSchedulerTimer(EnumBackground::Object object, FightLayer* layer, float scale);// �������Ʈ ��������, ������ �� ����̾ addchild ����, ������Ʈ ���� ���� 
};




class BackgroundSpawnScheduler{ //fightlayer���� �� �ϳ� ����. ������ ������Ʈ���� ���ε��� ����,���(���� �������� �ʴ´�)
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