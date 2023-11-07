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
            if (oEvent.type == Event::Closed)
                oWindow.close();
            if (oEvent.type==Event::KeyPressed && oEvent.key.code == Keyboard::Escape)
				oWindow.close();
        }

        //UPDATE

        //DRAW
        oWindow.clear();

        truc.Draw();
		canon.Draw();
        //canon.Rotate();
        canon2.Colision(canon);
        canon2.Move(fDeltaTime, { 1, 1 });
        canon2.Draw();
        oWindow.display();
        

        fDeltaTime = oClock.restart().asSeconds();
    }

    return 0;
}