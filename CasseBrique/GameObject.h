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
    float speed = 750;
    Color color;
    RenderWindow* oWindow;
    Shape* shape;

    bool collisionEnter = false;
    bool collisionExit = false;
    int collisionPersistCounter = 0;
    int collisionThreshold = 4;

	FloatRect boundingBox;
	FloatRect otherBox;



    GameObject(float posX, float posY, float sizeH, RenderWindow* oWindow, Color color);
    GameObject(float posX, float posY, float sizeH, float sizeW, RenderWindow* oWindow, Color color);

    void Draw();
    void Move(float fDeltaTime);
	void ChangeDirection(Vector2f direction);
	void CenterOrigin();
    void CanonRotate(Vector2i vPosition);
	bool WallBounce();
    float CollisionEnter(GameObject* gameobject, bool canBounce);
	void CollisionExit();
    void Collision(vector<GameObject>* brickList);
    void Bounce(string sens);
    void Shoot(vector<GameObject>* ballList);
    void LifeBrick(GameObject* gameobject);



    ~GameObject();
};

