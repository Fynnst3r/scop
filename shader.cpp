#include "scop.hpp"

Shader::Shader(const char *shaderSource, GLenum shaderType)
{
	this->readShaderFile(shaderSource);
	const char *shaderCode = this->_shaderCodeTmp.c_str();

	// Create Shader
	unsigned int shaderId;
	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);
	shaderSucceded(shaderId);

	this->_id = glCreateProgram();

	// Link Shader
	glAttachShader(this->_id, shaderId);
	glLinkProgram(this->_id);
	shaderProgramSucceded(this->_id);
	glDeleteShader(shaderId);
}

Shader::Shader(const Shader &other)
{
	_id = other._id;
}

Shader Shader::operator=(const Shader &other)
{
	if (this == &other)
		return *this;
	_id = other._id;
	return *this;
}

void Shader::readShaderFile(const char *path)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(path);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl
				  << "Attempting to read path as code" << std::endl;
		this->_shaderCodeTmp = path;
		return;
	}
	this->_shaderCodeTmp = shaderCode;
}

void Shader::use()
{
	glUseProgram(this->_id);
}

void Shader::addShader(const char *shaderSource, GLenum shaderType)
{
	this->readShaderFile(shaderSource);
	const char *shaderCode = this->_shaderCodeTmp.c_str();

	// Create Shader
	unsigned int shaderId;
	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);
	shaderSucceded(shaderId);

	// Link Shader
	glAttachShader(this->_id, shaderId);
	glLinkProgram(this->_id);
	shaderProgramSucceded(this->_id);
	glDeleteShader(shaderId);
}

unsigned int Shader::getId()
{
	return this->_id;
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->_id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->_id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(this->_id, name.c_str()), value);
}

int shaderSucceded(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
				  << infoLog << std::endl;
	}
	return success;
}

int shaderProgramSucceded(unsigned int program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
				  << infoLog << std::endl;
	}
	return success;
}

Shader::~Shader()
{
	glDeleteProgram(this->_id);
}