#include <stdio.h>
#include <fstream>
#include <iostream>

#include "../includes/game_engine.h"
#include "../includes/model.h"

void Model::Initialize(GLfloat *vertices, GLuint *indices, int size_of_vertices, int size_of_indices, std::string strVertex, std::string strFragment)
{
	m_Shader.Initialize(strVertex, strFragment);
	
	// Génération des buffers
	glGenBuffers( 2, CubeBuffers );

	// Buffer d'informations de vertex
	glBindBuffer(GL_ARRAY_BUFFER, CubeBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_STATIC_DRAW);

	// Buffer d'indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_of_indices, indices, GL_STATIC_DRAW);
}

void Model::Render()
{
	m_Shader.TurnOn();
	
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
	
	m_Shader.TurnOff();
}


void Model::Destroy()
{
	if ( CubeBuffers )
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &CubeBuffers[0]);
	}
	
	m_Shader.Destroy();
}