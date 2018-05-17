#ifndef MESH_H
#define MESH_H
#include <glm\glm.hpp>
#include <GL\glew.h>
#include "obj_loader.h"

class Vertex
{
private:
	glm::vec3 vertices;
	//glm::vec3 normals;
	glm::vec2 texCoord;

public:


	Vertex
	(
		const glm::vec3 &vertices,
		//const glm::vec3 &normals ,
		const glm::vec2 &texCoord
		)
	{
		this->vertices = vertices;
		//this->normals =  normals;
		this->texCoord = texCoord;
	}

	glm::vec3 getVertices()
	{
		return this->vertices;
	}

	glm::vec2 getTexCoord()
	{
		return this->texCoord;
	}
};

class Mesh
{
private:
	static const unsigned int NUM_BUFFERS = 4;
	enum { POSITION_VB, TEXTCOORD_VB, INDEX_VB};

	GLuint m_vertexArrayObject;
	unsigned int m_drawCount;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	

	Mesh(const Mesh& other);

	IndexedModel model;

public:
	Mesh();
	
	Mesh(Vertex * vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string &fileName, bool init);
	Mesh & operator=(const Mesh& rhs);
	virtual  ~Mesh();
	void loadModel(const std::string &fileName);
	void InitMesh(const IndexedModel &model);
	void InitMesh();
	void InitMesh(const std::string &fileName, bool init);
	void Draw();


};
#endif // !MESH_H

