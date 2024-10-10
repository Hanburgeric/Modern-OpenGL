#include <GLFW/glfw3.h>
#include <iostream>

#include "InputManager.h"

InputManager::InputManager()
{
	m_cursorX = { 0.0f, 0.0f, 0.0f };
	m_cursorY = { 0.0f, 0.0f, 0.0f };

	m_scrollOffsetX = 0.0f;
	m_scrollOffsetY = 0.0f;
}

void InputManager::update()
{
	m_cursorX.m_prevPos = m_cursorX.m_currPos;
	m_cursorX.m_deltaPos = 0.0f;
	m_cursorY.m_prevPos = m_cursorY.m_currPos;
	m_cursorY.m_deltaPos = 0.0f;

	m_wasKeyPressed.clear();
	m_wasKeyReleased.clear();

	m_wasMousePressed.clear();
	m_wasMouseReleased.clear();

	m_scrollOffsetX = 0.0f;
	m_scrollOffsetY = 0.0f;
}

void InputManager::cursorPosEvent(float xpos, float ypos)
{
	m_cursorX.m_prevPos += m_cursorX.m_deltaPos;
	m_cursorY.m_prevPos += m_cursorY.m_deltaPos;

	m_cursorX.m_currPos = xpos;
	m_cursorY.m_currPos = ypos;

	m_cursorX.m_deltaPos = m_cursorX.m_currPos - m_cursorX.m_prevPos;
	m_cursorY.m_deltaPos = m_cursorY.m_currPos - m_cursorY.m_prevPos;
}

void InputManager::keyEvent(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		m_wasKeyPressed[key] = true;
		m_isKeyHeld[key] = true;
	}

	else if (action == GLFW_RELEASE)
	{
		m_isKeyHeld[key] = false;
		m_wasKeyReleased[key] = true;
	}
}

void InputManager::mouseButtonEvent(int button, int action)
{
	if (action == GLFW_PRESS)
	{
		m_wasMousePressed[button] = true;
		m_isMouseHeld[button] = true;
	}

	else if (action == GLFW_RELEASE)
	{
		m_isMouseHeld[button] = false;
		m_wasMouseReleased[button] = true;
	}
}

void InputManager::scrollEvent(float xoffset, float yoffset)
{
	m_scrollOffsetX = xoffset;
	m_scrollOffsetY = yoffset;
}

CursorPos InputManager::getCursorX() const
{
	return m_cursorX;
}

CursorPos InputManager::getCursorY() const
{
	return m_cursorY;
}

bool InputManager::wasKeyPressed(int key) const
{
	bool result = false;
	std::unordered_map<int, bool>::const_iterator iter = m_wasKeyPressed.find(key);
	if (iter != m_wasKeyPressed.end())
	{
		result = iter->second;
	}
	return result;
}

bool InputManager::isKeyHeld(int key) const
{
	bool result = false;
	std::unordered_map<int, bool>::const_iterator iter = m_isKeyHeld.find(key);
	if (iter != m_isKeyHeld.end())
	{
		result = iter->second;
	}
	return result;
}

bool InputManager::wasKeyReleased(int key) const
{
	bool result = false;
	std::unordered_map<int, bool>::const_iterator iter = m_wasKeyReleased.find(key);
	if (iter != m_wasKeyReleased.end())
	{
		result = iter->second;
	}
	return result;
}

bool InputManager::wasMousePressed(int button) const
{
	bool result = false;
	std::unordered_map<int, bool>::const_iterator iter = m_wasMousePressed.find(button);
	if (iter != m_wasMousePressed.end())
	{
		result = iter->second;
	}
	return result;
}

bool InputManager::isMouseHeld(int button) const
{
	bool result = false;
	std::unordered_map<int, bool>::const_iterator iter = m_isMouseHeld.find(button);
	if (iter != m_isMouseHeld.end())
	{
		result = iter->second;
	}
	return result;
}

bool InputManager::wasMouseReleased(int button) const
{
	bool result = false;
	std::unordered_map<int, bool>::const_iterator iter = m_wasMouseReleased.find(button);
	if (iter != m_wasMouseReleased.end())
	{
		result = iter->second;
	}
	return result;
}

float InputManager::getScrollOffsetX() const
{
	return m_scrollOffsetX;
}

float InputManager::getScrollOffsetY() const
{
	return m_scrollOffsetY;
}
