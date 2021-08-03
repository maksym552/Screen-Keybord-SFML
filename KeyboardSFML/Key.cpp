#include "stdafx.h"
#include "Key.h"

Key::Key()
{
}

Key::Key(FloatRect area, Keyboard::Key code)
{
	this->rect.setPosition(area.left, area.top);
	this->rect.setSize(Vector2f(area.width, area.height));
	this->code = code;
}

void Key::update()
{
	if (Keyboard::isKeyPressed(code))
		rect.setFillColor(Color(0, 255, 0, 128));
	else
		rect.setFillColor(Color(0, 0, 0, 0));
}
