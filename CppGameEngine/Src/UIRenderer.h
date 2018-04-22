//
// Created by matha on 16/03/2018.
//

#pragma once

#include <GLFW/glfw3.h>
#include "vendor/imgui/imgui.h"
#include "Shader.h"

class UIRenderer {
private:
    GLuint m_VboHandle;
    GLuint m_ElementsHandle;
    GLuint m_FontTexture;

    Shader* m_FontShader;

    double m_Time;
public:
    void Init(GLFWwindow* window);
    void RenderDrawData(ImDrawData* drawData);


    void NewFrame(GLFWwindow* window);

private:
    void CreateFontsTexture();
    void InstallCallbacks(GLFWwindow *window);
    static const char *GetClipboardText(void *user_data);
    static  void SetClipboardText(void *user_data, const char *text);
    static void MouseButtonCallback(GLFWwindow *, int button, int action, int);
    static  void ScrollCallback(GLFWwindow *, double xoffset, double yoffset);
    static void KeyCallback(GLFWwindow *, int key, int, int action, int mods);
    static void CharCallback(GLFWwindow *, unsigned int c);
};


