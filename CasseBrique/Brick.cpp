#include <iostream>
#include "Brick.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Math.h"
#include <vector>


using namespace sf;
using namespace std;


//Création de rectangle et carré 
Brick::Brick(float posX, float posY, float sizeW, float sizeH, int life, RenderWindow* oWindow, Color color)
	: GameObject(posX, posY, sizeW, sizeH, oWindow, color)
{
	this->life = life;
}

Brick::~Brick() {

}


void Brick::LooseLife(Brick* brick)
{
	life -= 1;
}


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

