#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Brick.h"
#include "Ball.h"

using namespace sf;
using namespace std;

class TextureManager
{
public:

	map<string, Texture> mapTexture;



	TextureManager();
	
	void ChangeBrickTexture(Brick* brick);
	Texture* ChangeCanonTexture();
	void ChangeBallTexture(Ball* ball);

	~TextureManager();
};

