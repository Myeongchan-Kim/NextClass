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

	GLfloat bigColorR = 0.8f;
	GLfloat bigColorG = 0.8f;
	GLfloat bigColorB = 0.8f;

	GLfloat smallColorR = 0.3f;
	GLfloat smallColorG = 0.4f;
	GLfloat smallColorB = 0.5f;

	MyRect() :x1(0), y1(0), size(10), xVelocity(1.0f), yVelocity(1.0f) {};

	MyRect(GLfloat x, GLfloat y, GLsizei s, GLfloat xV, GLfloat yV,
		GLfloat br, GLfloat bg, GLfloat bb)
		: x1(x), y1(y), size(s), xVelocity(xV), yVelocity(yV),
		bigColorR(br), bigColorG(bg), bigColorB(bb)
	{};

	MyRect(	GLfloat x, GLfloat y, GLsizei s, GLfloat xV, GLfloat yV, 
			GLfloat br, GLfloat bg, GLfloat bb, 
			GLfloat sr, GLfloat sg, GLfloat sb )
		: x1(x), y1(y), size(s), xVelocity(xV), yVelocity(yV), 
		bigColorR(br), bigColorG(bg), bigColorB(bb), 
		smallColorR(sr), smallColorG(sg), smallColorB(sb)
	{};

	void Draw() 
	{
		glColor3f(bigColorR, bigColorG, bigColorB);
		glRectf(x1, y1, x1 + size, y1 + size);
		glColor3f(smallColorR, smallColorG, smallColorB);
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
		//물리법칙 흉내 버전
		float rvCenterX = rv.x1 + rv.size / 2.0f;
		float lvCenterX = lv.x1 + lv.size / 2.0f;
		float rvCenterY = rv.y1 + rv.size / 2.0f;
		float lvCenterY = lv.y1 + lv.size / 2.0f;

		float xForce = (rv.size + lv.size) / (rvCenterX - lvCenterX) *2.0f;
		float yForce = (rv.size + lv.size) / (rvCenterY - lvCenterY) *2.0f;
		
		//적게 겹친 쪽만 적용.
		if (std::abs(xForce) < std::abs(yForce)) {
			rv.xVelocity += xForce / rv.size;
			lv.xVelocity -= xForce / lv.size;
		}
		else {
			rv.yVelocity += yForce / rv.size;
			lv.yVelocity -= yForce / lv.size;
		}
		
		rv.Move();
		lv.Move();

		//단순 충돌
		/*float xCollisionDepth ;
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
			if (rv.xVelocity > 0)
			{
				rv.Move(xCollisionDepth / 2.0f, 0);
				lv.Move(-xCollisionDepth / 2.0f, 0);
			}
			else
			{
				rv.Move(-xCollisionDepth / 2.0f, 0);
				lv.Move(xCollisionDepth / 2.0f, 0);
			}
			
		}
		else
		{
			rv.yVelocity = -rv.yVelocity;
			lv.yVelocity = -lv.yVelocity;
			if (rv.yVelocity > 0)
			{
				rv.Move(0, yCollisionDepth / 2.0f);
				lv.Move(0, -yCollisionDepth / 2.0f);
			}
			else {
				rv.Move(0, -yCollisionDepth / 2.0f);
				lv.Move(0, yCollisionDepth / 2.0f);
			}
		}*/
		return true;
	}
	return false;
}

MyRect rectList[RECT_NUM];

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < RECT_NUM; i++)
	{
		rectList[i].Move();
		rectList[i].CollisionWindowBoundary();
	}

	for (int i = 0; i < RECT_NUM; i++)
		for (int j = i + 1; j < RECT_NUM; j++)
			CollisionProceed(rectList[i], rectList[j]);

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
	rectList[0] = MyRect(0, 0, 40, .6f, .6f, .8f, .7f, .6f);
	rectList[1] = MyRect(800 - 30, 600 - 30, 30, .6f, .6f, .5f, .7f, .9f);
	rectList[2] = MyRect(800 - 30, 0, 50, .6f, .6f, .3f, .5f, .7f);
	rectList[3] = MyRect(0, 600 - 30, 20, .6f, .6f, .4f, .7f, .6f);
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
