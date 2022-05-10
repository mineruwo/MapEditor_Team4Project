#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureHolder.h"
#include "InputMgr.h"

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

	Font font;
	Text UiText;

public:

	GUI();

	void InputUi();

	void SetString(std::string str);
	void DrawString(RenderWindow& window);

	void ShowGUIMenu(float dt);

	void DrawUI(RenderWindow& window);


};

