#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Utils.h"

class Grid
{
private:
	Texture& texgrid;
	VertexArray grid;

public:
	Grid();
	void CreateGrid(IntRect area);

	Texture& Gettexgrid();
	VertexArray& Getgrid();

};

