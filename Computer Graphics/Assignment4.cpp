/*
Programmed by Travis Crumley for CPTR355 (Computer Graphics) while at Walla Walla University 1/20/15
This program is designed to implement a basic floodfill function
*/

//Including standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector> //for my own shenanigans

#include <ctime> //For srand
#include <iostream> //for debugging

//Include GLUT
#include <GL/glut.h>

#include <cmath>
#define PI 3.14159265

const int windowsizeX = 1000;
const int windowsizeY = 1000;
float x[7], y[7]; //Global variables for simplicity in such a small program.

//This initializes the glut window and sets up some basic parameters
void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //Clear the screen to white
	glColor3f(0.0, 0.0, 0.0); //Drawing in black
	glPointSize(1.0f); //Set point size to 1 pixel
	glMatrixMode(GL_PROJECTION); //Setup our matrix mode for our drawings
	glLoadIdentity(); //The identity matrix I think, not sure
	gluOrtho2D(0, windowsizeX, 0, windowsizeY); //Set up an orthographic window
}

void initHouse()
{
	//I'm using space to name them just to make things easier for myself
	//Dimensions of the box of the house
	float top = windowsizeY*.75f;
	float bottom = windowsizeY*.625f;
	float left = windowsizeX*.6f;
	float right = windowsizeX*.8f;

	//Dimensions of the roof
	float roofLeft = windowsizeX*.575f;
	float roofRight = windowsizeX*.825f;
	float roofCenter = (roofLeft + roofRight) / 2;
	float roofTop = windowsizeY*.85f;
	float roofBottom = windowsizeY*.725f;

	//Starting with the box, top left then counter clockwise
	x[0] = left;
	y[0] = top;
	x[1] = left;
	y[1] = bottom;
	x[2] = right;
	y[2] = bottom;
	x[3] = right;
	y[3] = top;

	//Now left point of roof to center to right
	x[4] = roofLeft;
	y[4] = roofBottom;
	x[5] = roofCenter;
	y[5] = roofTop;
	x[6] = roofRight;
	y[6] = roofBottom;

}

void drawHouse()
{
	std::cout << "Calling draw house" << std::endl;
	//Begin and end line loops, it allows me to draw an outline of a square with only 4 vertices
	glBegin(GL_LINE_LOOP);
	glVertex2i(x[0], y[0]); //Left, top
	glVertex2i(x[1], y[1]); //Left, bottom
	glVertex2i(x[2], y[2]); //Right, bottom
	glVertex2i(x[3], y[3]); //Right, top
	glEnd();

	//Draw the roof
	glBegin(GL_LINE_STRIP); 
	glVertex2i(x[4], y[4]); //roofLeft, roofBottom
	glVertex2i(x[5], y[5]); //roofCenter, roofTop
	glVertex2i(x[6], y[6]); //roofRight, roofBottom
	glEnd();
}


void calculateTranslateTransform(float translateX, float translateY)
{
	for (int i = 0; i < 7; i++)
	{
		x[i] = x[i] + translateX;
		y[i] = y[i] + translateY;
	}
}

void calculateScaleTransform(float scaleX, float scaleY)
{
	//We're going to shear around the midpoint, first calculate it
	float midpointX = (x[1] - x[0]) / 2 + x[0]; //Between left and right
	float midpointY = (y[2] - y[1]) / 2 + y[1]; //Between roofTop and bottom
	//std::cout << "MidpointX: " << midpointX << " Midpoint Y: " << midpointY << std::endl;
	//Translate to origin
	calculateTranslateTransform(-midpointX, -midpointY);
	for (int i = 0; i < 7; i++)
	{
		x[i] = x[i] * scaleX;
		y[i] = y[i] * scaleY;
	}
	//Translate back
	calculateTranslateTransform(midpointX, midpointY);
}

