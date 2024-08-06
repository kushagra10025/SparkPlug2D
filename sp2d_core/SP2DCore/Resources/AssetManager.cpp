#include "AssetManager.h"

#include <SP2DRendering/Essentials/TextureLoader.h>
#include <SP2DRendering/Essentials/ShaderLoader.h>
#include <SP2DLogging/Log.h>

bool SP2D::Core::Resources::AssetManager::AddTexture(const std::string& textureName, const std::string& texturePath, bool pixelArt /*= true*/)
{
	if (m_mapTextures.find(textureName) != m_mapTextures.end())
	{
		SP2D_CORE_ERROR("Failed to add Texture [{0}] -- Already Exists!", textureName);
		return false;
	}

	auto texture = std::move(SP2D::Rendering::TextureLoader::Create(
		pixelArt ? SP2D::Rendering::Texture::TextureType::PIXEL : SP2D::Rendering::Texture::TextureType::BLENDED,
		texturePath
	));

	if (!texture)
	{
		SP2D_CORE_ERROR("Failed to load Texture [{0}] at Path [{1}]", textureName, texturePath);
		return false;
	}

	m_mapTextures.emplace(textureName, std::move(texture));
	return true;
}

const SP2D::Rendering::Texture& SP2D::Core::Resources::AssetManager::GetTexture(const std::string& textureName)
{
	auto textureItr = m_mapTextures.find(textureName);
	if (textureItr == m_mapTextures.end())
	{
		SP2D_CORE_ERROR("Failed to get Texture [{0}] -- Does not exist!", textureName);
		SP2D::Rendering::Texture texture{};
		return texture;
	}

	return *textureItr->second;
}

bool SP2D::Core::Resources::AssetManager::AddShader(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	if (m_mapShaders.find(shaderName) != m_mapShaders.end())
	{
		SP2D_CORE_ERROR("Failed to add Shader [{0}] -- Already Exists!", shaderName);
		return false;
	}

	auto shader = std::move(SP2D::Rendering::ShaderLoader::Create(vertexShaderPath, fragmentShaderPath));

	if (!shader)
	{
		SP2D_CORE_ERROR("Failed to load Shader [{0}] at Vert Path [{1}] and Frag Path [{2}]", shaderName, vertexShaderPath, fragmentShaderPath);
		return false;
	}

	m_mapShaders.emplace(shaderName, std::move(shader));
	return true;
}

SP2D::Rendering::Shader& SP2D::Core::Resources::AssetManager::GetShader(const std::string& shaderName)
{
	auto shaderItr = m_mapShaders.find(shaderName);
	if (shaderItr == m_mapShaders.end())
	{
		SP2D_CORE_ERROR("Failed to get Shader [{0}] -- Does not exist!", shaderName);
		SP2D::Rendering::Shader shader{};
		return shader;
	}

	return *shaderItr->second;
}
