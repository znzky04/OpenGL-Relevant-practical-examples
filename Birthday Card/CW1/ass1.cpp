// File ID: ASS1.cpp
// Title: Birthday Card
// Author: Enze Zhou
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <Math.h>
#include <iostream>
#include "stdio.h"
#include <cstdlib> 
#include <ctime>
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

//Draw star
void drawStar(float centerX, float centerY, float radius) {
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 0.0);

	float angleStep = M_PI / 5.0;
	for (int i = 0; i < 10; i++) {
		float angle = i * angleStep;
		float r = (i % 2 == 0) ? radius : radius / 2.5; // Radius of the inner and outer vertices
		float x = centerX + r * cos(angle);
		float y = centerY + r * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

//Draw moon
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

//Draw Meteor
float meteorX, meteorY;
float meteorSpeedX, meteorSpeedY;
void initRandomMeteor() {
	srand(time(0));
}//Random position generation
void generateRandomMeteor() {
	meteorX = -0.65 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.6));
	meteorY = 1 ;
	
	meteorSpeedX = 0.002f * (static_cast<float>(rand()) / RAND_MAX + 0.2f); 
	meteorSpeedY = meteorSpeedX * (-0.75f);
}
void drawMeteor() {
	glColor3f(1.0, 215/255.0, 0);  
	glBegin(GL_LINES);
	glVertex2f(meteorX, meteorY);
	glVertex2f(meteorX + 0.05, meteorY - 0.05); 
	glEnd();
}
void updateMeteor() {
	meteorX += meteorSpeedX;
	meteorY += meteorSpeedY;

	if (meteorY < 0.45) {
		generateRandomMeteor();
	}

	glutPostRedisplay();
}

//Draw Cloud
float cloudX = -1.0;
void drawCloud(float centerX, float centerY) {
	glColor3f(0.9, 0.9, 0.9);

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX - 0.15 + 0.1 * cos(angle); 
		float y = centerY + 0.02 + 0.05 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX + 0.15 + 0.1 * cos(angle);  
		float y = centerY + 0.02 + 0.05 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX + 0.0 + 0.15 * cos(angle);  
		float y = centerY + 0.05 + 0.07 * sin(angle);  
		glVertex2f(x, y);
	}
	glEnd();
}

// Function to handle keyboard events,control character
void keyboard(unsigned char key, int x, int y) {
	float moveAmount = 0.05;
	if (key == 'd' || key == 'D') {
		personX += moveAmount;
	}

	if (personX >= 0.725 && personX <= 0.775) {
		scene = 2;
	}
	glutPostRedisplay();
}

//Text
void drawText(const char* text, float x, float yStart, float yStep) {
	for (const char* c = text; *c != '\0'; c++) {
		glRasterPos2f(x, yStart); 
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  
		yStart -= yStep; 
	}
}

