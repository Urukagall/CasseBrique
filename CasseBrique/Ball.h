#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "GameObject.h"
#include "Brick.h"

using namespace sf;
using namespace std;

class Ball : public GameObject
{
public:

    Vector2f direction;
    float speed = 500;

    bool collisionEnter = false;
    bool collisionExit = false;
    int collisionPersistCounter = 0;
    int collisionThreshold = 4;

    FloatRect boundingBox;
    FloatRect otherBox;



	Ball(float posX, float posY, float sizeH, RenderWindow* oWindow);

    void Move(float fDeltaTime);
    void ChangeDirection(Vector2f direction);
    bool WallBounce();
    float CollisionEnter(Brick* brick, bool canBounce);
    void CollisionExit();
    void Collision(vector<Brick>* brickList);
    void Bounce(string sens);
    void Shoot(vector<Ball>* ballList);




    ~Ball();
};

