//
// Created by Devendra Varma on 08/09/22.
//

#ifndef OPENGL_BASICS_WINDOW_HANDLER_H
#define OPENGL_BASICS_WINDOW_HANDLER_H

#include <GLFW/glfw3.h>

class WindowHandler
{
private:
    static GLFWwindow *window;
public:
    static GLFWwindow* GetMainWindow();
    static bool InitMainWindow(const char *name);
    static void ResizeMainWindow(const int width, const int height);
    static void ReleaseMainWindow();
    static void TerminateGlfw();
};

#endif //OPENGL_BASICS_WINDOW_HANDLER_H