void calculateRotateTransform(float angle)
{
	//Converting angle to radians
	angle = -angle*PI / 180; //Negative because otherwise it goes backwards for some reason
	//std::cout << "Angle: " << angle << " cos: " << cos(angle) << " sin: " << sin(angle) << std::endl;
	//We're going to rotate around the midpoint, first calculate it
	float midpointX = (x[1] - x[0]) / 2 + x[0]; //Between left and right
	float midpointY = (y[2] - y[1]) / 2 + y[1]; //Between roofTop and bottom
	//std::cout << "MidpointX: " << midpointX << " Midpoint Y: " << midpointY << std::endl;
	//Translate to origin
	calculateTranslateTransform(-midpointX, -midpointY);
	//Rotate
	//std::cout << "x[4] before: " << x[4] << " y[2] before: " << y[2] << std::endl;
	int temp;
	for (int i = 0; i < 7; i++)
	{
		temp = x[i] * cos(angle) - y[i] * sin(angle);
		y[i] = x[i] * sin(angle) + y[i] * cos(angle);
		x[i] = temp;
	}
	//std::cout << "x[4] after: " << x[4] << " y[2] after: " << y[2] << std::endl;
	//Translate back
	calculateTranslateTransform(midpointX, midpointY);
}

void calculateShearTransform(float shearX, float shearY)
{
	//We're going to shear around the midpoint, first calculate it
	float midpointX = (x[1] - x[0]) / 2 + x[0]; //Between left and right
	float midpointY = (y[2] - y[1]) / 2 + y[1]; //Between roofTop and bottom
	//std::cout << "MidpointX: " << midpointX << " Midpoint Y: " << midpointY << std::endl;
	//Translate to origin
	calculateTranslateTransform(-midpointX, -midpointY);
	int temp;
	for (int i = 0; i < 7; i++)
	{
		temp = x[i] + shearX * y[i];
		y[i] = x[i] * shearY + y[i];
		x[i] = temp;
	}
	//Translate back
	calculateTranslateTransform(midpointX, midpointY);
}

void display() //Display the rectangles is all this is currently used for
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
	drawHouse();
	glFlush(); //Flip it to the screen I believe
}

void onMouseClick(int button, int state, int x, int y)
{
	//Only execute on mouseDown, not on up as well
	if (state == GLUT_DOWN)
	{
		int choice, translateX, translateY;
		float scaleX, scaleY, angle, shearX, shearY;
		std::cout << "Do you want to translate (0), scale(1), rotate(2), shear(3) or reset(4)?: ";
		std::cin >> choice;
		switch (choice)
		{
		case 0: //Translating
			std::cout << "\nHow much do you want to translate in the X direction?: ";
			std::cin >> translateX;
			std::cout << "\nHow much do you want to translate in the Y direction?: ";
			std::cin >> translateY;
			calculateTranslateTransform(translateX, translateY);
			break;
		case 1: //Scaling
			std::cout << "\nHow much do you want to scale in the X direction?: ";
			std::cin >> scaleX;
			std::cout << "\nHow much do you want to scale in the Y direction?: ";
			std::cin >> scaleY;
			calculateScaleTransform(scaleX, scaleY);
			break;
		case 2: //Rotate
			std::cout << "\nHow much do you want to rotate (in degrees)?: ";
			std::cin >> angle;
			calculateRotateTransform(angle);
			break;
		case 3: //Shear
			std::cout << "\nHow much do you want to shear in the X direction?: ";
			std::cin >> shearX;
			std::cout << "\nHow much do you want to shear in the Y direction?: ";
			std::cin >> shearY;
			calculateShearTransform(shearX, shearY);
			break;
		case 4: //Reset
			std::cout << "\n Resetting\n";
			initHouse();
			break;
		default:
			std::cout << "\nError, input not valid\n";
			break;
		}
		display(); //Update the display
		onMouseClick(0, GLUT_DOWN, 0, 0); //Fake button so we always have the menu open
	}
}

int main(int argc, char** argv)
{
	initHouse();
	glutInit(&argc, argv); //Initialize glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //One single window (I guess?) RGB 
	glutInitWindowSize(windowsizeX, windowsizeY); //Initial window size
	glutInitWindowPosition(200, 200); //Position relative to my screen I think
	glutCreateWindow("CPTR 355 Assignment 3"); //Title of the window
	init(); //My own init function for openGL and glut stuff
	glutDisplayFunc(display); //This is called every time it needs to display
	glutMouseFunc(onMouseClick); //This is called on every mouse click event (down and up)
	glutMainLoop(); //Glut takes control now, loops through its callbacks (glut specific functions above)
}