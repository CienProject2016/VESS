#pragma once

#include "cocos2d.h"

/*	by. hyobin
������ ����� ��𼭵� ã�Ƽ� �˰�; ����.
���ϱ� AppDelegate.cpp �ȿ� ������ ����� �����ϰ� �ִ���,
�ٸ������� ã�� ���� ������.
�׷��� ���ΰ� ������Ϸ� ������.

�׷��� �Ʒ� �װ��� �߿��� �츮�� designResolutionSize �� ������. �ٵ� �̰͸� ����.
*/
using namespace cocos2d;
static Size designResolutionSize = Size(1920, 1080);
static Size smallResolutionSize = Size(1920, 1080);
static Size mediumResolutionSize = Size(1920, 1080);
static Size largeResolutionSize = Size(1920, 1080);

/*	by. hyobin
visibleSize <- �̷��ɷ� �ش� ���̾��� ũ�⸦ �˾ƿ��� �;��µ�
��ü ������ ũ�⸦ ������ ������ �ٶ���
������ ���̾� ũ�⸦ ���� �غ��ϴ°� ���� �� ������
�׷��� �Ʒ��� refinementLayerSize �� fightLayerSize �� static ���� ���� ��
�� ������ �Ӱ����� �ּ�
�Ӱ����� �����ϸ� ������ ������ �غ�.
�Ӱ����� 0�� 1������ ������ ���� ������.

�׸��� static ���� �����ص״µ�, WindowSize.h �� �־����, �ƴϸ� GameScene.h �� �־������ ����ϴٰ�
������ ����� ���õ� ���� ���� ���� �־�δ°� �´� �� ���Ƽ� ���� �־��
�������� ������ ����� ������ ������ ã�� ������ �� ���Ƽ� �ѵ� ��Ƶδ°͵� ������ ���� �� ����.
*/
static float criticalPoint_refinementLayer_from_fightLayer = 0.3f;
static Size refinementLayerSize = Size(
	designResolutionSize.width * criticalPoint_refinementLayer_from_fightLayer,
	designResolutionSize.height);
static Size fightLayerSize = Size(
	designResolutionSize.width * (1 - criticalPoint_refinementLayer_from_fightLayer),
	designResolutionSize.height);
static Vec2 refinementLayerOrigin = Vec2(0, 0);
static Vec2 fightLayerOrigin = Vec2(refinementLayerSize.width, 0);