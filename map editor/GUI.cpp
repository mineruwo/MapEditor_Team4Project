#include "GUI.h"

GUI::GUI() :defaultTileKey(0)
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

	
	for(int idx = 0; idx < setTileKey.size();idx++)
	{
		tileMapFilePaths.insert(std::pair<tilesets,std::string>(tilesets(setTileKey[idx]), setTileValue[idx]));

	}

	rapidcsv::Document objsData("data_tables/obj/objs.csv");
	std::vector<std::string> setObjsKey = objsData.GetColumn<std::string>("Key");
	std::vector<std::string> setObjsValue = objsData.GetColumn<std::string>("ObjFilePath");


	for (int idx = 0; idx < setObjsKey.size(); idx++)
	{
		objFilePaths.insert(std::pair<std::string, std::string>(setObjsKey[idx], setObjsValue[idx]));

	}

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


	}

	if (objButtion.getGlobalBounds().contains(mouse.GetmousePosWindow().x, mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		isObjset = true;
		isTileset = false;
	}

	if (menuBar.getGlobalBounds().contains(mouse.GetmousePosWindow().x, mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left) && !isMenuOpen)
	{
		isMenuOpen = true;
	}
	if (menuBar.getGlobalBounds().contains(mouse.GetmousePosWindow().x, mouse.GetmousePosWindow().y) && InputMgr::GetMouseButtonDown(Mouse::Left) && isMenuOpen)
	{
		isMenuClose = true;
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
		
		loadTileSetButton();
	}

	if (isObjset)
	{
		for (auto it : tileSetButton)
		{
			delete it;
		}
		tileSetButton.clear();

	}
}

void GUI::DrawUI(RenderWindow& window)
{
	window.draw(menuBar);
	window.draw(menuInterface);
	window.draw(tileButton);
	window.draw(objButtion);
}

void GUI::loadTileSetButton()
{
	for (auto it : tileSetButton)
	{
		delete it;
	}

	tileSetButton.clear();


	int idx = 0;
	std::string path;

	path += TilePath;
	path += tileMapFilePaths.at(tilesets(defaultTileKey));

	
}
