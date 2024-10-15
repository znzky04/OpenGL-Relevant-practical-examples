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
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);


float personX = 0.0;// Global variable for the x-coordinate of the person
int scene = 1;

// Function to handle window resizing
void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set orthogonal projection with a [-1,1] coordinate system
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//star
void drawStar(float centerX, float centerY, float radius) {
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 0.0);

	float angleStep = M_PI / 5.0;  // The spacing of each vertex
	for (int i = 0; i < 10; i++) {
		float angle = i * angleStep;
		float r = (i % 2 == 0) ? radius : radius / 2.5; // Radius of the inner and outer vertices
		float x = centerX + r * cos(angle);
		float y = centerY + r * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

//moon
void drawMoon(float centerX, float centerY, float radius) {
	// Main body of the moon
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 0); 
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180;
		float x = centerX + radius * cos(angle);
		float y = centerY + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	// The shaded part of the moon
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(25 / 255.0, 25 / 255.0, 112 / 255.0);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180;
		float x = centerX + radius * 0.8 + radius * cos(angle);
		float y = centerY + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}


// Function to handle keyboard events
void keyboard(unsigned char key, int x, int y) {
	float moveAmount = 0.05;
	if (key == 'd' || key == 'D') {
		personX += moveAmount; // Move right
	}
	// Check if the person has reached the door
	if (personX >= 0.725 && personX <= 0.775) {
		scene = 2;
	}
	glutPostRedisplay(); // Request display update
}

//Draw a simple person
void drawPerson(float centerX, float centerY) {
	// Draw the head (circle)
	glColor3f(1.0, 0.8, 0.6);
	float radius = 0.05;
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX + radius * cos(angle);
		float y = centerY + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	// Draw the body (rectangle)
	glColor3f(0.0, 0.0, 1.0); // Blue color for shirt
	glBegin(GL_POLYGON);
	glVertex2f(centerX - 0.03, centerY - 0.05); // Top-left of body
	glVertex2f(centerX + 0.03, centerY - 0.05); // Top-right of body
	glVertex2f(centerX + 0.03, centerY - 0.15); // Bottom-right of body
	glVertex2f(centerX - 0.03, centerY - 0.15); // Bottom-left of body
	glEnd();

	// Draw the legs (two lines)
	glColor3f(0.0, 0.0, 0.0); // Black color for legs
	glBegin(GL_LINES);
	glVertex2f(centerX - 0.02, centerY - 0.15); // Left leg
	glVertex2f(centerX - 0.02, centerY - 0.25);

	glVertex2f(centerX + 0.02, centerY - 0.15); // Right leg
	glVertex2f(centerX + 0.02, centerY - 0.25);
	glEnd();

	// Draw the arms (two lines, arms down)
	glColor3f(0.0, 0.0, 0.0); // Black color for arms
	glBegin(GL_LINES);
	glVertex2f(centerX - 0.04, centerY - 0.05); // Left arm
	glVertex2f(centerX - 0.08, centerY - 0.12);

	glVertex2f(centerX + 0.04, centerY - 0.05); // Right arm
	glVertex2f(centerX + 0.08, centerY - 0.12);
	glEnd();
}

//Draw flower
void drawFlower(float centerX, float centerY, int petalCount) {
	// Draw flower center (shrink by reducing radius)
	glColor3f(255 /255.0, 165 / 255.0, 0);  // Yellow for center
	glBegin(GL_POLYGON);  // Draw center circle
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX + 0.025 * cos(angle);  // Change 0.1 to 0.05 to make center smaller
		float y = centerY + 0.025 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	// Draw petals (shrink by reducing petal sizes)
	glColor3f(255 / 255.0, 105 / 255.0, 180 / 255.0);  // Red color for petals
	float petalRadiusX = 0.025;  // X radius for elliptical petal (reduced from 0.1)
	float petalRadiusY = 0.075;   // Y radius for elliptical petal (reduced from 0.3)

	for (int i = 0; i < petalCount; i++) {
		float angle = i * (360.0 / petalCount);  // Angle between each petal
		glPushMatrix();  // Save current transformation matrix
		glTranslatef(centerX, centerY, 0);  // Move to flower center
		glRotatef(angle, 0, 0, 1);  // Rotate around center
		glTranslatef(0.05, 0, 0);  // Reduce translation from 0.2 to 0.1 to bring petals closer

		// Draw petal (ellipse)
		glBegin(GL_POLYGON);
		for (int j = 0; j <= 360; j++) {
			float petalAngle = j * M_PI / 180.0;
			float x = petalRadiusX * cos(petalAngle);
			float y = petalRadiusY * sin(petalAngle);
			glVertex2f(x, y);
		}
		glEnd();

		glPopMatrix();  // Restore original transformation matrix
	}
}


