#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObject.h"
#include <vector>

using namespace sf;
using namespace std;

Clock oClock;



int main(int argc, char** argv)
{

    //Création d'une fenêtre

    VideoMode fullscreenMode = VideoMode::getFullscreenModes()[0];
    RenderWindow oWindow(VideoMode(900, 900), "SFML");
    //sf::RenderWindow window(fullscreenMode, "SFML Fullscreen", sf::Style::Fullscreen);

    vector<GameObject> ballList;
	vector<GameObject> brickList;
    brickList.push_back(GameObject(200, 200, 100, 50, &oWindow, Color::Red));
    brickList[0].CenterOrigin();
	brickList.push_back(GameObject(400, 200, 100, 50, &oWindow, Color::Red));
	brickList[1].CenterOrigin();
    GameObject canon(oWindow.getSize().x / 2, 800, 50, 100, &oWindow, Color::Green);

    GameObject mouseSquare(0, 0, 25, 25, &oWindow, Color::Yellow);
    mouseSquare.CenterOrigin();


    float fDeltaTime = 0.0f;

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


        for (int i = 0; i < brickList.size(); i++)
        {
            brickList[i].Draw();       
        }

        for (int i = 0; i < ballList.size(); i++)
        {

            for (int j = 0; j < brickList.size(); j++)
            {
                ballList[i].Collision(&brickList[j]);
            }

            if (ballList[i].WallBounce()){
                ballList.erase(ballList.begin() + i);
            }else{
                ballList[i].Move(fDeltaTime);
			    ballList[i].Draw();
            }

			
        }

        for (int j = 0; j < brickList.size(); j++)
        {
            mouseSquare.Collision(&brickList[j]);
        }

        mouseSquare.posX = Mouse::getPosition(oWindow).x;
        mouseSquare.posY = Mouse::getPosition(oWindow).y;

        mouseSquare.Move(fDeltaTime);
        mouseSquare.Draw();

		canon.Draw();
        canon.CanonRotate(Mouse::getPosition(oWindow));

        oWindow.display();
        
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}