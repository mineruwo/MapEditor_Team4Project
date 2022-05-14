#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(std::string FilePath, int id)
{
	tile.setTexture(TextureHolder::GetTexture(FilePath));
	this->id = id;
	setFilePath = FilePath;

}

void Tile::Update(MyMouse mouse)
{
	tile.setPosition(Vector2f(((mouse.GetmousePosWindow().x/16)*16), ((mouse.GetmousePosWindow().y / 16)*16)));
}

void Tile::Draw(RenderWindow& window)
{
	window.draw(tile);
}

void Tile::SetFile(std::string FilePath)
{
	setFilePath = FilePath;
	tile.setTexture(TextureHolder::GetTexture(FilePath));
}

void Tile::SetPosition(Vector2i pos)
{
	tile.setPosition(Vector2f(pos));
}

std::string Tile::GetFilePath()
{
	return std::string();
}

Sprite Tile::GetSprite()
{
	return Sprite();
}

void Tile::SetActive(bool isActive)
{
	this->isActive = isActive;
}

bool Tile::GetActive()
{
	return isActive;
}

int Tile::GetID()
{
	return id;
}

void Tile::SetID(int id)
{
	this->id = id;
}

void Tile::SetTileSetsInfo(int idx)
{
	info = tilesets(idx);
}

tilesets Tile::GetTilesets()
{
	return info;
}
