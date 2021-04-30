#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

using namespace std;

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    cout << glGetString(GL_VERSION) << endl;
    cout << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << endl;
    float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f, 0.5f,
            -0.5f, 0.5f,
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    IndexBuffer ib(indices, 6);

    Shader shader("../res/shaders/basic.shader");
    shader.Bind();
    shader.setUniform4f("u_Color", 0.2f, 0.4f, 0.6f, 1.0f);
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    float r = 0.0f;
    float increment = 0.05f;
    Renderer renderer;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        shader.Bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.Draw(vb, ib, shader);

        if (r > 1.0f || r < 0.0f)
            increment *= -1;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}