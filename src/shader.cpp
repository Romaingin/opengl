#include <stdio.h>
#include <fstream>
#include <iostream>

#include "../includes/game_engine.h"
#include "../includes/shader.h"

std::string Shader::LoadShaderFile(std::string strFile)
{
	std::ifstream fin(strFile.c_str());
	
	if ( !fin )
		return "";

	std::string strLine = "";
	std::string strText = "";

	while ( getline(fin, strLine) )
	{
		strText = strText + "\n" + strLine;
	}

	fin.close();
	return strText;
}

void Shader::Initialize(std::string strVertexFile, std::string strFragmentFile)
{
	std::string strVShader, strFShader;

	if ( !strVertexFile.length() || !strFragmentFile.length() )
		return;

	if ( VertexShaderId || FragmentShaderId || ShaderProgramId )
		Destroy();

	GLenum ErrorCheckValue = glGetError();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	strVShader = LoadShaderFile(strVertexFile.c_str());
	strFShader = LoadShaderFile(strFragmentFile.c_str());

	const char *szVShader = strVShader.c_str();
	const char *szFShader = strFShader.c_str();

	glShaderSource(VertexShaderId, 1, &szVShader, nullptr);
	glShaderSource(FragmentShaderId, 1, &szFShader, nullptr);
	
	glCompileShader(VertexShaderId);
	glCompileShader(FragmentShaderId);

	ShaderProgramId = glCreateProgram();

	glAttachShader(ShaderProgramId, VertexShaderId);
	glAttachShader(ShaderProgramId, FragmentShaderId);

	glLinkProgram(ShaderProgramId);
	glUseProgram(ShaderProgramId);
	
	// Passing Uniform variables to the shader
	GLint gScale = glGetUniformLocation(ShaderProgramId, "Scale");
	if (gScale != -1)
	{
	   glUniform1f(gScale, 0.12);
	}
	
	GLint gColor = glGetUniformLocation(ShaderProgramId, "Color");
	
	if (gColor != -1)
	{
		float Color[4] = {1.0f, 0.5f, 0.5f, 1.0f};
		glUniform4fv(gColor, 1, Color);
	}

	glUseProgram(0);
	
	ErrorCheckValue = glGetError();

	if ( ErrorCheckValue != GL_NO_ERROR )
	{
		fprintf(stderr, "ERROR: Could not create the shader program with error Id: %d\n", ErrorCheckValue);
		exit(-1);
	}
}

GLint Shader::GetVariable(std::string strVariable)
{
	if(!ShaderProgramId)
		return -1;

	return glGetUniformLocation(ShaderProgramId, strVariable.c_str());
}

void Shader::Destroy()
{
	if(VertexShaderId)
	{
		glDetachShader(ShaderProgramId, VertexShaderId);
		glDeleteShader(VertexShaderId);
		VertexShaderId = 0;
	}

	if(FragmentShaderId)
	{
		glDetachShader(ShaderProgramId, FragmentShaderId);
		glDeleteShader(FragmentShaderId);
		FragmentShaderId = 0;
	}

	if(ShaderProgramId)
	{
		glDeleteShader(ShaderProgramId);
		ShaderProgramId = 0;
	}
}