#include<stdlib.h>//initialises standard library
//#include <glut.h>//initialises glut on Jack's PC
#include<GL/glut.h> //<--- Use this one for using on the lab PC's
#include <math.h>//initialises math functions
#include "Image_Loader.h"//initialises image loader
using namespace std;//initialises the std class

#define X .525731112119133606//defines X value
#define Z .850650808352039932//defines Y value

int texture = 1;//sets texture value for toggle

Image* image;//pointer to first image
Image* image2;//pointer to second image
Image* image3;//pointer to third image

int xpos = 0;//int value of position x
int ypos = 0;//int value of position y
int zpos = 0;//int value of position z

int xlookat = 0;//int value of xlookat
int ylookat = 0;//int value of y lookat
int zlookat = 0;//int value of zlookat

int screenwidth = 800;//sets the default screenwidth
int screenheight = 800;//sets the default screen height

typedef GLfloat point3[3];//initialises array

void init(void)//init class
{
	glClearColor(0, 0, 0, 0);//color white
	glColor3f(1.0, 1.0, 1.0);//color black
	glLineWidth(3);//sets width of the drawing line
	glShadeModel(GL_FLAT);//sets the shade model to flat
	glEnable(GL_DEPTH_TEST);//enable depth test
	glEnable(GL_COLOR_MATERIAL);//enable color material
	glEnable(GL_LIGHTING);//enable lighting
	glEnable(GL_LIGHT1);//enable light 1
	glEnable(GL_LIGHT2);//enable light 2
	glEnable(GL_LIGHT3);//enable light 3

	image = loadBMP("metal1a.bmp");//loads image file
	image2 = loadBMP("Conc01.bmp");//loads image2 file
	image3 = loadBMP("stone1.bmp");//loads image3 file

	glEnableClientState(GL_VERTEX_ARRAY);//enables vertex array
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);//enables texture array 
}
void draw_floor()//draw_floor class
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//sets texture parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);//sets texture size
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//sets texture modes

	point3 floor_vertices[4] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 } };//vertex array for the floor
	point3 texture_coords[4] = { { 1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } };//texture array for the floor

	glVertexPointer(3, GL_FLOAT, 0, floor_vertices);//enables vertex pointer
	glTexCoordPointer(3, GL_FLOAT, 0, texture_coords);//enables texture pointer

	if (texture == 1)// if statment that toggles texture
	{
		glEnable(GL_TEXTURE_2D);//enables texture
	}
	glBegin(GL_QUADS);//fills coordinates
	glTexCoord2f(0.0f, 0.0f); glArrayElement(2);//draws array element
	glTexCoord2f(1.0f, 0.0f); glArrayElement(3);//draws array element
	glTexCoord2f(1.0f, 1.0f); glArrayElement(1);//draws array element
	glTexCoord2f(0.0f, 1.0f); glArrayElement(0);//draws array element
	glEnd();//ends draw

	glFlush();//flushes image
}
void draw_backwall()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//sets texture parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->width, image2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->pixels);//sets texture size
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//sets texture modes

	point3 backwall_vertices[4] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 } };//vertex array for the floor
	point3 texture_coords[4] = { { 1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } };//texture array for the floor

	glVertexPointer(3, GL_FLOAT, 0, backwall_vertices);//enables vertex pointer
	glTexCoordPointer(3, GL_FLOAT, 0, texture_coords);//enables texture pointer

	glBegin(GL_QUADS);//fills coordinates
	glTexCoord2f(0.0f, 0.0f); glArrayElement(0);//draws array element
	glTexCoord2f(1.0f, 0.0f); glArrayElement(1);//draws array element
	glTexCoord2f(1.0f, 1.0f); glArrayElement(2);//draws array element
	glTexCoord2f(0.0f, 1.0f); glArrayElement(3);//draws array element
	glEnd();//ends draw

	glFlush();//flushes image
}
void draw_leftwall()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//sets texture parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->width, image2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->pixels);//sets texture size
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//sets texture modes

	point3 backwall_vertices[4] = { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, 1.0 }, { -1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 } };//vertex array for the floor
	point3 texture_coords[4] = { { 1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } };//texture array for the floor

	glVertexPointer(3, GL_FLOAT, 0, backwall_vertices);//enables vertex pointer
	glTexCoordPointer(3, GL_FLOAT, 0, texture_coords);//enables texture pointer

	glBegin(GL_QUADS);//fills coordinates
	glTexCoord2f(0.0f, 0.0f); glArrayElement(0);//draws array element
	glTexCoord2f(1.0f, 0.0f); glArrayElement(1);//draws array element
	glTexCoord2f(1.0f, 1.0f); glArrayElement(2);//draws array element
	glTexCoord2f(0.0f, 1.0f); glArrayElement(3);//draws array element
	glEnd();//ends draw

	glFlush();//flushes image
}
void draw_rightwall()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//sets texture parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->width, image2->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2->pixels);//sets texture size
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//sets texture modes

	point3 backwall_vertices[4] = { { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0 }, { 1.0, -1.0, 1.0 } };//vertex array for the floor
	point3 texture_coords[4] = { { 1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } };//texture array for the floor

	glVertexPointer(3, GL_FLOAT, 0, backwall_vertices);//enables vertex pointer
	glTexCoordPointer(3, GL_FLOAT, 0, texture_coords);//enables texture pointer

	glBegin(GL_QUADS);//fills coordinates
	glTexCoord2f(0.0f, 0.0f); glArrayElement(0);//draws array element
	glTexCoord2f(1.0f, 0.0f); glArrayElement(1);//draws array element
	glTexCoord2f(1.0f, 1.0f); glArrayElement(2);//draws array element
	glTexCoord2f(0.0f, 1.0f); glArrayElement(3);//draws array element
	glEnd();//ends draw

	glFlush();//flushes image
}
void draw_ceiling()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//sets texture parameters
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image3->width, image3->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image3->pixels);//sets texture size
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//sets texture modes

	point3 backwall_vertices[4] = { { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 }, { -1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 } };//vertex array for the floor
	point3 texture_coords[4] = { { 1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } };//texture array for the floor

	glVertexPointer(3, GL_FLOAT, 0, backwall_vertices);//enables vertex pointer
	glTexCoordPointer(3, GL_FLOAT, 0, texture_coords);//enables texture pointer


	glBegin(GL_QUADS);//fills coordinates
	glTexCoord2f(0.0f, 0.0f); glArrayElement(0);//draws array element
	glTexCoord2f(1.0f, 0.0f); glArrayElement(1);//draws array element
	glTexCoord2f(1.0f, 1.0f); glArrayElement(2);//draws array element
	glTexCoord2f(0.0f, 1.0f); glArrayElement(3);//draws array element
	glEnd();//ends draw

	glDisable(GL_TEXTURE_2D);//disables textures

	glFlush();//flushes image
}
void back_wall_struts()//strut class
{
	glColor3f(0.3f, 0.3f, 0.3f);//sets the color to grey

	glPushMatrix();//push matrix
	glTranslatef(-750, 0, -750);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(750, 0, -750);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(375, 0, -750);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 0, -750);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-375, 0, -750);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void left_wall_struts()//strut class
{
	glColor3f(0.3f, 0.3f, 0.3f);//sets the color to grey

	glPushMatrix();//push matrix
	glTranslatef(-750, 0, 745);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-750, 0, 375);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-750, 0, 0);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-750, 0, -375);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void right_wall_struts()//strut class
{
	glColor3f(0.3f, 0.3f, 0.3f);//sets the color to grey

	glPushMatrix();//push matrix
	glTranslatef(750, 0, 750);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(750, 0, 375);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(750, 0, 0);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(750, 0, -375);//translate object
	glScalef(10, 400, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void ceiling_struts()//strut class
{
	glColor3f(0.3f, 0.3f, 0.3f);//sets the color to grey

	glPushMatrix();//push matrix
	glTranslatef(0, 200, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(375, 200, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-375, 200, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(750, 200, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-750, 200, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void horizontal_ceiling_struts()//strut class
{
	glColor3f(0.3f, 0.3f, 0.3f);//sets the color to grey

	glPushMatrix();//push matrix
	glTranslatef(0, 200, -750);//translate object
	glScalef(1500, 10, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 200, -375);//translate object
	glScalef(1500, 10, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 200, 0);//translate object
	glScalef(1500, 10, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 200, 375);//translate object
	glScalef(1500, 10, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 200, 750);//translate object
	glScalef(1500, 10, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void window_struts()//strut class
{
	glColor3f(0.3f, 0.3f, 0.3f);//sets the color to grey

	glPushMatrix();//push matrix
	glTranslatef(0, 30, -750);//translate object
	glScalef(1500, 10, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(750, 30, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-750, 30, 0);//translate object
	glScalef(10, 10, 1500);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void plane_feet()//plane class
{
	glPushMatrix();//push matrix
	glColor3f(0.3, 0.3, 0.3);//sets the color to grey
	glTranslatef(0, -195, 500);//translate object
	glScalef(500, 10, 25);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0.3, 0.3, 0.3);//sets the color to grey
	glTranslatef(0, -195, 300);//translate object
	glScalef(500, 10, 25);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0.3, 0.3, 0.3);//sets the color to grey
	glTranslatef(0, -170, 500);//translate object
	glScalef(25, 50, 25);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0.3, 0.3, 0.3);//sets the color to grey
	glTranslatef(0, -170, 300);;//translate object
	glScalef(25, 50, 25);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0.3, 0.3, 0.3);//sets the color to grey
	glTranslatef(0, -140, 400);//translate object
	glScalef(25, 15, 225);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void plane_body()//plane class
{
	glPushMatrix();//push matrix
	glColor3f(0, 1, 0);//sets the color to green
	glTranslatef(0, -50, 400);//translate object
	glScalef(30, 10, 10);//scale object
	glutSolidSphere(10, 100, 100);//draws sphere
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(1, 1, 1);//sets to color to black
	glTranslatef(-150, 0, 400);//translate object
	glScalef(50, 50, 250);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0.3, 0.3, 0.3);//sets the color to grey
	glTranslatef(250, 0, 400);//translate object
	glScalef(500, 50, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void plane_propellers()//plane class
{
	glPushMatrix();//push matrix
	glColor3f(0.5, 0.5, 0.5);//sets the color to grey
	glTranslatef(475, 0, 400);//translate object
	glScalef(1, 1, 1);//scale object
	glutSolidTorus(10, 20, 10, 10);//draws torus
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0, 0, 0);//sets the color to white
	glTranslatef(475, 65, 400);//translate object
	glScalef(20, 75, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0, 0, 0);//sets the color to white
	glTranslatef(540, 0, 400);//translate object
	glScalef(75, 20, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0, 0, 0);//sets the color to white
	glTranslatef(475, -60, 400);//translate object
	glScalef(20, 75, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0, 0, 0);//sets the color to white
	glTranslatef(410, 0, 410);//translate object
	glScalef(75, 20, 10);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0, 0, 0);//sets the color to white
	glTranslatef(0, 70, 400);//translate object
	glScalef(20, 90, 40);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glColor3f(0, 0, 0);//sets the color to white
	glTranslatef(0, 110, 400);//translate object
	glScalef(1000, 10, 40);//scale object
	glutSolidCube(1);//draws cube
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void draw_plane()//plane class
{
	glPushMatrix();//push matrix
	glTranslatef(0, 0, -600);//translate object
	plane_feet();//draws plane_feet
	plane_body();//draws plane_body
	plane_propellers();//draws plane_propellers
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void normalize(GLfloat *a)//normalize class
{
	GLfloat d = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);//calculates the square roots of vectors
	a[0] /= d; a[1] /= d; a[2] /= d;
}
void drawtri(GLfloat *a, GLfloat*b, GLfloat*c, int div, float r)//draws gasket
{
	if (div <= 0)
	{
		glNormal3fv(a); glVertex3f(a[0] * r, a[1] * r, a[2] * r);//sets the vertex
		glNormal3fv(b); glVertex3f(b[0] * r, b[1] * r, b[2] * r);//sets the vertex
		glNormal3fv(c); glVertex3f(c[0] * r, c[1] * r, c[2] * r);//sets the vertex
	}
	else
	{
		GLfloat ab[3], ac[3], bc[3];
		for (int i = 0; i<3; i++)
		{
			ab[i] = (a[i] + b[i]) / 2;//sets the vertex
			ac[i] = (a[i] + c[i]) / 2;//sets the vertex
			bc[i] = (b[i] + c[i]) / 2;//sets the vertex
		}
		normalize(ab); normalize(ac); normalize(bc);
		drawtri(a, ab, ac, div - 1, r);//displays triangle
		drawtri(b, bc, ab, div - 1, r);//displays triangle
		drawtri(c, ac, bc, div - 1, r);//displays triangle
		drawtri(ab, bc, ac, div - 1, r);  //comment this line out and it shows all the gaskets
	}
}
void recursive_sphere(int ndiv, float radius = 1.0)//draws sphere
{
	glColor3f(1, 1, 0);//sets color to yellow
	static GLfloat vdata[12][3] = { { -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },//vertex array   
	{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
	{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 } };

	static GLuint tindices[20][3] = { { 0, 4, 1 }, { 0, 9, 4 }, { 9, 5, 4 }, { 4, 5, 8 }, { 4, 8, 1 },//vertex array    
	{ 8, 10, 1 }, { 8, 3, 10 }, { 5, 3, 8 }, { 5, 2, 3 }, { 2, 7, 3 },
	{ 7, 10, 3 }, { 7, 6, 10 }, { 7, 11, 6 }, { 11, 0, 6 }, { 0, 1, 6 },
	{ 6, 1, 10 }, { 9, 0, 11 }, { 9, 11, 2 }, { 9, 2, 5 }, { 7, 2, 11 } };

	glBegin(GL_TRIANGLES);//begins triangle
	for (int i = 0; i<20; i++)
		drawtri(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], ndiv, radius);//draws triangle
	glEnd();
}
void init_ceiling_light()//draw light
{
	glColor3f(0, 0, 0);//sets the color to black
	point3 cube_vertices[8] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 },//vertex array
	{ 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
	{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 },
	{ 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

	GLubyte cube[24] = { 0, 3, 2, 1, 2, 3, 7, 6,//draws cube
		0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7 };

	glVertexPointer(3, GL_FLOAT, 0, cube_vertices);//enables vertex pointer

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube);//draws object
}
void ceiling_light()//draw light
{
	glPushMatrix();//push matrix
	glTranslatef(0, 0, -370);//translate object
	glScalef(15, 10, 100);//scale object
	init_ceiling_light();//draw init_ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 0, -450);//translate object
	recursive_sphere(5, 15);//draw recursive_sphere
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 0, -290);//translate object
	recursive_sphere(5, 15);//draw recursive_sphere
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void ceiling_lights()//draw light
{

	glPushMatrix();//push matrix
	glTranslatef(0, 175, 0);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(375, 175, 0);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-375, 175, 0);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 175, 375);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(375, 175, 375);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-375, 175, 375);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(0, 175, 750);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(375, 175, 750);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glPushMatrix();//push matrix
	glTranslatef(-375, 175, 750);//translate object
	ceiling_light();//draws ceiling_light
	glPopMatrix();//pop matrix

	glFlush();//flushes the image
}
void display(void)//display class
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clears the color and depth buffer 

	glMatrixMode(GL_MODELVIEW);//sets the matrix mode to modelview
	glLoadIdentity();//loads scene identity
	gluLookAt(0, 0, 1000, xlookat, ylookat, zlookat, 0, 1, 0);//sets the camera position

	glTranslatef(xpos, ypos, zpos);//translates the xyz coordinites of the lookat
	glRotatef(zlookat, 0, 1, 0);//rotoates the vlaues and the lookat

	GLfloat ambientColour[] = { 0.3f, 0.3f, 0.3f, 0.3f };//adds ambient light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColour);//adds ambient light

	GLfloat lightColour1[] = { 1.0f, 1.0f, 1.0f, 1.0f };//adds light colour
	GLfloat lightPos1[] = { 0.0f, 160.0f, 0.0f, 1.0f };//light position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColour1);//draws light
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);//draws light position

	GLfloat lightPos2[] = { 0.0f, 160.0f, 375.0f, 1.0f };//light position
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColour1);//draws light
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);//draws light position

	GLfloat lightPos3[] = { 0.0f, 160.0f, 750.0f, 1.0f };//light position
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColour1);//draws light
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos3);//draws light position

	glPushMatrix();//push the matrix
	glScalef(750, 200, 750);//scales the object
	draw_floor();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	glScalef(750, 200, 750);
	draw_backwall();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	glScalef(750, 200, 750);
	draw_leftwall();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	glScalef(750, 200, 750);
	draw_rightwall();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	glScalef(750, 200, 750);
	draw_ceiling();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	back_wall_struts();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	left_wall_struts();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	right_wall_struts();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	ceiling_struts();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	horizontal_ceiling_struts();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	window_struts();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	ceiling_lights();//draws object
	glPopMatrix();//pop the matrix

	glPushMatrix();//push the matrix
	draw_plane();//draws object
	glPopMatrix();//pop the matrix

	glutSwapBuffers();//swaps buffers
}
void wasdmovement(unsigned char key, int x, int y)//wasdmovment class
{
	switch (key)//switch statement
	{
	case 'w'://w case
		//zpos++;//adds 1 to zpos
		zpos = zpos + 20;
		break;//breaks the case
	case 'a'://a case
		//xpos++;//adds 1 to xpos
		xpos = xpos + 20;
		break;//breaks the case
	case 's'://s case
		//zpos --;//subtracts 1 from zpos
		zpos = zpos - 20;
		break;//breaks the case
	case 'd'://d case
		//xpos--;//subtracts 1 from xpos
		xpos = xpos - 20;
		break;//breaks the case
	case'q'://q case
		zlookat--;//subtracts 1 from zlookat
		break;//breaks the case
	case'e'://ecase
		zlookat++;//adds one to zlookat
		break;//breaks the case
	case 'r'://r case
		ypos = ypos - 20;//subtracts 20 from ypos
		break;//breaks the case
	case 'f'://f case
		ypos = ypos + 20;//adds 20 to ypos
		break;//breaks the case
	case 't'://tcase
		texture--;//subtracts 1 from texture
		break;//breaks the case
	case 'g'://gcase
		texture++;//adss 1 to texture
		break;//breaks the case
	}
	glutPostRedisplay();//calls the display function
}
void mousetoggle(int button, int state, int x, int y)//toggle class
{
	if (button == GLUT_LEFT_BUTTON)
	{
		glEnable(GL_LIGHTING);//enables lighiting
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		glDisable(GL_LIGHTING);//disables lighting
	}
	glutPostRedisplay();
}
void reshape(int w, int h)//reshape class
{
	w = screenwidth;//sest w to screenwidth
	h = screenheight;//sets h to screenheight
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//viewport mapping
	glMatrixMode(GL_PROJECTION);//sets the matrix mode to projection
	glLoadIdentity();//loads scene identity
	gluPerspective(60, 1, 1, 10000);//sets the perspective
	glMatrixMode(GL_MODELVIEW);//sets the matrix mode to modelview
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);//glut initialisation
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);//initilases the display mode
	glutInitWindowSize(screenwidth, screenheight);//defines the window size
	glutCreateWindow("Waddington air show");//creates the window with caption
	init();//initilises all of opengl
	//start of callback functions
	glutDisplayFunc(display);//callback of display function
	glutKeyboardFunc(wasdmovement);//callback of keyboard function
	glutMouseFunc(mousetoggle);
	glutReshapeFunc(reshape);
	glutMainLoop();//loop waiting for event
	//end of callback functions
}