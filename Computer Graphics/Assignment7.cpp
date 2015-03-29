/*
Programmed by Travis Crumley for CPTR355 (Computer Graphics) while at Walla Walla University 2/11/15
This program is designed to Iterated Function Systems, input in an IFS table, Assignment 7
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

//This code implements an Iterated Function System engine.
//NOTE TO PROGRAMMERS: I start all of the arrays at 1 to keep things similar to mathematics. a[0] etc should not be touched.

const float Xres = 700; //Or whatever is desired
const float Yres = 700;

bool ignoreClick = false;
//Our x and y coordinates that we're transforming. 
float x = 0;
float y = 0;

int limit = 100000; //Max number of times we'll plot pixels

//A basic struct for an IFS table
class IFStable {
public:
	float a[10], b[10], c[10], d[10], e[10], f[10], p[10];
};

//Function prototypes, since it's simply easier to do things this way for this large of a program

//Functions for assignment 7
void plotPointIFS(IFStable ifs, int n);

//OpenGL functions I made/use
void init();
void display();
void onMouseClick(int button, int state, int x, int y);
//MAIN!

int main(int argc, char** argv)
{
	srand(7); //Seed our random generator for picking probabilities. I want a predictable seed for now

	//Set up the ifs table we'll be using. Defaults to zero so just change the values you need to
	IFStable ifs;
	//Fill it with zeroes (probably a better way to do this, but throws errors when I do it in the struct

	for (int i = 0; i < 10; i++)
	{
		ifs.a[i] = ifs.b[i] = ifs.c[i] = ifs.d[i] = ifs.e[i] = ifs.f[i] = ifs.p[i] = 0;
	}

	//Sierpinski Triangle
	//ifs.a[1] = ifs.a[2] = ifs.a[3] = 0.5;
	//ifs.d[1] = ifs.d[2] = ifs.d[3] = 0.5;
	//ifs.e[1] = ifs.e[2] = 1;
	//ifs.e[3] = 150;
	//ifs.f[1] = 1;
	//ifs.f[2] = ifs.f[3] = 150;
	//ifs.p[1] = ifs.p[2] = 0.33;
	//ifs.p[3] = 0.34;
	//int n = 3;

	//Square
	//ifs.a[1] = ifs.a[2] = ifs.a[3] = ifs.a[4] = 0.5;
	//ifs.d[1] = ifs.d[2] = ifs.d[3] = ifs.d[4] = 0.5;
	//ifs.e[1] = ifs.e[3] = 1;
	//ifs.e[2] = ifs.e[4] = 150;
	//ifs.f[1] = ifs.f[2] = 1;
	//ifs.f[3] = ifs.f[4] = 150;
	//ifs.p[1] = ifs.p[2] = ifs.p[3] = ifs.p[4] = 0.25;
	//int n = 4;

	//Fern
	//ifs.a[2] = 0.85;
	//ifs.a[3] = 0.2;
	//ifs.a[4] = 0.15;
	//ifs.b[3] = 0.26;
	//ifs.b[4] = -0.28;
	//ifs.c[2] = 0.04;
	//ifs.c[3] = -0.23;
	//ifs.c[4] = 0.26;
	//ifs.d[1] = 0.16;
	//ifs.d[2] = 0.85;
	//ifs.d[3] = 0.22;
	//ifs.d[4] = 0.24;
	//ifs.f[2] = ifs.f[3] = 70;
	//ifs.f[4] = 19;
	//ifs.p[1] = 0.01;
	//ifs.p[2] = 0.85;
	//ifs.p[3] = ifs.p[4] = 0.07;
	//int n = 4;

	//Tree
	//ifs.a[2] = ifs.a[3] = 0.42;
	//ifs.a[4] = 0.1;
	//ifs.b[2] = -0.42;
	//ifs.b[3] = 0.42;
	//ifs.c[2] = 0.42;
	//ifs.c[3] = -0.42;
	//ifs.d[1] = 0.5;
	//ifs.d[2] = ifs.d[3] = 0.42;
	//ifs.d[4] = 0.1;
	//ifs.f[2] = ifs.f[3] = ifs.f[4] = 200;
	//ifs.p[1] = 0.05;
	//ifs.p[2] = ifs.p[3] = 0.4;
	//ifs.p[4] = 0.15;
	//int n = 4;

	//For user input
	int n = 1;
	std::cout << "Please enter the number of transformations to be done: ";
	std::cin >> n;
	for (int i = 1; i <= n; i++)
	{
		std::cout << "\nFor transformation " << i << ": \n";
		std::cout << "a: ";
		std::cin >> ifs.a[i];
		std::cout << "b: ";
		std::cin >> ifs.b[i];
		std::cout << "c: ";
		std::cin >> ifs.c[i];
		std::cout << "d: ";
		std::cin >> ifs.d[i];
		std::cout << "e: ";
		std::cin >> ifs.e[i];
		std::cout << "f: ";
		std::cin >> ifs.f[i];
		std::cout << "p: ";
		std::cin >> ifs.p[i];
	}
	std::cout << "How many points do you wish to plot?";
	std::cin >> limit;

	glutInit(&argc, argv); //Initialize glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //One single window (I guess?) RGB 
	glutInitWindowSize(Xres, Yres); //Initial window size
	glutInitWindowPosition(600,200); //Position relative to my screen I think
	glutCreateWindow("CPTR 355 Assignment 6"); //Title of the window
	init(); //My own init function for openGL and glut stuff
	glutDisplayFunc(display); //This is called every time it needs to display
	glutMouseFunc(onMouseClick); //This is called on every mouse click event (down and up)
	glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
	glFlush(); //Flip to display said base color

	plotPointIFS(ifs, n); //Plot our points before letting glut take over

	glutMainLoop(); //Glut takes control now, loops through its callbacks (glut specific functions above)
}

//FUNCTION DECLARATIONS/ETC

//ASSIGNMENT 7 SECTION
void plotPointIFS(IFStable ifs, int n) //Using x and y as global variables
{
	std::cout << "Plotting " << limit << " points, please wait..." << std::endl;
	for (int i = 0; i < limit; i++)
	{
		//glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
		//glFlush();

		int random = rand() % 100; //Generate a random percentage
		float sum = 0; //Start at 0, adding on to find which transform to take
		int tform = 0; //I will set this to the transformation we're going to use
		for (int i = 1; i <= n; i++) //Iterate over all of our possible probabilities
		{
			sum = sum + ifs.p[i]; //Keep adding the probabilities until we find which one we'll take
			//std::cout << "sum " << sum << std::endl;
			//std::cout << "ifs.p[i] " << ifs.p[i] << std::endl;
			if (random < (sum * 100))
			{
				tform = i;
				//std::cout << "tform " << tform << std::endl;
				break; //Get out of the for loop
			}
		}

		//Now we transform based on that transformation
		float temp;
		temp = ifs.a[tform] * x + ifs.b[tform] * y + ifs.e[tform];
		y = ifs.c[tform] * x + ifs.d[tform] * y + ifs.f[tform];
		x = temp;

		//std::cout << "x: " << x << " y: " << y << std::endl;
		//Then we draw it!
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

		display(); //Update the display
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
	gluOrtho2D(-Xres/2, Xres/2, 0, Yres); //Set up an orthographic window
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
			//glClear(GL_COLOR_BUFFER_BIT); //Clear to the base color
			//glFlush();
			//////^ Not sure if those are working like I want them to here. Seems to work though

			////This is basically our main loop right here
			//
			//display(); //Update the display
		}
		else
		{
			
		}
		ignoreClick = !ignoreClick; //Ignore every other click
		
	}
}