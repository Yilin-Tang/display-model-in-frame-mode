#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

Mesh::Mesh(vector<glVertex> vertices, vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
	setupMesh();
}

void Mesh::setupMesh()
{
	// Generate
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glVertex Attibution
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glVertex), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glVertex), (void*)offsetof(glVertex, Normal));

	// Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); //将索引复制到缓冲里

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh(string path)
{
	Assimp::Importer import;
	// aiProcess_JoinIdenticalVertices makes vertices be pointed by more than one index, or the vertices will be stored repeatedly.
	const aiScene* scene = import.ReadFile(path, aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return;
	}
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		for (unsigned int j = 0; j < mesh->mNumVertices; j++)
		{
			glVertex vertex;
			glm::vec3 v;
			v.x = mesh->mVertices[j].x;
			v.y = mesh->mVertices[j].y;
			v.z = mesh->mVertices[j].z;
			vertex.Position = v;
			if (mesh->mNormals != NULL)
			{
				v.x = mesh->mNormals[j].x;
				v.y = mesh->mNormals[j].y;
				v.z = mesh->mNormals[j].z;
				vertex.Normal = v;
			}
			else vertex.Normal=glm::vec3{ 0.0f,0.0f,0.0f };
			vertices.push_back(vertex);
		}

		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace* face = &mesh->mFaces[j];
			for (unsigned int k = 0; k < face->mNumIndices; k++)
				indices.push_back(face->mIndices[k]);
		}
	}
	setupMesh();
}

void Mesh::draw(GLFWwindow* window, Shader& shader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // use frame mode to draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // background color
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();  // activate shader program
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}