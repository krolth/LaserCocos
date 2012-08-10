#ifndef __ACTOR_H__
#define __ACTOR_H__

#define SCREEN_WIDTH 465
#define SCREEN_HEIGHT 465
#define PI 3.1416f

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
	static const int SIZE = 45;

	Ship(int width, int height, CCLayer* p) : Actor(tagShip, width, height, p)
	{
		isDestroyed = false;
	}

	virtual void Move(CCPoint newPos)
	{
		if (isDestroyed) return;

		pos = newPos;

		KeepInScreen(-SIZE/2);

		sprite -> setPosition(pos);
	}

	void Update() 
	{
		// Code for this is in the Move method
	}

	void Destroy()
	{
		if (isDestroyed) return;

		//sprite = NULL; // TODO: clean up		
		//AddParticlesRound(300, pos, 10, 10);
		isDestroyed = true;		
		sprite-> setPosition(ccp(0,0));

		//StartGameOver();
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
	static const int WIDTH = 10;

	float angleRadians;
	int speed, width, height;
	CCPoint distanceVector;

public:

	Laser(int x, int y, float a, int s, int h, CCLayer* p) : Actor(tagLaser, WIDTH, h, p)
	{
		angleRadians = a;
		speed = s;
		width = WIDTH;
		height = h;

		pos.x = x;
		pos.y = y;		
		
		sprite->setPosition(ccp(x,y));
		sprite->setRotation(CC_RADIANS_TO_DEGREES(a));
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
			else if (d < width / 2 + ship->SIZE)
			{
				float a = PI/2;
				if (distanceVector.x <0) a = -a;
				a+= angleRadians;

				int n = speed * (width / 2 + ship->SIZE) / d;
				//addParticlesAngle(n/3, ship.pos , a, speed);
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