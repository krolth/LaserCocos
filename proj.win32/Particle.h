#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "cocos2d.h"
using namespace cocos2d;

class Particle
{
public:
	static float gravity;
	static CCRect rectangle;
	static int drawIndex;
	static int color;

	CCPoint pos;
	CCPoint vel;

	float size;
	float attenuation;
};

#endif