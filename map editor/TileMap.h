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

    std::vector<FloatRect> tilesSetRect;

public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height, std::vector<int> mapdata);
    VertexArray GetVertexArray();
    std::vector<FloatRect> GettilesRect();

    
 

};

