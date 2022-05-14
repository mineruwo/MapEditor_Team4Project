#pragma once
#include <SFML/Graphics.hpp>
#include "MyMouse.h"
#include "../map editor/TextureHolder.h"

using namespace sf;

class Obj
{
private:
	Sprite setSprite;
	std::string setFilePath;
public:
	Obj();
	Obj(std::string str);
	void Draw(RenderWindow& window);
	void Update(MyMouse mouse);

	void SetFile(std::string file);
	void SetPosition(Vector2f pos);
	std::string GetFilePath();
	Sprite GetSprite();
};

