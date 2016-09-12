#include <windows.h>
#include <gl/glut.h>
#include <cmath>
#include <cassert>
#define RECT_NUM 4

GLfloat window_width;
GLfloat window_height;


struct MyRect 
{
	GLfloat x1, y1;
	GLsizei size;
	GLfloat xVelocity;
	GLfloat yVelocity;
	GLfloat bigColor[3] = {0.8f, 0.8f, 0.8f};
	GLfloat smallColor[3] = {0.3f, 0.4f, 0.5f};
	
	MyRect() :x1(0), y1(0), size(10), xVelocity(1.0f), yVelocity(1.0f) {};

	MyRect(GLfloat x, GLfloat y, GLsizei s, GLfloat xV, GLfloat yV) 
		: x1(x), y1(y), size(s), xVelocity(xV), yVelocity(yV) {};

	void Draw() 
	{
		glColor3f(bigColor[0], bigColor[1], bigColor[2]);
		glRectf(x1, y1, x1 + size, y1 + size);
		glColor3f(smallColor[0], smallColor[1], smallColor[2]);
		glRectf(x1 + size / 4, y1 + size / 4, x1 + size * 3 / 4, y1 + size * 3 / 4);
	}

	void Move(GLfloat dx, GLfloat dy)
	{
		x1 += dx;
		y1 += dy;
	}

	void Move()
	{
		Move(xVelocity, yVelocity);
	}

	void CollisionWindowBoundary()
	{
		if (x1 > window_width - size || x1 < -window_width) xVelocity = -xVelocity;
		if (y1 > window_height - size || y1 < -window_height) yVelocity = -yVelocity;

		if (x1 > window_width - size)
			x1 = window_width - size + xVelocity;
		if (y1 > window_height - size)
			y1 = window_height - size + yVelocity;
		if (x1 < -window_width)
			x1 = -window_width;
		if (y1 < -window_height)
			y1 = -window_height;
	}
};


bool CollisionCheck(MyRect& rv, MyRect& lv)
{
	if (rv.x1 + rv.size > lv.x1 &&
		rv.x1 < lv.x1 + lv.size &&
		rv.y1 + rv.size > lv.y1 &&
		rv.y1 < lv.y1 + lv.size
		)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool CollisionProceed(MyRect& rv, MyRect& lv) 
{

	if (CollisionCheck(rv, lv))
	{
		float xCollisionDepth ;
		if (rv.x1 + rv.size - lv.x1 > 0)
			xCollisionDepth = rv.x1 + rv.size - lv.x1;
		else if (lv.x1 + lv.size - rv.x1 > 0)
			xCollisionDepth = lv.x1 + lv.size - rv.x1;
		else
			assert(false);

		float yCollisionDepth;
		if (rv.y1 + rv.size - lv.y1 > 0)
			yCollisionDepth = rv.y1 + rv.size - lv.y1;
		else if (lv.y1 + lv.size - rv.y1 > 0)
			yCollisionDepth = lv.y1 + lv.size - rv.y1;
		else
			assert(false);

		if (xCollisionDepth < yCollisionDepth)
		{
			rv.xVelocity = -rv.xVelocity;
			lv.xVelocity = -lv.xVelocity;
			rv.Move();
			lv.Move();
		}
		else
		{
			rv.yVelocity = -rv.yVelocity;
			lv.yVelocity = -lv.yVelocity;
			rv.Move();
			lv.Move();
		}
		return true;
	}

	rv.CollisionWindowBoundary();
	lv.CollisionWindowBoundary();
	return false;
}

MyRect rectList[RECT_NUM];

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < RECT_NUM; i++)
		for (int j = i + 1; j < RECT_NUM; j++)
			CollisionProceed(rectList[i], rectList[j]);
	for (int i = 0; i < RECT_NUM; i++)
	{
		rectList[i].Move();
	}

	for (int i = 0; i < RECT_NUM; i++)
	{
		rectList[i].Draw();
	}
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(17, TimerFunction, value);
}

void SetupRC(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat bigColor[3] = { 1,1,1 };
	GLfloat smallColor[3] = { 0.5f, 0.5f, 0.5f };
	rectList[0] = MyRect(0, 0, 40, 1.0f, 1.0f);
	rectList[1] = MyRect(800 - 30, 600 - 30, 30, 1.0f, 1.0f);
	rectList[2] = MyRect(800 - 30, 0, 50, 1.0f, 1.0f);
	rectList[3] = MyRect(0, 600 - 30, 20, 1.0f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		window_width = 100.0f;
		window_height = 100.0f * h / w;
		glOrtho(-100.0f, 100.0f, -window_height, window_height, 1.0f, -1.0f);
	}
	else
	{
		window_width = 100.0f * w / h;
		window_height = 100.0f;
		glOrtho(-window_width, window_width, -100.0f, 100.0f, 1.0f, -1.0f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("BounceRect");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(17, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
