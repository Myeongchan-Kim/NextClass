#include "SkySphere.h"
#include "lodepng.h"

SkySphere::SkySphere(const char* fileName)
{
	LoadTexture(fileName);
}


SkySphere::~SkySphere()
{
	for (auto& v : vList) {
		if (v != nullptr)
		{
			delete v;
			v = nullptr;
		}
	}
	vList.clear();
}

GLuint SkySphere::GetTexture()
{
	return m_texture;
}

void SkySphere::LoadTexture(const char* fileName)
{
	std::vector<unsigned char> imgMoon;
	unsigned width, height, error;

	//earth texture
	error = lodepng::decode(imgMoon, width, height, fileName);
	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	printf("Load texture : %s(%i)\n", fileName, imgMoon.size());

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgMoon.data());

}
