
#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <glm\glm.hpp>
#include <GL\glew.h>

using namespace std; 

static class ObjectLoader
{

public:
	
	ObjectLoader()
	{
	
	}
	ObjectLoader
	(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals

	)
	{
		loadOBJ(
			path,
			out_vertices,
			out_uvs,
			out_normals
		);
	
	
	}
	bool loadOBJ04(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals,
		std::vector< unsigned int > &vertexIndices,
		std::vector< unsigned int > &uvIndices,
		std::vector< unsigned int > &normalIndices
	)
	{
		string sPath(path);
		//std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		FILE * file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			cout << endl << sPath << endl;
			return false;
		}


		while (1)
		{
			char lineHeader[128];
			for (int i = 0; i < sizeof(lineHeader); i++)
			{
				lineHeader[i] = NULL;
			}
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);

			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == 0) {

				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				out_vertices.push_back(vertex);

			}
			else if (strcmp(lineHeader, "vt") == 0) {

				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				out_uvs.push_back(uv);

			}
			else if (strcmp(lineHeader, "vn") == 0) {

				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				out_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{

				unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
				char faces0[128];
				char faces1[128];
				char faces2[128];
				char faces3[128];

				fscanf(file, "%s %s %s %s", &faces0, &faces1, &faces2, &faces3);
				setF2(faces0, vertexIndex[0], uvIndex[0], normalIndex[0]);
				setF2(faces1, vertexIndex[1], uvIndex[1], normalIndex[1]);
				setF2(faces2, vertexIndex[2], uvIndex[2], normalIndex[2]);
				setF2(faces3, vertexIndex[3], uvIndex[3], normalIndex[3]);


				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				//for (unsigned int i = 0; i < vertexIndices.size(); i++)
				//{
				//	unsigned int vertexIndex = vertexIndices[i];

				//	//cout << "\n i"<< i; 
				//	//cout <<"\tVI: " << vertexIndex << endl;
				//	glm::vec3 vertex = temp_vertices[vertexIndex - 1];

				//	out_vertices.push_back(vertex);
				//}

				//for (unsigned int i = 0; i < normalIndices.size(); i++)
				//{
				//	unsigned int normalIndex = normalIndices[i];

				//	//cout << "\n i"<< i; 
				//	//cout <<"\tVI: " << vertexIndex << endl;
				//	glm::vec3 normal = temp_normals[normalIndex - 1];

				//	out_normals.push_back(normal);
				//}

				//for (unsigned int i = 0; i < uvIndices.size(); i++)
				//{
				//	unsigned int uvsIndex = uvIndices[i];

				//	//cout << "\n i"<< i; 
				//	//cout <<"\tVI: " << vertexIndex << endl;
				//	glm::vec2 uvs = temp_uvs[uvsIndex - 1];

				//	out_uvs.push_back(uvs);
				//}
			}
		}





		return 1;
	}
	bool loadOBJ02(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals,
		std::vector< unsigned int > &vertexIndices, 
		std::vector< unsigned int > &uvIndices, 
		std::vector< unsigned int > &normalIndices
	)
	{
		string sPath(path);
		//std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		FILE * file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			cout << endl << sPath << endl;
			return false;
		}


		while (1)
		{
			char lineHeader[128];
			for (int i = 0; i < sizeof(lineHeader); i++)
			{
				lineHeader[i] = NULL;
			}
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);

			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == 0) {

				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				out_vertices.push_back(vertex);

			}
			else if (strcmp(lineHeader, "vt") == 0) {

				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				out_uvs.push_back(uv);

			}
			else if (strcmp(lineHeader, "vn") == 0) {

				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				out_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{

				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				char faces0[128];
				char faces1[128];
				char faces2[128];


				fscanf(file, "%s %s %s", &faces0, &faces1, &faces2);
				setF2(faces0, vertexIndex[0], uvIndex[0], normalIndex[0]);
				setF2(faces1, vertexIndex[1], uvIndex[1], normalIndex[1]);
				setF2(faces2, vertexIndex[2], uvIndex[2], normalIndex[2]);


				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				//for (unsigned int i = 0; i < vertexIndices.size(); i++)
				//{
				//	unsigned int vertexIndex = vertexIndices[i];

				//	//cout << "\n i"<< i; 
				//	//cout <<"\tVI: " << vertexIndex << endl;
				//	glm::vec3 vertex = temp_vertices[vertexIndex - 1];

				//	out_vertices.push_back(vertex);
				//}

				//for (unsigned int i = 0; i < normalIndices.size(); i++)
				//{
				//	unsigned int normalIndex = normalIndices[i];

				//	//cout << "\n i"<< i; 
				//	//cout <<"\tVI: " << vertexIndex << endl;
				//	glm::vec3 normal = temp_normals[normalIndex - 1];

				//	out_normals.push_back(normal);
				//}

				//for (unsigned int i = 0; i < uvIndices.size(); i++)
				//{
				//	unsigned int uvsIndex = uvIndices[i];

				//	//cout << "\n i"<< i; 
				//	//cout <<"\tVI: " << vertexIndex << endl;
				//	glm::vec2 uvs = temp_uvs[uvsIndex - 1];

				//	out_uvs.push_back(uvs);
				//}
			}
		}



	

		return 1;
	}


	bool loadOBJ(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals
	)
	{
		string sPath(path);
		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		FILE * file = fopen(path, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
			cout << endl << sPath<< endl; 
			return false;
		}
		

		while (1) 
		{
			char lineHeader[128];
			for (int i = 0; i < sizeof(lineHeader); i++)
			{
				lineHeader[i] = NULL; 
			}
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);

			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == 0) {

				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);

			}
			else if (strcmp(lineHeader, "vt") == 0) {

				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);

			}
			else if (strcmp(lineHeader, "vn") == 0) {

				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				char faces0[128];
				char faces1[128];
				char faces2[128];

				fscanf(file, "%s %s %s", &faces0, &faces1, &faces2);
				setF2(faces0, vertexIndex[0], uvIndex[0], normalIndex[0]);
				setF2(faces1, vertexIndex[1], uvIndex[1], normalIndex[1]);
				setF2(faces2, vertexIndex[2], uvIndex[2], normalIndex[2]);


				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
				for (unsigned int i = 0; i < vertexIndices.size(); i++) 
				{
					unsigned int vertexIndex = vertexIndices[i];

					//cout << "\n i"<< i; 
					//cout <<"\tVI: " << vertexIndex << endl;
					glm::vec3 vertex = temp_vertices[vertexIndex - 1];
					
					out_vertices.push_back(vertex);						
				}

				for (unsigned int i = 0; i < normalIndices.size(); i++)
				{
					unsigned int normalIndex = normalIndices[i];

					//cout << "\n i"<< i; 
					//cout <<"\tVI: " << vertexIndex << endl;
					glm::vec3 normal = temp_normals[normalIndex - 1];

					out_normals.push_back(normal);
				}

				for (unsigned int i = 0; i < uvIndices.size(); i++)
				{
					unsigned int uvsIndex = uvIndices[i];

					//cout << "\n i"<< i; 
					//cout <<"\tVI: " << vertexIndex << endl;
					glm::vec2 uvs = temp_uvs[uvsIndex - 1];

					out_uvs.push_back(uvs);
				}
		
			}
		}

		return 1; 
	}


	void setF2(char faces0[128], unsigned int &vertexIndex, unsigned int &uvIndex, unsigned int &normalIndex)
	{
		int length = sizeof(faces0) / sizeof(char);

		string sF = string(faces0);
		string number = "";
		int n = 0;
		string::size_type sz;

		for (int i = 0; i < sF.length(); i++)
		{
			if (
				sF.at(i) == '/' ||
				sF.at(i) == '-' ||
				sF.at(i) == '0' ||
				sF.at(i) == '1' ||
				sF.at(i) == '2' ||
				sF.at(i) == '3' ||
				sF.at(i) == '4' ||
				sF.at(i) == '5' ||
				sF.at(i) == '6' ||
				sF.at(i) == '7' ||
				sF.at(i) == '8' ||
				sF.at(i) == '9'
				)
			{
				if (sF.at(i) == '/')
				{
					if (n == 0)
					{
						vertexIndex = stoi(number, &sz);

					}
					else if (n == 1)
					{
						uvIndex = stoi(number, &sz);

					}
					number = "";
					++n;
					continue;
				}
				else
				{
					number += faces0[i];
				}
			}
			else
			{
				continue;
			}
		}

		for (int i = 0; i < number.length(); i++)
		{
			if (!(
				number.at(i) == '0' ||
				number.at(i) == '1' ||
				number.at(i) == '2' ||
				number.at(i) == '3' ||
				number.at(i) == '4' ||
				number.at(i) == '5' ||
				number.at(i) == '6' ||
				number.at(i) == '7' ||
				number.at(i) == '8' ||
				number.at(i) == '9'
				)
				)
			{
				number.erase(number.begin() + i);
			}

		}
		normalIndex = stoi(number, &sz);


	}
};


#endif // !

