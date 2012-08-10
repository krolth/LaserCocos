#include "Particle.h"

using namespace cocos2d;

bool CCParticlePlayerTrail::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( CCParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        m_fDuration = kCCParticleDurationInfinity;

        // Gravity Mode
        m_nEmitterMode = kCCParticleModeGravity;

        // Gravity Mode: gravity
        modeA.gravity = ccp(0,0);
		
        // Gravity Mode: radial
        modeA.radialAccel = 0;
        modeA.radialAccelVar = 0;

        // Gravity Mode: speed of particles
        modeA.speed = 150;
        modeA.speedVar = 10;
		
        // angle
        m_fAngle = 90;
        m_fAngleVar = 10;

        // emitter position
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        this->setPosition(ccp(winSize.width/2, winSize.height/2));
        m_tPosVar = CCPointZero;

        // life of particles
        m_fLife = 3;
        m_fLifeVar = 1;

        // size, in pixels
        m_fStartSize = 54.0f;
        m_fStartSizeVar = 10.0f;
        m_fEndSize = kCCParticleStartSizeEqualToEndSize;

        // emits per second
        m_fEmissionRate = m_uTotalParticles/m_fLife;

        // color of particles
        m_tStartColor.r = 0.2f;
        m_tStartColor.g = 0.4f;
        m_tStartColor.b = 0.7f;
        m_tStartColor.a = 1.0f;
        m_tStartColorVar.r = 0.0f;
        m_tStartColorVar.g = 0.0f;
        m_tStartColorVar.b = 0.2f;
        m_tStartColorVar.a = 0.1f;
        m_tEndColor.r = 0.0f;
        m_tEndColor.g = 0.0f;
        m_tEndColor.b = 0.0f;
        m_tEndColor.a = 1.0f;
        m_tEndColorVar.r = 0.0f;
        m_tEndColorVar.g = 0.0f;
        m_tEndColorVar.b = 0.0f;
        m_tEndColorVar.a = 0.0f;

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

bool CCShipExplosion::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( CCParticleSystemQuad::initWithTotalParticles(numberOfParticles) ) 
    {
        // duration
        m_fDuration = 0.1f;

        m_nEmitterMode = kCCParticleModeGravity;

        // Gravity Mode: gravity
        modeA.gravity = ccp(0,0);

        // Gravity Mode: speed of particles
        modeA.speed = 70;
        modeA.speedVar = 40;

        // Gravity Mode: radial
        modeA.radialAccel = 0;
        modeA.radialAccelVar = 0;

        // Gravity Mode: tagential
        modeA.tangentialAccel = 0;
        modeA.tangentialAccelVar = 0;

        // angle
        m_fAngle = 90;
        m_fAngleVar = 360;

        // emitter position
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        this->setPosition(ccp(winSize.width/2, winSize.height/2));
        m_tPosVar = CCPointZero;

        // life of particles
        m_fLife = 5.0f;
        m_fLifeVar = 2;

        // size, in pixels
        m_fStartSize = 15.0f;
        m_fStartSizeVar = 10.0f;
        m_fEndSize = kCCParticleStartSizeEqualToEndSize;

        // emits per second
        m_fEmissionRate = m_uTotalParticles/m_fDuration;

        // color of particles
        m_tStartColor.r = 0.2f;
        m_tStartColor.g = 0.4f;
        m_tStartColor.b = 0.7f;
        m_tStartColor.a = 1.0f;
        m_tStartColorVar.r = 0.0f;
        m_tStartColorVar.g = 0.0f;
        m_tStartColorVar.b = 0.2f;
        m_tStartColorVar.a = 0.1f;
        m_tEndColor.r = 0.0f;
        m_tEndColor.g = 0.0f;
        m_tEndColor.b = 0.0f;
        m_tEndColor.a = 1.0f;
        m_tEndColorVar.r = 0.0f;
        m_tEndColorVar.g = 0.0f;
        m_tEndColorVar.b = 0.0f;
        m_tEndColorVar.a = 0.0f;

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}