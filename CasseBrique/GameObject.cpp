#include <iostream>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;

//Création d'un gameobject circulaire
GameObject::GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow)
	: posX(posX), posY(posY), sizeH(sizeH), oWindow(oWindow), color(color)
{
	shape = new CircleShape(sizeH);
	shape->setPosition(posX, posY);
}

//Création d'un gameobject rectangulaire
GameObject::GameObject(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow)
	: posX(posX), posY(posY), sizeW(sizeW), sizeH(sizeH), oWindow(oWindow)
{
	shape = new RectangleShape(Vector2f(sizeW, sizeH));
	shape->setPosition(posX, posY);
}

GameObject::~GameObject(){

}

//Affiche les GameObject
void GameObject::Draw() {
	oWindow->draw(*shape);
}

//Recentré l'origine du gameObject  
void GameObject::CenterOrigin() {
	if (sizeW == 0)
	{
		shape->setOrigin(sizeH, sizeH);
	}
	else {
		shape->setOrigin(sizeW / 2, sizeH / 2);
	}
}