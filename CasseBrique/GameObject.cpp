#include <iostream>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"


using namespace sf;
using namespace std;

GameObject::GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeH(sizeH), oWindow(oWindow), color(color)
{
	shape = new CircleShape(sizeH);
	shape->setPosition(posX, posY);
	shape->setFillColor(color);
}

GameObject::GameObject(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeH(sizeH), sizeW(sizeW), oWindow(oWindow)
{
	shape = new RectangleShape (Vector2f(sizeH, sizeW));
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

void GameObject::Rotate(Vector2i vPosition) {
	if (vPosition.y < posY) //à changer pour que l'angle soit moins de 180°
	{
		shape->setOrigin(sizeH / 2, 0);
		float mouseAngle = -atan2(vPosition.x - posX, vPosition.y - posY) * 180 / 3.14159;
		shape->setRotation(mouseAngle); 
	}
}

bool GameObject::WallBounce() {
	//left colision 
	if (shape->getPosition().x <= 0) {
		posX = 0;
		shape->setPosition(posX, posY);
		direction.x = -direction.x;
	}

	//right colision 
	if (shape->getPosition().x + shape->getGlobalBounds().width >= oWindow->getSize().x) {
		posX = oWindow->getSize().x - shape->getGlobalBounds().width;
		shape->setPosition(posX, posY);
		direction.x = -direction.x;
	}

	//top colision 
	if (shape->getPosition().y <= 0) {
		posY = 0;
		shape->setPosition(posX, posY);
		direction.y = -direction.y;
	}

	//bottom Colision
	if (shape->getPosition().y + shape->getGlobalBounds().height >= oWindow->getSize().y) {

		return true;
	}

	return false;
}

void GameObject::Colision(GameObject gameObject) {
	if (shape->getGlobalBounds().intersects(gameObject.shape->getGlobalBounds()))
	{
		// Collision détectée
		direction.y = -direction.y;
	}
	else
	{
		// Pas de collision
	}
}

void GameObject::Shoot(vector<GameObject>* ballList) {
	Vector2i mousePos = Mouse::getPosition((*oWindow));
	Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	Vector2f ballStartPosition(posX, posY);

	Vector2f direction = Vector2f(mousePosF.x - ballStartPosition.x, mousePosF.y - ballStartPosition.y);

	ballList->push_back(GameObject(posX, posY, 10, oWindow, Color::Blue));

	(*ballList)[ballList->size() - 1].shape->setOrigin((*ballList)[ballList->size() - 1].sizeH / 2, (*ballList)[ballList->size() - 1].sizeW / 2);


	(*ballList)[ballList->size() - 1].ChangeDirection(direction);
}

