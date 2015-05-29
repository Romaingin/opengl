#include "../includes/inputs.h"

void KeyboardHandler::handleKeyboardEvent(int keyIndex, bool isPressed) {
	keyState[keyIndex] = isPressed;
}

bool KeyboardHandler::isPressed(int keyIndex) {
	return (keyState[keyIndex]);
}

void MouseHandler::updateCoordinates(int x, int y, int w, int h) {
	m_deltaX = x - w;
	m_deltaY = y - h;
	m_mouseX = x;
	m_mouseY = y;
}

void MouseHandler::handleMouseEvent(int keyIndex, bool isPressed) {
	mouseState[keyIndex] = isPressed;
}

bool MouseHandler::isPressed(int keyIndex) {
	return (mouseState[keyIndex]);
}

int MouseHandler::mouseX() {
	return (m_mouseX);
}

int MouseHandler::mouseY() {
	return (m_mouseY);
}

int MouseHandler::deltaMouseX() {
	return (m_deltaX);
}

int MouseHandler::deltaMouseY() {
	return (m_deltaY);
}
