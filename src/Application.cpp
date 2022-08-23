#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "stb_image/stb_image_write.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include <mach-o/dyld.h>
#include <libgen.h>

void processInput(GLFWwindow *);

void saveImage(char *filepath, GLFWwindow *w);

void knowAppWorkingDirectory();

std::string appDir;

int main() {
    knowAppWorkingDirectory();
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSwapInterval(1);

    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0,
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        std::string shaderSourceFilePath = appDir + "/assets/shaders/Basic.shader";
        Shader shader(shaderSourceFilePath);
        shader.Bind();
        shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        auto texturePath = appDir + "/assets/textures/opengl-1-logo-png-transparent.png";
        Texture texture(texturePath.c_str());
        texture.Bind();
        shader.setUniform1i("u_texture", 0);

        VertexArray::Unbind();
        Shader::Unbind();
        VertexBuffer::Unbind();
        IndexBuffer::Unbind();

//        Renderer renderer;

        float redChannel = 0.0f;
        float interval = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            /* Render here */
            Renderer::Clear();

            shader.Bind();
            shader.setUniform4f("u_Color", redChannel, 0.3f, 0.8f, 1.0f);

            Renderer::Draw(va, ib, shader);
            if (redChannel > 1.0f) {
                interval = -0.05f;
            } else if (redChannel < 0.0f) {
                interval = 0.05f;
            }
            redChannel += interval;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

void saveImage(char *filepath, GLFWwindow *w) {
    int width, height;
    glfwGetFramebufferSize(w, &width, &height);
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * height;
    std::vector<char> buffer(bufferSize);
//    glPixelStorei(GL_PACK_ALIGNMENT, 4);
//    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    stbi_flip_vertically_on_write(true);
    stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);
}

void knowAppWorkingDirectory() {
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {}
    std::string chPath = std::string(path);
    char *executablePathStr = new char[chPath.length() + 1];
    strcpy(executablePathStr, chPath.c_str());
    char *executableDir = dirname(executablePathStr);
    delete[] executablePathStr;

    appDir = std::string(executableDir);
}

bool pressedP = false;

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pressedP) {
        pressedP = true;
        saveImage("demp.png", window);
        pressedP = false;
    }
}