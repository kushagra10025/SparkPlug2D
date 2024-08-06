#pragma once

#include <map>
#include <memory>
#include <string>

#include <SP2DRendering/Essentials/Shader.h>
#include <SP2DRendering/Essentials/Texture.h>

namespace SP2D::Core::Resources
{
	class AssetManager
	{
	private:
		std::map<std::string, std::shared_ptr<SP2D::Rendering::Texture>> m_mapTextures{};
		std::map<std::string, std::shared_ptr<SP2D::Rendering::Shader>> m_mapShaders{};

	public:
		AssetManager() = default;
		~AssetManager() = default;

		bool AddTexture(const std::string& textureName, const std::string& texturePath, bool pixelArt = true);
		const SP2D::Rendering::Texture& GetTexture(const std::string& textureName);

		bool AddShader(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		SP2D::Rendering::Shader& GetShader(const std::string& shaderName);

	};
}
