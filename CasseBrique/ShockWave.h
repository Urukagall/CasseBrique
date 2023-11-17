#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "GameObject.h"
#include "Ball.h"

using namespace sf;
using namespace std;

class ShockWave : public GameObject
{
public:

    Vector2f direction;
    float speed = 1500;

    bool isActivate = false;

    bool collisionEnter = false;
    bool collisionExit = false;
    int collisionPersistCounter = 0;
    int collisionThreshold = 4;

    FloatRect boundingBox;
    FloatRect otherBox;



    ShockWave(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow);

    void Move(float fDeltaTime);
    void ChangeDirection(Vector2f direction);
    bool WallDestroy();
    float CollisionEnter(Ball* ball, bool canBounce);
    void Collision(vector<Ball>* ballList);




    ~ShockWave();
};

