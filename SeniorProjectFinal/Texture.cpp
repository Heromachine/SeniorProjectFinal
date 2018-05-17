
#include "cTexture.h"

#include "stb_Image.h"

#include <iostream>
#include <cassert>



Texture2D::Texture2D(const string &fileName)
{
	int width, height, numComponents;

	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		cerr << "ERROR: TEXTURE DID NOT LOAD!!! [FILE: " << fileName <<"]" <<endl;
	}


	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData );


	stbi_image_free(imageData);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texture);
}


void Texture2D::Bind()
{
	//glActiveTexture(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture2D::Bind(int unit)
{
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, GLTextures.at(unit));
}



void Texture2D::InitText(const string &fileName)
{
	int width, height, numComponents;

	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);



	//string word(reinterpret_cast<char*>(imageData));



	if (imageData == NULL)
	{
		cerr << "ERROR: TEXTURE DID NOT LOAD!!! [FILE: " << fileName << "]" << endl;
	}


	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);


	



	//cout << "Word SIze:\n";
	//cout << sizeof(imageData)<<" | NUMOF C: " << word << endl;;
	//cout << "IMAGE DATA:\n";
	//for (int i = 0; i < word.size(); i++)
	//{
	//	cout << word.at(i) << endl;
	//}

	stbi_image_free(imageData);

}
void Texture2D::InitText02(const string &fileName)
{
	GLuint texture;
	int width, height, numComponents;

	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		cerr << "ERROR: TEXTURE DID NOT LOAD!!! [FILE: " << fileName << "]" << endl;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	GLTextures.push_back(texture);

	stbi_image_free(imageData);

}


//void Texture2D::InitTextur()
//{
//
//	int width, height, numComponents;
//
//
//	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
//
//	glEnable(GL_TEXTURE_2D);
//	glGenTextures(1, &texBufferID);
//	glBindTexture(GL_TEXTURE_2D, texBufferID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);
//
//	texCoordID = glGetAttribLocation(shaderProgramID, "s_vTexCoord");
//	glEnableVertexAttribArray(texCoordID);
//	int textureCoordOffset = 6 * NUM_VERTICES * sizeof(GLfloat);
//	glVertexAttribPointer(texCoordID, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(textureCoordOffset));
//
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	texID = glGetUniformLocation(shaderProgramID, "texture");
//	glActiveTexture(GL_TEXTURE0);
//	glUniform1i(texID, 0);
//
//}


