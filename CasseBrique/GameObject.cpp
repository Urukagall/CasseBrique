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

void GameObject::Colision(GameObject gameObject) {
	//left colision 
	if (shape->getPosition().x < 0) {
		posX = 0;
		shape->setPosition(posX, posY);
	}

	//top colision 
	if (shape->getPosition().y < 0) {
		posY = 0;
		shape->setPosition(posX, posY);
	}

	 //right colision 
	if (shape->getPosition().x + shape->getGlobalBounds().width  > oWindow->getSize().x) {
		posX = oWindow->getSize().x - shape->getGlobalBounds().width;
		shape->setPosition(posX, posY);
	}

	//bottom Colision
	if (shape->getPosition().y + shape->getGlobalBounds().height > oWindow->getSize().y) {
		posY = oWindow->getSize().y - shape->getGlobalBounds().height;
		shape->setPosition(posX, posY);

		//Il faut delete le gameObject
	}





	if (shape->getGlobalBounds().intersects(gameObject.shape->getGlobalBounds()))
	{
		// Collision détectée
		shape->setFillColor(sf::Color::Red);
		gameObject.shape->setFillColor(sf::Color::Red);
	}
	else
	{
		// Pas de collision
		shape->setFillColor(sf::Color::Green);
		gameObject.shape->setFillColor(sf::Color::Blue);
	}
}

void GameObject::Shoot(Vector2i vPosition) {

}

