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
#include "Tile.h"
#include "MyMouse.h"
#include "Obj.h"

class Map
{
private:

	std::vector<int> MapNumber;
	std::vector<int> MapXSize;
	std::vector<int> MapYSize;
	std::vector<std::string> OBJFilePath;
	std::vector<std::string> OBJSFilePath;

	std::vector<int> ColObjNum;
	std::vector<int> ColL;
	std::vector<int> ColT;
	std::vector<int> ColW;
	std::vector<int> ColH;

	std::vector<int> OBJnum;
	std::vector<std::string> ObjFilePath;
	std::vector<int> PosX;
	std::vector<int> PosY;

	std::vector<sf::RectangleShape*> blocks;
	std::vector<Obj*> Objs;
	std::vector <Tile*> tiles;

	Vector2i originPos;
	Vector2f worldPos;
	Vector2f currworldPos;
	bool isDrag = false;

	RectangleShape* currDrag;

public:
	Map();
	void InputMap(int& windowMagnification, View& mainview, Time& dt);
	void DragMap(RenderWindow& window, MyMouse& mouse);
	void DrawMap(sf::RenderWindow & window);

	void InputObj(Obj obj, MyMouse& mouse);
	void InputTiles(Tile tile, MyMouse& mouse);

	void LoadMap();
	void SaveMap();

	std::vector<int> GetMapNumber();
	std::vector<int> GetMapXSize();
	std::vector<int> GetMapYSize();
	std::vector<sf::RectangleShape*> Getblocks();
	std::vector<Obj*> GetObjs();

	
};

