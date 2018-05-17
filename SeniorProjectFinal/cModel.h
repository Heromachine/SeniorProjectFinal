#ifndef  CLASS_MODEL_H
#define CLASS_MODEL_H
#include "cTexture.h"
#include"cObjectLoader.h"

class Model3D
{
private: 

	string name; 
	ObjectLoader Loader;

	std::vector < glm::vec3 > vertices;
	std::vector < glm::vec2 > uvs;
	std::vector < glm::vec3 > normals;

	std::vector< unsigned int > vertexIndices;
	std::vector< unsigned int > uvIndices;
	std::vector< unsigned int > normalIndices;



public: 

	Model3D() {}
	Model3D(const char * meshPath)
	{
		Loader.loadOBJ02(meshPath, vertices, uvs, normals, vertexIndices, uvIndices, normalIndices);
	}

	void DrawMesh()
	{
		for (int i = 0; i < vertexIndices.size(); i++)
		{

			glTexCoord2f(uvs[uvIndices[i] - 1].x, uvs[uvIndices[i] - 1].y);
			glVertex3f(vertices[vertexIndices[i] - 1].x, vertices[vertexIndices[i] - 1].y, vertices[vertexIndices[i] - 1].z);
			glNormal3f(normals[normalIndices[i] - 1].x, normals[normalIndices[i] - 1].y, normals[normalIndices[i] - 1].z);

		}
	}

	//void DrawMesh(float scale, float posX, float posY, float posZ)
	//{
	//
	//	glPushMatrix();
	//	glEnable(GL_CULL_FACE);
	//	glCullFace(GL_FRONT);
	//	glFrontFace(GL_CW);
	//	glEnable(GL_TEXTURE_2D);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	//	glTranslatef(posX, posY, posZ);
	//	glRotated(45, 0, 1, 0);
	//	glScalef(scale, scale, scale);
	//	glColor3f(1, 1, 1);
	//	Skin.Bind();
	//	
	//	glBegin(GL_TRIANGLES);
	//	for (int i = 0; i < vertexIndices.size(); i++) 
	//	{

	//		glTexCoord2f(uvs[uvIndices[i] - 1].x, uvs[uvIndices[i] - 1].y);
	//		glVertex3f(vertices[vertexIndices[i] - 1].x, vertices[vertexIndices[i] - 1].y, vertices[vertexIndices[i] - 1].z);
	//		glNormal3f(normals[normalIndices[i] - 1].x, normals[normalIndices[i] - 1].y, normals[normalIndices[i] - 1].z);

	//	}
	//	glEnd();
	//	glDisable(GL_CULL_FACE);
	//	glDisable(GL_TEXTURE_2D);
	//	glPopMatrix();

	//}


};



#endif // ! CLASS_MODEL_H