//Draw face
void drawFace(float centerX, float centerY) {
	//eyes
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX - 0.02 + 0.01 * cos(angle);
		float y = centerY + 0.01 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX + 0.02 + 0.01 * cos(angle);
		float y = centerY + 0.01 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//smile
	glBegin(GL_LINE_STRIP);
	for (int i = 180; i <= 360; i++) { 
		float angle = i * M_PI / 180.0;
		float x = centerX + 0.03 * cos(angle);  
		float y = centerY - 0.02 + 0.01 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

//Draw a simple person
void drawPerson(float centerX, float centerY) {
	//head
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

	//body
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(centerX - 0.03, centerY - 0.05);
	glVertex2f(centerX + 0.03, centerY - 0.05);
	glVertex2f(centerX + 0.03, centerY - 0.15);
	glVertex2f(centerX - 0.03, centerY - 0.15);
	glEnd();

	//legs
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(centerX - 0.02, centerY - 0.15);
	glVertex2f(centerX - 0.02, centerY - 0.25);

	glVertex2f(centerX + 0.02, centerY - 0.15);
	glVertex2f(centerX + 0.02, centerY - 0.25);
	glEnd();

	//arms
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(centerX - 0.04, centerY - 0.05); 
	glVertex2f(centerX - 0.08, centerY - 0.12);

	glVertex2f(centerX + 0.04, centerY - 0.05); 
	glVertex2f(centerX + 0.08, centerY - 0.12);
	glEnd();

	drawFace(centerX, centerY + 0.03);
}

//Draw flower
void drawFlower(float centerX, float centerY, int petalCount) {
	//center
	glColor3f(255 /255.0, 165 / 255.0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = centerX + 0.025 * cos(angle);  
		float y = centerY + 0.025 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//petals
	glColor3f(255 / 255.0, 105 / 255.0, 180 / 255.0);  
	float petalRadiusX = 0.025;  
	float petalRadiusY = 0.075; 

	for (int i = 0; i < petalCount; i++) {
		float angle = i * (360.0 / petalCount);
		glPushMatrix();
		glTranslatef(centerX, centerY, 0);
		glRotatef(angle, 0, 0, 1);// Rotate around center
		glTranslatef(0.05, 0, 0);

		//petal (ellipse)
		glBegin(GL_POLYGON);
		for (int j = 0; j <= 360; j++) {
			float petalAngle = j * M_PI / 180.0;
			float x = petalRadiusX * cos(petalAngle);
			float y = petalRadiusY * sin(petalAngle);
			glVertex2f(x, y);
		}
		glEnd();

		glPopMatrix();
	}
}

//Draw heart
float scaleFactor = 1.0;
float scaleSpeed = 0.005;
void drawHeart(float scaleX, float scaleY, float posX, float posY) {
	glPushMatrix();
	glTranslatef(posX, posY, 0);

	glBegin(GL_POLYGON);
	for (float t = 0; t <= 2 * M_PI; t += 0.01) {
		float x = 16 * pow(sin(t), 3);
		float y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);

		glVertex2f(x * scaleX, y * scaleY);
	}

	glEnd();
	glPopMatrix();
}
// Idle function to update scale factor and trigger redisplay
void updateScale() {
	scaleFactor = 1.0 + 0.1 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.005);
	glutPostRedisplay();
}

//Draw tree
void drawTree(float trunkX, float trunkY, float trunkWidth, float trunkHeight,
	float canopyRadius, float canopyXOffset, float canopyYOffset) {
	//tree trunk
	glColor3f(0.55, 0.27, 0.07);
	glBegin(GL_POLYGON);
	glVertex2f(trunkX - trunkWidth / 2, trunkY);              
	glVertex2f(trunkX + trunkWidth / 2, trunkY);               
	glVertex2f(trunkX + trunkWidth / 2, trunkY + trunkHeight); 
	glVertex2f(trunkX - trunkWidth / 2, trunkY + trunkHeight); 
	glEnd();

	//tree canopy
	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = trunkX + canopyXOffset + canopyRadius * cos(angle);
		float y = trunkY + trunkHeight + canopyYOffset + canopyRadius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = trunkX + canopyXOffset - canopyRadius / 2 + 0.9 * canopyRadius * cos(angle);
		float y = trunkY + trunkHeight + canopyYOffset / 1.5 + 0.9 * canopyRadius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
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
	//the box body
	glColor3f(0.2, 0.6, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(centerX - boxWidth / 2, centerY - boxHeight / 2);
	glVertex2f(centerX + boxWidth / 2, centerY - boxHeight / 2);
	glVertex2f(centerX + boxWidth / 2, centerY + boxHeight / 2);
	glVertex2f(centerX - boxWidth / 2, centerY + boxHeight / 2);
	glEnd();

	//vertical ribbon
	glColor3f(0.8, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(centerX - ribbonWidth / 2, centerY - boxHeight / 2);
	glVertex2f(centerX + ribbonWidth / 2, centerY - boxHeight / 2);
	glVertex2f(centerX + ribbonWidth / 2, centerY + boxHeight / 2);
	glVertex2f(centerX - ribbonWidth / 2, centerY + boxHeight / 2);
	glEnd();

	//horizontal ribbon
	glBegin(GL_POLYGON);
	glVertex2f(centerX - boxWidth / 2, centerY - ribbonWidth / 2);
	glVertex2f(centerX + boxWidth / 2, centerY - ribbonWidth / 2);
	glVertex2f(centerX + boxWidth / 2, centerY + ribbonWidth / 2);
	glVertex2f(centerX - boxWidth / 2, centerY + ribbonWidth / 2);
	glEnd();

	//bow
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * 3.1416 / 180.0;
		float x = centerX - 0.03 + 0.04 * cos(angle);  
		float y = centerY + 0.04 + 0.02 * sin(angle);  
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * 3.1416 / 180.0;
		float x = centerX + 0.03 + 0.04 * cos(angle);  
		float y = centerY + 0.04 + 0.02 * sin(angle);  
		glVertex2f(x, y);
	}
	glEnd();
}

//CheckMouse
bool armToggle = false;
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		armToggle = !armToggle;
		glutPostRedisplay();
	}
}

