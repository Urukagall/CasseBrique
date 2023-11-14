#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "GameObject.h"

using namespace sf;
using namespace std;

class Brick : public GameObject
{
public:

	int life;
	Texture texture;

	//Brick(float posX, float posY, float sizeH, float sizeW, int life, RenderWindow* oWindow, Color color);
	Brick(float posX, float posY, float sizeH, float sizeW, int life, RenderWindow* oWindow, const string& textureFile);


	void LooseLife();
	void ChangeColor(); 
	bool DetectDeath();
	~Brick();
};

