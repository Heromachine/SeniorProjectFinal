#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H
#include "cBaseNode.h"
#include "cGrid.h"
#include "cBullet.h"
#include "cMesh.h"

class SpaceShip : public BaseNode
{
	private:
	int tilesFound = 0;
	int currentTile; 
	float health = 20;
	float highestX;
	float lowestX;	
	float lowestY;

	float CenterX;
	float CenterY; 
	float highestY;
	float bulletSpeed = 2.0;
	float radius;
	bool active = true; 

	float hitSum = 0;
	vector <Bullet> clip;

	Mesh model;



	public:
		SpaceShip()
		{
		
		}
		SpaceShip(Grid &grid, int id) 
		{
			init(grid, id);		
		}
		bool isActive()
		{
			return this->active;
		}
		void setActive(bool a)
		{
			this->active = a; 
		}
		void setHealth(float h)
		{
			this->health = h;
		}
		void reduceHealth(float r)
		{
			this->health -= r; 
		}
		void init(Grid &grid, int id)
		{
			int currentTile = id;
			setRadius(2);
			this->setPosX(grid.getTilePosX(id));
			this->setPosY(grid.getTilePosY(id));
			this->setPosZ(0.0f);
			this -> CenterX = this->getPosX() / 2;
			this->CenterY = this->getPosY() / 2;
			setBorders
			(
				/*left*/grid.getTilePosX(0),
				/*right*/grid.getTilePosX(grid.getCol() - 1),// - 1) + grid.getTileWidth(0) + (grid.getTileGap() * grid.getCol()),
				/*top*/grid.getTilePosY(0),
				/*bottom*/grid.getTilePosY(grid.getRow() * grid.getCol() - 1)
			);		
		}
		vector<Bullet> &getClip()
		{
			return this->clip;		
		}
		void InitDraw()
		{
			cout << "INITDRAW";
			Vertex vertices[] =
			{
				Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
				Vertex(glm::vec3(0.0,  0.5, 0), glm::vec2(0.0, 0.0)),
				Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(0.0, 0.0))
			};

			unsigned int indices[] = { 0, 1, 2 };



			Mesh modelTemp(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

			model = modelTemp;
	
		}

		void Draw()
		{
			model.Draw();		
		}
		void eraseBullet(int i)
		{
			clip.erase(clip.begin() + i);
		}
		Bullet &GetBullet(int i)
		{
			return clip.at(i);
		}
		float getHitSum()
		{
			return this->hitSum;
		}
		float getBulletPosX(int i)
		{
			return clip.at(i).getPosX();		
		}
		float getBulletPosY(int i)
		{
			return clip.at(i).getPosY();
		}
		float getBulletPosZ(int i)
		{
			return clip.at(i).getPosZ();
		}
		float getRadius()
		{
			return this->radius;
		}
		float getHealth()
		{
			return this->health;
		}
		int getClipSize()
		{
			return this->clip.size();
		}
		int getCurrentTileID()
		{
			return currentTile;
		}
		void setHitSum(float h)
		{
			this->hitSum = h;
		}
		void setCurrentTileID(int id)
		{
			currentTile = id; 
		}
		void setRadius(float r)
		{
			this->radius = r; 
		}
		float getHighestX()
		{
			return this->highestX;
		}
		float getHighestY()
		{
			return this->highestY;		
		}
		void setBorders(float left, float right ,float top, float bottom )
		{
			lowestX = left;
			highestX = right;
			highestY = bottom;
			lowestY = top;
		
		}
		void moveShipVertical(float y)
		{
			if (this->getPosY() > highestY)
			{
				this->setPosY(highestY -0.01f);
			}else
			if (this->getPosY() <= lowestY)
			{
				this->setPosY(0.0f + 0.03f);
			}	
			
			this->setPosY(this->getPosY() + y);			
		}
		void moveShipHorizontal(float x)
		{
			if (this->getPosX() >= highestX)
			{
				this->setPosX(highestX -0.01f);
				
			}
			else
			if (this->getPosX() <= 0)
			{

				this->setPosX(0.0f + 0.1f);
			}
			
			this->setPosX(this->getPosX() + x);
		}
		void addBullet()
		{
			//cout << "\nCLIP SIZE:" << clip.size() << endl;
			Bullet B(1);
			B.setPosX(this->getPosX());
			B.setPosY(this->getPosY());
			B.setPosZ(this->getPosZ());
			clip.push_back(B);
		}

	
		
		void projectBullets( )
		{
			if (clip.size() > 0)
				for (int i = 0; i < clip.size(); i++)
				{
					float newpos = clip.at(i).getPosY() + bulletSpeed;
					clip.at(i).setPosY(newpos);

					if (clip.at(i).getPosY() > highestY +5)
					{
						clip.erase(clip.begin() + i);
					}
				}


		
		}
		void PrintShip()
		{
		
			cout<< "CURRENT TILE: "<<currentTile <<endl;
			cout << "High X: "<< highestX << endl;
			cout << "Low X: "<<lowestX << endl;
			cout << "Low Y: "<< lowestY << endl;
			cout << "High Y:"<< highestY << endl;
			cout << "(" << this->getPosX() << ", " << this->getPosY() << ")" << endl;
		
		}


};


#endif // !SPACE_SHIP_H

