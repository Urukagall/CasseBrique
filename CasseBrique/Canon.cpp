#include <iostream>
#include "Canon.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;


//Création de rectangle et carré 
Canon::Canon(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow, Color color)
	: GameObject(posX, posY, sizeW, sizeH, oWindow, color)
{
}

Canon::~Canon() {

}



void Canon::ChangeDirection(Vector2f oDirection) {
	direction = Math::Normalized(oDirection);
}





//Rotation du Canon 
void Canon::CanonRotate(Vector2i vPosition) {
	if (vPosition.y < posY) //à changer pour que l'angle soit moins de 180°
	{
		//cout << posX << "   " << posY << endl;
		shape->setOrigin(sizeW / 2, 0);
		float mouseAngle = -atan2(vPosition.x - posX, vPosition.y - posY) * 180 / 3.14159;
		shape->setRotation(mouseAngle);
	}
}




void Canon::Shoot(vector<Ball>* ballList) {

	Vector2i mousePos = Mouse::getPosition((*oWindow));
	Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	Vector2f ballStartPosition(posX, posY);

	Vector2f direction = Vector2f(mousePosF.x - ballStartPosition.x, mousePosF.y - ballStartPosition.y);

	ballList->push_back(Ball(posX, posY, 10, oWindow, Color::Blue));

	(*ballList)[ballList->size() - 1].CenterOrigin();



	(*ballList)[ballList->size() - 1].ChangeDirection(direction);
}





