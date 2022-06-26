#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
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

        std::string shaderSourceFilePath = "../assets/shaders/Basic.shader";
        Shader shader(shaderSourceFilePath);
        shader.Bind();
        shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        Texture texture("../assets/textures/opengl-1-logo-png-transparent.png");
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
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            Renderer::Clear();

            shader.Bind();
            shader.setUniform4f("u_Color", redChannel, 0.3f, 0.8f, 1.0f);

            Renderer::Draw(va, ib, shader);
            if (redChannel > 1.0f) {
                interval = -0.05f;
            }
            else if (redChannel < 0.0f) {
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