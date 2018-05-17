#ifndef CLASS_GRID_H
#define CLASS_GRID_H
#include <iostream>
#include<vector>
#include <fstream>
#include<string>
#include <math.h>
#include <time.h> 
#include<queue>
#include<stack>
#include "cBaseNode.h"
#include "cTile.h"



using namespace std;

class Grid : public BaseNode
{
private:
	vector<Tile> tiles;

	vector<int> viUnknownNodes;//Nodes not been visted or acknowledged by agent
	vector<int> viVisitedNodes;//Nodes that have been visited by agent
	vector<int> viPendingNodes;//Nodes that have been aknowledge by agent, but visited
	vector<int> viObsticleNodes;//Nodes agent cannot access or tries to avoid
	queue<int> qBFS;

	int col = 0;
	int row = 0;
	int tileH;
	int tileW;
	int modulous; 
	int iDirtyAmount = 0;
	float tileGap = 0.0f;

	
public:
	//CONSTRUCTORS
	//
	Grid() 
	{	
		//this->CreateGridSquare(2, 2, 0.0f , 0.0f );	
	};

	Grid(int gridsize, int tilesize, int gapsize)
	{
		initSquareGrid(gridsize, tilesize, gapsize);	
	}
	Grid(int x, int y, int z, string fileName, int tilesize)
	{
		this->setPosX(0);
		this->setPosY(0);
		this->setPosZ(0);
		LoadGrid2(fileName, tilesize);
	}

	Grid(string fileName, float tilesize, float gapsize)
	{
		initLoad(fileName, tilesize, gapsize);
	}

	Grid(int x, int y, int z, int tilesize, int gridsize, int percent)
	{	

		
		setPosition(x, y, z);
		modulous = gridsize;

		
		for (int i = 0; i < gridsize*gridsize; i++)
		{


			Tile t(tilesize);

			t.setClean(dirtyChance(percent));

			if (t.isClean() == false)
			{
				t.setTileValue('x');
			}
			else
			{
				t.setTileValue(' ');
			}
			

			
			t.setID(i);
			if (t.getID() > 0)
			{
				t.setPosY(this->getPosY());

				if (i%modulous == 0)
				{					
					t.setPosX(this->getPosX());					
					t.setPosZ(tiles.at(i - gridsize).getPosZ() -tilesize);
				}
				else
				{
					t.setPosX(tiles.at(i - 1).getPosX() + gridsize);
					t.setPosZ(tiles.at(i - 1).getPosZ());					
				}		
			}
			else
			{
				t.setPosition(this->getPosX(), this->getPosY(), this->getPosZ());			
			}

			tiles.push_back(t);
		}	
		
	}
	
	void initSquareGrid(int gridsize, int tilesize, int gapsize)
	{
		tileH = tilesize;
		tileW = tilesize;
		tileGap = gapsize;
		this->CreateGridSquare(gridsize, tilesize, 0.0f, 0.0f);	
	}
	void initLoad(string fileName, float tilesize, float gapsize)
	{
		this->setPosX(0);
		this->setPosY(0);
		this->setPosZ(0);
		this->tileW = tilesize;
		this->tileH = tilesize;
		this->tileGap = gapsize;
		LoadGrid2(fileName, tilesize);
	
	}
	
	//GRID FUNCTIONS GETTERS AND SETTERS
	vector<float> getGridVectorPos()
	{
		return getVectPos();
	}
	vector<float> getTileVectorPos(int i)
	{
		return tiles.at(i).getVectPos();
	
	}
	int getDirtyAmount()
	{
		return this->iDirtyAmount;
	}
	int getCol()
	{
		return col;
	}
	int getRow()
	{
		return row; 
	}
	int getTileH()
	{
		return tileH;
	}
	int getTileW()
	{
		return tileW;
	}
	int getMod()
	{
		return modulous;
	}
	int getTileGap()
	{
		return tileGap;
	}
	
	bool dirtyChance(int percent)
	{
		//srand(time(NULL));
		int chance = (rand() % 100 + 1);


		if (chance < percent)
		{
			iDirtyAmount += 1;
			return false;

		}
		else
			return true;


	}
	bool isTileNeighborsFound(int id)
	{
		return this->tiles.at(id).isNeigborsFound();
	}

