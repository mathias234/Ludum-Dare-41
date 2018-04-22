#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Common.h"
#include "Texture.h"
#include "FrameBuffer.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
struct ShaderSamplerId {
	std::string UniformName;
	unsigned int SamplerId;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	std::unordered_map<std::string, unsigned int> m_SamplerIdsMap; // Use this to get sampler slot from string name
	std::vector<ShaderSamplerId> m_SamplerIds;            // Use this only if you need to iterate over the sampler maps
	float m_Loaded;

public:
    explicit Shader(const std::string& filepath);
	Shader();
	~Shader();

	void Reload();
	void SetTexture(const std::string &uniformName, Texture &texture);
	void SetTexture(const std::string &uniformName, FrameBuffer &texture, int targetId);
	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetMatrix4(const std::string &name, Matrix4f value);
	void SetMatrix4(const std::string &name, float* value);
	void SetFloat4(const std::string &name, Vector4f);
	void SetFloat3(const std::string &name, Vector3f vec3);
	void SetFloat2(const std::string &name, Vector2f value);
	void SetFloat(const std::string &name, float value);
	void SetInt(const std::string &name, int value);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);

};