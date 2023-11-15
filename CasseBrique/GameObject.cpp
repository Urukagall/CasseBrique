#include <iostream>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;

//Créaétion de ball 
GameObject::GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow)
	: posX(posX), posY(posY), sizeH(sizeH), oWindow(oWindow), color(color)
{
	shape = new CircleShape(sizeH);
	shape->setPosition(posX, posY);
}

/*
//Création de rectangle et carré 
GameObject::GameObject(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeW(sizeW), sizeH(sizeH), oWindow(oWindow)
{
	shape = new RectangleShape(Vector2f(sizeW, sizeH));
	shape->setPosition(posX, posY);
	shape->setFillColor(color);
}*/

//Création d'une image
GameObject::GameObject(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow)
	: posX(posX), posY(posY), sizeW(sizeW), sizeH(sizeH), oWindow(oWindow)
{
	
	shape = new RectangleShape(Vector2f(sizeW, sizeH));
	shape->setPosition(posX, posY);
	//shape->setTexture(&texture);
	
}

GameObject::~GameObject(){

}

void GameObject::Draw() {
	oWindow->draw(*shape);
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