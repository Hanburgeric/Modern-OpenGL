#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

struct CursorPos
{
	float m_prevPos;
	float m_currPos;
	float m_deltaPos;
};

class InputManager
{
public:
	InputManager();

	void update();

	void cursorPosEvent(float xpos, float ypos);
	void keyEvent(int key, int action);
	void mouseButtonEvent(int button, int action);
	void scrollEvent(float xoffset, float yoffset);

	CursorPos getCursorX() const;
	CursorPos getCursorY() const;

	bool wasKeyPressed(int key) const;
	bool isKeyHeld(int key) const;
	bool wasKeyReleased(int key) const;

	bool wasMousePressed(int button) const;
	bool isMouseHeld(int button) const;
	bool wasMouseReleased(int button) const;

	float getScrollOffsetX() const;
	float getScrollOffsetY() const;

private:
	CursorPos m_cursorX;
	CursorPos m_cursorY;

	std::unordered_map<int, bool> m_wasKeyPressed;
	std::unordered_map<int, bool> m_isKeyHeld;
	std::unordered_map<int, bool> m_wasKeyReleased;

	std::unordered_map<int, bool> m_wasMousePressed;
	std::unordered_map<int, bool> m_isMouseHeld;
	std::unordered_map<int, bool> m_wasMouseReleased;

	float m_scrollOffsetX;
	float m_scrollOffsetY;
};

#endif
