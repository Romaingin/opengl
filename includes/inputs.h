#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

class KeyboardHandler
{
public:
	void handleKeyboardEvent(int keyIndex, bool isPressed);
	bool isPressed(int keyIndex);

private:
	map<int, bool> keyState;
};

class MouseHandler
{
public:
	void updateCoordinates(int x, int y, int w, int h);
	void handleMouseEvent(int keyIndex, bool isPressed);
	bool isPressed(int keyIndex);
	int mouseX();
	int mouseY();
	int deltaMouseX();
	int deltaMouseY();

private:
	map<int, bool> mouseState;
	int m_mouseX;
	int m_mouseY;

	int m_deltaX;
	int m_deltaY;
};

extern KeyboardHandler g_keyHandler;
extern MouseHandler g_mouseHandler;

#endif
