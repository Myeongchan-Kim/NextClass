#pragma once
#include <gl/glut.h>
#include <vector>
class SkySphere;

class Practice5
{
public:
	static void Init();
	static void Run();

	static void RenderScene(void);
	static void CreateBackGroundList(void);
	static void SetupRC(void);
	static void ChangeSize(GLsizei w, GLsizei h);
	static void KeyControl(int key, int x, int y);
	static void MouseMove(int x, int y);

private:
	static GLfloat xRot;
	static GLfloat yRot;

	static std::vector<SkySphere*> bgList;
};