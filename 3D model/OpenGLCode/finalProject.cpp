/************************************************************
 * Group        : 06                                        *
 * Group Members: LAI KAI CHIAN        A21EC0041            *
 *              : GAN QI YOU           A21EC0178            *
 *              : KRISTY YAP JING WEI  A21EC0191            *
 * Assignment 3 : Nohara Shiro (Crayon Shin-Chan)           *
 ************************************************************/

#include <stdlib.h>
#include <GL/glut.h> // Include the GLUT header file 
#include <math.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
#include"imageloader.h"
#include"imageloader.cpp"

using namespace std;
#define PI 3.1415927
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 900

// angle of rotation for the camera direction
float angle = 0.0, yAngle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = -3.0f, z = 75.0f;
float roll = 0.0f;

//conditions to limit the rotation of model
bool stillCanRaiseLeft = true;
bool stillCanRaiseRight = true;
bool stillCanWalkForward = true;
bool stillCanWalkBackward = true;
bool rotateHead = true;
bool rotateTail = true;
bool displayT = true;
bool rotateX = true;


//for mouse movements
float halfWidth = (float)(WINDOW_WIDTH / 2.0);
float halfHeight = (float)(WINDOW_HEIGHT / 2.0);
float mouseX = 0.0f, mouseY = 0.0f;

//variables
static int forwardlegCount = 0, backwardlegCount = 0;
static int stepsForward = 0, stepsBackward = 0;
float rotate1 = 0.0f;
float rotate2 = 0.0f;
float _increment = 1.5f;
static float headPos = 0.0f, headLeft = 0.0f, headRight = 0.0f;
static float leftEar = 0.0f, rightEar = 0.0f;
static float body = 0.0f, tail = 0.0f, tailRotate = 0.0f;
static float moveBodyForward = 0.0f, moveBodyBackward = 0.0f;
static float moveLeftForward = 0.0f, moveRightForward = 0.0f;
static float moveLeftBackward = 0.0f, moveRightBackward = 0.0f;
static float frontLeft = 0.0f, frontRight = 0.0f, backLeft = 0.0f;
static float backRight = 0.0f, frRightRotate = 0.0f, frLeftRotate = 0.0f;
static float leftLegsAngle = 90, rightLegsAngle = 90, rotateFull = 0.0f;
static float headAngle = 0.0f, rightEarAngle = 0.0f, leftEarAngle = 0.0f;

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

GLuint _textureId1;
GLuint _textureId2;
GLuint _textureId3;
GLuint _textureId4;
GLuint _textureId5;
GLuint _textureId6;


void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1600.0, 0.0, 800.0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading

	Image* image1 = loadBMP("C:\\zmisc\\picture1.bmp");
	_textureId1 = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("C:\\zmisc\\picture_2.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("C:\\zmisc\\picture_3.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("C:\\zmisc\\picture_4.bmp");
	_textureId4 = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("C:\\zmisc\\picture_5.bmp");
	_textureId5 = loadTexture(image5);
	delete image5;

	Image* image6 = loadBMP("C:\\zmisc\\picture_6.bmp");
	_textureId6 = loadTexture(image6);
	delete image6;
}

