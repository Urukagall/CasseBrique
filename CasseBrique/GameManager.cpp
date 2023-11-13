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

vector<Brick> GameManager::loadBricksFromJson(const std::string& filename, sf::RenderWindow* oWindow) {
	std::vector<Brick> bricks;

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Erreur lors de l'ouverture du fichier JSON." << std::endl;
		return bricks;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string jsonContent = buffer.str();

	// Assurez-vous que le fichier JSON est bien formé et suit une structure spécifique
	size_t pos = jsonContent.find("[[");
	if (pos == std::string::npos) {
		std::cerr << "Structure JSON incorrecte." << std::endl;
		return bricks;
	}

	// Extraire la partie du JSON contenant les données des briques
	std::string bricksJson = jsonContent.substr(pos);

	// Parsez manuellement la chaîne JSON pour extraire les données des briques
	std::istringstream ss(bricksJson);
	std::string token;

	while (std::getline(ss, token, ']')) {
		std::vector<std::string> brickData;

		// Utilisez un autre délimiteur pour séparer les valeurs de la brique
		std::istringstream brickStream(token.substr(2));
		while (std::getline(brickStream, token, ',')) {
			brickData.push_back(token);
		}

		if (brickData.size() >= 6) {
			float posX = std::stof(brickData[0]);
			float posY = std::stof(brickData[1]);
			float sizeH = std::stof(brickData[2]);
			float sizeW = std::stof(brickData[3]);
			int life = std::stoi(brickData[4]);
			sf::Color color = sf::Color(std::stoi(brickData[5]));

			Brick brick(posX, posY, sizeH, sizeW, life, oWindow, color);
			bricks.push_back(brick);
		}
	}
	cout << bricks.size() << endl;
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

	//brickList = loadBricksFromJson("level.json", oWindow);


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