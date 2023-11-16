#include <iostream>
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;

//Créaétion de ball 
Ball::Ball(float posX, float posY, float sizeH, RenderWindow* oWindow)
	: GameObject(posX, posY, sizeH, oWindow)
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

//Détection des Première colisions et la direction des collisions
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


//Détection des collision avec les Brick 
void Ball::Collision(vector<Brick>* brickList, vector<Ball>* ballList)
{ 

	//Collision Brick
	pair<float, int> nearestBrick = { std::numeric_limits<float>::infinity(), -1 };

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
			collisionEnter = true;
			CollisionEnter(&(*brickList)[nearestBrick.second], true);
		}
	}
	else if (collisionEnter)
	{
		CollisionExit();
	}

	//Collision ball
	pair<float, int> nearestBall = { std::numeric_limits<float>::infinity(), -1 };

	for (int i = 0; i < ballList->size(); i++)
	{
		if (posX != (*ballList)[i].posX or posY != (*ballList)[i].posY)
		{
			bool currentCollision = shape->getGlobalBounds().intersects((*ballList)[i].shape->getGlobalBounds());

			if (currentCollision and !ballCollisionEnter)
			{
				ballCollisionEnter = true;
				Vector2f tangeante;
				tangeante = direction + (*ballList)[i].direction;
				tangeante = Math::Normalized(tangeante);
				if (posX >= (*ballList)[i].posX)
				{
					direction = Vector2f(tangeante.x , -tangeante.y);
				}
				else
				{
					direction = Vector2f(-tangeante.x, tangeante.y);
				}
				//(*ballList)[i].direction = Vector2f(-tangeante.x, tangeante.y);
				break;
			}
			else {
				ballCollisionEnter = false;
			}
		}
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
