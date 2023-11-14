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
Brick::Brick(float posX, float posY, float sizeW, float sizeH, int life, RenderWindow* oWindow, Color color)
	: GameObject(posX, posY, sizeW, sizeH, oWindow, color)
{
	this->life = life;
}

Brick::~Brick() {

}

//Perte des vie des bricks
void Brick::LooseLife(Brick* brick)
{
	life -= 1;

}

//Changement de la couleur de la brick en fonction de la vie 
void Brick::ChangeColor(Brick* brick)
{
	if (life == 2)
	{
		color = Color::Yellow;
	}
	else if (life == 1)
	{
		color = Color::Red;
	}
}


//Detection de la mort de la brick 
bool Brick::DetectDeath(Brick* brick)
{
	if (life <= 0)
	{
		return true;
	}
	else {
		return false;
	}
}

