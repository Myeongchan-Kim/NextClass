#include <windows.h>
#include <gl/glut.h>
#include <gl/gltools.h>
#include <math.h>
#include "lodepng.h"

#define GL_PI 3.14159f
static GLfloat xRot = 0.0f;
static GLfloat hours = 0.0f;
static GLfloat zDistance = 10.0f;

GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat dif[] = { 0.8f, 0.8f, 0.8f ,1.0f };
GLfloat lightPos[] = { 0.0f, 0.0f, 10.0f, 1.0f };

GLuint texEarth;
GLuint texSun;
GLuint texMoon;

GLUquadricObj *quadric = nullptr;

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//quadric Texture mapping
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);
}

void LoadTexture() {
	std::vector<unsigned char> imgEarth;
	std::vector<unsigned char> imgSun;
	std::vector<unsigned char> imgMoon;
	unsigned width, height, error;


	//earth texture
	error = lodepng::decode(imgEarth, width, height, "texture_earth.png");
	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	printf("A Earth image size is %i\n", imgEarth.size());
	
	glGenTextures(1, &texEarth);
	glBindTexture(GL_TEXTURE_2D, texEarth);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgEarth.data());


	//sun texture
	error = lodepng::decode(imgSun, width, height, "texture_sun.png");
	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	printf("A Sun image size is %i\n", imgSun.size());
	glGenTextures(1, &texSun);
	glBindTexture(GL_TEXTURE_2D, texSun);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgSun.data());

	
	// moon texture
	error = lodepng::decode(imgMoon, width, height, "texture_moon.png");
	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	printf("A Moon image size is %i\n", imgMoon.size());
	glGenTextures(1, &texMoon);
	glBindTexture(GL_TEXTURE_2D, texMoon);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgMoon.data());

}

void RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(90, 1.0f, 0.0f, 0.0f); // texture rotate;

	glPushMatrix();
	//sun
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texSun);

	glRotatef(hours * 3, 0.0f, 0.0f, 1.0f);
	gluSphere(quadric, 20.0f, 20, 20);
	glPopMatrix();
	

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texEarth);
		//°øÀü
		glRotatef(hours, 0.0f, 0.0f, 1.0f);
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);
		glTranslatef(80.0f, 0.0f, 0.0f);

		glPushMatrix();
		glRotatef(hours * 12, 0.0f, 0.0f, 1.0f);
		gluSphere(quadric, 5.0f, 20, 20);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, texMoon);
		glRotatef(hours * 5, 0.0f, 0.0f, 1.0f);
		glTranslatef(20.0f, 0.0f, 0.0f);
		gluSphere(quadric, 3.0f, 20, 20);

	glPopMatrix();

	
	glPopMatrix();//texture rotate
	glutSwapBuffers();
}

//
//void KeyControl(int key, int x, int y)
//{
//	if (key == GLUT_KEY_LEFT)
//		hours -= 1.0f;
//	if (key == GLUT_KEY_RIGHT)
//		hours += 1.0f;
//	glutPostRedisplay();
//}

void TimerFunc(int value)
{
	hours += 1.0f;
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}



void ChangeSize(int w, int h)
{
	//perspective
	GLfloat fAspect;
	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(30.0f, fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -200.0f);
}

void main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2D texture");
	//glutKeyboeardFunc(NormalkeyInput);
	//glutSpecialFunc(KeyControl);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	glutTimerFunc(33, TimerFunc, 1);

	SetupRC();
	LoadTexture();

	glutMainLoop();

	return;
}