#ifndef CRECTANGLE_H
#define CRECTANGLE_H
#include "cBaseNode.h"


class Rectangle : public BaseNode
{
private:
	float fLength;
	float fWidth;
	float r = 1.0f, b = 1.0f, g = 1.0f;
	float w, h; 
	string name;

public:
	Rectangle()
	{
		
	}

	Rectangle(string n, float x, float y, float z, float r, float g, float b)
	{
		this->setPosX(x);
		this->setPosX(y);
		this->setPosX(z);
		this->setRed(r);
		this->setGre(g);
		this->setBlu(b);
	};

	float getCr() { return this->r; }
	float getCg() { return this->g; }
	float getCb() { return this->b; }
	float getWidth	() { return w; }
	float getHeight	() { return h; }
	string getName() { return name; }
	void setRed(float r) { this->r = r; }
	void setGre(float g) { this->g = g; }
	void setBlu(float b) { this->b = b; }
	void setWidth(float w) { this->w = w; }
	void setHeight(float h) { this->h = h; }
	void setName(string n) { name = n; }

}; 
#endif // !CRECTANGLE_H