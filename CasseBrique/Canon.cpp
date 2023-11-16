#include <iostream>
#include "Canon.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;


//Création de rectangle et carré 
Canon::Canon(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow, TextureManager* textureManager)
	: GameObject(posX, posY, sizeW, sizeH, oWindow)
{
	this->textureManager = textureManager;
}

Canon::~Canon() {

}

//Rotation du Canon 
void Canon::CanonRotate(Vector2i vPosition) {
	if (vPosition.y < posY) //à changer pour que l'angle soit moins de 180°
	{
		//cout << posX << "   " << posY << endl;
		shape->setOrigin(sizeW / 2, 0);
		float mouseAngle = -atan2(vPosition.x - posX, vPosition.y - posY) * 180 / 3.14159;
		shape->setRotation(mouseAngle);
	}
}



//Fonction pour tiré là où la souris vise 
void Canon::Shoot(vector<Ball>* ballList) {

	Vector2i mousePos = Mouse::getPosition((*oWindow));
	Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	Vector2f ballStartPosition(posX, posY);

	Vector2f direction = Vector2f(mousePosF.x - ballStartPosition.x, mousePosF.y - ballStartPosition.y);

	ballList->push_back(Ball(posX, posY, 10, oWindow));

	(*ballList)[ballList->size() - 1].CenterOrigin();

	(*ballList)[ballList->size() - 1].ChangeDirection(direction);

	textureManager->ChangeBallTexture(&(*ballList)[ballList->size() - 1]);
}

//Fonction pour tiré là où la souris vise 
void Canon::ShockWaveShoot(ShockWave* shockWave) {

	Vector2i mousePos = Mouse::getPosition((*oWindow));
	Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	Vector2f shockStartPosition(posX, posY);

	Vector2f direction = Vector2f(mousePosF.x - shockStartPosition.x, mousePosF.y - shockStartPosition.y);


	float mouseAngle = -atan2(mousePos.x - posX, mousePos.y - posY) * 180 / 3.14159;
	shockWave->shape->setRotation(mouseAngle);

	shockWave->posX = shockStartPosition.x;
	shockWave->posY = shockStartPosition.y;
	shockWave->ChangeDirection(direction);
}





