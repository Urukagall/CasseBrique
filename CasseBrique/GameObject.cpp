#include <iostream>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"


using namespace sf;
using namespace std;

//Créaétion de ball 
GameObject::GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeH(sizeH), oWindow(oWindow), color(color)
{
	shape = new CircleShape(sizeH);
	shape->setPosition(posX, posY);
	shape->setFillColor(color);
}


//Création de rectangle et carré 
GameObject::GameObject(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeW(sizeW), sizeH(sizeH), oWindow(oWindow)
{
	shape = new RectangleShape (Vector2f(sizeW, sizeH));
	shape->setPosition(posX, posY);
	shape->setFillColor(color);
}

GameObject::~GameObject(){

}


void GameObject::Draw() {
	oWindow->draw(*shape);
}


void GameObject::Move(float fDeltaTime) 
{
	posX += direction.x * fDeltaTime * speed;
	posY += direction.y * fDeltaTime * speed;
	shape->setPosition(posX, posY);
}


void GameObject::ChangeDirection(Vector2f oDirection) {
	direction = Math::Normalized(oDirection);
}


//Recentré l'origine du rectangle  
void GameObject::CenterOrigin() {
	if (sizeW == 0)
	{
		shape->setOrigin(sizeH, sizeH);
	}
	else {
		shape->setOrigin(sizeW / 2, sizeH / 2);
	}
}


//Rotation du Canon 
void GameObject::CanonRotate(Vector2i vPosition) {
	if (vPosition.y < posY) //à changer pour que l'angle soit moins de 180°
	{
		shape->setOrigin(sizeW / 2, 0);
		float mouseAngle = -atan2(vPosition.x - posX, vPosition.y - posY) * 180 / 3.14159;
		shape->setRotation(mouseAngle); 
	}
}


//rebond si collision avec un mur est détectée 
bool GameObject::WallBounce() {
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


void GameObject::CollisionEnter(GameObject* gameobject)
{
	collisionEnter = true;
	float distanceV = abs((*gameobject).posY - this->posY) / ((*gameobject).sizeH / 2 + this->sizeH);
	float distanceH = abs((*gameobject).posX - this->posX) / ((*gameobject).sizeW / 2 + this->sizeH);

	if (distanceV >= distanceH)
	{
		Bounce("vertical");
	}
	else if (distanceV <= distanceH)
	{
		Bounce("horizontal");
	}
}




void GameObject::CollisionExit()
{
	collisionEnter = false;
}


//Détection des collision 
void GameObject::Collision(vector<GameObject>* brickList)
{
	bool isCollision = false;
	for (int j = 0; j < brickList->size(); j++)
	{
		bool currentCollision = shape->getGlobalBounds().intersects((*brickList)[j].shape->getGlobalBounds());

		if (currentCollision)
		{
			if (!isCollision and !collisionEnter)
			{
				cout << "enter" << endl;
				isCollision = true;
				CollisionEnter(&(*brickList)[j]);
				break;
				//Mettre la collsion seulement pour la brick la plus proche de la balle
			}
			else {
				isCollision = true;
				break;
			}
		}
	}

	if (!isCollision and collisionEnter)
	{
		cout << "exit" << endl;
		CollisionExit();
	}


	/*if (currentCollision)
	{
		return true;
	}
	else {
		return false;
	}*/

	/*if (currentCollision)
	{
		// Collision 
		if (!collisionEnter)
		{
			cout << "on collosion enter" << endl;
			CollisionEnter(gameobject);
			collisionEnter = true;
			return true;
		}
	}

	else if (collisionEnter)
	{
			cout << "on collosion exit" << endl;
			collisionEnter = false;
			return false;
	}

	return false;*/
}


//rebond si collision détectée entre les object
void GameObject::Bounce(string sens) {
	// Rebond

	if (sens == "vertical")
	{
		direction.y = -direction.y;
	}
	else if (sens =="horizontal")
	{
		direction.x = -direction.x;
	}
}


void GameObject::Shoot(vector<GameObject>* ballList) {

	Vector2i mousePos = Mouse::getPosition((*oWindow));
	Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	Vector2f ballStartPosition(posX, posY);

	Vector2f direction = Vector2f(mousePosF.x - ballStartPosition.x, mousePosF.y - ballStartPosition.y);

	ballList->push_back(GameObject(posX, posY, 10, oWindow, Color::Blue));

	(*ballList)[ballList->size() - 1].CenterOrigin();



	(*ballList)[ballList->size() - 1].ChangeDirection(direction);
}


void GameObject::LifeBrick(GameObject* gameobject)
{

}



