#include <iostream>
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;

//Créaétion de ball 
Ball::Ball(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color)
	: GameObject(posX, posY, sizeH, oWindow, color)
{
}

Ball::~Ball() {

}




//mouvement des ball
void Ball::Move(float fDeltaTime)
{
	posX += direction.x * fDeltaTime * speed;
	posY += direction.y * fDeltaTime * speed;
	shape->setPosition(posX, posY);
}

//Gestion du vecteur directeur des ball
void Ball::ChangeDirection(Vector2f oDirection) {
	direction = Math::Normalized(oDirection);
}


//rebond si collision avec un mur est détectée 
bool Ball::WallBounce() {
	//left colision 
	if (shape->getPosition().x - sizeH <= 0) {
		posX = 0 + sizeH;
		shape->setPosition(posX, posY);
		direction.x = -direction.x;
	}

	//right colision 
	if (shape->getPosition().x + shape->getGlobalBounds().width - sizeH >= oWindow->getSize().x) {
		posX = oWindow->getSize().x - shape->getGlobalBounds().width + sizeH;
		shape->setPosition(posX, posY);
		direction.x = -direction.x;
	}

	//top colision 
	if (shape->getPosition().y - sizeH <= 0) {
		posY = 0 + sizeH;
		shape->setPosition(posX, posY);
		direction.y = -direction.y;
	}

	//bottom destruction 
	if (shape->getPosition().y + shape->getGlobalBounds().height - sizeH >= oWindow->getSize().y) {
		return true;
	}

	return false;
}

//Détection des Première colisions 
float Ball::CollisionEnter(Brick* brick, bool canBounce)
{

	float distanceV = abs((*brick).posY - this->posY) / ((*brick).sizeH / 2 + this->sizeH);
	float distanceH = abs((*brick).posX - this->posX) / ((*brick).sizeW / 2 + this->sizeH);

	if (distanceV >= distanceH)
	{
		if (!canBounce)
		{
			return distanceV;
		}
		else {
			cout << "vertical" << (*brick).posY << "   " << this->posY << endl;
			Bounce("vertical");
			brick->LooseLife();
		}
	}
	else if (distanceV <= distanceH)
	{
		if (!canBounce)
		{
			return distanceH;
		}
		else {
			cout << "horizontal" << (*brick).posX << "   " << this->posX << endl;
			Bounce("horizontal");
			brick->LooseLife();
		}
	}
	return 0;
}



//Sortie des collision 
void Ball::CollisionExit()
{
	collisionEnter = false;
}


//Détection des collision 
void Ball::Collision(vector<Brick>* brickList)
{ 
	std::pair<float, int> nearestBrick = { std::numeric_limits<float>::infinity(), -1 };

	for (int i = 0; i < brickList->size(); i++)
	{
		bool currentCollision = shape->getGlobalBounds().intersects((*brickList)[i].shape->getGlobalBounds());

		if (currentCollision)
		{
			float distance = CollisionEnter(&(*brickList)[i], false);

			if (distance < nearestBrick.first)
			{
				nearestBrick = { distance, i };
			}
		}
	}

	if (nearestBrick.second != -1)
	{
		if (!collisionEnter)
		{
			cout << "enter" << endl;
			collisionEnter = true;
			CollisionEnter(&(*brickList)[nearestBrick.second], true);
		}
	}
	else if (collisionEnter)
	{
		cout << "exit" << endl;
		CollisionExit();
	}
}


//rebond si collision détectée entre les object
void Ball::Bounce(string sens) {
	// Rebond

	if (sens == "vertical")
	{
		direction.y = -direction.y;
	}
	else if (sens == "horizontal")
	{
		direction.x = -direction.x;
	}
}


//Aplication sur la ball de la fonction shoot 
void Ball::Shoot(vector<Ball>* ballList) {

	Vector2i mousePos = Mouse::getPosition((*oWindow));
	Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	Vector2f ballStartPosition(posX, posY);

	Vector2f direction = Vector2f(mousePosF.x - ballStartPosition.x, mousePosF.y - ballStartPosition.y);

	ballList->push_back(Ball(posX, posY, 10, oWindow, Color::Blue));

	(*ballList)[ballList->size() - 1].CenterOrigin();



	(*ballList)[ballList->size() - 1].ChangeDirection(direction);
}