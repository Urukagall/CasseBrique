#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace sf;

class GameObject
{
public:

    float posX = 0;
    float posY = 0;
    float sizeH = 0;
    float sizeW = 0;
    Vector2f direction; 
    float speed = 10;
    Color color;
    RenderWindow* oWindow;
    Shape* shape;


	FloatRect boundingBox;
	FloatRect otherBox;



    GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color);
    GameObject(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow, Color color);

    void Draw();
    void Move(float fDeltaTime, Vector2f direction);
    void Rotate(float VPositionX, float VPositionY);
    void Colision(GameObject gameObject);

};

