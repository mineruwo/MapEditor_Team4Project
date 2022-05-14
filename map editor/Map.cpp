#include "Map.h"
#define TILEDRAWSIZE 16;


Map::Map()
{
    rapidcsv::Document mapData("data_tables/Maps/Mapdata.csv");

    MapNumber = mapData.GetColumn<int>("MapNumber");
    MapXSize = mapData.GetColumn<int>("MapXSize");
    MapYSize = mapData.GetColumn<int>("MapYSize");
    OBJFilePath = mapData.GetColumn<std::string>("OBJFilePath");
    OBJSFilePath = mapData.GetColumn< std::string>("OBJSFilePath");

    for (auto it : OBJFilePath)
    {
        rapidcsv::Document objData(it);
        ColObjNum = objData.GetColumn<int>("ColObjNum");
        ColL = objData.GetColumn<int>("ColL");
        ColT = objData.GetColumn<int>("ColT");
        ColW = objData.GetColumn<int>("ColW");
        ColH = objData.GetColumn<int>("ColH");
    }

    for (auto it : OBJSFilePath)
    {
        rapidcsv::Document objsData(it);
        OBJnum = objsData.GetColumn<int>("OBJnum");
        ObjFilePath = objsData.GetColumn<std::string>("ObjFilePath");
        PosX = objsData.GetColumn<int>("PosX");
        PosY = objsData.GetColumn<int>("PosY");
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
    float offset = 320.f;

    if (InputMgr::GetKey(Keyboard::A))
    {

        mainview.move(-1 * offset * dt.asSeconds(), 0.f);
      
    }
    if (InputMgr::GetKey(Keyboard::D))
    {
        mainview.move(offset* dt.asSeconds(), 0.f);
    }

    if (InputMgr::GetKey(Keyboard::S))
    {
        mainview.move(0.f, offset* dt.asSeconds());
    }
    if (InputMgr::GetKey(Keyboard::W))
    {
        mainview.move(0.f, -1 * offset * dt.asSeconds());
    }

    if (InputMgr::GetKeyDown(Keyboard::BackSpace))
    {

        if (!blocks.empty())
        {
            blocks.pop_back();

        }
    }
    if (InputMgr::GetKeyDown(Keyboard::Delete))
    {

        if (!Objs.empty())
        {
            Objs.pop_back();

        }
    }
}

void Map::DragMap(RenderWindow& window,MyMouse& mouse)
{
    if (InputMgr::GetKey(Keyboard::LShift) && InputMgr::GetMouseButtonDown(Mouse::Left))
    {
        originPos.x = (int)(Mouse::getPosition(window).x) ;
        originPos.y = (int)(Mouse::getPosition(window).y) ;
        worldPos = window.mapPixelToCoords(originPos);
        
        currDrag = new RectangleShape;

        currDrag->setFillColor(Color(255, 0, 0, 128));
        currDrag->setPosition((int)(worldPos.x / 16)* 16, (int)(worldPos.y / 16) * 16);
        isDrag = true;
    }

    if (InputMgr::GetKey(Keyboard::LShift) && InputMgr::GetMouseButton(Mouse::Left) && isDrag)
    {
        Vector2i currMousePos;

        currMousePos.x = (int)Mouse::getPosition(window).x;
        currMousePos.y = (int)Mouse::getPosition(window).y;

       currworldPos = window.mapPixelToCoords(currMousePos);

        currDrag->setSize(Vector2f((int)(floor(currworldPos.x - worldPos.x) / 16) * 16 , (int)(floor(currworldPos.y - worldPos.y))/ 16 * 16 ));

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

void Map::InputObj(Obj obj, MyMouse& mouse)
{
    Obj* createObj = new Obj();
    Vector2f pos = (Vector2f)mouse.GetmousePosView();

    createObj->SetFile(obj.GetFilePath());

    createObj->SetPosition(pos);

    Objs.push_back(createObj);
}

void Map::InputTiles(Tile tile, MyMouse& mouse)
{
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

    idx = 0;
    for (auto it : OBJnum)
    {
      Obj* creatobj = new Obj;

      creatobj->SetFile(ObjFilePath[idx]);
      creatobj->SetPosition(Vector2f(PosX[idx], PosY[idx]));

      Objs.push_back(creatobj);

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
            fs << idx << "," << it2->getGlobalBounds().left << "," << it2->getGlobalBounds().top << ","
                << it2->getGlobalBounds().width << "," << it2->getGlobalBounds().height << "," << endl;
            idx++;
        }

        fs.close();
    }

    idx = 0;
    for (auto it : OBJSFilePath)
    {
        fs.open(it, ios::app);

        for (auto it2 : Objs)
        {
            fs << idx << "," << it2->GetFilePath() << "," << it2->GetSprite().getPosition().x << "," << it2->GetSprite().getPosition().y << "," << endl;
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

std::vector<Obj*> Map::GetObjs()
{
    return Objs;
}

