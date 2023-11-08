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
    float speed = 1000;
    Color color;
    RenderWindow* oWindow;
    Shape* shape;


	FloatRect boundingBox;
	FloatRect otherBox;



    GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color);
    GameObject(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow, Color color);

    void Draw();
    void Move(float fDeltaTime);
    void Rotate(Vector2i vPosition);
    void Colision(GameObject gameObject);
    bool WallBounce();
    void Shoot(vector<GameObject>* ballList);
    void ChangeDirection(Vector2f direction);

    ~GameObject();
};

