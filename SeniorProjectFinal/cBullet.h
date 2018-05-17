#ifndef CLASS_BULLET_H
#define CLASS_BULLET_H
#include"cBaseNode.h"


class Bullet : public BaseNode
{
private:
	
	int iWidth;
	int iHeight;

	bool bActive = true;
	float radius; 

public:
	//CONSTRUCTORS
	Bullet() {}
	Bullet(int w, int h)
	{
		iWidth = w;
		iHeight = h;
		radius = w / 2;
	}
	Bullet(int size)
	{
		iWidth = size;
		iHeight = size;
		radius = size;
	}

	//FLOAT FUNCTIONS

	//INT FUNCTIONS

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

	//STRING FUNCTIONS
	//BOOL FUNCTIONS
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


};
#endif // !CLASS_TILE_H

