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

#include <math.h>

const int windowsizeX = 200;
const int windowsizeY = 200;
const int numRectangles = 25;

struct Point {
	GLint x;
	GLint y;
};

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

//This initializes the glut window and sets up some basic parameters
void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //Clear the screen to white
	glColor3f(0.0, 0.0, 0.0); //Drawing in black
	glPointSize(1.0f); //Set point size to 1 pixel
	glMatrixMode(GL_PROJECTION); //Setup our matrix mode for our drawings
	glLoadIdentity(); //The identity matrix I think, not sure
	gluOrtho2D(0, windowsizeX, 0, windowsizeY); //Set up an orthographic window
}

//Function to get the color of a pixel at x,y. Returns a Color struct
Color getPixelColor(GLint x, GLint y)
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color); //Read 1 pixel at x,y, RGB format of type float.
	return color;
}

//Function to set a pixel's color, basically draws a point there
void setPixelColor(GLint x, GLint y, Color color) 
{
	glColor3f(color.r, color.g, color.b); //Set our drawing color
	glBegin(GL_POINTS); //Start drawing points
	glVertex2i(x, y); //Draw a point at x,y
	glEnd(); //End drawing
	glFlush(); //I think this flips the buffer to display the pixel
}

//Function to start the recursive floodFill function, starts a bunch more floodfills
void floodFill(GLint x, GLint y, Color oldColor, Color newColor)
{
	if (x <= windowsizeX && x >= 0 && y <= windowsizeY && y >= 0)
	{
		Color color;
		color = getPixelColor(x, y);

		if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b) //If it's the old color
		{
			setPixelColor(x, y, newColor); //Draw a new colored pixel there
			floodFill(x + 1, y, oldColor, newColor); //Then start another floodfill all around it
			floodFill(x, y + 1, oldColor, newColor);
			floodFill(x - 1, y, oldColor, newColor);
			floodFill(x, y - 1, oldColor, newColor);
		}
	}	
}

void onMouseClick(int button, int state, int x, int y)
{
	//Only execute on mouseDown, not on up as well
	if (state == GLUT_DOWN)
	{
		Color newColor;
		std::cout << "\nEnter the R value (0-1) of the color: ";
		std::cin >> newColor.r;
		std::cout << "\nEnter the G value (0-1) of the color: ";
		std::cin >> newColor.g;
		std::cout << "\nEnter the B value (0-1) of the color: ";
		std::cin >> newColor.b;

		Color oldColor = getPixelColor(x, y);

		floodFill(x, windowsizeY - y, oldColor, newColor);
	}
	
}

//Add a rectangle drawing function here probably
void drawRectangles()
{
	srand(time(0));
	//Have to specify in counter clockwise order, drawing 4 lines for each rectangle
	//Using LINE_LOOP here (or at least trying to)
	for (int i = 0; i < numRectangles; i++)
	{
		//Counting 0,0 as the bottom left
		float top = rand() % windowsizeY;
		float bottom = rand() % windowsizeY;
		float left = rand() % windowsizeX;
		float right = rand() % windowsizeX;
		if (bottom > top)
		{
			std::swap(bottom, top);
		}
		if (left > right)
		{
			std::swap(left, right);
		}
		//Debugging:
		//std::cout << "Top: " << top << "\nLeft: " << left << "\nBottom: " << bottom << "\nRight: " << right << std::endl;

		//Begin and end line loops, it allows me to draw an outline of a square with only 4 vertices
		glBegin(GL_LINE_LOOP);
		glVertex2i(left, top);
		glVertex2i(left, bottom);
		glVertex2i(right, bottom);
		glVertex2i(right, top);
		glEnd();
	}
}

void display() //Display the rectangles is all this is currently used for
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
	drawRectangles(); 
	glFlush(); //Flip it to the screen I believe
}

int main(int argc, char** argv)
{
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