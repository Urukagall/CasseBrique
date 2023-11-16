#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <fstream>
#include <sstream>


using namespace sf;
using namespace std;


//Constructeur vide 
GameManager::GameManager() 
{
	
}
//return de l'Instance 
GameManager* GameManager::pInstance = nullptr;


//Utilisation de l'instance pour Initialiser le GameManager 
void GameManager::Init()
{
	GameManager::pInstance = new GameManager();
}

//Récuperation de l'instance grâçe au get 
GameManager* GameManager::Get()
{
	return GameManager::pInstance;
}


//Méthode pour lire les fichier txt et créer les niveaux en fonction
vector<Brick> GameManager::loadBricksFromTxt(const string& filename, sf::RenderWindow* oWindow) {
	vector<Brick> bricks;

	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Erreur lors de l'ouverture du fichier TXT." << endl;
		return bricks;
	}

	string line;
	int row = 0;

	while (getline(file, line)) {

		if (line.size() <= 9)
		{
			for (size_t i = 0; i < line.size(); ++i) {
				int life = line[i] - '0';  // Convertir le caractère en entier 
				// Créer une brique avec les données spécifiques
				Brick brick(i * 100 + 50, row * 25 + 12.5, 100, 25, life, oWindow);
				brick.CenterOrigin();
				brick.ChangeColor();

				// Ajouter la brique à la rangée
				bricks.push_back(brick);
			}
		}
		else {
			for (size_t i = 0; i < 9; ++i) {
				int life = line[i] - '0';  // Convertir le caractère en entier

				// Créer une brique avec les données spécifiques
				Brick brick(i * 100 + 50, row * 25 + 12.5, 100, 25, life, oWindow);
				brick.CenterOrigin();
				brick.ChangeColor();

				// Ajouter la brique à la rangée
				bricks.push_back(brick);
			}
		}

		// Ajouter la rangée à la liste globale
		++row;
	}

	return bricks;
}



void GameManager::GameLoop(RenderWindow* oWindow) {
	Clock oClock;
	//GameLoop

	brickList = loadBricksFromTxt("Level/Level1.txt", oWindow);


	canon = new Canon(oWindow->getSize().x / 2, 800, 25, 50, oWindow, &textureManager);
	canon->shape->setTexture(textureManager.ChangeCanonTexture());
	
	shockWave = new ShockWave(oWindow->getSize().x / 2, 800, 100, 200, oWindow);
	shockWave->shape->setTexture(textureManager.ChangeShockTexture());
	shockWave->CenterOrigin();

	while (oWindow->isOpen())
	{
		//mouseSquare = new Brick(0, 0, 25, 25, 9, oWindow);

		//EVENT
		Event oEvent;
		while (oWindow->pollEvent(oEvent))
		{
			if (oEvent.type == Event::Closed) {
				oWindow->close();
			}
			if (oEvent.type == Event::KeyPressed && oEvent.key.code == Keyboard::Escape) {
				oWindow->close();
			}
			if (oEvent.type == Event::MouseButtonPressed && oEvent.key.code == Mouse::Left) {
				if (ballList.size() <= 100 and Mouse::getPosition(*oWindow).y < canon->posY)
				{
					canon->Shoot(&ballList);
				}
			}
			if (oEvent.type == Event::MouseButtonPressed && oEvent.key.code == Mouse::Right) {
				if (true)
				{
					shockWave->isActivate = true;
					canon->ShockWaveShoot(shockWave);
				}
			}
			//Changer de niveaux en +1
			if (oEvent.type == Event::KeyPressed && oEvent.key.code == Keyboard::Left) {
				if (level != 1)
				{
					level -= 1; 

					stringstream ss;
					ss << "Level/Level" << level << ".txt";
					string filePath = ss.str();

					brickList = loadBricksFromTxt(filePath, oWindow);
					ballList.clear();
				}
			}
			//Changer de niveaux en -1 
			if (oEvent.type == Event::KeyPressed && oEvent.key.code == Keyboard::Right) 
			{
				if(level != 10)
				{
					level += 1;

					stringstream ss;
					ss << "Level/Level" << level << ".txt";
					string filePath = ss.str();

					brickList = loadBricksFromTxt(filePath, oWindow);
					ballList.clear();
				}
			}
		
		}
		

		oWindow->clear();

		//Mouvement, collisions et affichage des balles
		for (int i = 0; i < ballList.size(); i++)
		{

			if (ballList[i].WallBounce()) {
				ballList.erase(ballList.begin() + i);
			}
			else {
				for (int j = 0; j < numSimulation; j++)
				{
					ballList[i].Collision(&brickList, &ballList);
					ballList[i].Move(fDeltaTime / numSimulation);
				}
				ballList[i].Draw();
			}
		}


		//Mouvement, collisions et affichage des bricks
		for (int i = 0; i < brickList.size(); i++)
		{
			if (brickList[i].DetectDeath())
			{
				brickList.erase(brickList.begin() + i);
			}
		}

		for (int i = 0; i < brickList.size(); i++)
		{
			textureManager.ChangeBrickTexture(&brickList[i]);
			brickList[i].Draw();
		}
		
		//mouseSquare->CenterOrigin();

		//mouseSquare->Collision(&brickList);

		//mouseSquare->posX = Mouse::getPosition(*oWindow).x;
		//mouseSquare->posY = Mouse::getPosition(*oWindow).y;

		//mouseSquare->Move(fDeltaTime);
		//mouseSquare->Draw();



		//Mouvement et affichage du canon
		canon->CanonRotate(Mouse::getPosition(*oWindow));
		canon->Draw();


		//Mouvement, affichage et mouvement du canon
		if (shockWave->isActivate and Mouse::getPosition(*oWindow).y < canon->posY)
		{
			shockWave->Collision(&ballList);
			shockWave->Move(fDeltaTime);
			shockWave->WallDestroy();
			shockWave->Draw();
		}

		oWindow->display();


		//Réglage des FPS
		fDeltaTime = oClock.restart().asSeconds();

		if (fDeltaTime < frameTime)
		{
			sleep(seconds(frameTime - fDeltaTime));
		}
	}
	
}