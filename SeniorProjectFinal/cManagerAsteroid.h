#ifndef MANAGE_ASTEROID_H
#define MANAGE_ASTEROID_H
#include <ctime>
#include <random>
#include "cBaseNode.h"

#include "cAsteroid.h"


class ManagerAsteroid : public BaseNode
{
private:
	int maxCuster = 1000;
	time_t start = time(0);
	time_t end = 0;

	float ReleaseTime = 0.05f;

	int tilesFound = 0;
	int currentTile;
	float highestX;
	float lowestX;
	float lowestY;
	float highestY;
	float asteroidSpeed = 0.05;
	float releastTime = 1.7;
	vector <Asteroid> cluster;

	


public:
	
	ManagerAsteroid()
	{
	
	
	}
	ManagerAsteroid(Grid &grid)
	{
		init(grid);
	}
	void init(Grid &grid)
	{
		srand(time(0));
		setBorders
		(
			/*left*/grid.getTilePosX(0),
			/*right*/grid.getTilePosX(grid.getCol() - 1),// - 1) + grid.getTileWidth(0) + (grid.getTileGap() * grid.getCol()),
			/*top*/grid.getTilePosY(0),
			/*bottom*/grid.getTilePosY(grid.getRow() * grid.getCol() - 1)

		);

		this->setPosX(lowestX);
		this->setPosY(highestY);
		this->setPosZ(0.0f);	
	}
	vector<Asteroid> getAsteroids()
	{
		return cluster; 
	}
	Asteroid GetAsteroid(int i)
	{
		return cluster.at(i);
	}
	void resetAstroids()
	{
		this->asteroidSpeed = 0.05;
		this->releastTime = 1.7;
		this->maxCuster = 1000;
	
	
	
	}
	void clearCluster()
	{
	
		this->cluster.clear();
	
	}
	void setMaxCluster(int i)
	{
		this->maxCuster = i;
	
	}
	void printMaxAstroids()
	{
		cout << this->maxCuster;
	
	}
	void deactivateAsteroid(int i)
	{
		cluster.at(i).setActive(false);
	}
	void deleteAteroid(int i)
	{
		cluster.erase(cluster.begin() + i);
	}	

	void reduceAstroidHealth(float i)
	{	
		cluster.at(i).reduceHealth(50);
	}

	float getAsteroidCenterX(int i)
	{
		return cluster.at(i).getCenterX();
	
	}
	float getAsteroidCenterY(int i)
	{
		return cluster.at(i).getCenterY();
	}
	float getAsteroidPosX(int i)
	{
		return cluster.at(i).getPosX();
	}
	float getAsteroidPosY(int i)
	{
		return cluster.at(i).getPosY();
	}
	float getAsteroidPosZ(int i)
	{
		return cluster.at(i).getPosZ();
	}
	int randXPos()
	{		
		 float randPos = lowestX + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (highestX - lowestX)));
		 return randPos;	
	}
	int getClusterSize()
	{
		return this->cluster.size();
	}
	int getCurrentTileID()
	{
		return currentTile;
	}
	void eraseAsteroid(int i)
	{
		cluster.erase(cluster.begin() + i);	
	}
	void setCurrentTileID(int id)
	{
		currentTile = id;
	}

	void setBorders(float left, float right, float top, float bottom)
	{
		lowestX = left;
		highestX = right;
		highestY = bottom;
		lowestY = top;

	}
	void damageEarth(int &health)
	{
		if (health > 0)
		health -= 5;

		if (health < 0)
			health = 0;
	
	}
	void addAsteroid(float x, float y, float z, float h)
	{
		Asteroid Ast(4, 4);
		Ast.setPosX(x);
		Ast.setPosY(y);
		Ast.setPosZ(z);
		Ast.setHeath(h);
		Ast.setActive(true);
		cluster.push_back(Ast);
	
	}
	void releaseAstroid()
	{
		if (end - start > releastTime)
		{
			if (maxCuster > 0)
			{
				Asteroid Ast(4, 4);
				Ast.setPosX(randXPos());
				Ast.setPosY(this->getPosY());
				Ast.setPosZ(this->getPosZ());
				cluster.push_back(Ast);
				start = time(0);
				--maxCuster;
			}
		}
		else
		{
			end = time(0);
		}

		if (maxCuster % 5 == 0)
		{
			this->asteroidSpeed *= 1.002;

		}
	
	
	}
	void projectAsteroid(int &health)
	{
		
		if (cluster.size() > 0)
			for (int i = 0; i < cluster.size(); i++)
			{
			
				float newpos = cluster.at(i).getPosY() - asteroidSpeed;
				cluster.at(i).setPosY(newpos);

				if (cluster.at(i).getPosY() < lowestY )
				{
					cluster.erase(cluster.begin() + i);
					damageEarth(health);
				}
			}
	}





};


#endif // !SPACE_SHIP_H


