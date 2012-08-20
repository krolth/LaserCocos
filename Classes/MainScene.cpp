#include "MainScene.h"
#include "Actor.h"
#include "Particle.h"
#include "Constants.h"

using namespace cocos2d;

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
        		
		// Add particle system used when "grazing" laser
		Ship::Trail = CCParticlePlayerTrail::create();
		Ship::Trail->retain();
		Ship::Trail->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire1) );
		this->addChild(Ship::Trail, 10);

		// Add particle system used when exploding
		Ship::Explosion = CCShipExplosion::create();
		Ship::Explosion->retain();
		Ship::Explosion->setTexture( CCTextureCache::sharedTextureCache()->addImage(s_fire1) );
		
		// Add the ship
		player = new Ship(1, 1, this);
		this->addChild(player->sprite, 0, tagShip);
		
		//lasers = new CCArray();
		
		addLaser();

		this->setTouchEnabled(true);
		this->scheduleUpdate();

        bRet = true;
    } while (0);

    return bRet;
}

int nextLaserTicks = 10;

void LaserGraze::addLaser()
{
	// Get random angle between 95 (going right) and 265 (left)
	const int maxRand = 265;
	const int minRand = 95;
	const int range = maxRand - minRand;
	
	int angle = (rand() % range) + minRand;
	float angleRadians = CC_DEGREES_TO_RADIANS(angle);

	int rank = 1;
	//rank += sawtoothWave(score / 10000) * 2;
	int speed = rand() % (rank*5) + 5;

	int x = rand() % SCREEN_WIDTH;
	int y = SCREEN_HEIGHT + LASER_HEIGHT/2; // Put it slightly offscreen

	int a = SCREEN_HEIGHT;

	Laser* laser = new Laser(x, y, angleRadians, speed, this);
	this->addChild(laser->sprite, 0, tagLaser);
	lasers.push_back(laser);

	nextLaserTicks = 10/rank;
}

void LaserGraze::update(float time)
{
	player->Update();
	player->NoImpact();

	for (int i=0; i<lasers.size(); ++i)
	{
		lasers.at(i)->Update(player);
	}

	if (--nextLaserTicks <=0) addLaser();

	//laser->Update(player);

	//Laser* pObj = NULL;
 //   CCARRAY_FOREACH(pFrames, pObj)
 //   {
 //       /*CCAnimationFrame* frame = (CCAnimationFrame*)pObj;
 //       float value = (accumUnitsOfTime * newUnitOfTimeValue) / singleDuration;
 //       accumUnitsOfTime += frame->getDelayUnits();
 //       m_pSplitTimes->push_back(value);*/
 //   }    

	//CCARRAY_FOREACH(_lasers,objs)
 //   {
 //       CCSprite * laser = (CCSprite *) objs;
 //       if (!isDestroyed) {
 //           // Check Hit
 //           checkHit(laser);
 //       }
 //       if (isFirstLaser) {
 //       	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
 //           addMessage((char *)"GRAZE THE BEAMS", winSize.width/2, winSize.height*0.7);
 //           isFirstLaser = false;
 //       }
 //   }
}

void LaserGraze::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint location = touch->locationInView();
    CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);

	player->Move(convertedLocation);
}

void LaserGraze::ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent) {
    
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);    
    CCPoint location = touch->locationInView();
    CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);
    
    CCPoint oldTouchLocation = touch->previousLocationInView();
    oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation); 
    //oldTouchLocation = convertToNodeSpace(oldTouchLocation);
    
    CCPoint translation = ccpSub(location, oldTouchLocation);    
    //movePlayer(translation);
	player->Move(convertedLocation);
    
    /*    lastTouchX = location.x;
     lastTouchY = location.y;
     isMouseClicked = true;*/
}

void LaserGraze::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}
