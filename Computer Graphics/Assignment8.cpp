
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <GL/glut.h>

#include <sstream> //To use to_string basically

#include <iostream>

using namespace std; //Because I'm lazy

float angle = 0.0, ratio;
float xS = 0.0f, yS = 1.75f, zS = 5.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int font = (int)GLUT_BITMAP_8_BY_13;
int w = 700;
int h = 700;


//This code allows the user to create Bezier Curves by defining the points
int n = 10; //set up initial defaults
int m = 100;

const int nmax = 20;
const int mmax = 500;
int ctrlpoint[nmax][2];
int c[nmax];
int x[mmax], y[mmax];

bool ignoreClick = false;

//Function prototypes

//Functions for assignment 8
void get_ctrl_points(int n);
void coefs(int n, int c[]);
float blending_value(int n, int i, float u);
void curve_points(int n, float u, int &x, int &y);
void plot_ctrlpoints(int n, int ctrlpoint[][2]);

//OpenGL functions I made/use
void drawLine(int Xd1, int Yd1, int Xd2, int Yd2);
void drawPoint(int X, int Y);

//Functions for displaying text/etc

void changeSize(int w1, int h1)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h1 == 0)
		h1 = 1;

	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xS, yS, zS,
		xS + lx, yS + ly, zS + lz,
		0.0f, 1.0f, 0.0f);


}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	//gluOrtho2D(0, w, h, 0);
	//gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2); //For centered
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font, string str)
{
	char *c;
	glRasterPos2f(x, y);
	for (c = (char*)str.c_str(); *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glPushMatrix();
	glColor3f(0.0f, 1.0f, 1.0f);
	setOrthographicProjection();
	glLoadIdentity();

	//Plot our control points
	plot_ctrlpoints(n, ctrlpoint);
	//Draw the polyline
	for (int i = 0; i < m; i++)
	{
		drawLine(x[i], y[i], x[i + 1], y[i + 1]);
		//cout << "x[i]: " << x[i] << " y[i]: " << y[i] << endl;
	}

	resetPerspectiveProjection();
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	cout << "Enter n for n+1 control points for the Bezier curve: ";
	cin >> n;
	get_ctrl_points(n);
	coefs(n, c);
	cout << "Enter the no. of st. line segments to approximate the Bezier curve: ";
	cin >> m;
	for (int i = 0; i <= m; i++)
	{
		curve_points(n, (float)i / m, x[i], y[i]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Assignment 8 with Text");

	glPointSize(5.0f); //Set point size to 10 pixels to make control points clear

	glutDisplayFunc(renderScene);

	glutReshapeFunc(changeSize);

	glutMainLoop();

	return(0);
}

//FUNCTION DECLARATIONS/ETC

//ASSIGNMENT 8 SECTION

int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
void get_ctrl_points(int n)
{
	for (int i = 0; i <= n; i++)
	{
		cout << "For P" << i << " x = ";
		cin >> ctrlpoint[i][0];
		cout << "      y = ";
		cin >> ctrlpoint[i][1];
	}
}
void coefs(int n, int c[])
{
	for (int k = 0; k <= n; k++)
	{
		c[k] = round(factorial(n) / (factorial(k)*factorial(n - k)));
		//cout << "c[k]: " << c[k] << endl;
	}
}
float blending_value(int n, int k, float u)
{
	return c[k] * pow(u, k) * pow(1 - u, n - k);
}
void curve_points(int n, float u, int &x, int &y)
{
	//cout << "curve points\n";
	float bv;
	x = y = 0;
	for (int i = 0; i <= n; i++)
	{
		bv = blending_value(n, i, u);
		x = round(x + bv*ctrlpoint[i][0]);
		y = round(y + bv*ctrlpoint[i][1]);
		//cout << "x: " << x << " y: " << y << endl;
	}
}
void plot_ctrlpoints(int n, int ctrlpoint[][2])
{
	for (int k = 0; k <= n; k++)
	{
		//Plot at ctrlpoint[k][0], ctrlpoint[k][1] I think, not sure what the str stuff is about, it's a label
		drawPoint(ctrlpoint[k][0], ctrlpoint[k][1]);
		//cout << to_string(k) << endl;
		renderBitmapString(ctrlpoint[k][0]-1, ctrlpoint[k][1]+8, (void *)font, to_string(k));
	}
}


//OPENGL SECTION
void drawLine(int Xd1, int Yd1, int Xd2, int Yd2)
{
	//std::cout << "Calling draw line" << std::endl;
	//Begin and end line loops, it allows me to draw an outline of a square with only 4 vertices
	glBegin(GL_LINES);
	glVertex2i(Xd1, Yd1);
	glVertex2i(Xd2, Yd2);
	glEnd();
}

void drawPoint(int X, int Y)
{
	//std::cout << "Calling draw line" << std::endl;
	//Begin and end line loops, it allows me to draw an outline of a square with only 4 vertices
	glBegin(GL_POINTS);
	glVertex2i(X, Y);
	glEnd();
}