#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <string>
#include <iostream>
#include "InputMgr.h"
#include "Map.h"
#include "Player.h"
#include "Wall.h"

void CreateWalls(std::vector<Wall*>& walls, Map& mapdata);
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(1366, 768), "Map simulator");
    TextureHolder textureHolder;
     
    int windowMagnification = 3;
    View mainView(FloatRect(0, 0, window.getSize().x / windowMagnification, window.getSize().y / windowMagnification));

    View UiView(FloatRect(0, 0, window.getSize().x, window.getSize().y));

    IntRect area;
    area.width = window.getSize().x;
    area.height = window.getSize().y;
 
    Grid grid;

    Player player;
    bool isPlayerInit = false;

    Map map;
    Clock clock;

    int currMap = 0;

    std::vector <Wall*> walls;

    CreateWalls(walls, map);

    while (window.isOpen())
    {
        Event event;
        InputMgr::ClearInput();

        Time dt = clock.restart();

        while (window.pollEvent(event))
        {
            InputMgr::ProcessInput(event);
            if (event.type == Event::Closed)
                window.close();
        }
 

        map.InputMap(windowMagnification, mainView,dt,window);
       
        
        if (InputMgr::GetKeyDown(Keyboard::F3))
        {
            std::string mgr;
            mgr += "Map simulator";
            mgr += "_CurrMap Number is ";
            mgr += currMap;

            window.setTitle(mgr);

          // CreateWalls(walls, map);
            area.width =  map.GetMapXSize()[currMap];
            area.height = map.GetMapYSize()[currMap];
            grid.CreateGrid(area);
        }
        if (InputMgr::GetKeyDown(Keyboard::F4))
        {
            player.Init();
            isPlayerInit = true;
        }

        if (InputMgr::GetKeyDown(Keyboard::F5))
        {
           /* for (auto it : walls)
            {
                delete it;
            }

            for (auto it : map.Getblocks())
            {
                delete it;
            }
            walls.clear();
            map.Getblocks().clear();*/
        }


        if (isPlayerInit && dt.asSeconds() <= 1.f / 200.f)
        {
            InputMgr::Update(dt.asSeconds());
            player.Update(dt.asSeconds(), walls);
            grid.CreateGrid(area);
        }
        CreateWalls(walls, map);


        window.clear();
        window.setView(mainView);
        window.draw(grid.Getgrid(), &grid.Gettexgrid());

        if (isPlayerInit && dt.asSeconds() <= 1.f / 200.f)
        {
            window.draw(player.GetSprite());
        }
        for (auto it : walls)
        {
            it->DrawWall(window);
        }
        map.DrawMap(window);
        window.display();
    }

    return 0;
}

void CreateWalls(std::vector<Wall*>& walls, Map& mapdata)
{
    for (auto v : walls)
    {
        delete v;
    }

    walls.clear();

    int idx = 0;

    while (true)
    {
       
        if (idx == mapdata.Getblocks().size())
        {
            break;
        }

        Wall* tile = new Wall(mapdata.Getblocks()[idx]->getGlobalBounds());
        walls.push_back(tile);

        idx++;
     
    }

}