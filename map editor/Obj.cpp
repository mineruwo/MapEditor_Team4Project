#include "Obj.h"

Obj::Obj()
{
}

Obj::Obj(std::string str)
{
	setSprite.setTexture(TextureHolder::GetTexture(str));
	setFilePath = str;
}

void Obj::Draw(RenderWindow& window)
{
	window.draw(setSprite);
}

void Obj::SetFile(std::string file)
{
	setSprite.setTexture(TextureHolder::GetTexture(file));
	setFilePath = file;
}

void Obj::SetPosition(Vector2f pos)
{
	setSprite.setPosition((Vector2f)pos);
}

std::string Obj::GetFilePath()
{
	return setFilePath;
}

Sprite Obj::GetSprite()
{
	return setSprite;
}

void Obj::Update(MyMouse mouse)
{
	setSprite.setPosition((Vector2f)mouse.GetmousePosWindow());
}
