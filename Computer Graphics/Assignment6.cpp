/*
Programmed by Travis Crumley for CPTR355 (Computer Graphics) while at Walla Walla University 2/4/15
This program is designed to implement a random fractal surface recursively, Assignment 6
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

#include <limits.h> //for max_int

//This code illustrates the use of windows and viewports in scaling
//world coordinates to device coordinates via Normalized Device Coordinates.

const float Xres = 1000; //Or whatever is desired
const float Yres = 700;

bool ignoreClick = false;
bool firstPass = false;
float incre = 0;
int depth, maxArea, minArea = 0; //Global variables for depth of the recusion and min/max areas

//A quick struct for floodfill
struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
//Default color
Color white = { 1.0f, 1.0f, 1.0f };

//Function prototypes, since it's simply easier to do things this way for this large of a program

//Functions for assignment 6
int rnd(float midx, float midy, int level);
Color getShade(int shade);
void computeArea(float x1, float y1, float x2, float y2, float x3, float y3);
void shadeArea(float x1, float y1, float x2, float y2, float x3, float y3);
void triangle(float x1, float y1, float x2, float y2, float x3, float y3, int level);

//OpenGL functions I made/use
void init();
void display();
void onMouseClick(int button, int state, int x, int y);
void drawLine(int Xd1, int Yd1, int Xd2, int Yd2);
void calculateTranslateTransform(float translateX, float translateY, float x[], float y[], int n);
void calculateScaleTransform(float scaleX, float scaleY, float x[], float y[], int n);
Color getPixelColor(float x, float y);
void setPixelColor(float x, float y, Color color);
void floodFill(float x, float y, Color oldColor, Color newColor);

//MAIN!

int main(int argc, char** argv)
{
	srand(7); //Seed the random generator

	glutInit(&argc, argv); //Initialize glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //One single window (I guess?) RGB 
	glutInitWindowSize(Xres, Yres); //Initial window size
	glutInitWindowPosition(600, 200); //Position relative to my screen I think
	glutCreateWindow("CPTR 355 Assignment 6"); //Title of the window
	init(); //My own init function for openGL and glut stuff
	glutDisplayFunc(display); //This is called every time it needs to display
	glutMouseFunc(onMouseClick); //This is called on every mouse click event (down and up)
	glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
	glFlush(); //Flip to display said base color
	glutMainLoop(); //Glut takes control now, loops through its callbacks (glut specific functions above)
}

//FUNCTION DECLARATIONS/ETC

int rnd(float midx, float midy, int level)
{
	const int range[8] = { 20, 19, 18, 12, 6, 1, 0, 0 };
	srand(midx + midy);
	return(rand() % (2 * range[level] + 1) - range[level]);
}

Color getShade(int shade)
//This function sets a palette of 16 shades from dark to light on whatever color is specified by the rgb input parameters. It then returns the desired color based on the shade wanted
{
	//We're doing just shades of green atm.
	return Color{ 0, 0.05*shade + .035, 0 };
}

void computeArea(float x1, float y1, float x2, float y2, float x3, float y3)
//Determine the min and max areas
{
	long area = abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
	if (area < minArea)
	{
		minArea = area;
	}
	if (area > maxArea)
	{
		maxArea = area;
	}
}

void shadeArea(float x1, float y1, float x2, float y2, float x3, float y3)
//color triangle according to its area
{
	long area = abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
	int color = round(float(area - minArea) / incre);
	//std::cout << "color: " << color << std::endl;
	float x = (x1 + x2 + x3) / 3;
	float y = (y1 + y2 + y3) / 3;
	floodFill(x, y, white, getShade(color));
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3, int level)
{
	
	//This is functional, I need now to avoid gaps and overlaps, because they're all over

	if (level <= depth)
	{
		//std::cout << "Triangle\n";
		//Determine midpoints of each side of the triangle
		float midx1 = (x1 + x2) / 2; 
		float midy1 = (y1 + y2) / 2;
		float midx2 = (x2 + x3) / 2;
		float midy2 = (y2 + y3) / 2;
		float midx3 = (x3 + x1) / 2;
		float midy3 = (y3 + y1) / 2;

		//Now adjust them all by a random amount, getting smaller as we get deeper
		//Can be both positive or negative at the moment, the +1 to level is so no divide by zero
		midx1 += rnd(midx1, midy1, level);
		midy1 += rnd(midx1, midy1, level);
		midx2 += rnd(midx2, midy2, level);
		midy2 += rnd(midx2, midy2, level);
		midx3 += rnd(midx3, midy3, level);
		midy3 += rnd(midx3, midy3, level);	

		if (level == depth)
		{
			if (firstPass)
			{
				computeArea(x1, y1, midx1, midy1, midx3, midy3); //Do this for all of its triangles
				computeArea(midx1, midy1, x2, y2, midx2, midy2);
				computeArea(midx3, midy3, midx2, midy2, x3, y3);
				computeArea(midx3, midy3, midx2, midy2, midx1, midy1);
			}
			else //Draw them!
			{
				//Draw the inner triangles
				//Draw the 9 lines for the 4 triangles
				//Draw new edges of large triangle first
				glColor3f(0.0f, 0.0f, 0.0f);
				drawLine(x1, y1, midx1, midy1); //Bottom
				drawLine(x2, y2, midx1, midy1);
				drawLine(x2, y2, midx2, midy2); //Right
				drawLine(x3, y3, midx2, midy2);
				drawLine(x1, y1, midx3, midy3); //Left
				drawLine(x3, y3, midx3, midy3);
				//Now for the inner triangle
				drawLine(midx3, midy3, midx2, midy2); //Top
				drawLine(midx2, midy2, midx1, midy1); //Right
				drawLine(midx1, midy1, midx3, midy3); //Left

				shadeArea(x1, y1, midx1, midy1, midx3, midy3); //Shade the other 3 triangles too
				shadeArea(midx1, midy1, x2, y2, midx2, midy2);
				shadeArea(midx3, midy3, midx2, midy2, x3, y3);
				shadeArea(midx3, midy3, midx2, midy2, midx1, midy1);
			}
		}
		else
		{
			//Four recursive calls on the triangles for the next level
			triangle(x1, y1, midx1, midy1, midx3, midy3, level + 1); //bottom left
			triangle(midx1, midy1, x2, y2, midx2, midy2, level + 1); //bottom right
			triangle(midx3, midy3, midx2, midy2, x3, y3, level + 1); //top
			triangle(midx3, midy3, midx2, midy2, midx1, midy1, level + 1); //middle (inverted)
		}
	}
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

			//This is basically our main loop right here
			maxArea = 0;
			minArea = INT_MAX;
			//Might want to set color here
			//Grab the depth
			std::cout << "What depth would you like to go to?";
			std::cin >> depth;

			firstPass = true; //Need to do a pass to determine min and max area
			std::cout << "\nStarting first pass" << std::endl;
			triangle(50, 50, Xres - 50, 100, Xres / 2, Yres - 50, 1);
			incre = (maxArea - minArea) / 15.0;
			firstPass = false;
			std::cout << "Starting triangle recursion" << std::endl;
			triangle(50, 50, Xres - 50, 100, Xres / 2, Yres - 50, 1);

			display(); //Update the display
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

//Float-based floodfill:

Color getPixelColor(float x, float y)
{
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color); //Read 1 pixel at x,y, RGB format of type float.
	return color;
}

//Function to set a pixel's color, basically draws a point there
void setPixelColor(float x, float y, Color color)
{
	glColor3f(color.r, color.g, color.b); //Set our drawing color
	glBegin(GL_POINTS); //Start drawing points
	glVertex2i(x, y); //Draw a point at x,y
	glEnd(); //End drawing
	glFlush(); //I think this flips the buffer to display the pixel
}

//Function to start the recursive floodFill function, starts a bunch more floodfills
void floodFill(float x, float y, Color oldColor, Color newColor)
{
	if (x <= Xres && x >= 0 && y <= Yres && y >= 0)
	{
		Color color;
		color = getPixelColor(x, y);

		if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b) //If it's the old color
		{
			setPixelColor(x, y, newColor); //Draw a new colored pixel there
			floodFill(x + 1, y, oldColor, newColor); //Then start more floodfills all around it
			floodFill(x, y + 1, oldColor, newColor);
			floodFill(x - 1, y, oldColor, newColor);
			floodFill(x, y - 1, oldColor, newColor);
		}
	}
}