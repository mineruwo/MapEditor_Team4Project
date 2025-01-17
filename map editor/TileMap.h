#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Utils.h"
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
    bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);

    VertexArray GetVertexArray();

    void setTileset(Texture tex);

};

