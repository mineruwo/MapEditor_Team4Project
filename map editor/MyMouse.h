#pragma once
#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include <string.h>
#include <stdlib.h>

using namespace sf;
class MyMouse
{
private:
	RectangleShape mouseBox;
	
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2u mousePosGrid;

	Font font;
	Text posText;

public:

	void initMouse();

	void updateMouse(RenderWindow& window, IntRect area);

	void drawMouse(RenderWindow& window);

	RectangleShape GetMouseBox();

	Vector2i GetmousePosScreen();
	Vector2i GetmousePosWindow();
	Vector2f GetmousePosView();
	Vector2u GetmousePosGrid();


};