void head()
{
	glPushMatrix();
	glTranslatef(-1.1f, 1.5f, 0.0f);  
	glTranslatef(-1.1f, 1.5f, 0.0f);
	glRotatef(headLeft, 1.0f, 0.0f, 0.0f);		//rotate left
	glRotatef(headRight, 1.0f, 0.0f, 0.0f);     //rotate right
	glTranslatef(1.1f, -1.5f, 0.0f);

		//head
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(-1.0f, 3.0f, 0.0f);
			glScalef(3.5f, 5.0f, 9.0f);
			glutSolidSphere(0.25, 100, 100);
		glPopMatrix();

		//ring on neck
		glPushMatrix();
			glColor3f(0.3f, 0.4f, 1.0f);
			glTranslatef(-1.8f, 2.2f, 0.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			glRotatef(-30, 1.0f, 0.0f, 0.0f);
			glScalef(2.8f, 1.68f, 1.0f);
			GLUquadric* quadric = gluNewQuadric();
			gluQuadricDrawStyle(quadric, GLU_FILL);
			gluCylinder(quadric, 0.3, 0.3, 0.2, 50, 50);
		glPopMatrix();

		//right eye brow
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(-0.3f, 3.2f, 1.3f);
			glRotatef(75, 0.0f, 1.0f, 0.0f);
			glScalef(9.5f, 9.5f, 9.5f);
			gluPartialDisk(gluNewQuadric(), 0.0475f, 0.052f, 10, 30, 270, 180);
		glPopMatrix();

		//right eye
		glPushMatrix();
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(-0.3f, 3.0f, 1.3f);
			glScalef(1.5f, 1.5f, 1.5f);
			glutSolidSphere(0.11, 100, 100);
		glPopMatrix();

		//left eye brow
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(-0.3f, 3.2f, -1.3f);
			glRotatef(110, 0.0f, 1.0f, 0.0f);	//rotate eye brow to symmetric with face
			glScalef(9.5f, 9.5f, 9.5f);
			gluPartialDisk(gluNewQuadric(), 0.0475f, 0.052f, 10, 30, 270, 180);
		glPopMatrix();

		//left eye
		glPushMatrix();
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(-0.3f, 3.0f, -1.3f);
			glScalef(1.5f, 1.5f, 1.5f);
			glutSolidSphere(0.11, 100, 100);
		glPopMatrix();

		//nose, combination of circles
		glColor3f(0.0f, 0.0f, 0.0f);
		glPushMatrix();
			glTranslatef(-0.3f, 2.4f, 0.4f);
			glScalef(1.0f, 1.0f, 1.5f);
			glutSolidSphere(0.085, 100, 100);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.3f, 2.4f, 0.3f);
			glScalef(1.0f, 1.0f, 2.5f);
			glutSolidSphere(0.095, 100, 100);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.3f, 2.4f, 0.0f);
			glScalef(1.0f, 1.0f, 4.5f);
			glutSolidSphere(0.095, 100, 100);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.3f, 2.4f, -0.3f);
			glScalef(1.0f, 1.0f, 2.5f);
			glutSolidSphere(0.095, 100, 100);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.3f, 2.4f, -0.4f);
			glScalef(1.0f, 1.0f, 1.5f);
			glutSolidSphere(0.085, 100, 100);
		glPopMatrix();

		glPushMatrix(); //bottom
			glTranslatef(-0.4f, 2.35f, -0.02f);
			glRotated(270, -1.0, 0.0, 0.0);
			glScalef(1.0f, 1.0f, 1.0f);
			glutSolidCone(0.2, 0.2, 100, 100);
		glPopMatrix();

		//right ear
		glPushMatrix();							//connection of ear and head
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(-1.0f, 4.17f, 1.4f);
			glRotatef(-30, 1.0f, 0.0f, 0.0f);
			glScalef(1.5f, 0.6f, 1.5f);
			glutSolidSphere(0.25, 100, 100);
		glPopMatrix();

		//outer right ear
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(-1.0f, 1.6f, 0.8f);
			//pivot = (-2.0, 5.2, 1.6);
			glTranslatef(-1.0f, 2.6f, 0.8f);		//select point x = 2.0/2,  point y = 5.17/2, point z = 1.4/2
			glRotatef(rightEar, 1.0f, 0.0f, 0.0f);
			glTranslatef(1.0f, -2.6f, -0.8f);
			glPushMatrix();
				glTranslatef(0.0f, 1.9f, 1.5f);	   //test position of sphere to ensure it can rotate using the pivot
				glRotatef(50, 1.0f, 0.0f, 0.0f);   //to make the ear slightly inclined
				glScalef(1.5f, 1.2f, 4.0f);
				glutSolidSphere(0.25, 100, 100);
			glPopMatrix();
		glPopMatrix();

		//left ear
		glPushMatrix();							   //connection of ear and head
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(-1.0f, 4.17f, -1.6f);
			glRotatef(-150, 1.0f, 0.0f, 0.0f);
			glScalef(1.5f, 0.6f, 1.5f);
			glutSolidSphere(0.25, 100, 100);
		glPopMatrix();

		//outer left ear
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glTranslatef(-1.0f, 1.6f, -0.8f);
			//pivot = (-2.0, 5.2, 1.6);
			glTranslatef(-1.0f, 2.6f, -0.8f);	   //select point x = 2.0/2,  point y = 5.17/2, point z = 1.4/2
			glRotatef(leftEar, 1.0f, 0.0f, 0.0f);
			glTranslatef(1.0f, -2.6f, 0.8f);
			glPushMatrix();
				glTranslatef(0.0f, 1.9f, -1.7f);
				glRotatef(130, 1.0f, 0.0f, 0.0f);
				glScalef(1.5f, 1.2f, 4.0f);
				glutSolidSphere(0.25, 100, 100);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void bodyPart()
{
	//conection between body and head
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-3.4f, 3.0f, 0.0f);
		glScalef(1.0f, 1.3f, 2.0f);
		glutSolidSphere(0.89, 100, 100);
	glPopMatrix();

	//middle long body
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-7.0f + body, 3.0f, 0.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glScalef(2.0f, 1.3f, 1.0f);
		GLUquadric* quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluCylinder(quadric, 0.9, 0.9, 3.7, 50, 50);
	glPopMatrix();

	//conection between body and tail
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(-7.0f + body, 3.0f, 0.0f);
		glScalef(1.0f, 1.3f, 2.0f);
		glutSolidSphere(0.89, 100, 100);
	glPopMatrix();

	//tail
	glPushMatrix();
		glTranslatef(-3.8f, 1.8f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		//pivot = (-3.8f, 1.8f, 0.0f)
		glTranslatef(-3.8f, 1.8f, 0.0f);
		glRotatef(tailRotate, 1.0f, 0.0f, 0.0f);
		glTranslatef(3.8f, -1.8f, 0.0f);
		glPushMatrix();
			glTranslatef(-3.9f, 2.8f, 0.0f);		//test position to make it turn on pivot
			glRotatef(90, 1.0f, 0.0f, 0.0f);		//rotate to make it straight 
			glRotatef(40, 0.0f, 1.0f, 0.0f);		//then, rotate to make it inclined 
			glScalef(0.6f, 0.6f, 5.0f);
			glutSolidSphere(0.25, 100, 100);
		glPopMatrix();
	glPopMatrix();
}

