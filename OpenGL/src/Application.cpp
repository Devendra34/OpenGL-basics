#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath) {

    std::fstream stream(filePath);
    enum class ShaderType {
        NONE     = -1,
        VERTESX  = 0,
        FRAGMENT = 1
    };
    std::string line;
    auto shaderType = ShaderType::NONE;
    std::stringstream ss[2];
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTESX;
            }
            else if (line.find("fragment") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)shaderType] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) alloca(length * sizeof (char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        auto typeStr = type == GL_VERTEX_SHADER ? "Vertex " : "Fragment";
        std::cout << "Failed to compile " << typeStr << "Shader\n";
        std::cout << message << std::endl;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << "\n";
    }
    else {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }
    {
        float positions[] = {
            -0.5f, -0.5f, 0.2f, 0.3f, 0.8f, 
             0.5f, -0.5f, 0.2f, 0.3f, 0.8f, 
             0.5f,  0.5f, 0.95f, 0.82f, 1.0f,
            -0.5f,  0.5f, 0.95f, 0.82f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        //VertexArray va;
        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //VertexBuffer vb(positions, sizeof(positions));
        //VertexBufferLayout layout;
        //layout.Push<float>(2);
        //va.AddBuffer(vb, layout);
        
        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int ibo;
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        //IndexBuffer ib(indices, 6);

        auto shaderProgramSource = ParseShader("res/shaders/Basic.shader");
        unsigned int shader = CreateShader(shaderProgramSource.vertexSource, shaderProgramSource.fragmentSource);
        GLCall(glUseProgram(shader));

        //GLCall(int location = glGetUniformLocation(shader, "u_Color"));
        //ASSERT(location != -1);
        //GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
        // 0.95f, 0.82f, 1.0f, 1.0f

        //va.Unbind();
        //GLCall(glUseProgram(0));
        //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float redChannel = 0.0f;
        float interval = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            //GLCall(glUseProgram(shader));
            //GLCall(glUniform4f(location, redChannel, 0.3f, 0.8f, 1.0f));

            //va.Bind();
            //ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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

        GLCall(glDeleteProgram(shader));
    }
    glfwTerminate();
    return 0;
}