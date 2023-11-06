#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
public:

    int posX = 0;
    int posY = 0;
    int sizeH = 0;
    int sizeW = 0;
    Color color;
    RenderWindow* oWindow;
    Shape* shape;
    GameObject(int posX, int posY, int sizeH, RenderWindow* oWindow, Color color);
    GameObject(int posX, int posY, int sizeH, int sizeW, RenderWindow* oWindow);

    void Draw();

};

