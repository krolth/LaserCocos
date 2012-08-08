#include "MainScene.h"

using namespace cocos2d;
#include "Actor.h"

CCScene* LaserGraze::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        LaserGraze *layer = LaserGraze::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LaserGraze::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		        
        CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
        		
		// Add the ship
		player = new Ship(1, 1, this);
		this->addChild(player->sprite, 0, tagShip);
		
		// Add one laser
		laser = new Laser(windowSize.width/2, windowSize.height/2, 2.35f, 1, 320, this);
		this->addChild(laser->sprite, 0, tagLaser);

		this->setTouchEnabled(true);
		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

void LaserGraze::update(float time)
{
	player->Update();
	laser->Update(player);
}

void LaserGraze::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint location = touch->locationInView();
    CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	player->Move(convertedLocation);
}

void LaserGraze::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
