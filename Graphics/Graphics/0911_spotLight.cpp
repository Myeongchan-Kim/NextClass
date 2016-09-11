#include <windows.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat sDistance = 10.0f;

//������ġ
GLfloat lightPos[] = { 0.0f, 0.0f, 75.0f, 1.0f }; 

GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f};

//���� ����
GLfloat spotDir[] = {0.0f, 0.0f, -1.0f };

#define MODE_FLAT 1
#define MODE_SMOOTH 2
#define MODE_VERYLOW 3
#define MODE_MEDIUM 4
#define MODE_VERYHIGH 5
int iShade = MODE_FLAT;
int iTess = MODE_VERYLOW;

void ProcessMenu(int value) {
	switch (value)
	{
	case 1:
		iShade = MODE_FLAT;
		break;
	case 2:
		iShade = MODE_SMOOTH;
		break;
	case 3:
		iTess = MODE_VERYLOW;
		break;
	case 4:
		iTess = MODE_MEDIUM;
		break;
	case 5:
	default:
		iTess = MODE_VERYHIGH;
		break;
	}
	glutPostRedisplay();
}


void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0f); // specific spot effects. ���� ���ߴ� ����.
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void RenderScene(void)
{
	if (iShade == MODE_FLAT)
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//place light
	glPushMatrix();
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	
	//draw a red cons (it looks like light source)
	glColor3ub(255, 0, 0);
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glutSolidCone(4.0f, 6.0f, 15, 15);

	glColor3ub(255, 255, 0);
	glutSolidSphere(3.0f, 15, 15);

	glPopMatrix();

	//draw sphere in the middle
	glColor3ub(0, 0, 255);
	if (iTess == MODE_VERYLOW)
		glutSolidSphere(30.0f, 7, 7);
	else {
		if (iTess == MODE_MEDIUM)
			glutSolidSphere(30.0f, 15, 15);
		else
			glutSolidSphere(30.0f, 50, 50); // MODE_HIGH
	}
	glutSwapBuffers();
}


void ChangeSize(int w, int h)
{
	//perspective
	GLfloat fAspect;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (GLfloat)w / (GLfloat)h;	
	gluPerspective(35.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -250.0f);
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
	//printf("x:%d, y:%d", x, y);
	glutPostRedisplay();
}

void main(void)
{
	int nMenu;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Spot Light");

	//menu
	nMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Flat Shading", 1);
	glutAddMenuEntry("smooth Shading", 2);
	glutAddMenuEntry("VL Shading", 3);
	glutAddMenuEntry("MD Shading", 4);
	glutAddMenuEntry("VH Shading", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}