#include "GUI.h"

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


void GUI::ShowGUIMenu(float dt)
{
	float X = menuBar.getPosition().x;

	if (isMenuOpen)
	{
	
		int offset = 200;
		menuBar.move(offset * dt * -1.f, 0);

		menuInterface.move(offset * dt * -1.f, 0);

		tileButton.move(offset * dt * -1.f, 0);

		objButtion.move(offset * dt * -1.f, 0);

	}

	if (isMenuClose)
	{
		int offset = 200;

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
}

void GUI::DrawUI(RenderWindow& window)
{
	window.draw(menuBar);
	window.draw(menuInterface);
	window.draw(tileButton);
	window.draw(objButtion);
}
