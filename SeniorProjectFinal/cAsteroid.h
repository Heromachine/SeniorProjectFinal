#ifndef CLASS_ASTEROID_H
#define CLASS_ASTEROID_H
#include"cBaseNode.h"


class Asteroid : public BaseNode
{
private:

	int iWidth;
	int iHeight;

	float health;
	bool bActive = true;

	float CenterX;
	float CenterY;

	float radius;



public:
	//CONSTRUCTORS
	Asteroid() {}

	Asteroid(int w, int h)
	{
		health = 100;
		iWidth = w;
		iHeight = h;
		radius = w/2; 
		CalCenter();
	}
	Asteroid(int size)
	{
		iWidth = size;
		iHeight = size;
	}


	void CalCenter()
	{
		CenterX = iWidth / 2;
		CenterY = iHeight / 2; 	
	}
	int getCenterX()
	{
		return CenterX;
	}
	int getCenterY()
	{
		return CenterY; 
	}
	int getWidth()
	{
		return iWidth;
	}
	int getHeight()
	{
		return iHeight;
	}
	float getRadius()
	{
		return radius; 
	}
	float getHealth()
	{
		return this->health;
	}
	float reduceHealth(float r)
	{
		
		health -= r;
		cout << "ASTEROID HEALTH: " << getHealth() << endl;
		return this->health;
		
	}



	bool isActive()
	{
		return bActive;
	}
	//VOID FUNCTIONS
	void setWidth(int           w)
	{
		iWidth = w;
	}
	void setHeight(int           h)
	{
		iHeight = h;
	}

	void setActive(bool          b)
	{
		this->bActive = b;
	}
	void setHeath(float h)
	{
		this->health = h; 
	}

};
#endif // !CLASS_Asteroid_H


