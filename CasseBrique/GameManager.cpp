#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>
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

vector<vector<Brick>> GameManager::loadBricksFromJson(const string& filename, sf::RenderWindow* oWindow) {
	vector<vector<Brick>> bricks;

	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Erreur lors de l'ouverture du fichier JSON." << endl;
		return bricks;
	}

	// Charger le contenu du fichier JSON dans une chaîne
	stringstream buffer;
	buffer << file.rdbuf();
	string jsonContent = buffer.str();

	// Analyser le JSON
	auto json = json::parse(jsonContent);

	// Assurez-vous que le champ "level" existe
	if (json.find("level") != json.end()) {
		// Récupérer le tableau "level"
		auto levelArray = json["level"];

		for (const auto& row : levelArray) {
			vector<Brick> brickRow;

			for (const auto& life : row) {
				// Créer une brique avec la valeur de vie
				Brick brick(0, 0, 100, 25, life, oWindow, Color::Blue);
				brickRow.push_back(brick);
			}

			bricks.push_back(brickRow);
		}
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

	loadBricksFromJson("level.json", oWindow);


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
			if (brickList[i].DetectDeath(&brickList[i]))
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