#include "practice5.h"
#include <functional>


GLfloat Practice5::xRot = 0.0f;
GLfloat Practice5::yRot = 0.0f;

std::vector<SkySphere*> Practice5::bgList;

void Practice5::RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glutSwapBuffers();
}

void Practice5::CreateBackGroundList(void)
{

}


void Practice5::SetupRC(void)
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//setup vertices
	CreateBackGroundList();
}

void Practice5::ChangeSize(GLsizei w, GLsizei h)
{
	////ortho
	//glViewport(0, 0, w, h);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//glOrtho(-w, w, -h, h, 1.0f, -1.0f);
	//
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//perspective
	GLfloat fAspect;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 1000.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);

	glutPostRedisplay();
}


void Practice5::KeyControl(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	glutPostRedisplay();
}

void Practice5::MouseMove(int x, int y)
{
	xRot = x;
	yRot = y;
	glutPostRedisplay();
}


void Practice5::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Cube interpolation");

	glutPassiveMotionFunc(MouseMove);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
}

void Practice5::Run()
{
	glutMainLoop();
}

