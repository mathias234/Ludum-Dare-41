#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
#include "Common.h"

std::map<std::string, Texture*> Texture::m_TextureCache;


Texture* Texture::GetTexture(const std::string &path) {
    if(m_TextureCache.find(path) == m_TextureCache.end()) {
        Texture* texture = new Texture();
        stbi_set_flip_vertically_on_load(1);
        texture->m_LocalBuffer = stbi_load(path.c_str(), &texture->m_Width, &texture->m_Height, &texture->m_BPP, 4);

        GLCall(glGenTextures(1, & texture->m_RendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D,  texture->m_RendererID));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  texture->m_Width,  texture->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE,  texture->m_LocalBuffer));

        GLCall(glGenerateMipmap(GL_TEXTURE_2D));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));


        GLCall(glBindTexture(GL_TEXTURE_2D, 0));

        if ( texture->m_LocalBuffer)
            stbi_image_free( texture->m_LocalBuffer);

        m_TextureCache.emplace(path, texture);
    }

    return m_TextureCache[path];
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Reload()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
	this->m_RendererID = GetTexture(m_FilePath)->m_RendererID;
}


void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned int Texture::GetTextureId() {
	return m_RendererID;
}



