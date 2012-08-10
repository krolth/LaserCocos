#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "cocos2d.h"
using namespace cocos2d;

class CCParticleFireworks2 : public CCParticleSystemQuad
{
public:
    CCParticleFireworks2(){}
    virtual ~CCParticleFireworks2(){}
    bool init(){ return initWithTotalParticles(150); }
    virtual bool initWithTotalParticles(unsigned int numberOfParticles);
    static CCParticleFireworks2 * node()
    {
        return create();
    }

    static CCParticleFireworks2 * create()
    {
        CCParticleFireworks2 *pRet = new CCParticleFireworks2();
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