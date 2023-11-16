#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>


using namespace sf;
using namespace std;

class GameObject
{
public:

    float posX = 0;
    float posY = 0;
    float sizeH = 0;
    float sizeW = 0;
    Vector2f direction; 
    float speed = 500;
    Color color;
    RenderWindow* oWindow;
    Shape* shape;


    bool collisionEnter = false;
    bool collisionExit = false;
    int collisionPersistCounter = 0;
    int collisionThreshold = 4;

	FloatRect boundingBox;
	FloatRect otherBox;

    GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow);
    GameObject(float posX, float posY, float sizeW, float sizeH, RenderWindow* oWindow);
    void CenterOrigin();
    void Draw();


    ~GameObject();
};

