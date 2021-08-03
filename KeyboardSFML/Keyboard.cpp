#include "stdafx.h"
#include <Windows.h>
#include "Key.h"

void createKeys(Key* key) {
	// 1st row
	key[0] = Key({1,1,34,34},Keyboard::Tilde);
	key[1] = Key({ 35,1,34,34 }, Keyboard::Num1);
	key[2] = Key({ 69,1,34,34 }, Keyboard::Num2);
	key[3] = Key({ 103,1,34,34 }, Keyboard::Num3);
	key[4] = Key({ 137,1,34,34 }, Keyboard::Num4);
	key[5] = Key({ 171,1,34,34 }, Keyboard::Num5);
	key[6] = Key({ 205,1,34,34 }, Keyboard::Num6);
	key[7] = Key({ 239,1,34,34 }, Keyboard::Num7);
	key[8] = Key({ 273,1,34,34 }, Keyboard::Num8);
	key[9] = Key({ 307,1,34,34 }, Keyboard::Num9);
	key[10] = Key({ 341,1,34,34 }, Keyboard::Num0);
	key[11] = Key({ 375,1,34,34 }, Keyboard::Dash);
	key[12] = Key({ 409,1,34,34 }, Keyboard::Equal);
	key[13] = Key({ 443,1,68,34 }, Keyboard::BackSpace);
	// 2nd row
	key[14] = Key({ 1,35,51,34 }, Keyboard::Tab);
	key[15] = Key({ 53,35,34,34 }, Keyboard::Q);
	key[16] = Key({ 87,35,34,34 }, Keyboard::W);
	key[17] = Key({ 121,35,34,34 }, Keyboard::E);
	key[18] = Key({ 155,35,34,34 }, Keyboard::R);
	key[19] = Key({ 189,35,34,34 }, Keyboard::T);
	key[20] = Key({ 223,35,34,34 }, Keyboard::Y);
	key[21] = Key({ 257,35,34,34 }, Keyboard::U);
	key[22] = Key({ 291,35,34,34 }, Keyboard::I);
	key[23] = Key({ 325,35,34,34 }, Keyboard::O);
	key[24] = Key({ 359,35,34,34 }, Keyboard::P);
	key[25] = Key({ 393,35,34,34 }, Keyboard::LBracket);
	key[26] = Key({ 427,35,34,34 }, Keyboard::RBracket);
	key[27] = Key({ 461,35,50,34 }, Keyboard::BackSlash);
	// 3rd row
	// key[28] = Key({ 0,0,0,60 }, Keyboard::Num1); Caps
	key[29] = Key({ 60,69,34,34 }, Keyboard::A);
	key[30] = Key({ 94,69,34,34 }, Keyboard::S);
	key[31] = Key({ 128,69,34,34 }, Keyboard::D);
	key[32] = Key({ 162,69,34,34 }, Keyboard::F);
	key[33] = Key({ 196,69,34,34 }, Keyboard::G);
	key[34] = Key({ 231,69,34,34 }, Keyboard::H);
	key[35] = Key({ 265,69,34,34 }, Keyboard::J);
	key[36] = Key({ 299,69,34,34 }, Keyboard::K);
	key[37] = Key({ 333,69,34,34 }, Keyboard::L);
	key[38] = Key({ 367,69,34,34 }, Keyboard::SemiColon);
	key[39] = Key({ 401,69,34,34 }, Keyboard::Quote);
	key[40] = Key({ 436,69,75,34 }, Keyboard::Enter);
	// 4th row
	key[41] = Key({ 1,103,77,34 }, Keyboard::LShift);
	key[42] = Key({ 78,103,34,34 }, Keyboard::Z);
	key[43] = Key({ 112,103,34,34 }, Keyboard::X);
	key[44] = Key({ 146,103,34,34 }, Keyboard::C);
	key[45] = Key({ 180,103,34,34 }, Keyboard::V);
	key[46] = Key({ 214,103,34,34 }, Keyboard::B);
	key[47] = Key({ 248,103,34,34 }, Keyboard::N);
	key[48] = Key({ 282,103,34,34 }, Keyboard::M);
	key[49] = Key({ 316,103,34,34 }, Keyboard::Comma);
	key[50] = Key({ 350,103,34,34 }, Keyboard::Period);
	key[51] = Key({ 384,103,34,34 }, Keyboard::Slash);
	key[52] = Key({ 418,103,93,34 }, Keyboard::RShift);
	// 5th row
	key[53] = Key({ 1,137,52,34 }, Keyboard::LControl);
	key[54] = Key({ 53,137,42,34 }, Keyboard::LSystem);
	key[55] = Key({ 95,137,44,34 }, Keyboard::LAlt);
	key[56] = Key({ 139,137,196,34 }, Keyboard::Space);
	key[57] = Key({ 332,137,44,34 }, Keyboard::RAlt);
	key[58] = Key({ 376,137,44,34 }, Keyboard::RSystem);
	key[59] = Key({ 419,137,42,34 }, Keyboard::Menu);
	key[60] = Key({ 461,137,50,34 }, Keyboard::RControl);
}

int main() {

	RenderWindow window({ 513,173 }, "Keyboard", Style::Close | Style::Titlebar);

	HWND console = GetConsoleWindow();
	HWND app = window.getSystemHandle();

	SetWindowPos(app, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowLong(app, GWL_STYLE, 0);
	bool topmost = true;

	ShowWindow(console, SW_HIDE);
	ShowWindow(app, SW_SHOW);

	window.setSize({ 513,173 });

	Texture keyboard_texture;

load_Keyboard:
	if (!keyboard_texture.loadFromFile("Keyboard.png")) {
		ShowWindow(app, SW_HIDE);
		ShowWindow(console, SW_SHOW);
		cout << ("\n","Please put this file into folder and press any key");
		cin.get();
		cin.clear();
		goto load_Keyboard;
	}
	ShowWindow(console, SW_HIDE);
	ShowWindow(app, SW_SHOW);

	RectangleShape keyboard;
	keyboard.setSize(Vector2f(window.getSize().x, window.getSize().y));
	keyboard.setTexture(&keyboard_texture);

	Key key[61];
	createKeys(key);

	Vector2i offset;
	bool grabbed = false;

	while (window.isOpen()) {
		Event ev;
		while (window.pollEvent(ev)) {

			if (ev.type == Event::KeyPressed) {
				if(Keyboard::isKeyPressed(Keyboard::Escape))
					window.close();
				if (Keyboard::isKeyPressed(Keyboard::F5)) {	// Switch TOPMOST
					if (topmost) {
						SetWindowPos(app, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						topmost = false;
					}
					else {
						SetWindowPos(app, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						topmost = true;
					}
				}
			}
			if (ev.type == Event::Closed)
				window.close();

			// mouse grab
			if (ev.type == Event::MouseButtonPressed) {
				if (ev.mouseButton.button == Mouse::Left) {
					offset = window.getPosition() - Mouse::getPosition();
					grabbed = true;
				}
			}
			else if (ev.type == Event::MouseButtonReleased) {
				if (ev.mouseButton.button == Mouse::Left)
					grabbed = false;
			}
			else if (ev.type == Event::MouseMoved)
				if (grabbed)
					window.setPosition(Mouse::getPosition() + offset);
		}

		window.clear();

		// Update
		for (int i = 0; i < 61; i++)
			key[i].update();

		// Draw
		window.draw(keyboard);
		for (int i = 0; i < 61; i++)
			window.draw(key[i].rect);

		window.display();
	}
	return 0;
}