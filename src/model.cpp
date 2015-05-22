#include "../includes/game_engine.h"
#include "../includes/model.h"

void Model::Initialize(Vertex3 vertices[], GLint length, std::string strVertex, std::string strFragment)
{
	m_Shader.Initialize(strVertex, strFragment);

	/*
	Vertices = vertices;
	VerticesLength = length;

	printf("Init vertices\n");
	
	GLenum ErrorCheckValue = glGetError();
	
	glGenVertexArrays(1, &VertexArrayObjectId);
	glBindVertexArray(VertexArrayObjectId);

	glGenBuffers(1, &VertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * length, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(kVertexIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), 0);

	glVertexAttribPointer(kColorIndex, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)sizeof(Vertices[0].xyz));

	ErrorCheckValue = glGetError();

	if ( ErrorCheckValue != GL_NO_ERROR )
	{
		fprintf(stderr, "ERROR: Could not create a VAO and VBO with error Id: %d\n", ErrorCheckValue);
		exit(-1);
	}
	*/
	
	
	GLfloat CubeArray[48] = {
		1.0f, 0.0f, 0.0f, -1.0f, 1.0f, -1.0f,
		1.0f, 0.0f, 1.0f, -1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, -1.0f, -1.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f
	};

	GLuint IndiceArray[36] = {
		0,1,2,2,1,3,
		4,5,6,6,5,7,
		3,1,5,5,1,7,
		0,2,6,6,2,4,
		6,7,0,0,7,1,
		2,3,4,4,3,5
	};

	// Génération des buffers
	glGenBuffers( 2, CubeBuffers );

	// Buffer d'informations de vertex
	glBindBuffer(GL_ARRAY_BUFFER, CubeBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeArray), CubeArray, GL_STATIC_DRAW);

	// Buffer d'indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceArray), IndiceArray, GL_STATIC_DRAW);


	
}

void Model::Render()
{
	/*
	m_Shader.TurnOn();
	
	glBindVertexArray(VertexArrayObjectId);
	glEnableVertexAttribArray(kVertexIndex);

	glEnableVertexAttribArray(kColorIndex);

	glDrawArrays(GL_TRIANGLES, 0, VerticesLength);
	
	glDisableVertexAttribArray(kColorIndex);

	glDisableVertexAttribArray(kVertexIndex);

	glBindVertexArray(0);

	m_Shader.TurnOff();
	*/
	
	// 1rst attribute buffer : vertices
	// Utilisation des données des buffers
	glBindBuffer(GL_ARRAY_BUFFER, CubeBuffers[0]);
	glVertexPointer( 3, GL_FLOAT, 6 * sizeof(float), ((float*)NULL + (3)) );
	glColorPointer( 3, GL_FLOAT, 6 * sizeof(float), 0 );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeBuffers[1]);

	// Activation d'utilisation des tableaux
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	// Rendu de notre géométrie
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}


void Model::Destroy()
{
	if ( VertexBufferId )
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &VertexBufferId);
		VertexBufferId = 0;
	}
	
	if ( VertexArrayObjectId )
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VertexArrayObjectId);
		VertexArrayObjectId = 0;
	}

	m_Shader.Destroy();
}