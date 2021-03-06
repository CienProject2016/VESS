#include "AppDelegate.h"
#include "StartScene.h"
#include "WindowSize.h"
#include "ResourcePath.h"
USING_NS_CC;



AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("vess", Rect(0, 0, 960, 540));
#else
        glview = GLViewImpl::create("vess");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    Size frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

	preloadAllSound();
	preloadAllPlists();
    // create a scene. it's an autorelease object
    auto startScene = StartScene::createScene();

    // run
    director->runWithScene(startScene);

    return true;
}

void AppDelegate::preloadAllPlists() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/dead/basic_slime_dead.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/attack1/slime_attack_effect_0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/stand/basic_slime_stand.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/attack1/basic_slime_attack0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/attack2/basic_slime_attack1_0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/basic_slime/attack2/basic_slime_attack1_1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/damage_effect/damage_effect_0/damage_effect.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/damage_effect/damage_effect_1/damage_effect_1.plist");
}

void AppDelegate::preloadAllSound() {
	log("preload all sound");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_JUMP_PATH.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_DIMENSION_GATE_PATH.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_OPEN_DOOR.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_ATTACK_PATH.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_BLOCK.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_UPGRADE_COMPLETE.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_PUI.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_QUENCHING.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_SMELTING.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_HAMMER.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(AudioPath::SOUND_SLIME_DEAD.c_str());

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AudioPath::BGM_NEO_ROCK.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AudioPath::BGM_DIALOG.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AudioPath::BGM_CLEAR.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AudioPath::BGM_ENTER.c_str());
	
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
