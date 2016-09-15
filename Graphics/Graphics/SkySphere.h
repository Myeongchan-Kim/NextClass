#pragma once
#include <gl/glut.h>
#include <vector>

struct TexVertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat texX;
	GLfloat texY;

	void PushVertex()
	{
		glNormal3f(-x, -y, -z);
		glTexCoord2f(texX, texY);
		glVertex3f(x, y, z);
	}
};

class SkySphere {
public:
	SkySphere(const char* fileName);
	virtual ~SkySphere();

	GLuint GetTexture();

protected:
	void LoadTexture(const char* fileName);

protected:
	std::vector<TexVertex*> vList;
	GLuint m_texture;
};
