#ifndef SHADER_PROGRAM_HEADER_INCLUDED
#define SHADER_PROGRAM_HEADER_INCLUDED
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<glad/glad.h>
#include"engine/util/Paths.h"

class ShaderProgram
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();
	void LoadFromFile(const GLenum&, const std::string&);
	void LoadFromString(const GLenum&, const std::string&);
	void Use();
	void UnUse();
	void CreateAndLink();
	void AddAttribute(const std::string&);
	void AddUniform(const std::string&);
	void DeleteProgram();
	void AutoFillUniformsFromString(const std::string&);
	void AutoFillUniformsFromFile(const std::string&);
	GLuint operator[](const std::string&);
	GLuint operator()(const std::string&);
	enum ShaderType : GLenum
	{
		VERTEX, FRAGMENT, GEOMETRY
	};
protected:
	static constexpr int MAX_SHADERS = 3;
	GLuint mProgram;
	GLuint mShaders[MAX_SHADERS];
	std::map<std::string, GLuint> mAttributeMap;
	std::map<std::string, GLuint> mUniformLocMap;
	void AttachShaders();
	void DeleteShaders();
};



#endif