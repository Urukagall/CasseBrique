#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Brick.h"

using namespace sf;
using namespace std;

class TextureManager
{
public:

	map<string, Texture> mapTexture;

	TextureManager();
	
	void ChangeBrickTexture(Brick* brick);


	~TextureManager();
};

