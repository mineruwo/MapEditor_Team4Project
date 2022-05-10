#include "Map.h"

Map::Map()
{
    rapidcsv::Document mapData("data_tables/Maps/Mapdata.csv");

    MapNumber = mapData.GetColumn<int>("MapNumber");
    MapXSize = mapData.GetColumn<int>("MapXSize");
    MapYSize = mapData.GetColumn<int>("MapYSize");
    OBJFilePath = mapData.GetColumn<std::string>("OBJFilePath");


    for (auto it : OBJFilePath)
    {
        rapidcsv::Document objData(it);
        ColObjNum = objData.GetColumn<int>("ColObjNum");
        ColL = objData.GetColumn<int>("ColL");
        ColT = objData.GetColumn<int>("ColT");
        ColW = objData.GetColumn<int>("ColW");
        ColH = objData.GetColumn<int>("ColH");
    }
    
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
    float offset = 32.f;

    if (InputMgr::GetKeyDown(Keyboard::A))
    {

        mainview.move(-1 * offset, 0.f);
      
    }
    if (InputMgr::GetKeyDown(Keyboard::D))
    {
        mainview.move(offset, 0.f);
    }

    if (InputMgr::GetKeyDown(Keyboard::S))
    {
        mainview.move(0.f, offset );
    }
    if (InputMgr::GetKeyDown(Keyboard::W))
    {
        mainview.move(0.f, -1 * offset);
    }

    if (InputMgr::GetKeyDown(Keyboard::BackSpace))
    {

        if (!blocks.empty())
        {
            blocks.pop_back();

        }

        
    }

 
}

void Map::DragMap(RenderWindow& window)
{
    if (InputMgr::GetKey(Keyboard::LShift) && InputMgr::GetMouseButtonDown(Mouse::Left))
    {
        originPos.x = (int)(Mouse::getPosition(window).x) ;
        originPos.y = (int)(Mouse::getPosition(window).y) ;
        worldPos = window.mapPixelToCoords(originPos);


        cout << "world : " << (int)worldPos.x/8 * 8 << " " << (int)worldPos.y / 8 * 8 << endl;
        cout << "origin : " << originPos.x << " " << originPos.y << endl;

        currDrag = new RectangleShape;

        currDrag->setFillColor(Color(255, 0, 0, 128));
        currDrag->setPosition((int)worldPos.x / 8 * 8, (int)worldPos.y / 8 * 8);
        isDrag = true;
    }

    if (InputMgr::GetKey(Keyboard::LShift) && InputMgr::GetMouseButton(Mouse::Left) && isDrag)
    {
        Vector2i currMousePos;

        currMousePos.x = (int)Mouse::getPosition(window).x;
        currMousePos.y = (int)Mouse::getPosition(window).y;

       currworldPos = window.mapPixelToCoords(currMousePos);

        currDrag->setSize(Vector2f((int)currworldPos.x / 8 * 8, (int)currworldPos.y / 8 * 8));
    }

    if (isDrag && InputMgr::GetMouseButton(Mouse::Right))
    {
        isDrag = false;
    }

    if ((InputMgr::GetKeyUp(Keyboard::LShift) || InputMgr::GetMouseButtonUp(Mouse::Left)) && isDrag)

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
    int idx = 0;
    for (auto it : ColObjNum)
    {
        RectangleShape* createBlock = new RectangleShape;

        createBlock->setPosition(ColL[idx], ColT[idx]);
        createBlock->setSize(Vector2f(ColW[idx],ColH[idx]));
        
        blocks.push_back(createBlock);

        idx++;
    }
    
}

void Map::SaveMap()
{
    fstream fs;

    int idx = 0;
    for (auto it : OBJFilePath)
    {
        fs.open(it, ios::app);
        
        for (auto it2 : blocks)
        {
            fs  << idx << "," << it2->getGlobalBounds().left << "," << it2->getGlobalBounds().top << ","
                << it2->getGlobalBounds().width << "," << it2->getGlobalBounds().height << ","<< endl;
            idx++;
        }

        fs.close();
    }
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

