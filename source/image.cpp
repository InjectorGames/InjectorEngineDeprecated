#include <injector_engine.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Injector
{
	Image::Image(const std::string& filePath, int targetChannels)
	{
		data = stbi_load(filePath.c_str(), &width, &height, &channels, targetChannels);

		if (!data)
			throw std::runtime_error("Failed to read image from the file");
	}
	Image::~Image()
	{
		stbi_image_free(data);
	}

	int Image::GetWidth()
	{
		return width;
	}
	int Image::GetHeight()
	{
		return height;
	}
	int Image::GetChannels()
	{
		return channels;
	}

	unsigned char* Image::GetData()
	{
		return data;
	}

	GLFWimage Image::GetGLFW()
	{
		auto image = GLFWimage();
		image.width = width;
		image.height = height;
		image.pixels = data;
		return image;
	}
}