#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

GameObject::GameObject(int posX, int posY, int sizeH, RenderWindow* oWindow, Color color)
	: posX(posX), posY(posY), sizeH(sizeH), oWindow(oWindow), color(color)
{
	shape = new CircleShape(sizeH);
	shape->setPosition(posX, posY);
	shape->setFillColor(color);
}

GameObject::GameObject(int posX, int posY, int sizeH, int sizeW, RenderWindow* oWindow)
	: posX(posX), posY(posY), sizeH(sizeH), sizeW(sizeW), oWindow(oWindow)
{

}

void GameObject::Draw() {
	oWindow->draw(*shape);
}