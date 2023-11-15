#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObject.h"
#include "Brick.h"
#include "Ball.h"
#include "Canon.h"
#include "GameManager.h"
#include <vector>

using namespace sf;
using namespace std;

Clock oClock;


    
int main(int argc, char** argv)
{
    sf::RenderWindow oWindow(VideoMode(900, 900), "Mon truc");

    GameManager::Init();
    GameManager::Get()->GameLoop(&oWindow);
   
    return 0;
}