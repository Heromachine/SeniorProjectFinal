#ifndef CLASS_TEXTURE_H
#define CLASS_TEXTURE_H
#include <vector> 
#include <string>
#include <GL\glew.h>
using namespace std; 

class Texture2D
{
private:

		Texture2D(const Texture2D &other);
		void operator =(const Texture2D& other);
public:
	Texture2D()
	{}
	Texture2D(const string &filename);
	virtual ~Texture2D();

	void Bind(int unit);
	void Bind();
	void InitText(const string &fileName);
	void InitText02(const string &fileName);

	GLuint m_texture;
	
	vector <GLuint> GLTextures;

};




#endif

