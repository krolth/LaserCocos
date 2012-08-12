#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Actor.h"
#include "SimpleAudioEngine.h"


class LaserGraze : public cocos2d::CCLayer
{
private:
	Ship* player;
	//CCMutableArray* lasers;
	std::vector<Laser*> lasers;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	virtual void update(float time);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	void addLaser();

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(LaserGraze);
};

#endif