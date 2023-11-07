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
    GameObject truc(0, 0, 100, &oWindow, Color::Red);
    GameObject canon(oWindow.getSize().x/ 2, 500, 50, 100, &oWindow, Color::Green);
	GameObject canon2(oWindow.getSize().x / 2 - 110, 350, 50, 100, &oWindow, Color::Blue);


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
                if (ballList.size() == 0)
                {
                    Vector2i mousePos = Mouse::getPosition(oWindow);
                    Vector2f mousePosF = Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                    Vector2f ballStartPosition = Vector2f(static_cast<float>(canon.posX), static_cast<float>(canon.posY));

                    Vector2f direction = Vector2f(mousePosF.x - ballStartPosition.x, mousePosF.y - ballStartPosition.y);

                    ballList.push_back(GameObject(canon.posX, canon.posY, 10, &oWindow, Color::Blue));

                    ballList[ballList.size() - 1].shape->setOrigin(ballList[ballList.size() - 1].sizeH / 2, ballList[ballList.size() - 1].sizeW / 2);

                    ballList[ballList.size() - 1].ChangeDirection(direction);

                    canon.Shoot(mousePos);
                }
            }
        }

        //UPDATE

        //DRAW
        oWindow.clear();

        truc.Draw();
		canon.Draw();
        canon.Rotate(Mouse::getPosition(oWindow));

        for (int i = 0; i < ballList.size(); i++)
        {
            ballList[i].Draw();
            ballList[i].Move(fDeltaTime);
        }

        //canon2.Colision(canon);
        //canon2.Move(fDeltaTime);
        //canon2.Draw();

        oWindow.display();
        
        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}