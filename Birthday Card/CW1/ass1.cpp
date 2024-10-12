// File ID: ASS1.cpp
// Title: Birthday Card
// Author: Enze Zhou
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <Math.h>
#include <iostream>
#include "stdio.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


using namespace std;
void define_to_OpenGL();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(320, 150);
	glutCreateWindow("Birthdat Card");
	glutDisplayFunc(define_to_OpenGL);
	glutMainLoop();
}

void define_to_OpenGL()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//This draws reference axes
	glColor3f(0.0, 0.0, 0.0);
	glLineStipple(2, 0x5555);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	//The roof
	glColor3f(255.0 / 255.0, 66.0 / 255.0, 14.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.8, 0.3);
	glVertex2f(1.0, 0.88);
	glVertex2f(1.0, 0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.7, 0.5);
	glVertex2f(1.0, 0.88);
	glVertex2f(0.8, 0.3);
	glEnd();

	//The chimney
	glColor3f(153.0 / 255.0, 204.0 / 255.0, 255.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.7, -0.5);
	glVertex2f(0.7, 0.5);
	glVertex2f(0.8, 0.3);
	glVertex2f(0.8, -0.7);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.8, -0.7);
	glVertex2f(0.8, 0.3);
	glVertex2f(1.0, 0.3);
	glVertex2f(1.0, -0.7);
	glEnd();

	//The door
	glColor3f(102.0 / 255.0, 51.0 / 255.0, 0.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.725, -0.55);
	glVertex2f(0.725, -0.05);
	glVertex2f(0.775, -0.15);
	glVertex2f(0.775, -0.65);
	glEnd();
	glFlush();

	//The road
	glColor3f(222 / 255.0, 184 / 255.0, 135 / 255.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.7, -0.65);
	glVertex2f(-0.75, -0.55);
	glVertex2f(0.725, -0.55);
	glVertex2f(0.775, -0.65);
	glEnd();
	glFlush();

	// Draw vertical lines for the sides of the gate
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-0.85, -0.35);  
	glVertex2f(-0.85, -0.15);  
	glVertex2f(-0.575, -0.90);  
	glVertex2f(-0.575, -0.70);  
	glEnd();
	glFlush();
	//I tried to make two congruent triangle so that the distance between the two sides of the road was the same,
	// but it did not look very good visually. The door frame in the southeast was made larger,and it's aslo the similar triangle
	

	//// The arch (semi-circular gate) at the end of the road
	//glColor3f(128.0 / 255.0, 64.0 / 255.0, 0.0 / 255.0);  // Brown color for the gate
	//float centerX = -0.725, centerY = -0.4, radius = 0.028;
	//int numSegments = 50;  // The number of segments used to approximate the arc
	//glBegin(GL_TRIANGLE_FAN);
	//glVertex2f(centerX, centerY);  // Center of the circle (bottom of the arch)
	//for (int i = 0; i <= numSegments; ++i) {
	//	float theta = (i / (float)numSegments) * M_PI;  // Angle in radians (0 to ¦Ð)
	//	float x = radius * cos(theta);
	//	float y = radius * sin(theta);
	//	glVertex2f(centerX + x, centerY + y);
	//}
	//glEnd();

	//Gate
	glBegin(GL_POLYGON);
	glVertex2f(-0.85, -0.20);
	glVertex2f(-0.85, -0.10);
	glVertex2f(-0.575, -0.65);
	glVertex2f(-0.575, -0.75);
	glEnd();
	glFlush();






	
}