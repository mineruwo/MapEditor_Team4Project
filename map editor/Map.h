#pragma once
#include "TextureHolder.h"
#include "InputMgr.h"
#include "rapidcsv.h"
#include <vector>
#include "Grid.h"
#include "TileMap.h"

class Map
{
private:

	std::vector<std::string> OBJname;
	std::vector<int> maxCount;
	std::vector<int> W;
	std::vector<int> H;

	std::vector<std::string> dataFilePath;
	std::vector<std::string> pngFilePath;

	std::vector<TileMap> tiles;
	std::vector<std::vector<int>> mapdate;
	std::vector <sf::FloatRect> tilesRect;
	std::vector<int> idxVertex;

public:
	Map();
	void InputMap(int& windowMagnification, View& mainview, Time& dt);
	void DrawMap(sf::RenderWindow& window);

	void LoadMap();
	void SaveMap();

	std::vector<TileMap> GeTtiles();
	std::vector< std::vector<int>> GetMapdate();
	std::vector<sf::FloatRect> GetRect();
	std::vector<int> GetIdxVertex();
};

