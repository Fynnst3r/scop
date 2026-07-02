#include "scop.hpp"

class Shader
{
private:
	unsigned int _id;
	void readShaderFile(const char *path);
	std::string _shaderCodeTmp;
public:
	Shader(const char *shaderSource, GLenum shaderType);
	Shader(const Shader &other);
	Shader operator=(const Shader &other);
	~Shader();

	void use();
	void addShader(const char *shaderSource, GLenum shaderType);
	unsigned int getId();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

int shaderSucceded(unsigned int shader);
int shaderProgramSucceded(unsigned int program);