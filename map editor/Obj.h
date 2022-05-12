#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "MyMouse.h"

using namespace sf;

class Obj
{
private:
	Sprite setSprite;
	std::string setFilePath;
public:
	Obj();
	Obj(std::string str);
	void Update(MyMouse mouse);
	void Draw(RenderWindow& window);

	void SetFile(std::string file);
	void SetPosition(Vector2f pos);
	std::string GetFilePath();
	Sprite GetSprite();
};