	void setCol(int c)
	{
		col = c;
	}
	void setRow(int r)
	{
		row = r; 
	}
	void setTileGap(int g)
	{
		tileGap = g;
	}
	
	//GRID ACTION FUNCTIONS
	void setTilePosition(Tile &t, int gridsize, int tilesize)
	{
		if (t.getID() > 0)
		{

			t.setPosY(this->getPosY());

			if (t.getID() % col == 0)
			{
				t.setPosX(this->getPosX());
				t.setPosZ(tiles.at(t.getID() - gridsize).getPosZ() - tilesize);
			}
			else
			{
				t.setPosX(tiles.at(t.getID() - 1).getPosX() + gridsize);
				t.setPosZ(tiles.at(t.getID() - 1).getPosZ());
			}
		}
		else if (t.getID() <= 0)
		{
			t.setPosition(this->getPosX(), this->getPosY(), this->getPosZ());
		}
		else
		{
			cout << "\n====================================================================\n";
		}


	}
	void consolePrintGrid()
	{
		cout << "Col: " << col << endl;
		cout << "Row: " << row << endl;
		cout << "Tile: " << tileH << "x" << tileW << endl; 
		cout << "Gap: " << tileGap << endl;
		for (int i = 0; i < row*col; i++)
		{
			if (i % row == 0)
			{
				cout << "\n";
			}			
			tiles.at(i).printTileInfoQuick();
		}
	}
	void consolePrintFloorGrid()
	{
		cout << "\n ===================================================\nGRID: \n";
		cout << "Dirty Tiles: " << iDirtyAmount << endl;
		for (int i = 0; i < modulous*modulous; i++)
		{
			if (i % modulous == 0)
			{
				cout << "\n";
			}

			//cout << "\n";
			cout << "[" << tiles.at(i).getValue() << "]";

		}


	}
	void LoadGrid(const string& fileName, int tilesize)
	{
		int x = 0;
		ifstream file;
		file.open((fileName).c_str());

		string line;

		if (file.is_open())
		{
			//cout << "\n\nFILE " << fileName << " is open" << endl;

			while (file.good())
			{
				getline(file, line);

				int linesize = line.size();

				for (int i = 0; i < linesize; i++)
				{
					char currentChar = line.at(i);
					if (currentChar == ' ')
					{
						continue;
					}
					else
					{
						Tile t(tilesize);
						t.setID(x);
						t.setTileValue(currentChar);
						tiles.push_back(t);
						x++;
					}
				}
			}
		}
		else
		{
			cerr << "UNABLE OPEN FILE" << fileName << endl;
		}

		int a_sqrt = sqrt(x);
		int b_sqrt = a_sqrt;
		//cout << x << "<-------------x\n";
		if (a_sqrt == b_sqrt);
		{
			modulous = a_sqrt;
			//cout << modulous << "<-------------Mod\n";
			for (int i = 0; i < x; i++)
			{

				this->setTilePosition(this->tiles.at(i), modulous, tilesize);
				//this->tiles.at(i).printTileInfo();

			}
		}

		cout << "\n GRID SIZE: " << (modulous * modulous) << endl;
		//this->consolePrintGrid();
	}
	void LoadGrid2(const string& fileName, int tilesize)
	{

		int x = 0;
		ifstream file;
		file.open((fileName).c_str());
		string line;
		stack<Tile> tempstack; 
		if (file.is_open())
		{
			cout << "\===================:"<< endl;
			cout << "Row: " << row << endl;
			cout << "Col: " << col << endl;
			cout << "Tile Size: " << tiles.size() << endl;
			cout << "\===================:" << endl;
			
			while (file.good())
			{
				col = 0;
				getline(file, line);

				int linesize = line.size();
				++row;

				for (int i = 0; i < linesize; i++)
				{
					char currentChar = line.at(i);
					if (currentChar == ' ')
					{
						continue;
					}
					else
					{						 
						++col;
						Tile t(tilesize);
						t.setID(x);
						t.setTileValue(currentChar);
						tiles.push_back(t);
						
						x++;
					}
				}
			}
		}
		else
		{
			cerr << "UNABLE OPEN FILE" << fileName << endl;
		}



		CreateGridAny(tilesize);
	}
	void CreateGridSquare(int size, int tilesize, float x, float y)
	{
		this->setPosX(x);
		this->setPosY(y);
		this->setRow(size);
		this->setCol(size);
		int id = 0;
		for (int r = 0; r < this->row; r++)
			for (int c = 0; c < this->col; c++)
			{
				int forx = (c * tilesize) + (tileGap * c);
				int fory = (r * tilesize) + (tileGap * r);
				Tile temp;
				temp.setPosX((float)forx);
				temp.setPosY((float)fory);
				temp.setID(id);
				temp.setHeight(tilesize);
				temp.setWidth(tilesize);
				tiles.push_back(temp);
				
				id++;
			}	
		
	}
	void CreateGridAny(float tilesize)
	{

		cout << "\nCreating GridANY" << endl; 
		int id = 0;
		for (int r = 0; r < this->row; r++)
			for (int c = 0; c < this->col; c++)
			{
				int forx = (c * tilesize) + (tileGap * c);
				int fory = (r * tilesize) + (tileGap * r);
				tiles[id].setPosX((float)forx);
				tiles[id].setPosY((float)fory);
				tiles[id].setID(id);
				tiles[id].setHeight(tilesize);
				tiles[id].setWidth(tilesize);
				id++;
			}

		//this->consolePrintGrid();
	}
	void decreaseDirtyAmount()
	{
		this->iDirtyAmount -= 1;

	}
	
