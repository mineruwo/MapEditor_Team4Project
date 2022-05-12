#include "TextBox.h"

TextBox::TextBox(std::string getname, std::string getstr)
{
	box.setFillColor((Color::White));
	box.setSize(Vector2f(100, 50));
	font.loadFromFile("graphics/RobotoFlex-Regular.ttf");

	name.setFont(font);
	name.setCharacterSize(10);
	name.setString(getname);
	name.setOrigin(box.getOrigin());
	name.setFillColor((Color::Black));

	this->getstr = getstr;

}

void TextBox::Draw(RenderWindow& window)
{
	window.draw(box);
	window.draw(name);
}

RectangleShape TextBox::Getbox()
{
	return  box;
}

Text TextBox::Getname()
{
	return name;
}

std::string TextBox::GetSetstr()
{
	return  getstr;
}

void TextBox::SetActive(bool act)
{
	isActive = act;
}

bool TextBox::GetActive()
{
	return isActive;
}

void TextBox::SetPosition(Vector2i pos)
{
	box.setPosition((Vector2f)pos);
	name.setPosition((Vector2f)pos);
}
