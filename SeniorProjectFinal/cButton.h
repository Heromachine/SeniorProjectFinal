#ifndef BUTTON_H
#define BUTTON_H
#include"cRectangle.h"
using namespace std; 

class Button : public Rectangle
{

	bool highlighted = false; 

	int action; 

public: 
	Button()
	{
	
	}
	Button(string n, float x, float y, float z, float w, float h, float r, float g, float b)
	{
		setName(n);
		setPosX(x);
		setPosY(y);
		setPosZ(z);

		setWidth(w);
		setHeight(h);
		
		setRed(r);
		setGre(g);
		setBlu(b);
	}

	void setButtonAttributes(string n, float x, float y, float z, float w, float h, float r, float g, float b)
	{		
		setName(n);
		setPosX(x);
		setPosY(y);
		setPosZ(z);

		setWidth(w);
		setHeight(h);

		setRed(r);
		setGre(g);
		setBlu(b);
	}

	bool isHighlighted()
	{
		return highlighted;
	}
	void setHighlighted(bool b)
	{
		highlighted = b; 
	}
	int getAction()
	{
		return action; 
	}

	void setAction(int action)
	{
		this->action = action;
	}

};

#endif