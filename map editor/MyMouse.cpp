#include "MyMouse.h"

void MyMouse::initMouse()
{
	mouseBox.setSize(Vector2f(16, 16));
	mouseBox.setFillColor(Color(100, 100, 150, 130));
	font.loadFromFile("graphics/RobotoFlex-Regular.ttf");
	posText.setFont(font);
	posText.setCharacterSize(7);
	posText.setFillColor(Color(0, 255, 100));

}

void MyMouse::updateMouse(RenderWindow& window, IntRect area)
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(mousePosWindow);

	if (mousePosView.x >= 0.f && mousePosView.y >= 0.f && mousePosView.x <= area.width * 16 && mousePosView.y <= area.height * 16)
	{
		mousePosGrid.x = mousePosView.x / 16;
		mousePosGrid.y = mousePosView.y / 16;
	}
	

	mouseBox.setPosition(mousePosView);

	std::string str;
	char temp[10];

	str += "Screen [ ";
	str += itoa(mousePosScreen.x,temp,10);
	str += " , ";
	str += itoa(mousePosScreen.y, temp, 10);
	str += " ]";
	str += "\n";

	str += "Window [ ";
	str += itoa(mousePosWindow.x, temp, 10);
	str += " , ";
	str += itoa(mousePosWindow.y, temp, 10);
	str += " ]";
	str += "\n";

	str += "View [ ";
	str += itoa(mousePosView.x, temp, 10);
	str += " , ";
	str += itoa(mousePosView.y, temp, 10);
	str += " ]";
	str += "\n";


	str += "Gird [ ";
	str += itoa(mousePosGrid.x, temp, 10);
	str += " , ";
	str += itoa(mousePosGrid.y, temp, 10);
	str += " ]";
	str += "\n";

	posText.setString(str);
	
	posText.setPosition(mousePosView.x + 16, mousePosView.y + 3);
	
}

void MyMouse::drawMouse(RenderWindow& window)
{
	window.draw(mouseBox);
	window.draw(posText);
}

RectangleShape MyMouse::GetMouseBox()
{
	return mouseBox;
}

Vector2i MyMouse::GetmousePosScreen()
{
	return mousePosScreen;
}

Vector2i MyMouse::GetmousePosWindow()
{
	return mousePosWindow;
}

Vector2f MyMouse::GetmousePosView()
{
	return mousePosView;
}

Vector2i MyMouse::GetmousePosGrid()
{
	return mousePosGrid;
}
