#include "InputManager.h"
#include <iostream>

GLFWwindow* InputManager::m_window;

// Values grabbed from GLFW api

int* InputManager::m_lastKeysFrame;
int* InputManager::m_lastMouseFrame;

bool InputManager::GetKeyDown(int GLFWKeyCode)
{
	return GetKey(GLFWKeyCode) && !m_lastKeysFrame[GLFWKeyCode - KeyCodesOffset];
}

bool InputManager::GetKeyUp(int GLFWKeyCode)
{
	return !GetKey(GLFWKeyCode) && m_lastKeysFrame[GLFWKeyCode - KeyCodesOffset];
}

bool InputManager::GetKey(int GLFWKeyCode)
{
	return static_cast<bool>(glfwGetKey(m_window, GLFWKeyCode));
}

bool InputManager::GetMouseDown(int GLFWKeyCode)
{
	return GetMouse(GLFWKeyCode) && !m_lastMouseFrame[GLFWKeyCode - MouseCodesOffset];
}

bool InputManager::GetMouseUp(int GLFWKeyCode)
{
	return !GetMouse(GLFWKeyCode) && m_lastMouseFrame[GLFWKeyCode - MouseCodesOffset];
}

bool InputManager::GetMouse(int GLFWKeyCode)
{
	return static_cast<bool>(glfwGetMouseButton(m_window, GLFWKeyCode));

}

void InputManager::Update()
{

	for (int i = 0; i < NumKeyCodes; i++)
	{
		int newCode = i + KeyCodesOffset;

		m_lastKeysFrame[i] = glfwGetKey(m_window, newCode);
	}

	for (int i = 0; i < NumMouseButtons; i++)
	{
		int newCode = i + MouseCodesOffset;

		m_lastMouseFrame[i] = glfwGetMouseButton(m_window, newCode);
	}
}

void InputManager::Init(GLFWwindow *window) {
	m_window = window;
	m_lastKeysFrame = new int[NumKeyCodes];
	m_lastMouseFrame = new int[NumMouseButtons];
}
