#include "GUI.h"

GUI::GUI()
{
	MenuBar.setTexture(TextureHolder::GetTexture("graphics/UIopenMenuBar.png"));
	font.loadFromFile("graphics/RobotoFlex-Regular.ttf");
	UiText.setFont(font);
}

Sprite GUI::GetMenuBar()
{
	return MenuBar;
}
