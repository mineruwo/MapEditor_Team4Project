#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Utils.h"

class dirt
{
private:
	Texture& texdirt;
	VertexArray dirts;
public:
	dirt();
	void SetVertexdirts();
};

