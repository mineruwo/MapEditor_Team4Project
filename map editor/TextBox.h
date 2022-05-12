#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "InputMgr.h"
#include "MyMouse.h"

using namespace sf;

class TextBox
{
private:

	RectangleShape box;
	std::string getstr;

	Font font;
	Text name;

	bool isActive = false;

public:
	
	TextBox(std::string name, std::string getstr);
	void Draw(RenderWindow& window);

	RectangleShape Getbox();
	Text Getname();
	std::string GetSetstr();
	void SetActive(bool act);
	bool GetActive();

	void SetPosition(Vector2i pos);

};

