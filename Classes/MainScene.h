#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Actor.h"
#include "SimpleAudioEngine.h"

static const char s_stars1[] = "stars.png";
static const char s_fire1[] = "fire.png";

class LaserGraze : public cocos2d::CCLayer
{
private:
	Ship* player;
	Laser* laser;
	CCParticleSystem* m_emitter;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	virtual void update(float time);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(LaserGraze);
};

#endif