#include <iostream>
#include "Brick.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;


//Création des Brick 
Brick::Brick(float posX, float posY, float sizeW, float sizeH, int life, RenderWindow* oWindow, const string& textureFile)
	: GameObject(posX, posY, sizeW, sizeH, oWindow, Color::White)
{
	this->life = life;
	if (!texture.loadFromFile(textureFile)) {
		cerr << "Erreur lors du chargement de la texture pour la brique." << endl;
		// Gérer l'erreur, par exemple en utilisant une texture de secours ou en quittant l'application.
	}

	shape->setTexture(&texture);	
}

Brick::~Brick() {

}

//Perte des vie des bricks
void Brick::LooseLife()
{
	life -= 1;
	ChangeColor();
}

//Changement de la couleur de la brick en fonction de la vie 
void Brick::ChangeColor()
{
	if (life == 1)
	{
		color = Color::Red;
	}
	else if (life == 2)
	{
		color = Color::Yellow;
	}
	else if (life == 3)
	{
		color = Color::Green;
	}
	shape->setFillColor(color);
}


//Detection de la mort de la brick 
bool Brick::DetectDeath()
{
	if (life <= 0)
	{
		return true;
	}
	else {
		return false;
	}
}

