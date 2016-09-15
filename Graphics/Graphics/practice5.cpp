#include "practice5.h"
#include <functional>
#include "SkySphere.h"

GLfloat Practice5::xRot = 0.0f;
GLfloat Practice5::yRot = 0.0f;
int Practice5::s_curIdx = 0;

std::vector<SkySphere*> Practice5::s_bgList;

void Practice5::RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, s_bgList[s_curIdx]->GetTexture());

	glPushMatrix();
	
	auto quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE);

	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 1.0f, 0.0f, 0.0f);
	glRotatef(xRot, 0.0f, 0.0f, 1.0f);
	gluSphere(quadric, 500.0f, 50, 50);
	glPopMatrix();

	glutSwapBuffers();
}

void Practice5::CreateBackGroundList()
{
	printf("PNG loading...\n");

	auto Deathvalleysky_nps_big = new SkySphere("resource/Deathvalleysky_nps_big.png");
	s_bgList.push_back(Deathvalleysky_nps_big);

	auto Regensburg_08_2006 = new SkySphere("resource/Regensburg_08_2006.png");
	s_bgList.push_back(Regensburg_08_2006);

	auto SonyCenter = new SkySphere("resource/SonyCenter.png");
	s_bgList.push_back(SonyCenter);

	auto mirrors_edge_bay = new SkySphere("resource/mirrors_edge_bay.png");
	s_bgList.push_back(mirrors_edge_bay);

	auto Bundeena_pier = new SkySphere("resource/Bundeena_pier.png");
	s_bgList.push_back(Bundeena_pier);

	auto trafalgar = new SkySphere("resource/Trafalgar_Square_Jun_2009.png");
	s_bgList.push_back(trafalgar);

	printf("Load Complete!\n");
}


void Practice5::SetupRC(void)
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Practice5::ChangeSize(GLsizei w, GLsizei h)
{
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


void Practice5::MouseClick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		s_curIdx++;
		if (s_curIdx >= s_bgList.size())
			s_curIdx = 0;
		glutPostRedisplay();
	}
}




void Practice5::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Cube interpolation");

	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();

	//setup vertices
	CreateBackGroundList();
}

void Practice5::Run()
{
	glutMainLoop();
}

