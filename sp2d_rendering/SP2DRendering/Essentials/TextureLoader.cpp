#include "TextureLoader.h"
#include <SP2DLogging/Log.h>
#include <SOIL2/SOIL2.h>

bool SP2D::Rendering::TextureLoader::LoadTexture(const std::string& filePath, GLuint& id, int& width, int& height, bool blended /*= false*/)
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(
		filePath.c_str(),	// Filename
		&width,				// Image Width
		&height,			// Image Height
		&channels,			// Number of Channels
		SOIL_LOAD_AUTO		// Force Channels Count
	);

	if (!image)
	{
		SP2D_CORE_ERROR("SOIL Failed to Load Image [{0}]\n{1}", filePath, SOIL_last_result());
		return false;
	}

	GLint format = GL_RGBA;

	switch (channels)
	{
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (!blended)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glTexImage2D(
		GL_TEXTURE_2D,			// Target
		0,						// Level of Detail
		format,					// Number of Color Components
		width,					// Image Width
		height,					// Image Height
		0,						// Border
		format,					// Format of Pixel Data
		GL_UNSIGNED_BYTE,		// Data type of Pixel Data
		image					// Data
	);

	// Delete Image Data from SOIL
	SOIL_free_image_data(image);

	return true;
}

std::shared_ptr<SP2D::Rendering::Texture> SP2D::Rendering::TextureLoader::Create(Texture::TextureType type, const std::string& texturePath)
{
	GLuint id;
	int width, height;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	switch (type)
	{
	case Texture::TextureType::PIXEL:
		LoadTexture(texturePath, id, width, height, false);
		break;
	case Texture::TextureType::BLENDED:
		LoadTexture(texturePath, id, width, height, true);
		break;
	default:
		SP2D_CORE_ERROR("The Current Type is not defined, Please use a defined Texture Type!");
		assert(false && "Refer the Logs!");
		return nullptr;
	}

	return std::make_shared<Texture>(id, width, height, type, texturePath);
}
