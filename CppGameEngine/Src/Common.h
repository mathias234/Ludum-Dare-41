#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#define ASSERT(x) Assert(x)
#define GLCall(x) GLClearError();\
	x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

typedef glm::mat4 Matrix4f;
typedef glm::vec4 Vector4f;
typedef glm::vec3 Vector3f;
typedef glm::vec2 Vector2f;
typedef glm::quat Quaternion;

inline void Assert(bool assert) {
	//if(!(assert)) __debugbreak();
}

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{

		const char* errorCodeName;
		switch (error)
		{
		case GL_INVALID_ENUM:
			errorCodeName = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorCodeName = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorCodeName = "GL_INVALID_OPERATION";
			break;
		case GL_STACK_OVERFLOW:
			errorCodeName = "GL_STACK_OVERFLOW";
			break;
		case GL_STACK_UNDERFLOW:
			errorCodeName = "GL_STACK_UNDERFLOW";
			break;
		case GL_OUT_OF_MEMORY:
			errorCodeName = "GL_OUT_OF_MEMORY";
			break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errorCodeName = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
		default:
            errorCodeName = std::to_string(error).c_str();
            break;
		}


		std::cout << "[OpenGL Error]: (" << errorCodeName << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}