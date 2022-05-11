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


#define TilePath "graphics/tilesets"

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

	Font font;
	Text UiText;

	int defaultTileKey;

	TileMap setTile;

	std::map<tilesets, std::string> tileMapFilePaths;
	std::vector <sf::Sprite*> tileSetButton;
	std::map<std::string, std::string> objFilePaths;


public:

	GUI();

	void InputUi();

	void SetString(std::string str);
	void DrawString(RenderWindow& window);
	void ClickButton(MyMouse& mouse);

	void ShowGUIMenu(float dt);
	void DrawUI(RenderWindow& window);

	void loadTileSetButton();

};

