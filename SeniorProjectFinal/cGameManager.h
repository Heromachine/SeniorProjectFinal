#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <iostream>
#include <vector>
#include "cButton.h"
#include "cAsteroid.h"
#include "SpaceShip.h"
#include "cManagerAsteroid.h"
#include "cGrid.h"



using namespace std; 
struct SaveGameInfo
{
	float ShipHealth;
	float ShipX;
	float ShipY;
	float ShipZ;
	float EarthHealth;

};

class GameManager
{
private:
	vector <Button> Buttons;


	Button ButtonHightlight;
	SpaceShip Ship;
	Grid grid;
	ManagerAsteroid MA;

	string SavedGameFile;

	int Money = 100;
	int EarthHealth = 100; 
	int Waves = 0;
	enum Pages {MAINMENU = 0, LOADGAME = 2, OPTIONS = 3, GAMEPLAY = 1, PAUSE = 4, GAMEOVER = 5, IDLE = 6};

	bool GamePaused = false; 
	bool GameOver = false;
	bool GameActive = true; 
	int currentButton = 0;
	int page = 0;

public:


	GameManager()
	{		
		grid.initLoad("Grid.txt", 3, 0);
		//grid.initSquareGrid(20, 2, 1);
		Ship.init(grid, 4);
		MA.init(grid);
		loadMainMenu();	
	}


	int getPage()
	{
		return this->page;
	}
	int getCurrentButton()
	{
		return this->currentButton;
	}
	void resetEarthHealth()
	{
		this->EarthHealth = 100;
		
	}
	bool isGameOver()
	{
		return this->GameOver;
	}
	int getEarthHealth()
	{
		return this->EarthHealth;
	
	}
	void Update()
	{

		switch (page)
		{
			case MAINMENU:
				//ROATES SHIP
				break;

			case GAMEPLAY:
				MA.releaseAstroid();
				MA.projectAsteroid(this->EarthHealth);
				Ship.projectBullets();
				CalShipAsteroidDistance();
				CalBulletAstroidDistance();
				updateScore();
				break;

			default :
				break;
		}
		
		
	}


	void updateScore()
	{
		if (Ship.getHealth() <= 0 || this->EarthHealth <= 0)
		{
		
			setPage(7);
			Action(7);
			
			//GameOver = true;


		}
 
	}
	void LoadGamePlay()
	{
		grid.initLoad("Grid.txt", 3, 0);
		//grid.initSquareGrid(20, 2, 1);
		Ship.init(grid, 4);
		
		MA.init(grid);
		loadMainMenu();	
	}
	void LoadGame(const string& fileName, int game)
	{
		
			ifstream file;
			file.open((fileName).c_str());
			string line;
			std::string::size_type sz;
			if (file.is_open())
			{
				while (file.good())
				{
					getline(file, line);

					if (line == "[WAVE]")
					{
						getline(file, line);
						Waves = (stof(line, &sz));
					}

					if (line == "[EARTH]")
					{
						getline(file, line);
						EarthHealth = (stof(line, &sz));
					}

					
					if (line == "[SHIP]")
					{

						getline(file, line);
						Ship.setPosX(stof(line, &sz));
						getline(file, line);
						Ship.setPosY(stof(line, &sz));
						getline(file, line);
						Ship.setPosZ(stof(line, &sz));
						getline(file, line);
						Ship.setHealth(stof(line, &sz));
					}

					if (line == "[ASTEROIDS]")
					{
						int i = 0;
						getline(file, line);
						while (line != "[END]")
						{
							++i;
							
							float x = stof(line, &sz);
							getline(file, line);
							float y = stof(line, &sz);
							getline(file, line);
							float z = stof(line, &sz);
							getline(file, line);
							float h = stof(line, &sz);
							MA.addAsteroid(x, y, z, h);
							getline(file, line);
						}

						MA.setMaxCluster(100 - i);
					}
				}
			}
			else
			{
				cout << "ERROR: FILE NOT OPEN" << endl; 
			}

			MA.printMaxAstroids();
	}

