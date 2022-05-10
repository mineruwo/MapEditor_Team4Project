#pragma once
#include "TextureHolder.h"
#include "InputMgr.h"
#include "rapidcsv.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string.h>
#include "Grid.h"
#include "TileMap.h"

class Map
{
private:

	std::vector<int> MapNumber;
	std::vector<int> MapXSize;
	std::vector<int> MapYSize;
	std::vector<std::string> OBJFilePath;

	std::vector<int> ColObjNum;
	std::vector<int> ColL;
	std::vector<int> ColT;
	std::vector<int> ColW;
	std::vector<int> ColH;


	std::vector<sf::RectangleShape*> blocks;

	Vector2i originPos;
	Vector2f worldPos;
	Vector2f currworldPos;
	bool isDrag = false;

	RectangleShape* currDrag;



public:
	Map();
	void InputMap(int& windowMagnification, View& mainview, Time& dt);
	void DragMap(RenderWindow& window);
	void DrawMap(sf::RenderWindow & window);

	void LoadMap();
	void SaveMap();

	std::vector<int> GetMapNumber();
	std::vector<int> GetMapXSize();
	std::vector<int> GetMapYSize();
	std::vector<sf::RectangleShape*> Getblocks();
	
};

