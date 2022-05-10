#include "GUI.h"

GUI::GUI()
{
	MenuBar.setTexture(TextureHolder::GetTexture("graphics/UIopenMenuBar.png"));
	MenuBar.setPosition(1366, 768 * 0.5);
	font.loadFromFile("graphics/RobotoFlex-Regular.ttf");
	UiText.setFont(font);
}

Sprite GUI::GetMenuBar()
{
	return MenuBar;
}