	void SaveGame()
	{

		ofstream myfile; 
		myfile.open("./res/saves/SavedGame.gs");
		{
			myfile << "[WAVE]" << endl; 
			myfile << Waves << endl;
			myfile << "[END]" << endl;

			myfile << "[EARTH]" << endl;
			myfile << EarthHealth << endl;
			myfile << "[END]" << endl;

			myfile << "[SHIP]" << endl;
			myfile << Ship.getPosX()<<endl;
			myfile << Ship.getPosY() << endl;
			myfile << Ship.getPosZ() << endl;
			myfile << Ship.getHealth() << endl;
			myfile << "[END]" << endl;

			myfile << "[ASTEROIDS]"<<endl;
			if (MA.getClusterSize() == 0)
			{
				myfile << "[END]" << endl;
			}
			else
			{
				for (int i = 0; i < MA.getClusterSize(); i++)
				{
					myfile << MA.GetAsteroid(i).getPosX() << endl;
					myfile << MA.GetAsteroid(i).getPosY()<< endl;
					myfile << MA.GetAsteroid(i).getPosZ()<< endl;
					myfile << MA.GetAsteroid(i).getHealth() << endl;					
				}
			}
			myfile << "[END]" << endl;
		}	
	}

	
	void Action(int action)
	{
		cout << "\nACTION: " << action;

		switch (action)
		{
			case 0: // Start Page
				loadMainMenu();
				break; 
			case 1:
				MA.resetAstroids();
				MA.clearCluster();
				this->EarthHealth = 100;
				Ship.setHealth(20);
				Ship.setHitSum(0);
				GameOver = false;
				break;
			case 2:
				LoadGame("./res/saves/SavedGame.gs", 0);
				break;
			case 3:
				ExitGame();
				break;
			case 4: //In Game Menu
				loadInGameMenu();
				
				break;
			case 5://Controlls page
				loadControllsMenu();
				break; 
			case 6:
				SaveGame();
				ExitGame();
				break;
			case 7://GAME OVER
				LoadGameOver();
				break; 
		
		}
 		cout << "\nPAGE: " << page<<endl;

	}
	void ExitGame()
	{
		SaveGame();
		exit(0);	
	}
	void UpdateHightlight( vector<Button> &bttns)
	{
		ButtonHightlight.setButtonAttributes
		(
			"HightLight", 
			bttns.at(currentButton).getPosX()-1, 
			bttns.at(currentButton).getPosY() -1, 
			bttns.at(currentButton).getPosZ() -1, 
			bttns.at(currentButton).getWidth()+ 1, 
			bttns.at(currentButton).getHeight()+2, 
			0.0, 1.749, 2
		);

	}
	void HighlightDown(vector<Button> &bttns)
	{
		
		if (currentButton < bttns.size() - 1)
		{
			bttns.at(currentButton).setHighlighted(false);
			++currentButton;
			bttns.at(currentButton).setHighlighted(true);
		}
		else if (currentButton == bttns.size() - 1)
		{
			bttns.at(currentButton).setHighlighted(false);
			currentButton = 0;
			bttns.at(currentButton).setHighlighted(true);
		}
		
		UpdateHightlight(bttns);
		cout << endl << "CURRENT BUTTON: " << currentButton;
	
	}
	void HighlightUp(vector<Button> &bttns)
	{

		if (currentButton > 0)
		{
			bttns.at(currentButton).setHighlighted(false);
			--currentButton;
			bttns.at(currentButton).setHighlighted(true);
		}
		else if (currentButton == 0)
		{
			bttns.at(currentButton).setHighlighted(false);
			currentButton = bttns.size() - 1;
			bttns.at(currentButton).setHighlighted(true);
		}

		UpdateHightlight(bttns);
		cout << endl << "CURRENT BUTTON: " << currentButton;
	}
	void ClearButtons()
	{
		Buttons.clear();
	}
	void loadMainMenu()
	{
		ClearButtons();
		Button StartGame("Start Game",	70 ,  11, 0,  40,  3, 0.863, 0.863, 0.863);
		Button LoadGame("LoadGame"   ,	50,  6,  0,  60,  4, 0.863, 0.863, 0.863);
		Button Options("Options"   ,	30 ,  0,  0,  80,  5, 0.863, 0.863, 0.863);

		StartGame.setAction(1);
		LoadGame.setAction(2);
		Options.setAction(3);

		StartGame.setHighlighted(true);

		Buttons.push_back(StartGame);
		Buttons.push_back(LoadGame);
		Buttons.push_back(Options);

		UpdateHightlight(Buttons);
	
	}

	void loadInGameMenu()
	{
		ClearButtons();
		Button Continue("Continue",  60, 15, 0, 50, 4, 0.863, 0.863, 0.863);
		Button Controlls("Controls", 60, 10, 0, 50, 4, 0.863, 0.863, 0.863);
		Button ExitGame("Exit Game", 60, 5, 0, 50, 4, 0.863, 0.863, 0.863);

		Continue.setAction(1);
		Controlls.setAction(5);
		ExitGame.setAction(6);

		Continue.setHighlighted(true);

		Buttons.push_back(Continue);
		Buttons.push_back(Controlls);
		Buttons.push_back(ExitGame);

		UpdateHightlight(Buttons);
	}

