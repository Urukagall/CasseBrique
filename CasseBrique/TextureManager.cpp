#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;


//Création des Brick 
TextureManager::TextureManager()
{
	mapTexture["Brick1"].loadFromFile("Image/Brick1.png");
	mapTexture["Brick1"].setSmooth(true);
	mapTexture["Brick2"].loadFromFile("Image/Brick2.png");
	mapTexture["Brick2"].setSmooth(true);
	mapTexture["Brick3"].loadFromFile("Image/Brick3.png");
	mapTexture["Brick3"].setSmooth(true);
	mapTexture["Brick4"].loadFromFile("Image/Brick4.png");
	mapTexture["Brick4"].setSmooth(true);
	mapTexture["Brick5"].loadFromFile("Image/Brick5.png");
	mapTexture["Brick5"].setSmooth(true);
	mapTexture["Brick6"].loadFromFile("Image/Brick6.png");
	mapTexture["Brick6"].setSmooth(true);
	mapTexture["Brick7"].loadFromFile("Image/Brick7.png");
	mapTexture["Brick7"].setSmooth(true);
	mapTexture["Brick8"].loadFromFile("Image/Brick8.png");
	mapTexture["Brick8"].setSmooth(true);
	mapTexture["Brick9"].loadFromFile("Image/Brick9.png");
	mapTexture["Brick9"].setSmooth(true);
	mapTexture["Canon"].loadFromFile("Image/Canon.png");
	mapTexture["Canon"].setSmooth(true);
	mapTexture["Ball"].loadFromFile("Image/Ball.png");
	mapTexture["Ball"].setSmooth(true);
}

//Appliquer la texture au canon 
Texture* TextureManager::ChangeCanonTexture()
{
	return &mapTexture["Canon"];
}

//Appliquer la texture à la balle  
void TextureManager::ChangeBallTexture(Ball* ball)
{
	ball->shape->setTexture(&mapTexture["Ball"]);
}

//Changer la couleur des bricks en fonction de leur vie 
void TextureManager::ChangeBrickTexture(Brick* brick)
{
	if (brick->life == 1) {
		brick->shape->setTexture(&mapTexture["Brick1"]);
	}
	else if (brick->life == 2) {
		brick->shape->setTexture(&mapTexture["Brick2"]);
	}
	else if (brick->life == 3) {
		brick->shape->setTexture(&mapTexture["Brick3"]);
	}
	else if (brick->life == 4) {
		brick->shape->setTexture(&mapTexture["Brick4"]);
	}
	else if (brick->life == 5) {
		brick->shape->setTexture(&mapTexture["Brick5"]);
	}
	else if (brick->life == 6) {
		brick->shape->setTexture(&mapTexture["Brick6"]);
	}
	else if (brick->life == 7) {
		brick->shape->setTexture(&mapTexture["Brick7"]);
	}
	else if (brick->life == 8) {
		brick->shape->setTexture(&mapTexture["Brick8"]);
	}
	else if (brick->life == 9) {
		brick->shape->setTexture(&mapTexture["Brick9"]);
	}
}

TextureManager::~TextureManager() 
{
	
}