//Draw heart
float scaleFactor = 1.0;  // Current scale factor for heart
float scaleSpeed = 0.005; // Speed of the scaling effect (for heartbeat)
void drawHeart(float scaleX, float scaleY, float posX, float posY) {
	glPushMatrix();  // Save the current matrix
	glTranslatef(posX, posY, 0);  // Move heart to the desired position

	glBegin(GL_POLYGON);  // Or use GL_LINE_LOOP for an outline

	// t represents the angle in radians, from 0 to 2*PI (full circle)
	for (float t = 0; t <= 2 * M_PI; t += 0.01) {
		// Parametric equations for the heart shape
		float x = 16 * pow(sin(t), 3);
		float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);

		// Scale the heart and plot the points
		glVertex2f(x * scaleX, y * scaleY);
	}

	glEnd();
	glPopMatrix();  // Restore the original matrix
}
// Idle function to update scale factor and trigger redisplay
void updateScale() {
	scaleFactor = 1.0 + 0.1 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.005);
	glutPostRedisplay();
}

//Draw tree
void drawTree(float trunkX, float trunkY, float trunkWidth, float trunkHeight,
	float canopyRadius, float canopyXOffset, float canopyYOffset) {
	// Draw the tree trunk (brown color)
	glColor3f(0.55, 0.27, 0.07);  // Brown
	glBegin(GL_POLYGON);
	glVertex2f(trunkX - trunkWidth / 2, trunkY);               // Bottom-left
	glVertex2f(trunkX + trunkWidth / 2, trunkY);               // Bottom-right
	glVertex2f(trunkX + trunkWidth / 2, trunkY + trunkHeight); // Top-right
	glVertex2f(trunkX - trunkWidth / 2, trunkY + trunkHeight); // Top-left
	glEnd();

	// Draw the tree canopy (green color)
	glColor3f(0.0, 0.8, 0.0);  // Green
	glBegin(GL_POLYGON);  // First circle
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = trunkX + canopyXOffset + canopyRadius * cos(angle);
		float y = trunkY + trunkHeight + canopyYOffset + canopyRadius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);  // Second circle
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = trunkX + canopyXOffset - canopyRadius / 2 + 0.9 * canopyRadius * cos(angle);
		float y = trunkY + trunkHeight + canopyYOffset / 1.5 + 0.9 * canopyRadius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);  // Third circle
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = trunkX + canopyXOffset + canopyRadius / 2 + 0.9 * canopyRadius * cos(angle);
		float y = trunkY + trunkHeight + canopyYOffset / 1.5 + 0.9 * canopyRadius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

//Draw giftbox
void drawGiftBox(float centerX, float centerY, float boxWidth, float boxHeight, float ribbonWidth) {
	// Draw the box body (blue)
	glColor3f(0.2, 0.6, 0.8);  // Light blue
	glBegin(GL_POLYGON);  // Draw the box (rectangle)
	glVertex2f(centerX - boxWidth / 2, centerY - boxHeight / 2);  // Bottom-left
	glVertex2f(centerX + boxWidth / 2, centerY - boxHeight / 2);  // Bottom-right
	glVertex2f(centerX + boxWidth / 2, centerY + boxHeight / 2);  // Top-right
	glVertex2f(centerX - boxWidth / 2, centerY + boxHeight / 2);  // Top-left
	glEnd();

	// Draw vertical ribbon (red)
	glColor3f(0.8, 0.0, 0.0);  // Red
	glBegin(GL_POLYGON);  // Draw vertical ribbon
	glVertex2f(centerX - ribbonWidth / 2, centerY - boxHeight / 2);
	glVertex2f(centerX + ribbonWidth / 2, centerY - boxHeight / 2);
	glVertex2f(centerX + ribbonWidth / 2, centerY + boxHeight / 2);
	glVertex2f(centerX - ribbonWidth / 2, centerY + boxHeight / 2);
	glEnd();

	// Draw horizontal ribbon (red)
	glBegin(GL_POLYGON);  // Draw horizontal ribbon
	glVertex2f(centerX - boxWidth / 2, centerY - ribbonWidth / 2);
	glVertex2f(centerX + boxWidth / 2, centerY - ribbonWidth / 2);
	glVertex2f(centerX + boxWidth / 2, centerY + ribbonWidth / 2);
	glVertex2f(centerX - boxWidth / 2, centerY + ribbonWidth / 2);
	glEnd();

	// Draw the bow (yellow, two ovals)
	glColor3f(1.0, 1.0, 0.0);  // Yellow
	// Left part of the bow (oval)
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * 3.1416 / 180.0;
		float x = centerX - 0.03 + 0.04 * cos(angle);  
		float y = centerY + 0.04 + 0.02 * sin(angle);  
		glVertex2f(x, y);
	}
	glEnd();

	// Right part of the bow (oval)
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * 3.1416 / 180.0;
		float x = centerX + 0.03 + 0.04 * cos(angle);  
		float y = centerY + 0.04 + 0.02 * sin(angle);  
		glVertex2f(x, y);
	}
	glEnd();
}

