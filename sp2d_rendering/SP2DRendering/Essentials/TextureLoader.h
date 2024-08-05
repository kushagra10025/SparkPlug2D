#pragma once

#include "Texture.h"
#include <memory>

namespace SP2D::Rendering
{
	class TextureLoader
	{
	private:
		static bool LoadTexture(const std::string& filePath, GLuint& id, int& width, int& height, bool blended = false);
	public:
		TextureLoader() = delete;
		static std::shared_ptr<Texture> Create(Texture::TextureType type, const std::string& texturePath);
	};
}