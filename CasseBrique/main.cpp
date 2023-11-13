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
   



















    /*
    //Création d'une fenêtre

    VideoMode fullscreenMode = VideoMode::getFullscreenModes()[0];
    RenderWindow oWindow(VideoMode(900, 900), "SFML");
    //sf::RenderWindow window(fullscreenMode, "SFML Fullscreen", sf::Style::Fullscreen);

    vector<Ball> ballList;
	vector<Brick> brickList;
    brickList.push_back(Brick(200, 200, 100, 50, 1, &oWindow, Color::Red));
    brickList[0].CenterOrigin();
	brickList.push_back(Brick(300, 200, 100, 50, 2, &oWindow, Color::Blue));
	brickList[1].CenterOrigin();
    Canon canon(oWindow.getSize().x / 2, 800, 50, 100, &oWindow, Color::Green);

    //GameObject mouseSquare(0, 0, 100, 100, &oWindow, Color::Yellow);
    //mouseSquare.CenterOrigin();

    float frameTime = 1.0f / 60.0f;

    float fDeltaTime = 0.0f;

    int numSimulation = 10;
 //Création d'une fenêtre

    VideoMode fullscreenMode = VideoMode::getFullscreenModes()[0];
    RenderWindow oWindow(VideoMode(900, 900), "SFML");
    //sf::RenderWindow window(fullscreenMode, "SFML Fullscreen", sf::Style::Fullscreen);

    vector<Ball> ballList;
	vector<Brick> brickList;
    brickList.push_back(Brick(200, 200, 100, 50, 1, &oWindow, Color::Red));
    brickList[0].CenterOrigin();
	brickList.push_back(Brick(305, 200, 100, 50, 2, &oWindow, Color::Blue));
	brickList[1].CenterOrigin();
    Canon canon(oWindow.getSize().x / 2, 800, 50, 100, &oWindow, Color::Green);

    //GameObject mouseSquare(0, 0, 100, 100, &oWindow, Color::Yellow);
    //mouseSquare.CenterOrigin();

    float frameTime = 1.0f / 60.0f;

    float fDeltaTime = 0.0f;

    int numSimulation = 10;

    //GameLoop
    while (oWindow.isOpen())
    {

        //EVENT
        Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == Event::Closed) {
                oWindow.close();
            }
            if (oEvent.type == Event::KeyPressed && oEvent.key.code == Keyboard::Escape) {
				oWindow.close();
            }
            if (oEvent.type == Event::MouseButtonPressed && oEvent.key.code == Mouse::Left) {
                if (ballList.size() <= 100 and Mouse::getPosition(oWindow).y < canon.posY)
                {
                    canon.Shoot(&ballList);
                }
            }
        }

        //UPDATE

        //DRAW
        oWindow.clear();

        for (int i = 0; i < ballList.size(); i++)
        {

            if (ballList[i].WallBounce()){
                ballList.erase(ballList.begin() + i);
            }else{
                for (int j = 0; j < numSimulation; j++)
                {
                    ballList[i].Collision(&brickList);
                    ballList[i].Move(fDeltaTime / 10);
                }
			    ballList[i].Draw();
            }
        }

        for (int i = 0; i < brickList.size(); i++)
        {
            brickList[i].Draw();
            if (brickList[i].DetectDeath(&brickList[i]))
            {
                brickList.erase(ballList.begin() + i);
            }
        }
        /*
        mouseSquare.Collision(&brickList);

        mouseSquare.posX = Mouse::getPosition(oWindow).x;
        mouseSquare.posY = Mouse::getPosition(oWindow).y;

        //mouseSquare.Move(fDeltaTime);
        //mouseSquare.Draw();
       
        canon.CanonRotate(Mouse::getPosition(oWindow));
		canon.Draw();

        oWindow.display();
        
        fDeltaTime = oClock.restart().asSeconds();

        if (fDeltaTime < frameTime)
        {
            sf::sleep(seconds(frameTime - fDeltaTime));
        }
    }
//GameLoop
    while (oWindow.isOpen())
    {

        //EVENT
        Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == Event::Closed) {
                oWindow.close();
            }
            if (oEvent.type == Event::KeyPressed && oEvent.key.code == Keyboard::Escape) {
				oWindow.close();
            }
            if (oEvent.type == Event::MouseButtonPressed && oEvent.key.code == Mouse::Left) {
                if (ballList.size() <= 100 and Mouse::getPosition(oWindow).y < canon.posY)
                {
                    canon.Shoot(&ballList);
                }
            }
        }

        //UPDATE

        //DRAW
        oWindow.clear();

        for (int i = 0; i < ballList.size(); i++)
        {

            if (ballList[i].WallBounce()){
                ballList.erase(ballList.begin() + i);
            }else{
                for (int j = 0; j < numSimulation; j++)
                {
                    ballList[i].Collision(&brickList);
                    ballList[i].Move(fDeltaTime / 10);
                }
			    ballList[i].Draw();
            }
        }

        for (int i = 0; i < brickList.size(); i++)
        {
            brickList[i].Draw();
            if (brickList[i].DetectDeath(&brickList[i]))
            {
                brickList.erase(brickList.begin() + i);
            }
        }
        /*
        mouseSquare.Collision(&brickList);

        mouseSquare.posX = Mouse::getPosition(oWindow).x;
        mouseSquare.posY = Mouse::getPosition(oWindow).y;

        //mouseSquare.Move(fDeltaTime);
        //mouseSquare.Draw();
  
        canon.CanonRotate(Mouse::getPosition(oWindow));
		canon.Draw();

        oWindow.display();
        
        fDeltaTime = oClock.restart().asSeconds();

        if (fDeltaTime < frameTime)
        {
            sf::sleep(seconds(frameTime - fDeltaTime));
        }
    }*/

    return 0;
}