void legPart()
{
	glPushMatrix();
		glTranslatef(-1.9f, 1.1f, 0.45f);
		//rotate about a pivot = (-3.8, 2.2, 0.9)
		glTranslatef(-1.9f, 1.1f, 0.45f);
		glRotatef(moveRightForward, 0.0f, 0.0f, 1.0f);
		glRotatef(moveRightBackward, 0.0f, 0.0f, 1.0f);
		glTranslatef(1.9f, -1.1f, -0.45f);
		//rightFront
		glPushMatrix();
			glTranslatef(-1.9f, 0.6f, 0.35f);
			
			glTranslatef(-1.9f, 0.6f, 0.35f);
			glRotatef(frontRight, 1.0f, 0.0f, 0.0f);
			glTranslatef(1.9f, -0.6f, -0.35f);
			glPushMatrix();
				glColor3f(1.0f, 1.0f, 1.0f);
				glTranslatef(-0.1f, 0.5f, 0.2f);   
				glRotatef(90, 1.0f, 0.0f, 0.0f);
				GLUquadric* quadric = gluNewQuadric();
				gluQuadricDrawStyle(quadric, GLU_FILL);
				gluCylinder(quadric, 0.3, 0.3, 0.9, 50, 50);
			glPopMatrix();
			//lower part
			glPushMatrix();
				glTranslatef(-0.2f, -0.12f, 0.1f);
				//rotate about a pivot = (-0.4, -0.24, 0.2) 
				glTranslatef(-0.2f, -0.12f, 0.1f);  
				glRotatef(frRightRotate, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.2f, 0.12f, -0.1f);
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(0.1f, -0.2f, 0.1f);    
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					gluQuadricDrawStyle(quadric, GLU_FILL);
					gluCylinder(quadric, 0.295, 0.295, 1.0, 50, 50);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//rightback
	glPushMatrix();
		glTranslatef(-3.4f, 1.2f, 0.65f);
		//rotate about a pivot = (-6.8, 2.4, 1.3)
		glTranslatef(-3.4f, 1.2f, 0.65f);
		glRotatef(moveRightForward, 0.0f, 0.0f, 1.0f);
		glRotatef(moveRightBackward, 0.0f, 0.0f, 1.0f);
		glTranslatef(3.4f, -1.2f, -0.65f);
		
			glPushMatrix();
				glTranslatef(-3.4f, 0.7f, 0.25f);
				//rotate about a pivot = (-6.8, 1.4, 0.5)
				glTranslatef(-3.4f, 0.7f, 0.25f);
				glRotatef(backRight, 1.0f, 0.0f, 0.0f);
				glTranslatef(3.4f, -0.7f, -0.25f);
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(0.1f, 0.3f, 0.0f);
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					gluQuadricDrawStyle(quadric, GLU_FILL);
					gluCylinder(quadric, 0.3, 0.3, 0.9, 50, 50);
				glPopMatrix();
				//lower part
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(0.1f, -0.5f, 0.0f);
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					gluQuadricDrawStyle(quadric, GLU_FILL);
					gluCylinder(quadric, 0.295, 0.295, 1.0, 50, 50);
				glPopMatrix();
			glPopMatrix();
	glPopMatrix();

	//leftFront
	glPushMatrix();
		glTranslatef(-1.9f, 1.1f, -0.45f);
		//rotate about a pivot = (-3.8, 2.2, -0.9)
		glTranslatef(-1.9f, 1.1f, -0.45f);
		glRotatef(moveLeftForward, 0.0f, 0.0f, 1.0f);
		glRotatef(moveLeftBackward, 0.0f, 0.0f, 1.0f);
		glTranslatef(1.9f, -1.1f, 0.45f);
	
			glPushMatrix();
				glTranslatef(-1.9f, 0.6f, -0.35f);
				//rotate about a pivot = (-3.8, 1.2, -0.7)
				glTranslatef(-1.9f, 0.6f, -0.35f);
				glRotatef(frontLeft, 1.0f, 0.0f, 0.0f);
				glTranslatef(1.9f, -0.6f, 0.35f);
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(-0.1f, 0.5f, -0.2f);
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					gluQuadricDrawStyle(quadric, GLU_FILL);
					gluCylinder(quadric, 0.3, 0.3, 0.9, 50, 50);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-0.2f, -0.12f, -0.1f);
					//rotate about a pivot = (-0.4, -0.24, -0.2)
					glTranslatef(-0.2f, -0.12f, -0.1f);
					glRotatef(frLeftRotate, 1.0f, 0.0f, 0.0f);
					glTranslatef(0.2f, 0.12f, 0.1f);
					glPushMatrix();
						glColor3f(1.0f, 1.0f, 1.0f);
						glTranslatef(0.1f, -0.2f, -0.1f);          
						glRotatef(90, 1.0f, 0.0f, 0.0f);
						gluQuadricDrawStyle(quadric, GLU_FILL);
						gluCylinder(quadric, 0.295, 0.295, 1.0, 50, 50);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
	glPopMatrix();

	//rightback
	glPushMatrix();
		glTranslatef(-3.4f, 1.2f, -0.65f);
		//rotate about a pivot = (-6.8, 2.4, 1.3)
		glTranslatef(-3.4f, 1.2f, -0.65f);
		glRotatef(moveLeftForward, 0.0f, 0.0f, 1.0f);
		glRotatef(moveLeftBackward, 0.0f, 0.0f, 1.0f);
		glTranslatef(3.4f, -1.2f, 0.65f);
		
			glPushMatrix();
				glTranslatef(-3.4f, 0.7f, -0.25f);
				//rotate about a pivot = (-6.8, 2.4, 1.3)
				glTranslatef(-3.4f, 0.7f, -0.25f);
				glRotatef(backLeft, 1.0f, 0.0f, 0.0f);
				glTranslatef(3.4f, -0.7f, 0.25f);
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(0.1f, 0.3f, 0.0f);
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					gluQuadricDrawStyle(quadric, GLU_FILL);
					gluCylinder(quadric, 0.3, 0.3, 0.9, 50, 50);
				glPopMatrix();
				//lower part
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(0.1f, -0.5f, 0.0f);
					glRotatef(90, 1.0f, 0.0f, 0.0f);
					gluQuadricDrawStyle(quadric, GLU_FILL);
					gluCylinder(quadric, 0.295, 0.295, 1.0, 50, 50);
				glPopMatrix();
			glPopMatrix();
	glPopMatrix();
}

