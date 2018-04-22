#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "Common.h"

Shader::Shader() {
    m_Loaded = false;
}

Shader::Shader(const std::string & filepath) : m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

	Bind();

	for (int i = 0; i < m_SamplerIds.size(); ++i) {
		auto sampler = this->m_SamplerIds[i];
        this->SetInt(sampler.UniformName, sampler.SamplerId);
	}

	Unbind();
    m_Loaded = true;
}

Shader::~Shader()
{
    if(m_Loaded) {
	    GLCall(glDeleteProgram(m_RendererID));
        m_Loaded = false;
    }
}

void Shader::Reload()
{
    m_SamplerIdsMap.clear();
    m_SamplerIds.clear();
	m_UniformLocationCache.clear();
	GLCall(glDeleteProgram(m_RendererID));

	ShaderProgramSource source = ParseShader(m_FilePath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

	Bind();

	for (int i = 0; i < m_SamplerIds.size(); ++i) {
		auto sampler = this->m_SamplerIds[i];
        this->SetInt(sampler.UniformName, sampler.SamplerId);
	}

	Unbind();
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = static_cast<ShaderType>(ShaderType::NONE);

	unsigned int currentSamplerPos = 0;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = static_cast<ShaderType>(ShaderType::VERTEX);
			else if (line.find("fragment") != std::string::npos)
				type = static_cast<ShaderType>(ShaderType::FRAGMENT);
		}
		else
		{
			ss[(int)type] << line << '\n';
		}


		if(line.find("uniform sampler2D") != std::string::npos) {
			char currentChar = line[18]; // 18 is length of uniform sampler2D
			int index = 0;
			std::stringstream uniformName;
			while(currentChar != ';')
			{
				uniformName << currentChar;
				index++;
				currentChar = line[18+index];
			}

			std::cout << "Parsed sampler with name: " << uniformName.str() << ", assigning it the id " << currentSamplerPos << std::endl;

			m_SamplerIds.push_back({ uniformName.str(), currentSamplerPos });
			m_SamplerIdsMap.emplace(uniformName.str(), currentSamplerPos);
			currentSamplerPos++;
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;

	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(id));

		return 0;
	}

	return id;
}


unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::SetTexture(const std::string &uniformName, Texture &texture) {
	if(m_SamplerIdsMap.find(uniformName) == m_SamplerIdsMap.end()){
		return;
	}

	unsigned int id = m_SamplerIdsMap[uniformName];
	texture.Bind(id);
}

void Shader::SetTexture(const std::string &uniformName, FrameBuffer &texture, int targetId) {
	if(m_SamplerIdsMap.find(uniformName) == m_SamplerIdsMap.end()){
		return;
	}

	int id = m_SamplerIdsMap[uniformName];
    texture.BindAsTexture(targetId, id);
}


void Shader::Bind() const
{
    if(m_Loaded ) {
	    GLCall(glUseProgram(m_RendererID));
	}
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetMatrix4(const std::string &name, Matrix4f value)
{
	auto uniformLoc = GetUniformLocation(name);

	GLCall(glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(value)));
}

void Shader::SetMatrix4(const std::string &name, float* value)
{
	auto uniformLoc = GetUniformLocation(name);

	GLCall(glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, value));
}

void Shader::SetFloat4(const std::string &name, Vector4f vec4)
{
	auto uniformLoc = GetUniformLocation(name);

	GLCall(glUniform4f(uniformLoc, vec4.x, vec4.y, vec4.z, vec4.w));
}

void Shader::SetFloat3(const std::string &name, Vector3f vec3)
{
	auto uniformLoc = GetUniformLocation(name);

	GLCall(glUniform3f(uniformLoc, vec3.x, vec3.y, vec3.z));
}


void Shader::SetFloat2(const std::string &name, Vector2f value)
{
    auto uniformLoc = GetUniformLocation(name);

    GLCall(glUniform2f(uniformLoc, value.x, value.y));
}

void Shader::SetFloat(const std::string &name, float value)
{
	auto uniformLoc = GetUniformLocation(name);

	GLCall(glUniform1f(uniformLoc, value));
}


void Shader::SetInt(const std::string &name, int value)
{
	auto uniformLoc = GetUniformLocation(name);

	GLCall(glUniform1i(uniformLoc, value));
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
		
	m_UniformLocationCache[name] = location;

	return location;
}
