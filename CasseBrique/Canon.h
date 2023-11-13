#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Ball.h"
#include "GameObject.h"

using namespace sf;
using namespace std;



class Canon : public GameObject
{
public:

    Vector2f direction;
    FloatRect boundingBox;
    FloatRect otherBox;


	Canon(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow, Color color);
    void CanonRotate(Vector2i vPosition);
    void ChangeDirection(Vector2f oDirection);
    void Shoot(vector<Ball>* ballList);

    ~Canon();
};

