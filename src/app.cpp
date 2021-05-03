#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

using namespace std;
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    /* Initialize the library */
    if (!glfwInit())
        return 1;

    GLFWwindow* window;


    /* Create a windowed mode window and its OpenGL context */
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    cout << glGetString(GL_VERSION) << endl;
    cout << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << endl;
//    float positions[] = {
//            -0.5f, -0.5f,
//             0.5f, -0.5f,
//             0.5f, 0.5f,
//            -0.5f, 0.5f,
//    };

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    float positions[] = {
            100.0f, 100.0f, 0.0f, 0.0f,
             200.0f, 100.0f, 1.0f, 0.0f,
             200.0f, 200.0f, 1.0f, 1.0f,
            100.0f, 200.0f, 0.0f, 1.0f,
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0,0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));

    glm::mat4 mvp = proj * view * model;

    Shader shader("../res/shaders/basic.shader");
    shader.Bind();

    shader.setUniform4f("u_Color", 0.2f, 0.4f, 0.6f, 1.0f);
    shader.setUniformMat4f("u_MVP", mvp);

    Texture texture("../res/textures/trek.png");
    texture.Bind();
    shader.setUniform1i("u_Texture", 0);

    unsigned int positionLocation = shader.getAttributeLocation("v_pos");
    unsigned int texLocation = shader.getAttributeLocation("v_texCoord");
    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
    glEnableVertexAttribArray(texLocation);
    glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)8);



    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    float r = 0.0f;
    float increment = 0.05f;
    Renderer renderer;

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        renderer.Clear();


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        shader.Bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.Draw(vb, ib, shader);

        if (r > 1.0f || r < 0.0f) {
            increment *= -1;
        }

        r += increment;


        ImGui::ShowDemoWindow(&show_demo_window);


        // Rendering
        ImGui::Render();

        // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
        // you may need to backup/reset/restore other state, e.g. for current shader using the commented lines below.
        GLint last_program;
        glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        glUseProgram(0);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        //glUseProgram(last_program);

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}