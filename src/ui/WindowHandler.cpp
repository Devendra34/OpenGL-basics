//
// Created by Devendra Varma on 08/09/22.
//

#include "WindowHandler.h"

GLFWwindow* WindowHandler::window = nullptr;

bool WindowHandler::InitMainWindow(const char *title) {
    if(!WindowHandler::window) {

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, title, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return false;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
    }
    return true;
}

void WindowHandler::ResizeMainWindow(const int width, const int height) {
    glfwSetWindowSize(window, width, height);
}

void WindowHandler::ReleaseMainWindow() {
    if(window != nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

GLFWwindow* WindowHandler::GetMainWindow() {
    return window;
}

void WindowHandler::TerminateGlfw() {
    glfwTerminate();
}