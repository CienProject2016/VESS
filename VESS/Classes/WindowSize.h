#pragma once

#include "cocos2d.h"

/*	by. hyobin
윈도우 사이즈를 어디서든 찾아서 알고싶어서 만듬.
보니까 AppDelegate.cpp 안에 윈도우 사이즈를 정의하고 있던데,
다른데서는 찾을 수가 없었어.
그래서 빼두고 헤더파일로 만들어둠.

그런데 아래 네가지 중에서 우리는 designResolutionSize 만 쓰더라. 다들 이것만 쓰셈.
*/
using namespace cocos2d;
static Size designResolutionSize = Size(1920, 1080);
static Size smallResolutionSize = Size(1920, 1080);
static Size mediumResolutionSize = Size(1920, 1080);
static Size largeResolutionSize = Size(1920, 1080);

/*	by. hyobin
visibleSize <- 이런걸로 해당 레이어의 크기를 알아오고 싶었는데
전체 윈도우 크기를 리턴해 버리는 바람에
각각의 레이어 크기를 따로 준비하는게 좋을 것 같았음
그래서 아래의 refinementLayerSize 와 fightLayerSize 를 static 으로 선언 후
그 사이의 임계점을 둬서
임계점만 조절하면 나누어 지도록 해봄.
임계점은 0과 1사이의 값으로 설정 가능함.

그리고 static 으로 설정해뒀는데, WindowSize.h 에 넣어둘지, 아니면 GameScene.h 에 넣어둘지는 고민하다가
윈도우 사이즈에 관련된 것은 전부 여기 넣어두는게 맞는 것 같아서 여기 넣어둠
여기저기 윈도우 사이즈가 나뉘어 있으면 찾기 불편할 것 같아서 한데 모아두는것도 나쁘지 않을 것 같아.
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