	void loadControllsMenu()
	{
		ClearButtons();
		Button ExitControllsPage("Back", 50, 6, 0, 60, 4, 0.863, 0.863, 0.863);
		Button ExitGame("Exit Game", 30, 0, 0, 80, 5, 0.863, 0.863, 0.863);


		ExitControllsPage.setAction(1);
		ExitGame.setAction(4);

		ExitControllsPage.setHighlighted(true);

		Buttons.push_back(ExitControllsPage);
		Buttons.push_back(ExitGame);

		UpdateHightlight(Buttons);
	}

	void LoadGameOver()
	{
		ClearButtons();
		Button ExitControllsPage("Try Again", 50, 6, 0, 60, 4, 0.863, 0.863, 0.863);
		Button ExitGame("Exit Game", 30, 0, 0, 80, 5, 0.863, 0.863, 0.863);


		ExitControllsPage.setAction(1);
		ExitGame.setAction(6);

		ExitControllsPage.setHighlighted(true);

		Buttons.push_back(ExitControllsPage);
		Buttons.push_back(ExitGame);

		UpdateHightlight(Buttons);	
	
	}

	
	void CalShipAsteroidDistance()
	{
		for (int a = 0; a < this->MA.getClusterSize(); a++)
		{
			if (MA.GetAsteroid(a).isActive())
			{
				if (
					CalDistance
					(
						MA.GetAsteroid(a).getPosX(),
						MA.GetAsteroid(a).getPosY(),
						Ship.getPosX(),
						Ship.getPosY()
					)
					<
					(
						MA.GetAsteroid(a).getRadius() + Ship.getRadius())
					)
				{
					float hs = MA.GetAsteroid(a).getRadius()* .3;
					Ship.setHitSum(Ship.getHitSum() + hs);
					Ship.reduceHealth(hs);
					//cout << Ship.getHealth();

				
					if (Ship.getHealth() <= 0) 
					{
						Ship.setActive(false);
					}
				}
			}
		}

	}
	void CalBulletAstroidDistance()
	{	
		
		for (int a = 0; a < this-> MA.getClusterSize(); a++)
		{
			
			for (int b = 0; b < Ship.getClipSize(); b++)
			{
				if (Ship.GetBullet(b).isActive() && MA.GetAsteroid(a).isActive())
				{		
				
					if (
						CalDistance
						(
							MA.GetAsteroid(a).getPosX()+1, 
							MA.GetAsteroid(a).getPosY(), 
							Ship.GetBullet(b).getPosX()+1, 
							Ship.GetBullet(b).getPosY()
						)
						<
						(
							MA.GetAsteroid(a).getRadius() + Ship.GetBullet(b).getRadius() - -2)
						)
					{
						
						MA.reduceAstroidHealth(a);
						Ship.GetBullet(b).setActive(false);

						if (MA.GetAsteroid(a).getHealth() <= 0)						{
							
							MA.deactivateAsteroid(a);
						}
					}
				}
			}
		}

		for (int a = 0; a < MA.getClusterSize(); a++)
		{
			if (!MA.GetAsteroid(a).isActive())
				MA.eraseAsteroid(a);
		}
		
		for (int b = 0; b < Ship.getClipSize(); b++)
		{
			
			if (Ship.GetBullet(b).isActive() == false)
			{
				Ship.eraseBullet(b);				
			}
		}
		

	}
	void setPage(int p)
	{
		this->page = p;
	}
	//void loadLoadMenu()
	//{
	//}
	//void loadOptionsMenu()
	//{
	//}
	//void MenuOption()
	//{
	//}
	void addAsteroid()
	{
		MA.releaseAstroid();

	}
	void addBullet()
	{
		Ship.addBullet();

	}
	float CalDistance(float Pos1X, float Pos1Y, float Pos2X, float Pos2Y)
	{
		return  pow((Pos1X - Pos2X), 2) + pow((Pos1Y - Pos2Y), 2);		
	}
	vector<Button> &getButtons()
	{
		return Buttons;
	}
	ManagerAsteroid &getAsteroidManager()
	{
		return MA;
	}
	Grid &getGrid()
	{
		return grid;
	}
	SpaceShip &getShip()
	{
	
		return Ship;
	}
	Button getButtonHL()
	{	
		return ButtonHightlight;	
	}


};

#endif
