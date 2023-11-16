#include "ShockWave.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;

//Créaétion de ball 
ShockWave::ShockWave(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow)
	: GameObject(posX, posY, sizeW, sizeH, oWindow)
{
}

ShockWave::~ShockWave() {

}


//mouvement des ball
void ShockWave::Move(float fDeltaTime)
{
	posX += direction.x * fDeltaTime * speed;
	posY += direction.y * fDeltaTime * speed;
	shape->setPosition(posX, posY);
}

//Gestion du vecteur directeur des ball
void ShockWave::ChangeDirection(Vector2f oDirection) {
	direction = Math::Normalized(oDirection);
}


//rebond si collision avec un mur est détectée 
bool ShockWave::WallDestroy() {
	//left colision 
	if (shape->getPosition().x - sizeH <= 0) {
		isActivate = false;
	}

	//right colision 
	if (shape->getPosition().x + shape->getGlobalBounds().width - sizeH >= oWindow->getSize().x) {
		isActivate = false;
	}

	//top colision 
	if (shape->getPosition().y - sizeH <= 0) {
		isActivate = false;
	}

	//bottom destruction 
	if (shape->getPosition().y + shape->getGlobalBounds().height - sizeH >= oWindow->getSize().y) {
		return true;
	}

	return false;
}

//Détection des Première colisions et la direction des collisions
float ShockWave::CollisionEnter(Ball* ball, bool canBounce)
{

	return 0;
}


//Détection des collision avec les Brick 
void ShockWave::Collision(vector<Ball>* ballList)
{

	for (int i = 0; i < ballList->size(); i++)
	{
		bool currentCollision = shape->getGlobalBounds().intersects((*ballList)[i].shape->getGlobalBounds());

		if (currentCollision)
		{
			(*ballList)[i].ChangeDirection(direction);
			isActivate = false;
			break;
		}
	}
}