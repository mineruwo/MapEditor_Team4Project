#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "InputMgr.h"
#include "MyMouse.h"
#include <vector>
#include <map>
#include "TileMap.h"
#include "rapidcsv.h"
#include "TextBox.h"
#include "Obj.h"
#include "Tile.h"

#define TilePath "graphics/tilesets"
#define ObjPath "graphics"

using namespace sf;



class GUI
{
private:
	Sprite menuBar;
	Sprite tileButton;
	Sprite objButtion;
	Sprite menuInterface;

	bool isMenuOpen = false;
	bool isMenuClose = false;
	bool isInputTab = false;

	bool isTileset = false;
	bool isObjset = false;

	bool isSelectObj = false;
	bool isSelectTile = false;

	Font font;
	Text UiText;

	Obj* setobj;
	Tile* setTile;
	

	int currentPage = 0;
	int tileCurrpage = 0;


	std::map <tilesets, std::string> tileMapFilePaths;
	std::map <std::string, std::string> objFilePaths;
	std::vector <TextBox*> objSetButton;
	std::vector<std::vector<Tile*>> tilesButtion;

public:

	GUI();

	void InputUi();

	void SetString(std::string str);
	void DrawString(RenderWindow& window);
	void ClickButton(MyMouse& mouse);

	void ShowGUIMenu(float dt);
	void DrawUI(RenderWindow& window);


	bool IsSelectObj()
	{
		return isSelectObj;
	}

	Obj Getobj()
	{
		return *setobj;
	}

	bool IsSelectTile()
	{
		return isSelectTile;
	}

	Tile GetTile()
	{
		return *setTile;
	}
};

