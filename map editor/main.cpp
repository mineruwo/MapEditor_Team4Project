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
    View mainView(FloatRect(00, 0, 1366 / windowMagnification, 768 / windowMagnification));
    View uiView(FloatRect(0, 0, 320, 240));

    IntRect area;
    area.width = window.getSize().x;
    area.height = window.getSize().y;
 
    Grid grid;
    grid.CreateGrid(area);

    Player player;
    bool isPlayerInit = false;

    Map map;
    Clock clock;

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
 

        map.InputMap(windowMagnification, mainView,dt);
       
        
        if (InputMgr::GetKeyDown(Keyboard::F3))
        {
           CreateWalls(walls, map);
    
        }
        if (InputMgr::GetKeyDown(Keyboard::F4))
        {
            player.Init();
            isPlayerInit = true;
        }

        if (isPlayerInit && dt.asSeconds() <= 1.f / 200.f)
        {
            InputMgr::Update(dt.asSeconds());
            player.Update(dt.asSeconds(), walls);
        }

        window.clear();
        window.setView(mainView);

        window.draw(grid.Getgrid(), &grid.Gettexgrid());

        if (isPlayerInit && dt.asSeconds() <= 1.f / 200.f)
        {
            window.draw(player.GetSprite());
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
        if (mapdata.GetIdxVertex().empty())
        {
            break;
        }

        if (idx == mapdata.GeTtiles()[0].GettilesRect().size())
        {
            break;
        }
       
        if (mapdata.GetIdxVertex()[idx] == 89)
        {
            idx++;
            continue;
        }
    
        Wall* tile = new Wall(mapdata.GeTtiles()[0].GettilesRect()[idx]);
        walls.push_back(tile);
        std::cout << idx << "loaded" << std::endl;


        idx++;
     
    }



}