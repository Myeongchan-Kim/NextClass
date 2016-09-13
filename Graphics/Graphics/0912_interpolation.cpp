#include <windows.h>
#include <gl/glut.h>
#include <cmath>

GLfloat xRot;
GLfloat yRot;

struct CubeVertex {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLubyte r;
	GLubyte g;
	GLubyte b;

	void PushVertex()
	{
		glColor3ub(r, g, b);
		glVertex3f(x, y, z);
	}
};

CubeVertex vList[8];

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	
	//back
	glBegin(GL_POLYGON);	
	vList[0].PushVertex();
	vList[2].PushVertex();
	vList[3].PushVertex();
	vList[1].PushVertex();
	glEnd();

	//front
	glBegin(GL_POLYGON);
	vList[5].PushVertex();
	vList[7].PushVertex();
	vList[6].PushVertex();
	vList[4].PushVertex();
	glEnd();

	//right
	glBegin(GL_POLYGON);
	vList[7].PushVertex();
	vList[5].PushVertex();
	vList[1].PushVertex();
	vList[3].PushVertex();
	glEnd();

	//left
	glBegin(GL_POLYGON);
	vList[4].PushVertex();
	vList[6].PushVertex();
	vList[2].PushVertex();
	vList[0].PushVertex();
	glEnd();

	//top
	glBegin(GL_POLYGON);
	vList[2].PushVertex();
	vList[6].PushVertex();
	vList[7].PushVertex();
	vList[3].PushVertex();
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	vList[0].PushVertex();
	vList[1].PushVertex();
	vList[5].PushVertex();
	vList[4].PushVertex();
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}


void SetupRC(void)
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	//setup vertices
	for (int i = 0; i < 8; i++)
	{
		vList[i].x = -100 + (i % 2) * 200;
		vList[i].y = -100 + ((i / 2) % 2) * 200;
		vList[i].z = -100 + ((i / 4) % 2) * 200;

		vList[i].r = (i % 2) * 200;;
		vList[i].g = ((i / 2) % 2) * 200;;
		vList[i].b = ((i / 4) % 2) * 200;;
	}
}

void ChangeSize(GLsizei w, GLsizei h)
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

	glTranslatef(0.0f, 0.0f, -500.0f);

	glutPostRedisplay();
}


void KeyControl(int key, int x, int y)
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

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Cube interpolation");
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
