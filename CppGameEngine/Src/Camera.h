#pragma once
#include "Common.h"
#include <GLFW/glfw3.h>

class Camera
{
private:
public:
	Camera();
	~Camera();

	Vector3f Rotation;
	Vector3f Position;

	Matrix4f GetViewMatrix();
	void Input(GLFWwindow* window);
};

