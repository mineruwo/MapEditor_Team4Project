#include "GUI.h"
#include <cmath>

GUI::GUI() 
{
	menuBar.setTexture(TextureHolder::GetTexture("graphics/UIopenMenuBar.png"));
	menuBar.setPosition(1270, 768 * 0.5 - 100);
	
	tileButton.setTexture(TextureHolder::GetTexture("graphics/TileButton.png"));

	objButtion.setTexture(TextureHolder::GetTexture("graphics/OBJButton.png"));

	menuInterface.setTexture(TextureHolder::GetTexture("graphics/GUIMenuInterface.png"));

	menuInterface.setPosition(1366, 0);
	tileButton.setPosition(1416, 20);
	objButtion.setPosition(1516, 20);

	font.loadFromFile("graphics/RobotoFlex-Regular.ttf");
	UiText.setFont(font);

	UiText.setPosition(Vector2f(0, 50));
	UiText.setCharacterSize(30);
	UiText.setFillColor(Color(0, 0, 240));

	rapidcsv::Document tileMapdata("data_tables/Tiles/tilesets.csv");

	std::vector<int> setTileKey = tileMapdata.GetColumn<int>("Key");
	std::vector<std::string> setTileValue = tileMapdata.GetColumn<std::string>("TileFilePath");

	
	for (int idx = 0; idx < setTileKey.size(); idx++)
	{
		tileMapFilePaths.insert(std::pair<tilesets, std::string>(tilesets(setTileKey[idx]), setTileValue[idx]));
		std::vector<Tile*>* createvecter = new std::vector<Tile*>;	

		int tileid = 0;

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				Tile* createTile = new Tile(TilePath + setTileValue[idx], tileid, IntRect(0+(i*8),0+(j*8), 8, 8));

				tileid++;

				createvecter->push_back(createTile);
			}
		}

		tilesButtion.push_back(*createvecter);
	}

	//tile 버튼 init

	rapidcsv::Document objsData("data_tables/obj/objs.csv");
	std::vector<std::string> setObjsKey = objsData.GetColumn<std::string>("Key");
	std::vector<std::string> setObjsValue = objsData.GetColumn<std::string>("ObjFilePath");


	for (int idx = 0; idx < setObjsKey.size(); idx++)
	{
		objFilePaths.insert(std::pair<std::string, std::string>(setObjsKey[idx], setObjsValue[idx]));
		TextBox* createBox = new TextBox(setObjsKey[idx], setObjsValue[idx]);
		objSetButton.push_back(createBox);
	}

	//textbox 버튼 init
}

void GUI::InputUi()
{
	if (InputMgr::GetKeyDown(Keyboard::Tab) && !isInputTab)
	{
		isMenuOpen = true;
		isInputTab = true;
	}
	else if (InputMgr::GetKeyDown(Keyboard::Tab) && isInputTab)
	{
		isMenuClose = true;
		isInputTab = false;
		isTileset = false;
		isObjset = false;
	}
}

void GUI::SetString(std::string str)
{
	UiText.setString(str);
}

void GUI::DrawString(RenderWindow& window)
{
	window.draw(UiText);
}

