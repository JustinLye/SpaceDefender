#ifndef SHADER_PROGRAM_HEADER_INCLUDED
#define SHADER_PROGRAM_HEADER_INCLUDED

#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<glad/glad.h>

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


ShaderProgram::ShaderProgram() :
	mProgram(0)
{
	mShaders[VERTEX] = 0;
	mShaders[FRAGMENT] = 0;
	mShaders[GEOMETRY] = 0;
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::LoadFromFile(const GLenum& shader_type, const std::string& file_path)
{
	std::ifstream source_file;
	source_file.open(file_path);
	if (!source_file)
	{
		std::string msg = std::string("Source file path: ") + std::string(file_path) + std::string(" was not found.");
		throw std::runtime_error(std::string(msg.c_str()));
	}
	std::stringstream ss;
	ss << source_file.rdbuf();
	source_file.close();
	std::string file_content = ss.str();
	LoadFromString(shader_type, file_content);
}

void ShaderProgram::LoadFromString(const GLenum& shader_type, const std::string& source_string)
{
	switch (shader_type)
	{
	case VERTEX:
		mShaders[VERTEX] = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT:
		mShaders[FRAGMENT] = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GEOMETRY:
		mShaders[GEOMETRY] = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	default:
		throw std::runtime_error("Invalid shader type.");
		break;
	}
	const char* source_cstr = source_string.c_str();
	glShaderSource(mShaders[shader_type],1, &source_cstr, NULL);

	GLint status;
	glCompileShader(mShaders[shader_type]);
	glGetShaderiv(mShaders[shader_type], GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint info_log_len;
		glGetShaderiv(mShaders[shader_type], GL_INFO_LOG_LENGTH, &info_log_len);
		GLchar* info_log = new GLchar[info_log_len];
		glGetShaderInfoLog(mShaders[shader_type], info_log_len, NULL, info_log);
		std::cout << "Failure compiling shader: " << info_log << '\n';
		delete[] info_log;
	}
}

void ShaderProgram::Use()
{
	glUseProgram(mProgram);
}

void ShaderProgram::UnUse()
{
	glUseProgram(0);
}

void ShaderProgram::CreateAndLink()
{
	mProgram = glCreateProgram();
	AttachShaders();

	GLint status;
	glLinkProgram(mProgram);
	glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint info_log_len;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &info_log_len);
		GLchar* info_log = new GLchar[info_log_len];
		glGetProgramInfoLog(mProgram, info_log_len, NULL, info_log);
		std::cout << "Failed to link program " << info_log << '\n';
		delete[] info_log;
	}
	DeleteShaders();
}

void ShaderProgram::AddAttribute(const std::string& attribute)
{
	mAttributeMap[attribute] = glGetAttribLocation(mProgram, attribute.c_str());
}

void ShaderProgram::AddUniform(const std::string& uniform)
{
	mUniformLocMap[uniform] = glGetUniformLocation(mProgram, uniform.c_str());
}

void ShaderProgram::DeleteProgram()
{
	glDeleteProgram(mProgram);
}


void ShaderProgram::AutoFillUniformsFromString(const std::string& source_str)
{
	std::string::size_type start_pos, end_pos, curr_pos;
	std::string uniform = "uniform";
	std::string::size_type uniform_len = uniform.length();
	curr_pos = source_str.find(uniform, 0);
	while (curr_pos != std::string::npos && curr_pos + uniform_len < source_str.length() - 1)
	{
		end_pos = source_str.find_first_of(';', curr_pos + uniform_len);
		if (end_pos != std::string::npos)
		{
			--end_pos;
			start_pos = source_str.find_last_of(' ', end_pos);
			if (start_pos != std::string::npos)
			{
				++start_pos;
				AddUniform(source_str.substr(start_pos, end_pos - start_pos+1));
			}
		}
		curr_pos = source_str.find(uniform, end_pos + 1);
	}
}

void ShaderProgram::AutoFillUniformsFromFile(const std::string& file_path)
{
	std::ifstream input_file;
	input_file.open(file_path.c_str());
	if (!input_file)
	{
		throw std::runtime_error("Source file could not be opened. Uniforms not auto-filled.");
	}
	std::stringstream ss;
	ss << input_file.rdbuf();
	input_file.close();
	std::string file_content = ss.str();
	AutoFillUniformsFromString(file_content);
}


GLuint ShaderProgram::operator[](const std::string& attribute)
{
	return mAttributeMap[attribute];
}

GLuint ShaderProgram::operator()(const std::string& uniform)
{
	return mUniformLocMap[uniform];
}

void ShaderProgram::AttachShaders()
{
	for (GLuint i = 0; i < MAX_SHADERS; ++i)
	{
		if (mShaders[i] != 0)
		{
			glAttachShader(mProgram, mShaders[i]);
		}
	}
}

void ShaderProgram::DeleteShaders()
{
	for (GLuint i = 0; i < MAX_SHADERS; ++i)
	{
		glDeleteShader(mShaders[i]);
	}
}

#endif