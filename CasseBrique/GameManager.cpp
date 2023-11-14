#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <fstream>
#include <sstream>


using namespace sf;
using namespace std;



GameManager::GameManager() {
	//Création d'une fenêtre

	//sf::RenderWindow window(fullscreenMode, "SFML Fullscreen", sf::Style::Fullscreen);

	

	//GameObject mouseSquare(0, 0, 100, 100, &oWindow, Color::Yellow);
	//mouseSquare.CenterOrigin();


}

GameManager* GameManager::pInstance = nullptr;

void GameManager::Init()
{
	GameManager::pInstance = new GameManager();
}

GameManager* GameManager::Get()
{
	return GameManager::pInstance;
}

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
		vector<Brick> brickRow;

		if (line.size() <= 9)
		{
			for (size_t i = 0; i < line.size(); ++i) {
				int life = line[i] - '0';  // Convertir le caractère en entier

				// Créer une brique avec les données spécifiques
				Brick brick(i * 100, row * 25, 100, 25, life, oWindow, "Brick1");
				brick.ChangeColor();

				// Ajouter la brique à la rangée
				bricks.push_back(brick);
			}
		}
		else {
			for (size_t i = 0; i < 9; ++i) {
				int life = line[i] - '0';  // Convertir le caractère en entier

				// Créer une brique avec les données spécifiques
				Brick brick(i * 100, row * 25, 100, 25, life, oWindow, "Brick1");
				brick.ChangeColor();

				// Ajouter la brique à la rangée
				bricks.push_back(brick);
			}
		}

		// Ajouter la rangée à la liste globale
		//bricks.push_back(brickRow);

		++row;
	}

	return bricks;
}




void GameManager::GameLoop(RenderWindow* oWindow) {
	Clock oClock;
	//GameLoop
	/*
	brickList.push_back(Brick(200, 200, 100, 25, 1, oWindow, Color::Red));
	brickList[0].CenterOrigin();
	brickList.push_back(Brick(300, 200, 100, 25, 2, oWindow, Color::Blue));
	brickList[1].CenterOrigin();
	*/

	brickList = loadBricksFromTxt("level.txt", oWindow);


	canon = new Canon(oWindow->getSize().x / 2, 800, 25, 50, oWindow, Color::Green);

	while (oWindow->isOpen())
	{

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
		}

		//UPDATE

		//DRAW
		oWindow->clear();

		for (int i = 0; i < ballList.size(); i++)
		{

			if (ballList[i].WallBounce()) {
				ballList.erase(ballList.begin() + i);
			}
			else {
				for (int j = 0; j < numSimulation; j++)
				{
					ballList[i].Collision(&brickList);
					ballList[i].Move(fDeltaTime / 10);
				}
				ballList[i].Draw();
			}
		}

		for (int i = 0; i < brickList.size(); i++)
		{
			brickList[i].Draw();
			if (brickList[i].DetectDeath())
			{
				brickList.erase(brickList.begin() + i);
			}
		}
		/*
		mouseSquare.Collision(&brickList);

		mouseSquare.posX = Mouse::getPosition(oWindow).x;
		mouseSquare.posY = Mouse::getPosition(oWindow).y;

		//mouseSquare.Move(fDeltaTime);
		//mouseSquare.Draw();
		*/
		canon->CanonRotate(Mouse::getPosition(*oWindow));
		canon->Draw();

		oWindow->display();

		fDeltaTime = oClock.restart().asSeconds();

		if (fDeltaTime < frameTime)
		{
			sf::sleep(seconds(frameTime - fDeltaTime));
		}
	}

}