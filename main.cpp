#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "Mesh_assimp.cpp"
#include "glfw_utils.cpp"
using namespace std;

const unsigned int SCR_width = 1000;
const unsigned int SCR_height = 1000;

int main()
{
    glfwInitial();
    GLFWwindow* import = CreateWindow(SCR_width, SCR_height, "Display Model in Frame Mode");

    Shader shader("vertex_shader_for_bunny.txt", "fragment_shader.txt");
    Mesh mesh("bunny.obj");
    mesh.draw(import, shader);

    glfwTerminate();
    return 0;
}
