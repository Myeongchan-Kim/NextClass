#include <windows.h>
#include <iostream>
#include <gl/glut.h>
#include <math.h>
#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat sDistance = 50.0f;

GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat spotDir[] = { 1.0f, 1.0f, 1.0f, 1.0f };

#define MODE_FLAT 1
#define MODE_SMOOTH 2
#define MODE_VERYLOW 3
#define MODE_MEDIUM 4
#define MODE_VERYHIGH 5
int iShade = MODE_SMOOTH;
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
	glFrontFace(GL_CCW);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 100.0f);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR , specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
	//orthograpic
	/*GLfloat nRange = 100.0f;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange*2.0f, nRange*2.0f);
	else
	glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	//perspective
	GLfloat fAspect;
	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	if (iShade == MODE_FLAT)
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static GLfloat fElect1 = 0.0f;

	//place light
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	glPopMatrix();

	//sun
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -100.0f);
	glColor3ub(255, 255, 130);
	glutSolidSphere(6.0f, 15, 15);

	//earth
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(20.0f, 0.0f, 0.0f);
	glColor3ub(100, 100, 200);
	glutSolidSphere(4.0f, 15, 15);
	
	//moon
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 15.0f);
	glColor3ub(100, 100, 100);
	glutSolidSphere(2.0f, 15, 15);
	glPopMatrix();

	glPopMatrix(); // pop earth matrix

	fElect1 += 10.0f;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;

	glutSwapBuffers();
}

void KeyControl(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		sDistance -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		sDistance += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	//printf("x:%d, y:%d", x, y);
	glutPostRedisplay();
}

//void ChangeSize(int w, int h)
//{
//	GLfloat nRange = 100.0f;
//
//	
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glViewport(0, 0, w, h);
//	
//	if (w <= h)
//		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
//	else
//		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}

void main(void)
{
	int nMenu;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Spot Light Atom");

	//menu
	nMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Flat Shading", 1);
	glutAddMenuEntry("smooth Shading", 2);
	glutAddMenuEntry("VL Shading", 3);
	glutAddMenuEntry("MD Shading", 4);
	glutAddMenuEntry("VH Shading", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
}