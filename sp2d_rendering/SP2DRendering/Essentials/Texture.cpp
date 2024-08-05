#include "Texture.h"

SP2D::Rendering::Texture::Texture()
	: Texture(0, 0, 0, TextureType::NONE)
{

}

SP2D::Rendering::Texture::Texture(GLuint id, int width, int height, TextureType type /*= TextureType::PIXEL*/, const std::string& texturePath /*= ""*/)
	: m_TextureID{ id }, m_Width{ width }, m_Height{ height }, m_eType{ type }, m_sPath{ texturePath }
{

}

void SP2D::Rendering::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void SP2D::Rendering::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