void GUI::ClickButton(MyMouse& mouse)
{
	if(tileButton.getGlobalBounds().contains(mouse.GetmousePosWindow().x,mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		isObjset = false;
		isTileset = true;
		std::cout << "tile" << endl;
	}

	if (objButtion.getGlobalBounds().contains(mouse.GetmousePosWindow().x, mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		isObjset = true;
		isTileset = false;

		std::cout << "obj" << endl;
	}

	if (isObjset)
	{
		for (auto it : objSetButton)
		{

			if (it->Getbox().getGlobalBounds().contains(mouse.GetmousePosWindow().x, mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left) && it->GetActive())
			{
				std::string str; 
				str += ObjPath;
				str += it->GetSetstr();

				if (!(setobj = nullptr))
				{
					delete setobj;
				}
				setobj = new Obj(str);

				isSelectObj = true;

			}

		}

	}

	if (isTileset)
	{
		for (auto it : tilesButtion[tileCurrpage])
		{
			if (it->GetSprite().getGlobalBounds().contains(mouse.GetmousePosWindow().x, mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left) )
			{
				if (!(setTile = nullptr))
				{
					delete setTile;
				}

				setTile = new Tile();
				setTile->CopyTile(*it);

				isSelectTile = true;

				cout << it->GetID() << endl;

			}
		}
	}
	
	if (isSelectObj)
	{
		setobj->Update(mouse);

		if (InputMgr::GetMouseButtonDown(Mouse::Right))
		{
			delete setobj;
			isSelectObj = false;
		}
	}

	if (isSelectTile)
	{
		setTile->Update(mouse);

		if (InputMgr::GetMouseButtonDown(Mouse::Right))
		{
			delete setTile;
			isSelectTile = false;
		}

	}
}

void GUI::ShowGUIMenu(float dt)
{
	float X = menuBar.getPosition().x;

	if (isMenuOpen)
	{
	
		int offset = 300;
		menuBar.move(offset * dt * -1.f, 0);

		menuInterface.move(offset * dt * -1.f, 0);

		tileButton.move(offset * dt * -1.f, 0);

		objButtion.move(offset * dt * -1.f, 0);

	}

	if (isMenuClose)
	{
		int offset = 300;

		menuBar.move(offset * dt * 1.f, 0);

		menuInterface.move(offset * dt * 1.f, 0);

		tileButton.move(offset * dt * 1.f, 0);

		objButtion.move(offset * dt * 1.f, 0);

		float X = menuBar.getPosition().x;

	}

	if (X < 970.f)
	{
		isMenuOpen = false;
	}
	else if(X > 1270.f)
	{
		isMenuClose = false;
	}


	if (isTileset)
	{

		int i = 0;
		int j = 0;
	
		for (auto it : objSetButton)
		{
			if (it->GetActive())
			{
				it->SetActive(false);
			}
		}

		for (auto it : tilesButtion[tileCurrpage])
		{
			it->SetActive(true);
		
			it->SetPosition(Vector2f(1100 + (i * 32) + i, 100 + (j * 32)+j));
			
			j++;

			if (j > 15)
			{
				j = 0;
				i++;
			}

		}

	}

	if (isObjset)
	{

		for (auto it : tilesButtion[tileCurrpage])
		{
			if (it->GetActive())
			{
				it->SetActive(false);
			}
		}


		for (int i = 0; i < 20; i++)
		{
			int offset = 75;
			int idx = i + (currentPage * 20);


			objSetButton[idx]->SetPosition(Vector2i(1100 + (i / 10) * offset * 1.75, 100 + (i % 10) * offset));
			objSetButton[idx]->SetActive(true);

		}
	}


	if (InputMgr::GetKeyDown(Keyboard::Num4))
	{

		if (isObjset)
		{
			for (auto it : objSetButton)
			{

				it->SetActive(false);

			}

			currentPage--;
			if (currentPage < 0)
			{
				currentPage = 0;
			}
			cout << currentPage << endl;
		}

		if (isTileset)
		{
			for (auto it : tilesButtion[tileCurrpage])
			{
				it->SetActive(false);
			}
			tileCurrpage--;
			if (tileCurrpage < 0)
			{
				tileCurrpage = 0;
			}

		}
		
	}

	if (InputMgr::GetKeyDown(Keyboard::Num6))
	{

		if (isObjset)
		{
			for (auto it : objSetButton)
			{

				it->SetActive(false);

			}
			currentPage++;
			if (currentPage > 4)
			{
				currentPage = 4;
			}
			cout << currentPage << endl;
		}

		if (isTileset)
		{
			for (auto it : tilesButtion[tileCurrpage])
			{

				it->SetActive(false);

			}
			tileCurrpage++;
			if (tileCurrpage > 6)
			{
				tileCurrpage = 6;
			}
		}
		
	}
}

void GUI::DrawUI(RenderWindow& window)
{
	window.draw(menuBar);
	window.draw(menuInterface);
	window.draw(tileButton);
	window.draw(objButtion);


	if (isObjset)
	{
		for (auto it : objSetButton)
		{

			if (it->GetActive())
			{
				it->Draw(window);
			}	
		}
	}

	if (isTileset)
	{
		for (auto it : tilesButtion[tileCurrpage])
		{
			if (it->GetActive())
			{
				it->Draw(window);
			}

		}
	}

	if (isSelectObj)
	{
		setobj->Draw(window);
	}

	if (isSelectTile)
	{
		setTile->Draw(window);
	}
}





