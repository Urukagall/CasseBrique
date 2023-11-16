#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Ball.h"
#include "GameObject.h"
#include "TextureManager.h"

using namespace sf;
using namespace std;



class Canon : public GameObject
{
public:

    Vector2f direction;
    FloatRect boundingBox;
    FloatRect otherBox;

    TextureManager* textureManager;


	Canon(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow, TextureManager* textureManager);
    void CanonRotate(Vector2i vPosition);
    void Shoot(vector<Ball>* ballList);

    ~Canon();
};

