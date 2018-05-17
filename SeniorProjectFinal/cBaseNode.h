#ifndef BASE_NODE_H
#define BASE_NODE_H
#include <vector>

#include "cBaseEntity.h"
using namespace std; 


class BaseNode : public BaseEntity
{
private: 
	float X = 0;
	float Y = 0;
	float Z = 0;


	bool bVisited = false;
	int ParentID;


	vector<float> vecPos;

public:
	BaseNode() {}
	virtual ~BaseNode() {}


	
	BaseNode(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;

		vecPos.push_back(X);
		vecPos.push_back(Y);
		vecPos.push_back(Z);
	}

	bool isVisited()
	{
		return this->bVisited;
	}

	
	void setIsVisited(bool          b)
	{
		this->bVisited = b;
	}
	void setPosition(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;

		vecPos.push_back(X);
		vecPos.push_back(Y);
		vecPos.push_back(Z);
	}

	void setPosX(float x)
	{
		this->X = x;
	}
	void setPosY(float y)
	{
		Y = y;
	}
	void setPosZ(float z)
	{
		Z = z;
	}
	float getPosX()
	{
		return X;
	}
	float getPosY()
	{
		return Y;
	}
	float getPosZ()
	{
		return Z;
	}

	vector<float> getVectPos()
	{
		return vecPos;
	}

};
#endif // !BASE_NODE_H

