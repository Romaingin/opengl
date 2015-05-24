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
	void handleKeyboardEvent(int keyIndex, bool isPressed)
	{
		keyState[keyIndex] = isPressed;
	}

	bool isPressed(int keyIndex) {
		return (keyState[keyIndex]);
	}
private:
	map<int, bool> keyState;
};

extern KeyboardHandler g_keyHandler;

#endif