	///////////////////////////////////////TILE FUNCTIONS///////////////////////////////////////////////////
	char  getTileValue     (int id)
	{
		return this->tiles.at(id).getValue();
	}
	float getTilePosX      (int id)
	{
		return this->tiles.at(id).getPosX();
	}
	float getTilePosY      (int id)
	{
		return this->tiles.at(id).getPosY();
	}
	float getTileHCost(int id)
	{
		return tiles.at(id).getHCost();
	}
	float getTileGCost(int id)
	{
		return tiles.at(id).getGCost();
	}
	float getTileFCost(int id)
	{
		return tiles.at(id).getFCost();
	}
	int   getTilePoints(int id) 
	{ return tiles.at(id).getPoints(); }
	int   getTileWidth     (int id)
	{
		return this->tiles.at(id).getWidth();
	}
	int   getTileHeight    (int id)
	{
		return this->tiles.at(id).getHeight();
	}
	int   getTileID        (int id)
	{
		return this->tiles.at(id).getID();
	}
	int   getTileParentNode(int id)
	{
		return tiles.at(id).getParentNode();
	}
	bool  isTileClean      (int id)
	{
		return this->tiles.at(id).isClean();

	}
	bool  isTileVisited    (int id)
	{
		return this->tiles.at(id).isVisited();
	}
	bool  isTileNeborsFound(int id)
	{
		return this->tiles.at(id).isNeigborsFound();
	}

	void setTIleParentNode(int id, int p)
	{
		tiles.at(id).setParentNode(p);	
	}
	void setTilePosX         (int id, float  x)
	{
		this->tiles.at(id).setPosX(x);	
	}
	void setTilePosY         (int id, float  y)
	{
		this->tiles.at(id).setPosX(y);
	}
	void setTileWidth        (int id, int w)
	{
		tiles.at(id).setWidth(w);
	}
	void setTileHeight        (int id, int h)
	{
		tiles.at(id).setHeight(h);
	}
	void setTileClean        (int id, bool b)
	{
		tiles.at(id).setClean(b);
	}
	void setTileValue        (int id, char val)
	{
		this->tiles.at(id).setTileValue(val);
	}
	void setTileNeigborsFound(int id, bool b)
	{
		this->tiles.at(id).setIsNeigborsFound(b);
	}	
	void setTileVisited      (int id, bool   b)
	{		this->tiles.at(id).setIsVisited(b);   }
	void setTilePoints(int id, int points)
	{
		tiles.at(id).setPoins(points);
	}
	void setTileHCost(int id, float h)
	{
		tiles.at(id).setHCost(h);		
	}
	void setTileGCost(int id, float g)
	{
		tiles.at(id).setGCost(g);
	}
	void setTileFCost(int id, float f)
	{
		tiles.at(id).setFCost(f);
	}
	
	void incrimentTileTimesVisited(int id)
	{
		tiles.at(id).incrimentPoints();
	
	}
	///////////////////////////////////////TILE FUNCTIONS///////////////////////////////////////////////////



};
#endif // !CLASS_GRID_H

