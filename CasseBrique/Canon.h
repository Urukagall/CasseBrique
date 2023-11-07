#pragma once

#include "GameObject.h"

using namespace sf;

class Canon : public GameObject
{
public:

    Vector2f mousePosition;

    Canon();

    void GetMousePosition();

};

