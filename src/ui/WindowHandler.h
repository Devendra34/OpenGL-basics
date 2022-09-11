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
    static int mWidth;
    static int mHeight;
public:
    static GLFWwindow* GetMainWindow();
    static bool InitMainWindow(const char *name);
    static void ResizeMainWindow(const int &width, const int &height);
    static void ReleaseMainWindow();
    static void TerminateGlfw();

    static int getWidth();

    static int getHeight();
};

#endif //OPENGL_BASICS_WINDOW_HANDLER_H
