/*
Code of Travis Crumley for CPTR355 Computer Graphics
Made for Assignment 2, 1/13/15
*/

//Including standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

//#include <iostream> //for debugging

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <glfw3.h>
GLFWwindow* window;

//Include GLM for math stuff
#include <glm/glm.hpp>
using namespace glm;
const int windowsize = 1000;
const int pixelDensity = 1000;

void DDA(int x1, int y1, int x2, int y2, std::vector<GLfloat> &vertices)
{
	float dx, dy, steps;
	float xincre, yincre, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	xincre = dx / steps;
	yincre = dy / steps;
	x = x1;
	y = y1;
	//plot(x,y)
	//The cout calls are for debugging
	//std::cout << "steps: " << steps << std::endl;
	//std::cout << "x: " << x << " y: " << y << std::endl;
	//std::cout << "xf: " << (float)x / pixelDensity << " yf: " << (float)y / pixelDensity << std::endl;
	vertices.push_back((float)x / pixelDensity);
	vertices.push_back((float)y / pixelDensity);
	vertices.push_back(0.0f); //For z coord

	for (float i = 0; i < steps; i++)
	{
		//std::cout << "x: " << x << " y: " << y << std::endl; //For debugging
		x = x + xincre;
		y = y + yincre;
		//plot(round(x), round(y));
		vertices.push_back((float)round(x) / pixelDensity);
		vertices.push_back((float)round(y) / pixelDensity);
		vertices.push_back(0.0f); //For z coord
	}
}


int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	//Using OpenGL 3.3 here, non resizable screen
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( windowsize, windowsize, "Assignment 2", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile -- Had to add this from tut 2
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Light Pink background for no reason
	glClearColor(1.0f, .8f, 1.0f, 0.0f);

	//This creates a VertexArray Object and sets it to the current one used in GL
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//Make a vector for easy pushing back/etc
	std::vector<GLfloat> vertices;

	for (float m = 0; m <= 1.05; m += .05f)
	{
		//Start at left side and go progressively towards y=mX where m is 0-1 with +.05
		//For some reason I have to go to 1.05 in the loop to get actually to 1 slope
		DDA(-pixelDensity, (int)(-m * pixelDensity), pixelDensity, (int)(m * pixelDensity), vertices); 
	}
	//Copy over our array (for some reason just pointing to it doesn't work with openGL)
	static GLfloat g_vertex_buffer_data[windowsize*windowsize];
	for (int i = 0; i < vertices.size(); i++)
	{
		g_vertex_buffer_data[i] = vertices[i];
	}


	//Now we need to give the data for our triangle to openGL, do this with a buffer
	// This will identify our vertex buffer
	GLuint vertexbuffer;

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Initialize points
	glEnable(GL_PROGRAM_POINT_SIZE);

	//Antialiasing attempt. Conclusion: no quick fix and too complex in openGL to do otherwise atm
	//glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize(1); //sets the point size, 1 for 1x1 pixel

	//Number of points
	//std::cout << "SizeOf Array: " << sizeof(g_vertex_buffer_data) << std::endl;
	int numPoints = vertices.size() / 3;
	//The following calls are for debugging:
	//std::cout << "numpoints: " << numPoints << std::endl;
	//for (int i = 0; i < vertices.size(); i += 3)
	//{
	//	std::cout << "x: " << g_vertex_buffer_data[i] << "y: " << g_vertex_buffer_data[i + 1] << "z: " << g_vertex_buffer_data[i + 2] << std::endl;
	//}

	//Now enter the main drawing loop
	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		//Draw the points!
		glDrawArrays(GL_POINTS, 0, numPoints); //Start from 0 go to our point number

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;


}
