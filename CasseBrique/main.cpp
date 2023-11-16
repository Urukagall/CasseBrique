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


//Fonction main 
int main(int argc, char** argv)
{
    //création de la window
    sf::RenderWindow oWindow(VideoMode(900, 900), "Mon truc");

    //initialisation du GameManager 
    GameManager::Init();
    //Récuperation de la GameLoop du GameManager grâçe au Get et ouverture dans la wondow  
    GameManager::Get()->GameLoop(&oWindow);
   
    return 0;
}