void home()
{
	glPushMatrix();
		// Draw floor
		glColor3f(0.0f, 0.8f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(-20.0f, 0.0f, -20.0f);
		glVertex3f(-20.0f, 0.0f, 20.0f);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(20.0f, 0.0f, 20.0f);
		glVertex3f(20.0f, 0.0f, -20.0f);
		glEnd();

		glColor3f(0.9f, 1.0f, 0.8f);           //wall behind
		glBegin(GL_QUADS);
		glVertex3f(-20.0f, 0.0f, -20.0f);
		glVertex3f(-20.0f, 0.0f, 20.0f);
		glVertex3f(-20.0f, 20.0f, 20.0f);
		glVertex3f(-20.0f, 20.0f, -20.0f);
		glEnd();

		glColor3f(0.9f, 1.0f, 0.8f);         //wall in front
		glBegin(GL_QUADS);
		glVertex3f(20.0f, 0.0f, 20.0f);
		glVertex3f(20.0f, 0.0f, -20.0f);
		glVertex3f(20.0f, 20.0f, -20.0f);
		glVertex3f(20.0f, 20.0f, 20.0f);
		glEnd();

		glColor3f(1.0f, 0.9f, 0.4f);		 //wall at left
		glBegin(GL_QUADS);
		glVertex3f(20.0f, 0.0f, -20.0f);
		glVertex3f(-20.0f, 0.0f, -20.0f);
		glVertex3f(-20.0f, 20.0f, -20.0f);
		glVertex3f(20.0f, 20.0f, -20.0f);
		glEnd();

		glColor3f(0.8f, 0.7f, 1.0f);         //wall at right / open door
		glBegin(GL_QUADS);
		glVertex3f(20.0f, 0.0f, 20.0f);
		glVertex3f(20.0f, 20.0f, 20.0f);
		glVertex3f(5.0f, 20.0f, 20.0f);
		glVertex3f(5.0f, 0.0f, 20.0f);

		glVertex3f(-20.0f, 0.0f, 20.0f);
		glVertex3f(-20.0f, 20.0f, 20.0f);
		glVertex3f(-5.0f, 20.0f, 20.0f);
		glVertex3f(-5.0f, 0.0f, 20.0f);

		glVertex3f(-5.0f, 10.0f, 20.0f);    //upper wall
		glVertex3f(-5.0f, 20.0f, 20.0f);
		glVertex3f(5.0f, 20.0f, 20.0f);
		glVertex3f(5.0f, 10.0f, 20.0f);
		glEnd();
	glPopMatrix();

	glPushMatrix();                     //upper wall with name
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(0.0f, 15.0f, 20.2f);
		glScalef(4.9f, 4.9f, 0.1f);
		glutSolidCube(2.0f);
	glPopMatrix();


	//name
	glPushMatrix();
		glColor3f(0.3f, 0.1f, 1.0f);
		glTranslatef(-2.5f, 16.3f, 20.5f);
		glRotatef(-30, 0.0f, 0.0f, 1.0f);
		glScalef(1.1f, 0.4f, 0.2f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//name
	glPushMatrix();
		glColor3f(0.3f, 0.1f, 1.0f);
		glTranslatef(-3.5f, 14.5f, 20.5f);
		glRotatef(-25, 0.0f, 0.0f, 1.0f);
		glScalef(0.9f, 0.4f, 0.2f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//name
	glPushMatrix();
		glColor3f(0.3f, 0.1f, 1.0f);
		glTranslatef(-1.8f, 13.7f, 20.5f);
		glRotatef(50, 0.0f, 0.0f, 1.0f);
		glScalef(2.0f, 0.4f, 0.2f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//name
	glPushMatrix();
		glColor3f(0.3f, 0.1f, 1.0f);
		glTranslatef(2.5f, 14.5f, 20.5f);
		glScalef(1.9f, 1.9f, 0.2f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//name
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(2.5f, 14.4f, 20.7f);
		glScalef(1.3f, 1.3f, 0.2f);
		glutSolidCube(2.0f);
	glPopMatrix();


	glColor3f(0.2f, 0.0f, 0.5f);         //roof
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 30.0f, 0.0f);
	glVertex3f(-20.0f, 20.0f, 20.0f);
	glVertex3f(20.0f, 20.0f, 20.0f);
	glVertex3f(20.0f, 20.0f, -20.0f);
	glVertex3f(-20.0f, 20.0f, -20.0f);
	glVertex3f(-20.0f, 20.0f, 20.0f);
	glEnd();

	glPushMatrix();						//bowl
		glColor3f(0.4f, 0.1f, 0.5f);
		glTranslatef(-17.0f, 0.5f, -10.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glScalef(2.0f, 1.5f, 1.0f);
		GLUquadric* quadric = gluNewQuadric();
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluCylinder(quadric, 0.5, 0.9, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();                      //bottom of bowl
		glColor3f(0.4f, 0.1f, 0.5f);
		glTranslatef(-17.0f, 0.01f, -10.0f);
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glScalef(2.0f, 1.5f, 1.0f);
		gluDisk(quadric, 0.0, 0.9, 50, 50);
	glPopMatrix();
	
	//window
	glPushMatrix();
		glColor3f(0.0f, 1.0f, 1.0f);
		glTranslatef(-12.5f, 6.0f, 20.0f);
		glScalef(2.0f, 2.0f, 0.2f);
		glutSolidCube(3.5);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.0f, 1.0f, 1.0f);
		glTranslatef(12.5f, 6.0f, 20.0f);
		glScalef(2.0f, 2.0f, 0.2f);
		glutSolidCube(3.5);
	glPopMatrix();

	//window border
	glColor3f(0.1f, 0.1f, 0.1f);
	glLineWidth(15.0f);
	glPushMatrix();
		glTranslatef(0.0f, 2.5f, 20.3f);
		glBegin(GL_LINES);
		glVertex3f(-9.0f, 0.0f, 0.0f);     //right
		glVertex3f(-9.0f, 7.0f, 0.0f);
		glVertex3f(-9.0f, 7.0f, 0.0f);     //up
		glVertex3f(-16.0f, 7.0f, 0.0f);
		glVertex3f(-16.0f, 7.0f, 0.0f);    //left
		glVertex3f(-16.0f, 0.0f, 0.0f);
		glVertex3f(-16.0f, 0.0f, 0.0f);    //down
		glVertex3f(-9.0f, 0.0f, 0.0f);
		glEnd();
	glPopMatrix();

	//window border
	glColor3f(0.1f, 0.1f, 0.1f);
	glLineWidth(15.0f);
	glPushMatrix();
		glTranslatef(25.0f, 2.5f, 20.3f);
		glBegin(GL_LINES);
		glVertex3f(-9.0f, 0.0f, 0.0f);     //right
		glVertex3f(-9.0f, 7.0f, 0.0f);
		glVertex3f(-9.0f, 7.0f, 0.0f);     //up
		glVertex3f(-16.0f, 7.0f, 0.0f);
		glVertex3f(-16.0f, 7.0f, 0.0f);    //left
		glVertex3f(-16.0f, 0.0f, 0.0f);
		glVertex3f(-16.0f, 0.0f, 0.0f);    //down
		glVertex3f(-9.0f, 0.0f, 0.0f);
		glEnd();
	glPopMatrix();

	//stand for spinning cube
	//top
	glPushMatrix();
		glColor3f(0.6f, 0.2f, 0.7f);
		glTranslatef(6.0f, 7.0f, -13.0f);
		glScalef(3.7f, 0.3f, 0.5f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//bottom
	glPushMatrix();
		glColor3f(0.6f, 0.2f, 0.7f);
		glTranslatef(6.0f, 0.6f, -13.0f);
		glScalef(3.7f, 0.3f, 0.5f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//left
	glPushMatrix();
		glColor3f(1.0f, 0.5f, 1.0f);
		glTranslatef(9.4f, 3.8f, -13.0f);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glScalef(2.9f, 0.3f, 0.5f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//right
	glPushMatrix();
		glColor3f(1.0f, 0.5f, 1.0f);
		glTranslatef(2.6f, 3.8f, -13.0f);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glScalef(2.9f, 0.3f, 0.5f);
		glutSolidCube(2.0f);
	glPopMatrix();
	//middle top
	glPushMatrix();
		glColor3f(0.6f, 0.2f, 0.7f);
		glTranslatef(6.0f, 4.0f, -13.0f);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glScalef(3.2f, 0.1f, 0.1f);
		glutSolidCube(2.0f);
	glPopMatrix();

}

void renderBitmap(float _x, float _y, float _z, void* font, char* string)
{
	char* c;
	
	glRasterPos3f(_x, _y, _z);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void displayText()
{
	char buf[100] = { 0 };
	glColor3f(0.0f, 0.0f, 0.0f);
	
	sprintf_s(buf, "Press 'p' to move forward, 'P' to move backward.");
	renderBitmap(-10.0, 13.0, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'j' to rotate tail(right), 'J' to rotate tail(left).");
	renderBitmap(-10.0, 12.6, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'h' to rotate whole model(clockwise)");
	renderBitmap(-10.0, 12.2, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'H' to rotate whole model(clockwise).");
	renderBitmap(-10.0, 11.8, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'q' to set back camera view position.");
	renderBitmap(-10.0, 11.4, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'x' to rotate tail(right), 'z' to rotate tail(left).");
	renderBitmap(-10.0, 11.0, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'm' or 'M' to start or stop playing music.");
	renderBitmap(-10.0, 10.6, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'u' to move right ear(up), 'U' to move right ear(down).");
	renderBitmap(-10.0, 10.2, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'i' to move left ear(up), 'I' to move left ear(down).");
	renderBitmap(-10.0, 9.8, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'k' to move entire left leg(up and down)");
	renderBitmap(-10.0, 9.4, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'l' to move entire right leg(up and down)");
	renderBitmap(-10.0, 9.0, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'o' to rotate head(right)");
	renderBitmap(-10.0, 8.6, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'O' to rotate head(left)");
	renderBitmap(-10.0, 8.2, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 't' to rotate lower front right leg (inner)");
	renderBitmap(-10.0, 7.8, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'T' to rotate lower front right leg (outer)");
	renderBitmap(-10.0, 7.4, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'y' to rotate lower front left leg (inner)");
	renderBitmap(-10.0, 7.0, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'Y' to rotate lower front left leg (outer)");
	renderBitmap(-10.0, 6.6, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'v' or 'V' to display or close these text");
	renderBitmap(-10.0, 6.2, -7.0, GLUT_BITMAP_9_BY_15, buf);
	sprintf_s(buf, "Press 'b' or 'B' to change rotation of cube");
	renderBitmap(-10.0, 5.8, -7.0, GLUT_BITMAP_9_BY_15, buf);
}

void food()
{
	glPushMatrix();
	glTranslatef(-17.5f, 0.0f, -10.5f);
	for (int k = 5; k > 0; k--)
	{
		int m = 0;
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				glPushMatrix();
				glColor3f(0.9, 0.6+0.07*i, 0.0+0.07*j);
				glTranslatef(i * 0.2 + 0.2f, m*0.1+0.2f, j * 0.2 + 0.2f);
				glScalef(0.2f, 0.2f, 0.2f);
				glutSolidCube(1.0);
				glPopMatrix();
			}
			m += 1;
		}
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-17.9f, 0.0f, -10.5f);
	for (int k = 5; k > 0; k--)
	{
		int m = 0;
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				glPushMatrix();
				glColor3f(0.9, 0.6 + 0.07 * i, 0.0 + 0.07 * j);
				glTranslatef(i * 0.2 + 0.2f, m * 0.1 + 0.2f, j * 0.2 + 0.2f);
				glScalef(0.2f, 0.2f, 0.2f);
				glutSolidCube(1.0);
				glPopMatrix();
			}
			m += 1;
		}
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-16.8f, 0.0f, -10.5f);
	for (int k = 3; k > 0; k--)
	{
		int m = 0;
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < k; j++)
			{
				glPushMatrix();
				glColor3f(0.9, 0.6 + 0.07 * i, 0.0 + 0.07 * j);
				glTranslatef(i * 0.2 + 0.2f, m * 0.1 + 0.2f, j * 0.2 + 0.2f);
				glScalef(0.2f, 0.2f, 0.2f);
				glutSolidCube(1.0);
				glPopMatrix();
			}
			m += 1;
		}
	}
	glPopMatrix();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//Clear the colour buffer and depth buffer
	glLoadIdentity();											// Load the Identity Matrix to reset our drawing locations 
	glMatrixMode(GL_MODELVIEW);									// Use the Modelview Matrix(is a must to set the view of gluLookAt)

	GLfloat ambientColor[] = { 0.3f, 0.3f, 0.3f, 1.0f };       //lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);       //specify ambient RGBA intensity of entire scene / lighting model parameter

	GLfloat lightColor0[] = { 0.4f, 0.4f, 1.0f, 1.0f };			//lightblue source light
	GLfloat lightPos0[] = { -4.0f, 1.5f, 4.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	GLfloat lightColor1[] = { 0.4f, 0.5f, 0.4f, 1.0f };          //lightyellow source light
	GLfloat lightPos1[] = { 4.0f, 1.5f, 4.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	//set camera
	gluLookAt(x, 4.5f, z, x + lx, 4.5f + ly, z + lz, roll, 4.5f, 0.0f);

	glPushMatrix();
		glTranslatef(6.0f, 3.5f, -13.0f);
		//front
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glScaled(3.5, 3.5, 3.5);
			glRotated(rotate1, 0.0, 1.0, 0.0);
			glRotated(rotate2, 1.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);		glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);		glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
		glPopMatrix();
		
		//right
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId2);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glScaled(3.5, 3.5, 3.5);
			glRotated(rotate1, 0.0, 1.0, 0.0);
			glRotated(rotate2, 1.0, 0.0, 0.0);
			glRotated(90, 0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);		glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);		glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
		glPopMatrix();

		//left
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId3);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glScaled(3.5, 3.5, 3.5);
			glRotated(rotate1, 0.0, 1.0, 0.0);
			glRotated(rotate2, 1.0, 0.0, 0.0);
			glRotated(-90, 0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);		glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);		glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
		glPopMatrix();

		//behind
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId4);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glScaled(3.5, 3.5, 3.5);
			glRotated(rotate1, 0.0, 1.0, 0.0);
			glRotated(rotate2, 1.0, 0.0, 0.0);
			glTranslated(0, 0, -1.0);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);		glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);		glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
		glPopMatrix();

		//top
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId5);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glScaled(3.5, 3.5, 3.5);
			glRotated(rotate1, 0.0, 1.0, 0.0);
			glRotated(rotate2, 1.0, 0.0, 0.0);
			glRotated(-90, 1.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);		glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);		glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
		glPopMatrix();

		//bottom
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId6);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glColor3f(1.0f, 1.0f, 1.0f);
			glScaled(3.5, 3.5, 3.5);
			glRotated(rotate1, 0.0, 1.0, 0.0);
			glRotated(rotate2, 1.0, 0.0, 0.0);
			glRotated(90, 1.0, 0.0, 0.0);
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);		glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);		glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);		glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);		glVertex3f(0.5f, -0.5f, 0.5f);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	home();
	food();
	//full set of Nohara Shiro
	glPushMatrix();
		glRotatef(rotateFull, 0.0f, 0.0f, 1.0f);
		glTranslatef(moveBodyForward, 0.0f, 0.0f);
		glTranslatef(moveBodyBackward, 0.0f, 0.0f);
		head();
		bodyPart();
		legPart();
	glPopMatrix();

	if (z < 18.0 && displayT) {
		displayText();	
	}

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int xx, int yy) {
	float fraction = 0.4f;
	if (key == 'w')
	{
		x += lx * fraction;
		z += lz * fraction;
	}
	else if (key == 'a')
	{
		x += sin(angle - PI / 2.0) * fraction;
		z += -cos(angle - PI / 2.0) * fraction;
	}
	else if (key == 's')
	{
		x -= lx * fraction;
		z -= lz * fraction;
	}
	else if (key == 'd')
	{
		x += sin(PI / 2.0 + angle) * fraction;
		z += -cos(PI / 2.0 + angle) * fraction;
	}
	else if (key == 'x')    //rotation clockwise
	{
		roll += 0.5f;
	}
	else if (key == 'z')   //rotation anticlockwise
	{
		roll -= 0.5f;
	}
	else if (key == 'q')  //set back the camera view position
	{
		x = -3.0f;
		z = 75.0f;
		roll = 0.0f;
	}
	else if (key == 'v')     //close text
	{
		displayT = FALSE;
	}
	else if (key == 'V')     //display text
	{
		displayT = TRUE;
	}
	else if (key == 'b')
	{
		rotateX = false;
	}
	else if (key == 'B')
	{
		rotateX = true;
	}

	//below buttons enables movement on the model
	else if (key == 'h') //rotate full model in z axis (clockwise)
	{
		rotateFull -= 1.0f;
		glutPostRedisplay();
	}
	else if (key == 'H')  //rotate full model in z axis (anti-clockwise)
	{
		rotateFull += 1.0f;
		glutPostRedisplay();
	}
	else if (key == 'm')
	{
		PlaySound(TEXT("C:\\zmisc\\song_to_play.wav"), NULL, SND_ASYNC);
	}
	else if (key == 'M')
	{
		PlaySound(NULL, 0, 0);
	}
	else if (key == 'j')  //move tail right 
	{
		if (tailRotate <= 40)
		{
			tailRotate += 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'J')  //move tail left
	{
		if (tailRotate >= -40)
		{
			tailRotate -= 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'u')  //move right ear to up
	{
		if(rightEar >= -20)
		{ 
			rightEar -= 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'U') //move right ear to down
	{
		if (rightEar< 0)
		{
			rightEar += 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'i')  //move left ear to up
	{
		if (leftEar <= 20)
		{
			leftEar += 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'I')  //move left ear to down
	{
		if (leftEar > 0)
		{
			leftEar -= 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'k') //move entire left legs(front and back)
	{
		if (stillCanRaiseLeft && leftLegsAngle < 135)  //move legs up
		{
			frontLeft += 1.0f;
			backLeft += 1.0f;
			leftLegsAngle += 1.0;
		}
		else
		{
			stillCanRaiseLeft = false;
		}

		if (!stillCanRaiseLeft && leftLegsAngle >= 90) //move legs down
		{
			frontLeft -= 1.0f;
			backLeft -= 1.0f;
			leftLegsAngle -= 1.0;
		}
		else
		{
			stillCanRaiseLeft = true;
		}
		glutPostRedisplay();
	}
	else if (key == 'l') //move entire right legs(front and back)
	{
		if (stillCanRaiseRight && rightLegsAngle > 45) //move legs up
		{
			frontRight -= 1.0f;
			backRight -= 1.0f;
			rightLegsAngle -= 1.0f;
		}
		else
		{
			stillCanRaiseRight = false;
		}

		if (!stillCanRaiseRight && rightLegsAngle <= 90) //move legs down
		{
			frontRight += 1.0f;
			backRight += 1.0f;
			rightLegsAngle += 1.0f;
		}
		else
		{
			stillCanRaiseRight = true;
		}
		glutPostRedisplay();
	}
	else if (key == 'o') //head rotate right
	{
		if (headAngle >= 0 && headAngle <= 30)  //rotate from origin
		{
			headLeft += 1.0f;
			headAngle += 1.0f;
		}
		else if (headAngle <= 0)  //rotate to right from left side
		{
			headLeft += 1.0f;
			headAngle += 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'O') //head rotate left
	{
		if (headAngle <= 0 && headAngle >= -30)  //rotate from origin
		{
			headRight -= 1.0f;
			headAngle -= 1.0f;
		}
		if (headAngle >=0) //rotate to left from right side
		{
			headRight -= 1.0f;
			headAngle -= 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 't') //rotate lower front right leg(inner)
	{
		if (frRightRotate <= 30)
		{
			frRightRotate += 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'T')   //rotate lower front right leg(outer)
	{
		if (frRightRotate >= -30)
		{
			frRightRotate -= 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'y') //rotate lower front left leg(inner)
	{
		if (frLeftRotate >= -30)
		{
			frLeftRotate -= 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'Y')  //rotate lower front left leg(outer)
	{
		if (frLeftRotate <= 30)
		{
			frLeftRotate += 1.0f;
		}
		glutPostRedisplay();
	}
	else if (key == 'p')  //move forward
	{
		if (stepsBackward > 0)
		{
			stepsBackward -= 1;
			stillCanWalkBackward = true;
		}
		if (stillCanWalkForward)
		{
			if (forwardlegCount % 2 == 0)
			{
				moveRightForward += 10;
				forwardlegCount++;
				stepsForward += 1;
			}
			else if (forwardlegCount % 2 != 0)
			{
				moveLeftForward += 10;
				forwardlegCount++;
				stepsForward += 1;
			}

			if (stepsForward <= 5)
			{
				moveBodyForward += 2.0f;
				if (forwardlegCount % 2 == 0)
				{
					moveRightForward -= 10;
				}
				else if (forwardlegCount % 2 != 0)
				{
					moveLeftForward -= 10;
				}
			}
			else
			{
				moveRightForward -= 10;
				stillCanWalkForward = false;
			}
		}
		glutPostRedisplay();
	}
	else if (key == 'P')  //move backward
	{
		if (stillCanWalkBackward)
		{
			if (stepsForward > 0)
			{
				stepsForward -= 1;
				stillCanWalkForward = true;
			}
			if (backwardlegCount % 2 == 0)
			{
				moveRightBackward -= 10;
				backwardlegCount++;
				stepsBackward += 1;
			}
			else if (backwardlegCount % 2 != 0)
			{
				moveLeftBackward -= 10;
				backwardlegCount++;
				stepsBackward += 1;
			}

			if (stepsBackward <= 5)
			{
				moveBodyBackward -= 2.0f;
				if (backwardlegCount % 2 == 0)
				{
					moveRightForward += 10;
				}
				else if (backwardlegCount % 2 != 0)
				{
					moveLeftForward += 10;
				}
			}
			else
			{
				moveRightBackward += 10;
				stillCanWalkBackward = false;
			}
		}
		glutPostRedisplay();
	}

	if (key == 27)
		exit(0);
}

void processMouseMovement(int xx, int yy) 
{
	mouseX = (float)(halfWidth - xx) / halfWidth;
	mouseY = (float)(halfHeight - yy) / halfHeight;
	angle -= (0.005f * mouseX);
	lx = sin(angle);
	lz = -cos(angle);

	if (abs(yAngle) < (PI / 2)) {
		yAngle += (0.005f * mouseY);
	}
	ly = sin(yAngle);
}

void update(int value)
{
	if (rotateX)
	{
		rotate1 += _increment;
		if (rotate1 > 360)
		{
			rotate1 -= 360;
		}
	}
	else {
		rotate2 += _increment;
		if (rotate2 > 360)
		{
			rotate2 -= 360;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

void reshape(int w, int h)
{ 
	//light source move together with viewport
	GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);										// Initialize GLUT 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);			// Set the width and height of the window 
	glutInitWindowPosition(50, 50);								// Set the position of the window 
	glutCreateWindow("Nohara Shiro (Crayon Shin-Chan)");		// Set the title for the window 
	init();														// call the initial condition function

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);									// Tell GLUT to use the method "display" for rendering 
	glutPassiveMotionFunc(processMouseMovement);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(display);
	glutTimerFunc(25, update, 0);
	glutMainLoop();												// Enter GLUT's main loop 

	return 0;
}