//Draw a new scene
void drawNewScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.7, 0.9); // Set background color for the new scene (e.g., blue sky)
	glBegin(GL_POLYGON);  // Draw a simple background for the new scene
	glVertex2f(-1.0, -1.0);
	glVertex2f(-1.0, 1.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	// Draw something in the new scene (e.g., a simple house or a different layout)
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON); // A simple red square in the new scene
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Using double bufferin
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(320, 150);
	glutCreateWindow("Birthdat Card");
	glutDisplayFunc(define_to_OpenGL);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(updateScale);

	glutMainLoop();
}

void define_to_OpenGL()
{
	if (scene == 1) {
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


		//Flowers in clusters
		//down
		glColor3f(220 / 255.0, 20 / 255.0, 60 / 255.0);
		glBegin(GL_POLYGON);
		glVertex2f(-0.675, -0.7);
		glVertex2f(-0.7, -0.65);
		glVertex2f(0.775, -0.65);
		glVertex2f(0.8, -0.7);
		glEnd();

		//up
		glBegin(GL_POLYGON);
		glVertex2f(-0.75, -0.55);
		glVertex2f(-0.775, -0.5);
		glVertex2f(0.7, -0.5);
		glVertex2f(0.725, -0.55);
		glEnd();
		glFlush();


		//lawn
		//down
		glColor3f(124 / 255.0, 222 / 255.0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(-0.575, -0.9);
		glVertex2f(-0.675, -0.7);
		glVertex2f(1, -0.7);
		glVertex2f(1, -0.9);
		glEnd();

		//up
		glBegin(GL_POLYGON);
		glVertex2f(-0.775, -0.5);
		glVertex2f(-0.85, -0.35);
		glVertex2f(0.7, -0.35);
		glVertex2f(0.7, -0.5);
		glEnd();

		//Wall
		glColor3f(128 / 255.0, 128 / 255.0, 128 / 255.0);
		glBegin(GL_POLYGON);
		glVertex2f(-1, -0.05);
		glVertex2f(-1, 0.1);
		glVertex2f(-0.85, -0.2);
		glVertex2f(-0.85, -0.35);
		glEnd();


		// Draw vertical lines for the sides of the gate
		glColor3f(0, 0, 0);
		glLineWidth(1.5);
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
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(-0.85, -0.20);
		glVertex2f(-0.85, -0.10);
		glVertex2f(-0.575, -0.65);
		glVertex2f(-0.575, -0.75);
		glEnd();
		glFlush();


		//Sky
		glColor3f(25 / 255.0, 25 / 255.0, 112 / 255.0);
		glBegin(GL_POLYGON);
		glVertex2f(-1, 0.4);
		glVertex2f(-1, 1);
		glVertex2f(0.7, 1);
		glVertex2f(0.7, 0.4);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(0.7, 0.5);
		glVertex2f(0.7, 1);
		glVertex2f(1, 1);
		glVertex2f(1, 0.88);
		glEnd();
		glFlush();



		//star and moon(It's a little complicated.Use function)
		drawStar(-0.3, 0.55, 0.1);
		drawStar(-0.45, 0.75, 0.1);
		drawStar(-0.05, 0.72, 0.1);
		drawStar(0.3, 0.6, 0.1);
		drawStar(0.5, 0.75, 0.1);
		drawMoon(-0.8, 0.8, 0.15);
		glFlush();

		//flower
		drawFlower(0.0, -0.8, 6);
		drawFlower(-0.3, -0.8, 6);
		drawFlower(0.3, -0.8, 6);
		drawFlower(0.6, -0.8, 6);

		//tree
		drawTree(-0.5, -0.4, 0.1, 0.4, 0.15, 0.0, 0.1);

		//Person(It's a little complicated.Use function)
		drawPerson(personX, -0.35);
		
		//heart
		glColor3f(1.0, 0.0, 0.0);
		drawHeart(0.008 * scaleFactor, 0.008 * scaleFactor,-0.85,-0.8);

		//giftbox
		drawGiftBox(0.5, -0.42, 0.2, 0.1, 0.01);

		// Ensures that the buffer swap happens
		glutSwapBuffers();


	}

	else if (scene == 2) {
		// If scene == 2, draw the new scene
		drawNewScene();
	}



}
