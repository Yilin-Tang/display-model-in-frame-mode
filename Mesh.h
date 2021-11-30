#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Shader.h"
using namespace std;

struct glVertex
{
	glm::vec3 Position;
	glm::vec3 Normal{ 0,0,0 };
};

class Mesh
{
public:
	vector<glVertex> vertices;
	vector<unsigned int> indices;
	Mesh(vector<glVertex> vertices, vector<unsigned int> indices);
	Mesh(string path);
	void draw(GLFWwindow* window, Shader& shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif
