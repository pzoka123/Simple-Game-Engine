#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textID);
}

void Texture::load()
{
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filename, 0), filename);
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit)
	);

	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR
	);

	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::unload()
{
	glDeleteTextures(1, &textID);
}
