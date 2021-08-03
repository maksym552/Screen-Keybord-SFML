#pragma once
class Key
{
	Keyboard::Key code;
public:
	RectangleShape rect;

	Key();
	Key(FloatRect area, Keyboard::Key code);
	void update();
};

