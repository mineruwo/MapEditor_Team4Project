#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

using namespace sf;
class GUI
{
private:
	Sprite MenuBar;
	Font font;
	Text UiText;

public:

	GUI();

	Sprite GetMenuBar();


};

