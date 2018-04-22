#pragma once
#include <vector>

#include "GLFW\glfw3.h"

class InputManager
{
public:
	static bool GetKeyDown(int GLFWKeyCode);
	static bool GetKeyUp(int GLFWKeyCode);
	static bool GetKey(int GLFWKeyCode);

	static bool GetMouseDown(int GLFWKeyCode);
	static bool GetMouseUp(int GLFWKeyCode);
	static bool GetMouse(int GLFWKeyCode);

	static void Update();


	static void Init(GLFWwindow *pWwindow);

private:
	static GLFWwindow* m_window;

	// Values grabbed from GLFW api
	static const int KeyCodesOffset = 32;
	static const int MouseCodesOffset = 0;

	static const int NumKeyCodes = 130;
	static const int NumMouseButtons = 8;

	static int* m_lastKeysFrame;
	static int* m_lastMouseFrame;

};
