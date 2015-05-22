#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "../includes/shader.h"

class Vertex3
{
public:
	
	float xyz[3];
	float rgba[4];
};

class Model
{
public:
	static const GLuint kVertexIndex = 0;
	static const GLuint kColorIndex = 1;
	static const GLuint kTextureIndex = 2;
	static const GLuint kNormalIndex = 3;
	
	Model()		{ }
	~Model()	{ Destroy(); }

	void Initialize(GLfloat *vertices, GLuint *indices, int size_of_vertices, int size_of_indices, std::string strVertex, std::string strFragment);
	void Render();
	void Destroy();

private:
	GLuint CubeBuffers[2];
	GLuint indexBuffer;
	
	Shader m_Shader;						
};

#endif
