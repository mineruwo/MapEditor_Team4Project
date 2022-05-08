#include "Map.h"

Map::Map()
{
    rapidcsv::Document mapData("data_tables/Tiles/dirt/Mapdata.csv");

    OBJname = mapData.GetColumn<std::string>("OBJname");
    maxCount = mapData.GetColumn<int>("MapSize");
    W = mapData.GetColumn<int>("W");
    H = mapData.GetColumn<int>("H");
    dataFilePath = mapData.GetColumn<std::string>("BinFilePath");
    pngFilePath = mapData.GetColumn<std::string>("PNGsheetFilePath");
}

void Map::InputMap(int& windowMagnification, View& mainview, Time& dt)
{
    if (InputMgr::GetKeyDown(Keyboard::F3))
    {
        LoadMap();
    }

    if (InputMgr::GetKeyDown(Keyboard::F2))
    {
        SaveMap();
    }

    if (InputMgr::GetKeyDown(Keyboard::PageUp))
    {
        windowMagnification++;

        if (windowMagnification > 7)
        {
            windowMagnification = 7;
        }

        mainview.setSize(1366 / windowMagnification, 768 / windowMagnification);
    }
    if (InputMgr::GetKeyDown(Keyboard::PageDown))
    {
        windowMagnification--;

        if (windowMagnification < 1)
        {
            windowMagnification = 1;
        }

        mainview.setSize(1366 / windowMagnification, 768 / windowMagnification);

    }
    float offset = 150.f;

    if (InputMgr::GetKey(Keyboard::A))
    {

        mainview.move(-1 * offset * dt.asSeconds(), 0.f);
      
    }
    if (InputMgr::GetKey(Keyboard::D))
    {
        mainview.move(offset * dt.asSeconds(), 0.f);
    }

    if (InputMgr::GetKey(Keyboard::S))
    {
        mainview.move(0.f, offset * dt.asSeconds());
    }
    if (InputMgr::GetKey(Keyboard::W))
    {
        mainview.move(0.f, -1 * offset* dt.asSeconds());
    }

}

void Map::DrawMap(sf::RenderWindow& window)
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        window.draw(*it);
    }

}

void Map::LoadMap()
{
 
    TileMap tile;

    int idx = 0;
    int count = 0;
    std::ifstream ifs;

    tiles.clear();
    idxVertex.clear();

    while(true)
    {
        ifs.open(dataFilePath[idx], std::ifstream::in);

        while (true)
        {
            int id;
            ifs >> id;

            idxVertex.push_back(id);

            count++;

            if (count == maxCount[idx])
            {
                break;
            }

        }
        // mapdate load

        ifs.close();

        tile.load(pngFilePath[idx], Vector2u(8, 8), idxVertex, W[idx], H[idx], idxVertex);

        tiles.push_back(tile);

        idx++;

        if (idx == 1)
        {
            break;
        }

    }
}

void Map::SaveMap()
{
}

std::vector<TileMap> Map::GeTtiles()
{
    return tiles;
}

std::vector<std::vector<int>> Map::GetMapdate()
{
    return mapdate;
}

std::vector<sf::FloatRect> Map::GetRect()
{
    return tilesRect;
}

std::vector<int> Map::GetIdxVertex()
{
    return idxVertex;
}
