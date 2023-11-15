#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Brick.h"
#include "Ball.h"
#include "Canon.h"
#include "TextureManager.h"

using namespace sf;
using namespace std;

class GameManager
{

private:
	GameManager();
	static GameManager* pInstance;

public:

	vector<Ball> ballList;
	vector<Brick> brickList;
	TextureManager textureManager;


	Canon* canon;

	float frameTime = 1.0f / 60.0f;

	float fDeltaTime = 0.0f;

	int numSimulation = 10;


	static void Init();
	static GameManager* Get();
	vector<Brick> loadBricksFromTxt(const string& filename, sf::RenderWindow* oWindow);
	void GameLoop(RenderWindow* oWindow);



};

