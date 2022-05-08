#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Utils.h"

class Grid
{
private:
	Texture& texgrid;
	VertexArray grid;

	Texture& texdirt;
	VertexArray dirt;

public:
	Grid();
	void CreateGrid(IntRect area);
	void SetVertexdirt();

	Texture& Gettexgrid();
	VertexArray& Getgrid();

};

