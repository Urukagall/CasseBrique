#include <iostream>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;

//Cr�a�tion de ball 
GameObject::GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeH(sizeH), oWindow(oWindow), color(color)
{
	shape = new CircleShape(sizeH);
	shape->setPosition(posX, posY);
	shape->setFillColor(color);
}


//Cr�ation de rectangle et carr� 
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


//Recentr� l'origine du rectangle  
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
	if (vPosition.y < posY) //� changer pour que l'angle soit moins de 180�
	{
		shape->setOrigin(sizeW / 2, 0);
		float mouseAngle = -atan2(vPosition.x - posX, vPosition.y - posY) * 180 / 3.14159;
		shape->setRotation(mouseAngle); 
	}
}


//rebond si collision avec un mur est d�tect�e 
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


float GameObject::CollisionEnter(GameObject* gameobject, bool canBounce)
{
	float distanceV = abs((*gameobject).posY - this->posY) / ((*gameobject).sizeH / 2 + this->sizeH);
	float distanceH = abs((*gameobject).posX - this->posX) / ((*gameobject).sizeW / 2 + this->sizeH);

	if (distanceV >= distanceH)
	{
		if (!canBounce)
		{
			return distanceV;
		}
		else {
			Bounce("vertical");
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
		}
	}
	return 0;
}




void GameObject::CollisionExit()
{
	collisionEnter = false;
}


//D�tection des collision 
void GameObject::Collision(vector<GameObject>* brickList)
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


//rebond si collision d�tect�e entre les object
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



