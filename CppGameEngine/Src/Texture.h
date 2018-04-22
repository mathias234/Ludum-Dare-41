#pragma once
#include <string>
#include <map>

class Texture
{
private:
	static std::map<std::string, Texture*> m_TextureCache;

    unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;


	void Create(const std::string& path);

public:
    static Texture* GetTexture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	unsigned int GetTextureId();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	void Reload();
};

