#include <SFML/Graphics.hpp>
#include "GameObject.h"

using namespace sf;

int main(int argc, char** argv)
{
    //Création d'une fenêtre
    RenderWindow oWindow(VideoMode(640, 480), "SFML");

    //Création d'un cercle de radius 100
    CircleShape oCircle(100.f);
    //A la position 0, 0
    oCircle.setPosition(0.f, 0.f);
    //Et de couleur verte
    oCircle.setFillColor(Color::Green);


    //Création d'un rectangle de taille 50, 50
    RectangleShape oRectangle(Vector2f(50.f, 50.f));
    //A la position 100, 100
    oCircle.setPosition(100.f, 100.f);
    //Et de couleur rouge
    oRectangle.setFillColor(Color::Red);
    
    GameObject truc(0, 0, 100, &oWindow, Color::Red);

    //GameLoop
    while (oWindow.isOpen())
    {
        //EVENT
        Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == Event::Closed)
                oWindow.close();
        }

        //UPDATE

        //DRAW
        oWindow.clear();

        oWindow.draw(oCircle);
        oWindow.draw(oRectangle);
        truc.Draw();
        oWindow.display();
    }

    return 0;
}