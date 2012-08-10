#include "Particle.h"

using namespace cocos2d;

bool CCParticleFireworks2::initWithTotalParticles(unsigned int numberOfParticles)
{
    if( CCParticleSystemQuad::initWithTotalParticles(numberOfParticles) )
    {
        // duration
        m_fDuration = kCCParticleDurationInfinity;

        // Gravity Mode
        m_nEmitterMode = kCCParticleModeGravity;

        // Gravity Mode: gravity
        modeA.gravity = ccp(-200,200);

        // Gravity Mode: speed of particles
        modeA.speed = 15;
        modeA.speedVar = 5;

        // Gravity Mode: radial
        modeA.radialAccel = 0;
        modeA.radialAccelVar = 0;

        // Gravity Mode: tagential
        modeA.tangentialAccel = 0;
        modeA.tangentialAccelVar = 0;

        // angle
        m_fAngle = 0;
        m_fAngleVar = 360;

        // emitter position
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        this->setPosition(ccp(winSize.width/2, winSize.height/2));
        m_tPosVar = CCPointZero;

        // life of particles
        m_fLife = 2;
        m_fLifeVar = 1;

        // size, in pixels
        m_fStartSize = 60.0f;
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