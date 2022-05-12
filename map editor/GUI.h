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

#define TilePath "graphics/tilesets"
#define ObjPath "graphics"

using namespace sf;

enum class tilesets
{
	bgDirt,
	bgBrick,
	bgSnow,
	cement,
	dirt,
	girder,
	snow,
	count
};

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

	Font font;
	Text UiText;

	Obj* setobj;
	
	int defaultTileKey;

	int currentPage = 0;

	TileMap setTile;

	std::map <tilesets, std::string> tileMapFilePaths;
	std::vector <sf::Sprite> tileSetButton;
	std::map <std::string, std::string> objFilePaths;
	std::vector <TextBox*> objSetButton;

public:

	GUI();

	void InputUi();

	void SetString(std::string str);
	void DrawString(RenderWindow& window);
	void ClickButton(MyMouse& mouse);

	void ShowGUIMenu(float dt);
	void DrawUI(RenderWindow& window);

	void loadTileSetButton();
	void loadObjSetButton();

	bool IsSelectObj()
	{
		return isSelectObj;
	}

	Obj Getobj()
	{
		return *setobj;
	}
};

