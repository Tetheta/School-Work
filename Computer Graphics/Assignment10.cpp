/*
Programmed by Travis Crumley for CPTR355 (Computer Graphics) while at Walla Walla University 3/13/15
This program is designed to Create and Model a 3D cylinder using Polygonal Meshes, Assignment 10
*/

//#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.1415926

GLfloat gAngle = 0.0;

struct Point3
{
	float x, y, z = 0;
};

struct Vector3
{
	float x, y, z = 0;
};

// Vertex ID
class VertexID {
public:
	int vertIndex; // index of this vertex in the vertex list
	int normIndex; // index of this vertex’s normal
};
// Face
class Face {
public:
	int nVerts; // number of vertices in this face
	VertexID *vert; // the list of vertex and normal indices
	Face(){ nVerts = 0; vert = NULL; }; // constructor
	~Face(){ nVerts = 0; delete[] vert; }; // destructor
	void createFace(int numVerts);
};

void Face::createFace(int numVerts)
{
	nVerts = numVerts;
	vert = new VertexID[numVerts];
}

// Mesh
class Mesh {
private:
	int numVerts; // number of vertices in the mesh
	Point3 *pt; // array of 3D vertices
	int numNormals; // number of normal vertices for the mesh
	Vector3 *norm; // array of normals
	int numFaces; // number of faces in the mesh
	Face *face; // array of face data
	// ... others to be added later
public:
	Mesh(){ numVerts = 0; numNormals = 0; numFaces = 0; pt = NULL; norm = NULL; face = NULL; }; // constructor
	~Mesh() { numVerts = 0; numNormals = 0; numFaces = 0; delete[] pt; delete[] norm; delete[] face; }; // destructor
	int readFile(char *fileName); // to read in mesh file.
	void makeCylinder(); //To setup cylinder
	void draw(); //To draw the mesh
};