void drawNewScene() {

	glClearColor(0.96f, 0.87f, 0.70f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	//father head
	glColor3f(0.8, 0.5, 0.3);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = -0.6 + 0.1 * cos(angle);
		float y = 0.4 + 0.1 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//body
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.7, 0.3);
	glVertex2f(-0.5, 0.3);
	glVertex2f(-0.5, -0.2);
	glVertex2f(-0.7, -0.2);
	glEnd();

	//arm
	glColor3f(0.8, 0.5, 0.3);
	glBegin(GL_LINES);
	if (armToggle) {
		// Arms up
		glVertex2f(-0.7, 0.1);
		glVertex2f(-0.8, 0.25);
		glVertex2f(-0.5, 0.1);
		glVertex2f(-0.4, 0.25);
	}
	else {
		// Arms down
		glVertex2f(-0.7, 0.1);
		glVertex2f(-0.8, -0.15);
		glVertex2f(-0.5, 0.1);
		glVertex2f(-0.4, -0.15);
	}
	glEnd();


    //Eyes and mouth
	glColor3f(0.0, 0.0, 0.0); 
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(-0.63, 0.45);  
	glVertex2f(-0.57, 0.45);  
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.64, 0.37);
	glVertex2f(-0.60, 0.35);
	glVertex2f(-0.60, 0.35);
	glVertex2f(-0.56, 0.37);
	glEnd();

	//leg
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.65, -0.2);
	glVertex2f(-0.65, -0.4);
	glVertex2f(-0.55, -0.2);
	glVertex2f(-0.55, -0.4);
	glEnd();

	//mother(same to father)
	glColor3f(0.9, 0.6, 0.4);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = 0.6 + 0.1 * cos(angle);
		float y = 0.4 + 0.1 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.5); 
	glBegin(GL_POLYGON);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.7, 0.3);
	glVertex2f(0.7, -0.2);
	glVertex2f(0.5, -0.2);
	glEnd();

	glColor3f(0.9, 0.6, 0.4);
	glBegin(GL_LINES);
	if (armToggle) {
		glVertex2f(0.5, 0.1);
		glVertex2f(0.4, -0.15);
		glVertex2f(0.7, 0.1);
		glVertex2f(0.8, -0.15);
	}
	else {
		glVertex2f(0.5, 0.1);
		glVertex2f(0.4, 0.25);
		glVertex2f(0.7, 0.1);
		glVertex2f(0.8, 0.25);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(0.57, 0.45);
	glVertex2f(0.63, 0.45);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.56, 0.37);
	glVertex2f(0.60, 0.35);
	glVertex2f(0.60, 0.35);
	glVertex2f(0.64, 0.37);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.55, -0.2);
	glVertex2f(0.55, -0.4);
	glVertex2f(0.65, -0.2);
	glVertex2f(0.65, -0.4);
	glEnd();

	//Cake

	//second floor
	glColor3f(1.0, 0.8, 0.6);
	glBegin(GL_POLYGON);
	glVertex2f(-0.15, -0.3);
	glVertex2f(0.15, -0.3);
	glVertex2f(0.15, -0.45);
	glVertex2f(-0.15, -0.45);
	glEnd();

	//first floor
	glColor3f(0.9, 0.7, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, -0.4);
	glVertex2f(0.2, -0.4);
	glVertex2f(0.2, -0.6);
	glVertex2f(-0.2, -0.6);
	glEnd();

	//cream
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = -0.2 + 0.02 * cos(angle);
		float y = -0.4 + 0.02 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = 0.2 + 0.02 * cos(angle);
		float y = -0.4 + 0.02 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = -0.2 + 0.02 * cos(angle);
		float y = -0.6 + 0.02 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = 0.2 + 0.02 * cos(angle);
		float y = -0.6 + 0.02 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//candle
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.02, -0.3);
	glVertex2f(0.02, -0.3);
	glVertex2f(0.02, -0.2);
	glVertex2f(-0.02, -0.2);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.10, -0.31);
	glVertex2f(-0.06, -0.31);
	glVertex2f(-0.06, -0.21);
	glVertex2f(-0.10, -0.21);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f( 0.06, -0.31);
	glVertex2f( 0.10, -0.31);
	glVertex2f( 0.10, -0.21);
	glVertex2f( 0.06, -0.21);
	glEnd();

	//fire
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(-0.02, -0.2);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(0.02, -0.2);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.0, -0.1);
	glEnd();
	glFlush();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(-0.10, -0.21);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(-0.06, -0.21);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.08, -0.11);
	glEnd();
	glFlush();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(0.06, -0.21);
	glColor3f(1.0, 0.5, 0.0);
	glVertex2f(0.10, -0.21);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.08, -0.11);
	glEnd();
	glFlush();

	//Gift box
	glColor3f(0, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.8);
	glVertex2f(-0.3, -0.8);
	glColor3f(0, 0, 1);
	glVertex2f(-0.3, -0.6);
	glVertex2f(-0.5, -0.6);
	glEnd();
	glColor3f(0.8, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.4, -0.8);
	glVertex2f(-0.4, -0.6);
	glVertex2f(-0.5, -0.7);
	glVertex2f(-0.3, -0.7);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(0.3, -0.8);
	glVertex2f(0.5, -0.8);
	glColor3f(1, 1, 0);
	glVertex2f(0.5, -0.6);
	glVertex2f(0.3, -0.6);
	glEnd();
	glColor3f(0.9, 0.1, 0.1);
	glBegin(GL_LINES);
	glVertex2f(0.4, -0.8);
	glVertex2f(0.4, -0.6);
	glVertex2f(0.3, -0.7);
	glVertex2f(0.5, -0.7);
	glEnd();

	//cabinet
	glColor3f(0.6, 0.3, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(-0.95, -0.95);
	glVertex2f(-0.75, -0.95);
	glVertex2f(-0.75, -0.5);
	glVertex2f(-0.95, -0.5);
	glEnd();

	glColor3f(0.4, 0.2, 0.1); 
	for (int i = 0; i < 3; i++) {
		float yOffset = 0.15 * i;
		glBegin(GL_POLYGON);
		glVertex2f(-0.93, -0.8 + yOffset);
		glVertex2f(-0.77, -0.8 + yOffset);
		glVertex2f(-0.77, -0.65 + yOffset);
		glVertex2f(-0.93, -0.65 + yOffset);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glPointSize(3.0);
		glBegin(GL_POINTS);
		glVertex2f(-0.85, -0.725 + yOffset);
		glEnd();
	}

	//flower
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.85f, -0.9f);
	glVertex2f(0.85f, -0.5f);
	glEnd();

	glColor3f(0.5, 0.2, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(0.8f, -0.9f);
	glVertex2f(0.9f, -0.9f);
	glVertex2f(0.95f, -0.6f);
	glVertex2f(0.75f, -0.6f);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < 5; i++) {
		float angle = i * 2.0 * M_PI / 5.0;
		float offsetX = 0.05 * cos(angle);
		float offsetY = 0.05 * sin(angle);
		glBegin(GL_POLYGON);
		for (int j = 0; j <= 360; j++) {
			float petalAngle = j * M_PI / 180.0;
			float x = 0.85f + offsetX + 0.05 * cos(petalAngle);
			float y = -0.45f + offsetY + 0.07 * sin(petalAngle);
			glVertex2f(x, y);
		}
		glEnd();
	}

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * M_PI / 180.0;
		float x = 0.85f + 0.03 * cos(angle);
		float y = -0.45f + 0.03 * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	//banner
	glColor3f(0.4, 0.6, 0.8);
	glBegin(GL_POLYGON);
	glVertex2f(-0.9, 0.9);
	glVertex2f(0.9, 0.9);
	glVertex2f(0.8, 0.7);
	glVertex2f(-0.8, 0.7);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.15, 0.8);
	const char* message = "HAPPY BIRTHDAY";
	for (const char* c = message; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	//strap
	float flagStartX = -0.9;
	float flagSpacing = 0.2;
	for (int i = 0; i < 9; i++) {
		if (i % 2 == 0) {
			glColor3f(1.0, 0.6, 0.6);
		}
		else {
			glColor3f(0.3, 0.5, 0.8);
		}
		glBegin(GL_TRIANGLES);
		glVertex2f(flagStartX + i * flagSpacing, 0.75);
		glVertex2f(flagStartX + i * flagSpacing + 0.1, 0.55);
		glVertex2f(flagStartX + i * flagSpacing + 0.2, 0.75);
		glEnd();
	}

	glColor3f(1.0, 0.8, 0.0);
	for (int i = 0; i < 8; i++) {
		float xOffset = -0.8 + i * 0.25;
		float yOffset = 0.65 + ((i % 2 == 0) ? 0.05 : -0.05);
		glBegin(GL_POLYGON);
		for (int j = 0; j <= 360; j++) {
			float angle = j * M_PI / 180.0;
			float x = xOffset + 0.02 * cos(angle);
			float y = yOffset + 0.02 * sin(angle);
			glVertex2f(x, y);
		}
		glEnd();
	}

	//crown
	glColor3f(1.0, 0.84, 0.0);

	glBegin(GL_POLYGON);
	glVertex2f(-0.2, 0.2); 
	glVertex2f(0.2, 0.2); 
	glVertex2f(0.18, 0.15);
	glVertex2f(-0.18, 0.15);
	glEnd();

	for (int i = -1; i <= 1; i++) {
		float baseX = i * 0.1f;
		glBegin(GL_TRIANGLES);
		glVertex2f(baseX - 0.05, 0.2);
		glVertex2f(baseX + 0.05, 0.2);
		glVertex2f(baseX, 0.4);
		glEnd();
	}

	glColor3f(1.0, 0.0, 0.0);
	for (int i = -1; i <= 1; i++) {
		float baseX = i * 0.1f;
		float centerX = baseX;
		float centerY = 0.45;

		glBegin(GL_POLYGON);
		for (int j = 0; j <= 360; j++) {
			float angle = j * M_PI / 180.0;
			float x = centerX + 0.01 * cos(angle);
			float y = centerY + 0.01 * sin(angle);
			glVertex2f(x, y);
		}
		glEnd();
	}

	//heart
	glColor3f(1.0, 0.0, 0.0);
	drawHeart(0.005f, 0.005f, -0.9f, 0.2f);
	glColor3f(1.0, 0.0, 0.0);
	drawHeart(0.005f, 0.005f, 0.9f, 0.2f);

	//Text
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(-0.45, 0.4);
	const char* messageLine11 = "Wherever you are";
	for (const char* c = messageLine11; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	glRasterPos2f(0.2, 0.4);
	const char* messageLine22 = "Whenever it is";
	for (const char* c = messageLine22; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	glRasterPos2f(-0.2, 0);
	const char* messageLine33 = "We will be there for you";
	for (const char* c = messageLine33; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

	glPushMatrix();
	glColor3f(1, 1, 0.0);
	glTranslatef(-0.25, -0.8, 0);
	glScalef(0.0005, 0.0005, 1.0);
	const char* messageLine44 = "Welcome home!";
	for (const char* c = messageLine44; *c != '\0'; c++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();


	//balloon
	static float balloonOffsetY = 0.0;
	static float waveOffset = 0.0;
	balloonOffsetY += 0.0002;
	waveOffset += 0.01;
	if (balloonOffsetY > 1.5) {
		balloonOffsetY = -0.8;
	}

	for (int i = 0; i < 5; i++) {
		float balloonX = -0.8 + i * 0.4;
		float wave = 0.02 * sin(waveOffset + i * M_PI / 4);

		//ball
		glColor3f(1.0 - i * 0.05, 0.4 + i * 0.12, 0.4);
		glBegin(GL_POLYGON);
		for (int j = 0; j <= 360; j++) {
			float angle = j * M_PI / 180.0;
			float x = balloonX + 0.05 * cos(angle);
			float y = 0.0 + balloonOffsetY + 0.05 * sin(angle);
			glVertex2f(x, y);
		}
		glEnd();

		//rope
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(balloonX, balloonOffsetY - 0.03);
		glVertex2f(balloonX + wave, balloonOffsetY - 0.2);
		glEnd();
	}


	glutSwapBuffers();
}


void updateAll() {
	updateScale();  
	updateMeteor(); 

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
	
	// Using double bufferin
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(320, 150);
	glutCreateWindow("Birthdat Card");
	glutDisplayFunc(define_to_OpenGL);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseClick);

	initRandomMeteor();
	generateRandomMeteor();

	glutIdleFunc(updateAll);

	glutMainLoop();
}

void define_to_OpenGL()
{
	if (scene == 1) {

		glClearColor(0.96f, 0.87f, 0.70f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Activate anti-aliasing and blending effects
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
		drawStar(0.6, 0.69, 0.1);
		drawMoon(-0.8, 0.8, 0.15);
		glFlush();

		//Meteor
		drawMeteor();

		//Cloud
		drawCloud(0.7, 0.8);
		drawCloud(0.1, 0.85);

		//flower
		drawFlower(0.0, -0.8, 6);
		drawFlower(-0.3, -0.8, 6);
		drawFlower(0.3, -0.8, 6);
		drawFlower(0.6, -0.8, 6);

		//tree
		drawTree(-0.5, -0.4, 0.1, 0.4, 0.15, 0.0, 0.1);
		glColor3f(255 / 255.0, 215 / 255.0, 1.0);
		drawText("HAPPY", -0.515, -0.13, 0.05);

		drawTree(0.2, -0.4, 0.1, 0.5, 0.15, 0.0, 0.1);
		glColor3f(255/255.0, 215/255.0, 1.0);
		drawText("BIRTHDAY", 0.195, -0.02, 0.05);
		
		//heart
		glColor3f(1.0, 0.0, 0.0);
		drawHeart(0.008 * scaleFactor, 0.008 * scaleFactor,-0.81,-0.8);

		//giftbox
		drawGiftBox(0.5, -0.42, 0.2, 0.1, 0.01);

		//Person(It's a little complicated.Use function)
		drawPerson(personX, -0.35);

		//lace
		glColor3f(0.0, 0.5, 0.7);
		glBegin(GL_LINE_STRIP);
		for (float x = -1.0; x <= 1.0; x += 0.1) {
			for (int i = 0; i <= 180; i++) {
				float angle = i * M_PI / 180.0;  
				float y = -1 + 0.04 * sin(angle); 
				glVertex2f(x + 0.05 * cos(angle), y);
			}
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (float y = -0.9; y <= -0.1; y += 0.1) {
			for (int i = 0; i <= 180; i++) {
				float angle = i * M_PI / 180.0;  
				float x = -1 + 0.04 * sin(angle);  
				glVertex2f(x, y + 0.05 * cos(angle));
			}
		}
		glEnd();

		//Text
		glColor3f(0.0, 0.0, 0.0); 
		glRasterPos2f(-0.2, -0.1);
		const char* message = "Press \"D\" to move";
		for (const char* c = message; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}

		glRasterPos2f(-0.15, -0.15);
		const char* messageLine2 = "to your home";
		for (const char* c = messageLine2; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}

		// Ensures that the buffer swap happens
		glutSwapBuffers();


	}

	else if (scene == 2) {
		// If scene == 2, draw the new scene
		drawNewScene();
	}

}
