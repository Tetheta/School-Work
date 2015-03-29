/*
Programmed by Travis Crumley for CPTR355 (Computer Graphics) while at Walla Walla University 1/30/15
This program is designed to implement a viewport and window transformation/etc. Assignment 5
*/

//Including standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream> //for debugging

//Include GLUT
#include <GL/glut.h>

//Math stuff
#include <cmath>
#define PI 3.14159265

//This code illustrates the use of windows and viewports in scaling
//world coordinates to device coordinates via Normalized Device Coordinates.

const float Xres = 1025; //Or whatever is desired
const float Yres = 760;
int n;
float XW[20], YW[20], Xd[20], Yd[20]; //Arrays to hold data in world and device coordinate values
float XWmin, XWmax, YWmin, YWmax;
bool ignoreClick = false;

//Function prototypes, since it's simply easier to do things this way for this large of a program

//Functions for assignment 5
void getData(int &n);
void setWindow(float Xmin, float Xmax, float Ymin, float Ymax);
void setViewport(float XVmin, float XVmax, float YVmin, float YVmax, int n);

//OpenGL functions I made/use
void init();
void display();
void onMouseClick(int button, int state, int x, int y);
void drawLine(int Xd1, int Yd1, int Xd2, int Yd2);
void calculateTranslateTransform(float translateX, float translateY, float x[], float y[], int n);
void calculateScaleTransform(float scaleX, float scaleY, float x[], float y[], int n);

//MAIN!

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //Initialize glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //One single window (I guess?) RGB 
	glutInitWindowSize(Xres, Yres); //Initial window size
	glutInitWindowPosition(200, 200); //Position relative to my screen I think
	glutCreateWindow("CPTR 355 Assignment 5"); //Title of the window
	init(); //My own init function for openGL and glut stuff
	glutDisplayFunc(display); //This is called every time it needs to display
	glutMouseFunc(onMouseClick); //This is called on every mouse click event (down and up)
	glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
	glFlush(); //Flip to display said base color
	glutMainLoop(); //Glut takes control now, loops through its callbacks (glut specific functions above)
}

//FUNCTION DECLARATIONS/ETC

void getData(int &n)
//This function promts the user to enter the number of, and 
//value of the data in world coordinates to be plotted
{
	std::cout << "Please enter the number of data elements: ";
	std::cin >> n;
	//Cap n at the size of our arrays
	if (n > 20)
	{
		n = 20;
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << "\nPlease enter X coordinate #" << i + 1 << std::endl;
		std::cin >> XW[i];
		std::cout << "\nPlease enter Y coordinate #" << i + 1 << std::endl;
		std::cin >> YW[i];
	}

	//FOR TESTING PURPOSES:
	//n = 20;
	////Make a square around the left viewport first

	//YW[0] = 300;
	//XW[0] = 1;
	//YW[1] = 700;
	//XW[1] = 1;

	//YW[2] = 700;
	//XW[2] = 1;
	//YW[3] = 700;
	//XW[3] = n;

	//YW[4] = 700;
	//XW[4] = n;
	//YW[5] = 300;
	//XW[5] = n;

	//YW[6] = 300;
	//XW[6] = n;
	//YW[7] = 300;
	//XW[7] = 1;

	////For the right viewport

	//YW[8] = 10;
	//XW[8] = 1;
	//YW[9] = 100;
	//XW[9] = 1;

	//YW[10] = 100;
	//XW[10] = 1;
	//YW[11] = 100;
	//XW[11] = n;

	//YW[12] = 100;
	//XW[12] = n;
	//YW[13] = 10;
	//XW[13] = n;

	//YW[14] = 10;
	//XW[14] = n;
	//YW[15] = 10;
	//XW[15] = 1;

	//Now add some data
	/*YW[16] = 0;
	XW[16] = 0;
	YW[17] = 700;
	XW[17] = n;

	YW[18] = 50;
	XW[18] = n/2;
	YW[19] = 450;
	XW[19] = n;

	//Add a bit more data for when no viewportsp
	int counter = 0;
	for (int i = 0; i < 16; i++)
	{
		XW[i] = .5*counter;
		if (counter < 6)
		{
			YW[i] = 40 * counter;
		}
		else
		{
			YW[i] = 40 * (counter-6) + 300;
		}
		counter++;

	}*/
}

void setWindow(float Xmin, float Xmax, float Ymin, float Ymax)
/*	The following 4 min and max window coordinates are global variables,
and as such, globally communicate their values for use in the
setViewport function. After being set, clipping is done with respect
to this window, however clipping is extra credit for this assignment. */
{
	XWmin = Xmin;
	XWmax = Xmax;
	YWmin = Ymin;
	YWmax = Ymax;
	//TODO: Clipping here
	//Code for clipping is extra credit.
	for (int i = 0; i < n; i++)
	{
		//X crude clipping
		if (XW[i] > XWmax)
		{
			XW[i] = XWmax;
		}
		else if (XW[i] < XWmin)
		{
			XW[i] = XWmin;
		}
		//Y crude clipping
		if (YW[i] > YWmax)
		{
			YW[i] = YWmax;
		}
		else if (YW[i] < YWmin)
		{
			YW[i] = YWmin;
		}
	}
}