void Mesh::draw(void) { // use openGL to draw this mesh
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		// for each vertex of this polygon
		for (int v = 0; v < face[f].nVerts; v++) {
			// index of the normal for this vertex
			//printf("normIndex: " + face[0].vert[0].normIndex);
			int in = face[f].vert[v].normIndex;
			glNormal3f(norm[in].x, norm[in].y, norm[in].z);
			// index of this vertex
			//printf("face: %i, vert: %i", f, v);
			int iv = face[f].vert[v].vertIndex;
			//printf("iv: %i\n", iv);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::makeCylinder()
{
	numVerts = 720;
	numNormals = 720;
	numFaces = 360;
	pt = new Point3[numVerts]; //Create new array for the points
	norm = new Vector3[numNormals]; //New array for the normals
	face = new Face[numFaces]; //New array for faces

	//Example code for creating a tetrahedron:

	//	pt[0].x = 0; pt[0].y = 0; pt[0].z = 0;
	//	pt[1].x = 5; pt[1].y = 0; pt[1].z = 0;
	//	pt[2].x = 0; pt[2].y = 5; pt[2].z = 0;
	//	pt[3].x = 0; pt[3].y = 0; pt[3].z = 5;

	//	norm[0].x = .577f; norm[0].y = .577f; norm[0].z = .577f;
	//	norm[1].x = 0; norm[1].y = 0; norm[1].z = -1;
	//	norm[2].x = -1; norm[2].y = 0; norm[2].z = 0;
	//	norm[3].x = 0; norm[3].y = -1; norm[3].z = 0;

	//	face[0].createFace(3);
	//	face[0].vert[0].normIndex = 0; face[0].vert[1].normIndex = 0; face[0].vert[2].normIndex = 0;
	//	face[0].vert[0].vertIndex = 1; face[0].vert[1].vertIndex = 2; face[0].vert[2].vertIndex = 3;
	//	face[1].createFace(3);
	//	face[1].vert[0].normIndex = 1; face[1].vert[1].normIndex = 1; face[1].vert[2].normIndex = 1;
	//	face[1].vert[0].vertIndex = 0; face[1].vert[1].vertIndex = 2; face[1].vert[2].vertIndex = 1;
	//	face[2].createFace(3);
	//	face[2].vert[0].normIndex = 2; face[2].vert[1].normIndex = 2; face[2].vert[2].normIndex = 2;
	//	face[2].vert[0].vertIndex = 0; face[2].vert[1].vertIndex = 3; face[2].vert[2].vertIndex = 2;
	//	face[3].createFace(3);
	//	face[3].vert[0].normIndex = 0; face[3].vert[1].normIndex = 0; face[3].vert[2].normIndex = 0;
	//	face[3].vert[0].vertIndex = 1; face[3].vert[1].vertIndex = 3; face[3].vert[2].vertIndex = 0;

	//Example code for creating a cube:

		//pt[0].x = 0; pt[0].y = 0; pt[0].z = 0;
		//pt[1].x = 5; pt[1].y = 0; pt[1].z = 0;
		//pt[2].x = 5; pt[2].y = 0; pt[2].z = 5;
		//pt[3].x = 0; pt[3].y = 0; pt[3].z = 5;
		//pt[4].x = 0; pt[4].y = 5; pt[4].z = 0;
		//pt[5].x = 5; pt[5].y = 5; pt[5].z = 0;
		//pt[6].x = 5; pt[6].y = 5; pt[6].z = 5;
		//pt[7].x = 0; pt[7].y = 5; pt[7].z = 5;

		//norm[0].x = 0;  norm[0].y = 0;  norm[0].z = -1;
		//norm[1].x = 1;  norm[1].y = 0;  norm[1].z = 0;
		//norm[2].x = 0;  norm[2].y = 0;  norm[2].z = 1;
		//norm[3].x = -1; norm[3].y = 0;  norm[3].z = 0;
		//norm[4].x = 0;  norm[4].y = 1;  norm[4].z = 0;
		//norm[5].x = 0;  norm[5].y = -1; norm[5].z = 0;

		//face[0].createFace(4);
		//face[0].vert[0].normIndex = 0; face[0].vert[1].normIndex = 0; 
		//face[0].vert[2].normIndex = 0; face[0].vert[3].normIndex = 0;
		//face[0].vert[0].vertIndex = 0; face[0].vert[1].vertIndex = 1; 
		//face[0].vert[2].vertIndex = 5; face[0].vert[3].vertIndex = 4;
		//face[1].createFace(4);
		//face[1].vert[0].normIndex = 1; face[1].vert[1].normIndex = 1;
		//face[1].vert[2].normIndex = 1; face[1].vert[3].normIndex = 1;
		//face[1].vert[0].vertIndex = 1; face[1].vert[1].vertIndex = 2;
		//face[1].vert[2].vertIndex = 6; face[1].vert[3].vertIndex = 5;
		//face[2].createFace(4);
		//face[2].vert[0].normIndex = 2; face[2].vert[1].normIndex = 2;
		//face[2].vert[2].normIndex = 2; face[2].vert[3].normIndex = 2;
		//face[2].vert[0].vertIndex = 2; face[2].vert[1].vertIndex = 3;
		//face[2].vert[2].vertIndex = 7; face[2].vert[3].vertIndex = 6;
		//face[3].createFace(4);
		//face[3].vert[0].normIndex = 3; face[3].vert[1].normIndex = 3;
		//face[3].vert[2].normIndex = 3; face[3].vert[3].normIndex = 3;
		//face[3].vert[0].vertIndex = 3; face[3].vert[1].vertIndex = 0;
		//face[3].vert[2].vertIndex = 4; face[3].vert[3].vertIndex = 7;
		//face[4].createFace(4);
		//face[4].vert[0].normIndex = 4; face[4].vert[1].normIndex = 4;
		//face[4].vert[2].normIndex = 4; face[4].vert[3].normIndex = 4;
		//face[4].vert[0].vertIndex = 5; face[4].vert[1].vertIndex = 6;
		//face[4].vert[2].vertIndex = 7; face[4].vert[3].vertIndex = 4;
		//face[5].createFace(4);
		//face[5].vert[0].normIndex = 5; face[5].vert[1].normIndex = 5;
		//face[5].vert[2].normIndex = 5; face[5].vert[3].normIndex = 5;
		//face[5].vert[0].vertIndex = 0; face[5].vert[1].vertIndex = 3;
		//face[5].vert[2].vertIndex = 2; face[5].vert[3].vertIndex = 1;

	//Creating a cylinder:
	int ct = 0; //current count
	int fNum = 0; //Current face
	bool toggle = false;
	for (float i = 0; i < 360; i++)
	{
		//Create top circle point
		pt[ct].x = 2 * cos(i*M_PI / 180); pt[ct].y = 2 * sin(i*M_PI / 180); pt[ct].z = 0; //should be circle radius 2, roughly speaking
		//printf("x: %f, y: %f, z: %f\n", pt[ct].x, pt[ct].y, pt[ct].z);
		norm[ct].x = cosf(pt[ct].x); norm[ct].y = sinf(pt[ct].y); norm[ct].z = 0;
		ct++;
		
		//Create bottom circle point
		pt[ct].x = 2 * cos(i*M_PI / 180); pt[ct].y = 2 * sin(i*M_PI / 180); pt[ct].z = 10; //should be circle radius 2, roughly speaking
		//printf("x: %f, y: %f, z: %f\n", pt[ct].x, pt[ct].y, pt[ct].z);
		norm[ct].x = cosf(pt[ct].x); norm[ct].y = sinf(pt[ct].y); norm[ct].z = 0; //no idea if works

		//This is for making a sort of wire-mesh cylinder, with no caps
		//if (toggle)
		//{
		//	//Create faces (this creates an almost wire-mesh effect, no caps
		//	face[fNum].createFace(4);
		//	face[fNum].vert[0].normIndex = ct - 3; face[fNum].vert[1].normIndex = ct - 1; //top
		//	face[fNum].vert[2].normIndex = ct; face[fNum].vert[3].normIndex = ct - 2;  //bottom
		//	face[fNum].vert[0].vertIndex = ct - 3; face[fNum].vert[1].vertIndex = ct - 1; //top
		//	face[fNum].vert[2].vertIndex = ct; face[fNum].vert[3].vertIndex = ct - 2; //bottom
		//	fNum++;
		//}
		//toggle = !toggle;
		ct++;
	}
	//This makes a full cylinder, all one face
	face[fNum].createFace(720);
	int counter = 0;
	for (int i = 0; i < 720; i += 1)
	{
		face[fNum].vert[counter].normIndex = i;
		face[fNum].vert[counter].vertIndex = i;
		counter++;
	}
	fNum++;
}

Mesh cylinder;

void timer(int value)
{
	const int desiredFPS = 120;
	glutTimerFunc(1000 / desiredFPS, timer, ++value);
	GLfloat dt = 1. / desiredFPS;

	gAngle += dt*360. / 8.; //rotate 360 degrees every 8 seconds

	glutPostRedisplay(); // initiate display() call at desiredFPS rate
}

void display() {
	// Will be called at FPS rate, ok to use global values now to rener scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0, 0, -100);
	glRotatef(gAngle, 1, 0, 1);

	cylinder.draw();

	glPopMatrix();

	glutSwapBuffers();
}

void init() {
	GLfloat mat_specular[] = { 1.0,1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLdouble Vol = 10/*10 * 1.8*/;
	GLdouble Left = -Vol;
	GLdouble Right = Vol;
	GLdouble Bottom = -Vol;
	GLdouble Top = Vol;
	GLdouble Near = 0;
	GLdouble Far = 2 * Vol;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(Left, Right, Bottom, Top, Near, Far);

	GLdouble eyeX = 0;
	GLdouble eyeY = 0;
	GLdouble eyeZ = -100 + Vol;
	GLdouble centerX = 0;
	GLdouble centerY = 0;
	GLdouble centerZ = -100/*-100*/;
	GLdouble upX = 1/*0*/;
	GLdouble upY = 0/*1*/;
	GLdouble upZ = 0/*0*/;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ,
		centerX, centerY, centerZ,
		upX, upY, upZ);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:  // escape key
		exit(0);
		break;
	default:
		break;
	}
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 10");

	cylinder.makeCylinder();

	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();
	return 0;
}