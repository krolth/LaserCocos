#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "cocos2d.h"
using namespace cocos2d;

class CCParticlePlayerTrail : public CCParticleSystemQuad
{
public:
	
	bool isEnabled;

    CCParticlePlayerTrail(){ isEnabled = false; }
    virtual ~CCParticlePlayerTrail(){}
    bool init(){ return initWithTotalParticles(150); }

	void setAngle(float angle){ m_fAngle = angle; }

	void enable()
	{
		isEnabled = true;
		m_bIsActive = true;
	}

	void killAll()
	{
		isEnabled = false;
		m_bIsActive = false;
	}

    virtual bool initWithTotalParticles(unsigned int numberOfParticles);

	//virtual void draw();

    static CCParticlePlayerTrail * node()
    {
        return create();
    }

    static CCParticlePlayerTrail * create()
    {
        CCParticlePlayerTrail *pRet = new CCParticlePlayerTrail();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

class CCShipExplosion : public CCParticleSystemQuad
{
public:
    CCShipExplosion(){}
    virtual ~CCShipExplosion(){}
    bool init(){ return initWithTotalParticles(700); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCShipExplosion * node()
    {
        return create();
    }
    static CCShipExplosion * create()
    {
        CCShipExplosion *pRet = new CCShipExplosion();
        if (pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
};

#endif