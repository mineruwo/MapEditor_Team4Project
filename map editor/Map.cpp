#include "Map.h"

Map::Map()
{
    rapidcsv::Document mapData("data_tables/Maps/Mapdata.csv");

    MapNumber = mapData.GetColumn<int>("MapNumber");
    MapXSize = mapData.GetColumn<int>("MapXSize");
    MapYSize = mapData.GetColumn<int>("MapYSize");
    OBJFilePath = mapData.GetColumn<std::string>("OBJFilePath");


    /*ColL = mapData.GetColumn<int>("ColL");
    ColT = mapData.GetColumn<int>("ColT");
    ColW = mapData.GetColumn<int>("ColW");
    ColH = mapData.GetColumn<int>("ColH");*/

  
   
}

void Map::InputMap(int& windowMagnification, View& mainview, Time& dt, RenderWindow& window)
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
    float offset = 300.f;

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

    if (InputMgr::GetKey(Keyboard::LShift) && InputMgr::GetMouseButtonDown(Mouse::Left))
    {
        originPos = Mouse::getPosition(window)/8 * 8;
        worldPos = window.mapPixelToCoords(originPos);

        currDrag = new RectangleShape;

        currDrag->setFillColor(Color(255, 0, 0,128));
        currDrag->setPosition(worldPos.x/8 * 8,worldPos.y/8 * 8);
        isDrag = true;
    }
    
    if (InputMgr::GetKey(Keyboard::LShift) && InputMgr::GetMouseButton(Mouse::Left)&& isDrag)
    {
        worldPos = window.mapPixelToCoords(originPos);

        currDrag->setSize(Vector2f((Mouse::getPosition(window).x/8)*8- worldPos.x, (Mouse::getPosition(window).y / 8)*8- worldPos.y));
    }

    if ((InputMgr::GetKeyUp(Keyboard::LShift) || InputMgr::GetMouseButtonUp(Mouse::Left))&&isDrag)

    {
        RectangleShape* createBlock = new RectangleShape;
        
        createBlock->setPosition(currDrag->getPosition());
        createBlock->setSize(currDrag->getSize());

        blocks.push_back(createBlock);

        delete currDrag;
        isDrag = false;
    }
}

void Map::DrawMap(sf::RenderWindow& window)
{
 
    if (isDrag)
    {
       window.draw(*currDrag);
    }
   
}

void Map::LoadMap()
{
    
    
}

void Map::SaveMap()
{
}

std::vector<int> Map::GetMapNumber()
{
    return MapNumber;
}

std::vector<int> Map::GetMapXSize()
{
    return MapXSize;
}

std::vector<int> Map::GetMapYSize()
{
    return MapYSize;
}

std::vector<sf::RectangleShape*> Map::Getblocks()
{
    return blocks;
}