void setViewport(float XVmin, float XVmax, float YVmin, float YVmax, int n)
/*  This function scales the world coordinate points in arrays XW and YW
to actual device coordinates in arrays Xd, Yd. The scaling is done
via 4 min and max viewport coordinates which specify in NDC's
what part of the screen the data is to be plotted. */
{
	float S1, S2;
	float xv[20], yv[20];

	//Basically doing EQ #1 but in non-matrix form here
	//Set x and y scaling factors, S1 and S2
	S1 = (XVmax - XVmin) / (XWmax - XWmin);
	S2 = (YVmax - YVmin) / (YWmax - YWmin);
	std::cout << "S1: " << S1 << " S2: " << S2 << std::endl;

	//Calculate the viewport coordinates
	for (int i = 0; i < n; i++)
	{
		xv[i] = S1*(XW[i] - XWmin) + XVmin;
		yv[i] = S2*(YW[i] - YWmin) + YVmin;
		std::cout << "xv: " << xv[i] << " yv: " << yv[i] << std::endl;
	}

	//Apply the transforms of EQ #2
	calculateScaleTransform(Xres, Yres, xv, yv, n); //Scale to the desired resolution
	//I don't need these because of the origins in OpenGL:
	//calculateScaleTransform(1, -1, xv, yv, n); //Basically flipping over the x axis (not sure if I need)
	//calculateTranslateTransform(0, Yres, xv, yv, n); //move to 1st quadrant (not sure if I need this in OpenGL)

	//At this point xv is xd, I just need to assign xd to the values.
	std::cout << "AfterScaling\n";
	for (int i = 0; i < n; i++)
	{
		//Determine the equations for the device coordinates based
		//on the composition of the transformation matrices for
		//going from world -- to window -- to device
		Xd[i] = xv[i];
		Yd[i] = yv[i];
		std::cout << "Xd: " << Xd[i] << " Yd: " << Yd[i] << std::endl;
	}
}

void graphData(int n)
//This function plots the data in device coordinates
{
	for (int i = 0; i < n - 1; i++)
	{
		drawLine(Xd[i], Yd[i], Xd[i + 1], Yd[i + 1]); //Using my own drawline since there isn't one in my library
	}
}

void runViewportTest()
{
	getData(n);
	setWindow(1, n, 300, 700); //Clip on this window range in world coordinates
	setViewport(0.0, 0.5, 0.5, 1.0, n); //Put in the upper left quadrant
	graphData(n);

	getData(n);
	setWindow(1, n, 10, 100);
	setViewport(0.5, 1.0, 0.5, 1.0, n); //Put in the upper right quadrant
	graphData(n);
}

//OPENGL SECTION
//This initializes the glut window and sets up some basic parameters
void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //Clear the screen to white
	glColor3f(0.0, 0.0, 0.0); //Drawing in black
	glPointSize(1.0f); //Set point size to 1 pixel
	glMatrixMode(GL_PROJECTION); //Setup our matrix mode for our drawings
	glLoadIdentity(); //The identity matrix I think, not sure
	gluOrtho2D(0, Xres, 0, Yres); //Set up an orthographic window
}

void display() //Display the rectangles is all this is currently used for
{
	//glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
	//Need to draw here I think =/
	//drawLine(50, 50, 100, 100);
	glFlush(); //Flip it to the screen I believe
}

void onMouseClick(int button, int state, int x, int y)
{
	//Only execute on mouseDown, not on up as well
	if (state == GLUT_DOWN)
	{
		if (!ignoreClick)
		{
			glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
			glFlush();
			////^ Not sure if those are working like I want them to here.
			runViewportTest(); //Run our test
			display(); //Update the display
			//onMouseClick(0, GLUT_DOWN, 0, 0); //Fake button so we always have the menu open
		}
		else
		{
			
		}
		ignoreClick = !ignoreClick; //Ignore every other click
		
	}
}

void drawLine(int Xd1, int Yd1, int Xd2, int Yd2)
//I need to test this function individually to make sure it works, perhaps in the assignment4.cpp
{
	//std::cout << "Calling draw line" << std::endl;
	//Begin and end line loops, it allows me to draw an outline of a square with only 4 vertices
	glBegin(GL_LINES);
	glVertex2i(Xd1, Yd1);
	glVertex2i(Xd2, Yd2);
	glEnd();
}

void calculateScaleTransform(float scaleX, float scaleY, float x[], float y[], int n)
{
	//I'm just scaling with respect to the origin here.
	for (int i = 0; i < n; i++)
	{
		x[i] = x[i] * scaleX;
		y[i] = y[i] * scaleY;
	}
}