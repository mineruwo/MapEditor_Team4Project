#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <string>
#include <iostream>
#include "InputMgr.h"
#include "Map.h"
#include "Player.h"
#include "Wall.h"
#include "GUI.h"
#include "MyMouse.h"

void CreateWalls(std::vector<Wall*>& walls, Map& mapdata);
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(1366, 768), "Map simulator");
    TextureHolder textureHolder;

    IntRect area;
    area.width = window.getSize().x;
    area.height = window.getSize().y;
     
    int windowMagnification = 2;

    View mainView(FloatRect(736, 256, area.width / windowMagnification, area.height / windowMagnification));
    View UiView = window.getDefaultView();
    View backgroundView = window.getDefaultView();
    View FrontgroundView = window.getDefaultView();
    
    window.setMouseCursorVisible(false);
    
    GUI ui;
    MyMouse mouse;
    mouse.initMouse();
    Grid grid;

    Player player;
    bool isPlayerInit = false;

    Map map;
    Clock clock;

    float stringTimer = 0.f;
    bool isStringPrint = false;

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

        map.InputMap(windowMagnification, mainView, dt);
        map.DragMap(window,mouse);
        mouse.updateMouse(window, area);

        if(isStringPrint)
        {
            stringTimer += dt.asSeconds();
            if (stringTimer >= 2.f)
            {
                stringTimer = 0.f;
                isStringPrint = false;
            }
        }

        if (InputMgr::GetKeyDown(Keyboard::F2))
        {
            ui.SetString("Save MapData");
            window.setView(UiView);
            ui.DrawString(window);
            isStringPrint = true;
            stringTimer = 0.f;
        }

        if (InputMgr::GetKeyDown(Keyboard::F3))
        {
            std::string mgr;
            mgr += "Map simulator";
            mgr += "_CurrMap Number is ";
            mgr += currMap;

            window.setTitle(mgr);

            area.width =  map.GetMapXSize()[currMap];
            area.height = map.GetMapYSize()[currMap];
            grid.CreateGrid(area);
            ui.SetString("Create Grid & Load Mapdata");
            isStringPrint = true;
            stringTimer = 0.f;
        }

        if (InputMgr::GetKeyDown(Keyboard::F4))
        {
            player.Init();
            isPlayerInit = true;
            ui.SetString("Player Spawn");
            window.setView(UiView);
            ui.DrawString(window);
            isStringPrint = true;
            stringTimer = 0.f;
        }

        if (isPlayerInit && dt.asSeconds() <= 1.f / 60.f)
        {
            InputMgr::Update(dt.asSeconds());
            player.Update(dt.asSeconds(), walls);
            grid.CreateGrid(area);
        }
        CreateWalls(walls, map);

        ui.InputUi();
        ui.ShowGUIMenu(dt.asSeconds());
        ui.ClickButton(mouse);

        window.clear();
        window.setView(mainView);
        window.draw(grid.Getgrid(), &grid.Gettexgrid());

        if (isPlayerInit && dt.asSeconds() <= 1.f / 60.f)
        {
            window.draw(player.GetSprite());
        }
        for (auto it : walls)
        {
            it->DrawWall(window);
        }

        map.DrawMap(window);

        window.setView(UiView);
        if (isStringPrint)
        {
            ui.DrawString(window);
        }

        ui.DrawUI(window);
        window.setView(mainView);
        mouse.drawMouse(window);


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