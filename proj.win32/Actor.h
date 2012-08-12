#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "Particle.h"
#include "Constants.h"

using namespace cocos2d;

enum
{
    tagShip = 0,
	tagLaser = 1,
};

class Actor
{
public:
	CCPoint pos;
	CCSprite* sprite;
	CCLayer* parent;
	int tag;

	Actor(int type, int width, int height, CCLayer* p)
	{
		parent = p;
		tag = type;

		InitializeActor(width, height);		
	}

private:
	void InitializeActor(int width, int height)
	{
		if (tag == tagShip)
		{
			sprite = CCSprite::create("player.png");
		}
		else
		{
			sprite = CCSprite::create("laser-b.png");
		}
	}
};

class Ship : public Actor
{
	bool isDestroyed;
	
public:

	static CCParticlePlayerTrail* Trail;
	static CCShipExplosion* Explosion;

	Ship(int width, int height, CCLayer* p) : Actor(tagShip, width, height, p)
	{
		isDestroyed = false;
	}

	virtual void Move(CCPoint newPos)
	{
		if (isDestroyed) return;

		pos = newPos;

		KeepInScreen(-SHIP_SIZE/2);

		sprite->setPosition(pos);

		// This will be set by the laser
		Ship::Trail->isEnabled = false;
		parent->removeChild(Ship::Trail, false);
	}

	void Update() 
	{
		// Code for this is in the Move method
	}

	void Destroy()
	{
		if (isDestroyed) return;

		isDestroyed = true;
				
		Ship::Trail->isEnabled = false;
		parent->removeChild(Ship::Trail, false);
		//sprite->setPosition(ccp(0,0));
		parent->removeChild(sprite, false);
				
		Ship::Explosion->setPosition(pos);
		parent->addChild(Ship::Explosion, 10);

		//StartGameOver();
	}

	void Graze(int impact, float angle)
	{
		if (!Ship::Trail->isEnabled)
		{
			parent->addChild(Ship::Trail, 10);
			Ship::Trail->isEnabled = true;
		}
		Ship::Trail->setPosition(pos);

		// We convert the angle from the sprite angle to a particle angle
		// The sprite angle: Right is 90 degrees and up is 0 (clockwise). Particle angle right is 0 and up is 90 (CCW)
		float particleAngle = 450 - angle + 180; 
		Ship::Trail->setAngle(particleAngle);
	}

	void NoImpact()
	{
		Ship::Trail->isEnabled = false;
		parent->removeChild(Ship::Trail, false);

		Ship::Trail->killAll();
	}

	bool IsDestroyed()
	{
		return isDestroyed;
	}

private:
	void KeepInScreen(float spacing)
	{
		if (pos.x < -spacing) pos.x = -spacing;
		else if (pos.x > SCREEN_WIDTH + spacing) pos.x = SCREEN_WIDTH + spacing;

		if (pos.y < -spacing) pos.y = -spacing;
		else if (pos.y > SCREEN_HEIGHT + spacing) pos.y = SCREEN_HEIGHT + spacing;
	}
};

class Laser : public Actor
{
	float angleRadians;
	int speed, width, height;
	CCPoint distanceVector;

public:

	Laser(int x, int y, float a, int s, CCLayer* p) : Actor(tagLaser, LASER_WIDTH, LASER_HEIGHT, p)
	{
		angleRadians = a;
		speed = s;
		width = LASER_WIDTH;
		height = LASER_HEIGHT;

		pos.x = x;
		pos.y = y;		
		
		sprite->setPosition(ccp(x,y));

		float deg = CC_RADIANS_TO_DEGREES(a);
		sprite->setRotation(deg);
	}

	bool Update(Ship* ship) 
	{
		UpdatePosition();
		if (!ship->IsDestroyed()) CheckHit(ship);

		// Draw
		sprite->setPosition(ccp(pos.x,pos.y));

		return pos.y < SCREEN_HEIGHT + height /2; // do we need to remove from list?
	}

	void CheckHit(Ship* ship)
	{
		// get the distance vector
		distanceVector.x = ship->pos.x - pos.x;
		distanceVector.y = ship->pos.y - pos.y;

		// transform to the laser point of reference :)
		TransformDistanceVectorToLaserPoR();
		
		if (abs(distanceVector.y) < height/2)
		{

			float d = abs(distanceVector.x);
			if (d<width/2)
			{
				ship->Destroy();
			}
			else if (d < width / 2 + SHIP_SIZE)
			{
				float a = PI/2;
				if (distanceVector.x <0) a = -a;
				a+= angleRadians;

				int impact = speed * (width / 2 + SHIP_SIZE) / d;
				ship->Graze(impact/3, CC_RADIANS_TO_DEGREES(angleRadians));
				//addParticlesAngle(impact/3, ship.pos , a, speed);
				//score += n;
			}
		}
	}

	void UpdatePosition()
	{
		pos.x += sin(angleRadians) * speed;
		pos.y += cos(angleRadians) * speed;
	}

	void TransformDistanceVectorToLaserPoR()
	{
		float temp = distanceVector.x;
		distanceVector.x = distanceVector.x * cos(angleRadians) - distanceVector.y * sin(angleRadians);
		distanceVector.y = temp * sin(angleRadians) + distanceVector.y * cos(angleRadians);
	}
};

#endif