#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#define M_PI 3.14159265358979323846

// Camera parameters
float cameraX = 0.0;
float cameraY = 1.7;
float cameraZ = 3.0;
float cameraRotX = 0.0;
float cameraRotY = 0.0;

// mouse control parameters
bool firstMouse = true;
int windowCenterX;
int windowCenterY;
float mouseSensitivity = 0.05;

// Moving speed
float moveSpeed = 0.1;

// Three light switch status
bool ceilingLightOn = true;
bool floorLampOn = true;
bool bedroomLightOn = true;

//Door parameters
float doorAngle = 0.0;  // Rotation Angle
bool isDoorOpening = false;  
bool isDoorClosing = false;  
const float DOOR_SPEED = 2.0;  // Switching speed

// Global variable for the texture ID 
GLuint textureIDs[8];


// Material property setting function
void setMaterial(GLfloat r, GLfloat g, GLfloat b, GLfloat shininess, GLfloat specularStrength) {
    // Three Light sources 
    GLfloat ambient[] = { r * 0.30, g * 0.30, b * 0.30, 1.0 };
    GLfloat diffuse[] = { r, g, b, 1.0 };
    GLfloat specular[] = { specularStrength, specularStrength, specularStrength, 1.0 }; //easy to change specularStrength

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glColor3f(r, g, b);
}

// Draw cylinder function
void drawCylinder(float radius, float height, int subdivisions) {
    float angle;
    // flank
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= subdivisions; i++) {
        angle = i * 2.0 * M_PI / subdivisions;
        glNormal3f(cos(angle), 0.0, sin(angle));
        glVertex3f(cos(angle) * radius, 0.0, sin(angle) * radius);
        glVertex3f(cos(angle) * radius, height, sin(angle) * radius);
    }
    glEnd();

    // Top and bottom
    for (int j = 0; j < 2; j++) {
        glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, j == 0 ? -1.0 : 1.0, 0.0);
        glVertex3f(0.0, j == 0 ? 0.0 : height, 0.0);
        for (int i = 0; i <= subdivisions; i++) {
            angle = i * 2.0 * M_PI / subdivisions;
            glVertex3f(cos(angle) * radius, j == 0 ? 0.0 : height, sin(angle) * radius);
        }
        glEnd();
    }
}

// Sofa function
void drawSofa() {
    // Sofa body - dark blue
    glPushMatrix();
    setMaterial(0.1, 0.2, 0.4, 20.0, 0.2); 
    glTranslatef(-2.0, 0.4, 0.0);

    // Cushions and cushions - slightly lighter blue
    setMaterial(0.15, 0.25, 0.45, 16.0, 0.1);  // slightly
    // Seat body
    glPushMatrix();
    glScalef(1.5, 0.4, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Seat cushions
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.5 + i * 0.5, 0.21, 0.0);
        glScalef(0.45, 0.1, 0.9);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();

    // Sofa backrest
    glPushMatrix();
    glTranslatef(-2.0, 0.9, -0.4);

    // Backrest body
    glPushMatrix();
    glScalef(1.5, 0.6, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Backrest cushions
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-0.5 + i * 0.5, 0.0, 0.12);
        glScalef(0.45, 0.5, 0.1);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();

    // handrail
    setMaterial(0.3, 0.15, 0.1, 32.0, 0.2);  // Wood color
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-2.75 + i * 1.5, 0.6, 0.1);
        glScalef(0.2, 0.4, 1.0);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}

// FlowerPot function
void drawFlowerPot() {
    glPushMatrix();
    // FlowerPot body
    setMaterial(0.6, 0.3, 0.2, 16.0, 0.1);
    glPushMatrix();
    glTranslatef(-2.0, 0.0, -4.0);
    // Use Cylinder to be pot
    drawCylinder(0.3, 0.6, 20);
    glPopMatrix();

    // Flower pot base
    glPushMatrix();
    glTranslatef(0.0, 0.02, 0.0);
    glTranslatef(-2.0, 0.0, -4.0);
    drawCylinder(0.35, 0.04, 20);
    glPopMatrix();

    // Plant
    setMaterial(0.2, 0.5, 0.2, 8.0, 0.1);  // green
    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0);
    glTranslatef(-2.0, 0.0, -4.0);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();

    // The other flowerPot
    setMaterial(0.6, 0.3, 0.2, 16.0, 0.1);
    glPushMatrix();
    glTranslatef(2.0, 0.0, -4.0);
    drawCylinder(0.3, 0.6, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.02, 0.0);
    glTranslatef(2.0, 0.0, -4.0);
    drawCylinder(0.35, 0.04, 20);
    glPopMatrix();

    setMaterial(1.0, 0.2, 0.2, 8.0, 0.1);  // red
    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0);
    glTranslatef(2.0, 0.0, -4.0);
    glutSolidSphere(0.4, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

// TV function
void drawTV() {
    // TV screen (Black panel)
    glPushMatrix();
    glTranslatef(-2.5, 2.0, 4.8);
    setMaterial(0.05, 0.05, 0.05, 32.0, 0.7);
    glScalef(1.6, 0.9, 0.08);
    glutSolidCube(1.0);
    glPopMatrix();

    // TV frame
    glPushMatrix();
    glTranslatef(-2.5, 2.0, 4.8);
    setMaterial(0.2, 0.2, 0.2, 16.0, 0.5);
    glTranslatef(0.0, 0.0, 0.01);
    glScalef(1.7, 1.0, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

// Door function
void drawDoor() {
    // Door frame
    glPushMatrix();
    glTranslatef(0.0, 0.55, 2.4);
    setMaterial(0.4, 0.25, 0.1, 32.0, 0.3);

    // Upper door frame
    glPushMatrix();
    glTranslatef(0.0, 0.55, 2.4);
    glTranslatef(0.0, 1.0, 0.0);
    glScalef(1.2, 0.1, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Left door frame
    glPushMatrix();
    glTranslatef(0.0, 0.55, 2.4);
    glTranslatef(-0.6, 0.0, 0.0);
    glScalef(0.1, 2.0, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Right door frame
    glPushMatrix();
    glTranslatef(0.0, 0.55, 2.4);
    glTranslatef(0.6, 0.0, 0.0);
    glScalef(0.1, 2.0, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Door body
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
    glPushMatrix();
    glTranslatef(0.0, 0.55, 2.4);
    glTranslatef(-0.5, 0.0, 0.0);    // Shift matrix
    glRotatef(doorAngle, 0.0, 1.0, 0.0);  // Rotate around the Y axis to mimic a door opening
    glTranslatef(0.5, 0.0, 0.0);  // Shift back
    glScalef(1.0, 2.0, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

// Table function
void drawTable() {
    // Tabletop
    glPushMatrix();
    setMaterial(0.6, 0.4, 0.2, 16.0, 0.2);  // Wood color
    glTranslatef(2.0, 0.7, 0.0);

    // Main desktop
    glPushMatrix();
    glScalef(2.0, 0.1, 1.4);
    glutSolidCube(1.0);
    glPopMatrix();

    // Desktop border
    glPushMatrix();
    setMaterial(0.5, 0.3, 0.15, 16.0, 0.2);
    glTranslatef(0.0, -0.05, 0.0);
    glScalef(2.1, 0.05, 1.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    // Table legs
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        setMaterial(0.4, 0.25, 0.1, 16.0, 0.2);
        float xOffset = (i < 2) ? -0.8 : 0.8;
        float zOffset = (i % 2 == 0) ? -0.6 : 0.6;
        glTranslatef(2.0 + xOffset, 0.35, zOffset);

        glPushMatrix();
        glScalef(0.1, 0.7, 0.1);
        glutSolidCube(1.0);
        glPopMatrix();

        // Leg decoration
        glPushMatrix();
        glTranslatef(0.0, -0.3, 0.0);
        glScalef(0.15, 0.05, 0.15);
        glutSolidCube(1.0);
        glPopMatrix();

        glPopMatrix();
    }
}

// Chair function
void drawChair() {
    // Chair 1
    glPushMatrix();
    glTranslatef(2.0, 0.4, 0.8);
    glRotatef(180.0, 0.0, 1.0, 0.0);

    // Seat
    glPushMatrix();
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
    glScalef(0.4, 0.05, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    // Backrest
    glPushMatrix();
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
    glTranslatef(0.0, 0.3, -0.18);
    glScalef(0.4, 0.6, 0.04);
    glutSolidCube(1.0);
    glPopMatrix();

    // Legs
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
        float xOffset = (i < 2) ? -0.17 : 0.17;
        float zOffset = (i % 2 == 0) ? -0.17 : 0.17;
        glTranslatef(xOffset, -0.2, zOffset);
        glScalef(0.04, 0.4, 0.04);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    glPopMatrix();

    // Chair 2
    glPushMatrix();
    glTranslatef(2.0, 0.4, -0.8);

    // Seat
    glPushMatrix();
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
    glScalef(0.4, 0.05, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    // Backrest
    glPushMatrix();
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
    glTranslatef(0.0, 0.3, -0.18);
    glScalef(0.4, 0.6, 0.04);
    glutSolidCube(1.0);
    glPopMatrix();

    // Legs
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        setMaterial(0.6, 0.4, 0.2, 32.0, 0.4);
        float xOffset = (i < 2) ? -0.17 : 0.17;
        float zOffset = (i % 2 == 0) ? -0.17 : 0.17;
        glTranslatef(xOffset, -0.2, zOffset);
        glScalef(0.04, 0.4, 0.04);
        glutSolidCube(1.0);
        glPopMatrix();
    }
    glPopMatrix();
}

// Room wall (Use texture to decorate)
void drawRoom() {
    // Floor 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[5]);  // Floor texture 地板纹理
    glPushMatrix();
    glTranslatef(0.0, 0.0, 5.0);

    // Set material 
    GLfloat floor_ambient[] = { 0.4, 0.2, 0.1, 1.0 };
    GLfloat floor_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, floor_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.0, -10.0);
    glTexCoord2f(5.0, 0.0); glVertex3f(5.0, 0.0, -10.0);
    glTexCoord2f(5.0, 10.0); glVertex3f(5.0, 0.0, 10.0);
    glTexCoord2f(0.0, 10.0); glVertex3f(-5.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Rear wall(bedroom) 
    glPushMatrix();
    glTranslatef(0.0, 2.5, 15.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[6]);  // Rear wall texture 后墙纹理

    GLfloat back_wall_ambient[] = { 0.36, 0.25, 0.20, 1.0 };
    GLfloat back_wall_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, back_wall_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, back_wall_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    // Set size 
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -2.5, 0.0);
    glTexCoord2f(3.0, 0.0); glVertex3f(5.0, -2.5, 0.0);
    glTexCoord2f(3.0, 2.0); glVertex3f(5.0, 2.5, 0.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(-5.0, 2.5, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Front wall(Living room) 
    glPushMatrix();
    glTranslatef(0.0, 2.5, -5.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);  // Wallpaper texture(Almost every wall use this) 

    GLfloat front_wall_ambient[] = { 0.63, 0.63, 0.63, 1.0 };
    GLfloat front_wall_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, front_wall_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, front_wall_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -2.5, 0.0);
    glTexCoord2f(3.0, 0.0); glVertex3f(5.0, -2.5, 0.0);
    glTexCoord2f(3.0, 2.0); glVertex3f(5.0, 2.5, 0.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(-5.0, 2.5, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Corner trim - slightly darker beige 
    setMaterial(0.90, 0.87, 0.82, 8.0, 0.05);
    glPushMatrix();
    glTranslatef(0.0, -2.4, 0.05);
    glScalef(10.0, 0.2, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Left wall(Living room) 
    glPushMatrix();
    glTranslatef(-5.0, 2.5, -5.0);//(Extending from the middle to both sides,so just move 5.0) 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);

    GLfloat left_wall_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat left_wall_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, left_wall_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, left_wall_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);

    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -2.5, 0.0);
    glTexCoord2f(5.0, 0.0); glVertex3f(0.0, -2.5, 10.0);
    glTexCoord2f(5.0, 2.0); glVertex3f(0.0, 2.5, 10.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(0.0, 2.5, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    setMaterial(0.85, 0.85, 0.85, 8.0, 0.05);
    glPushMatrix();
    glTranslatef(0.05, -2.4, 5.0);
    glScalef(0.05, 0.2, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Left wall (Bedroom) 
    glPushMatrix();
    glTranslatef(-5.0, 2.5, 5.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);

    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -2.5, 0.0);
    glTexCoord2f(3.0, 0.0); glVertex3f(0.0, -2.5, 10.0);
    glTexCoord2f(3.0, 2.0); glVertex3f(0.0, 2.5, 10.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(0.0, 2.5, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    setMaterial(0.85, 0.85, 0.85, 8.0, 0.05);
    glPushMatrix();
    glTranslatef(0.05, -2.4, 5.0);
    glScalef(0.05, 0.2, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Right room (Living Room) 
    glPushMatrix();
    glTranslatef(5.0, 2.5, -5.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);

    GLfloat right_wall_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat right_wall_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, right_wall_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, right_wall_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -2.5, 0.0);
    glTexCoord2f(5.0, 0.0); glVertex3f(0.0, -2.5, 10.0);
    glTexCoord2f(5.0, 2.0); glVertex3f(0.0, 2.5, 10.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(0.0, 2.5, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    setMaterial(0.85, 0.85, 0.85, 8.0, 0.05);
    glPushMatrix();
    glTranslatef(-0.05, -2.4, 5.0);
    glScalef(0.05, 0.2, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Right wall 2 
    glPushMatrix();
    glTranslatef(5.0, 2.5, 5.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);  // Wall texture 

    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(0.0, -2.5, 0.0);
    glTexCoord2f(3.0, 0.0); glVertex3f(0.0, -2.5, 10.0);
    glTexCoord2f(3.0, 2.0); glVertex3f(0.0, 2.5, 10.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(0.0, 2.5, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Corner decoration 
    setMaterial(0.85, 0.85, 0.85, 8.0, 0.05);
    glPushMatrix();
    glTranslatef(-0.05, -2.4, 5.0);
    glScalef(0.05, 0.2, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Left part of partition wall 
    glPushMatrix();
    glTranslatef(-2.75, 2.5, 4.9);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);

    GLfloat partition_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat partition_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, partition_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, partition_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-2.15, -2.5, 0.0);
    glTexCoord2f(2.0, 0.0); glVertex3f(2.15, -2.5, 0.0);
    glTexCoord2f(2.0, 2.0); glVertex3f(2.15, 2.5, 0.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(-2.15, 2.5, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Right part of partition wall 
    glPushMatrix();
    glTranslatef(2.75, 2.5, 4.9);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);

    glMaterialfv(GL_FRONT, GL_AMBIENT, partition_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, partition_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-2.15, -2.5, 0.0);
    glTexCoord2f(2.0, 0.0); glVertex3f(2.15, -2.5, 0.0);
    glTexCoord2f(2.0, 2.0); glVertex3f(2.15, 2.5, 0.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(-2.15, 2.5, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // Upper part of partition wall 
    glPushMatrix();
    glTranslatef(0.0, 3.6, 4.9);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[4]);

    glMaterialfv(GL_FRONT, GL_AMBIENT, partition_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, partition_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.6, -1.425, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.6, -1.425, 0.0);
    glTexCoord2f(1.0, 2.0); glVertex3f(0.6, 1.425, 0.0);
    glTexCoord2f(0.0, 2.0); glVertex3f(-0.6, 1.425, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    // ceiling
    glPushMatrix();
    glTranslatef(0.0, 5.0, 5.0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[7]);  // Use a new ceiling texture

    GLfloat ceiling_ambient[] = { 0.93, 0.93, 0.93, 1.0 };
    GLfloat ceiling_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ceiling_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ceiling_diffuse);

    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);  // The normal is down
    glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.0, -10.0);
    glTexCoord2f(5.0, 0.0); glVertex3f(5.0, 0.0, -10.0);
    glTexCoord2f(5.0, 10.0); glVertex3f(5.0, 0.0, 10.0);
    glTexCoord2f(0.0, 10.0); glVertex3f(-5.0, 0.0, 10.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Ceiling Lamp Function
void drawCeilingLamp() {
    glPushMatrix();
    glTranslatef(2.0, 3.2, 0.0);
    // Ceiling lamp rod 
    setMaterial(0.4, 0.4, 0.4, 32.0, 0.8);
    glPushMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    drawCylinder(0.05, 1.0, 20);
    glPopMatrix();
    // Lamp shade
    if (ceilingLightOn) {
        // Brighter material when light is on, simulating glow
        setMaterial(1.0, 1.0, 0.9, 16.0, 0.2);
    }
    else {
        // Dimmer material when light is off
        setMaterial(0.8, 0.8, 0.8, 16.0, 0.1);
    }
    glPushMatrix();
    glTranslatef(0.0, -0.7, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.4, 0.6, 16, 16);
    glPopMatrix();
    // Lighting effect
    if (ceilingLightOn) {
        GLfloat lightPos[] = { 0.0, -0.8, 0.0, 1.0 };  
        GLfloat lightColor[] = { 2.5, 2.4, 2.0, 1.0 };
        GLfloat lightSpec[] = { 2.0, 2.0, 2.0, 1.0 };
        GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

        // Set attenuation for point light
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);    
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);     
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.02);  

        // Remove spotlight parameters as we're using point light
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);  // 180° present point light
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
    }
    else {
        GLfloat noLight[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat lowAmbient[] = { 0.1, 0.1, 0.1, 1.0 };  
        glLightfv(GL_LIGHT0, GL_DIFFUSE, noLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, noLight);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lowAmbient);
    }
    glPopMatrix();
}
// Floor Lamp Function
void drawFloorLamp() {
    glPushMatrix();
    glTranslatef(-2.8, 0.0, -0.5);

    // Lamp base
    setMaterial(0.3, 0.3, 0.3, 32.0, 0.8);
    glPushMatrix();
    glScalef(0.3, 0.05, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // Lamp pole
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    drawCylinder(0.03, 1.8, 16);
    glPopMatrix();

    // Lamp shade 
    if (floorLampOn) {
        setMaterial(1.0, 1.0, 0.9, 16.0, 0.2);
    }
    else {
        setMaterial(0.9, 0.9, 0.9, 16.0, 0.1);
    }

    glPushMatrix();
    glTranslatef(0.0, 1.8, 0.0);
    glRotatef(-70.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.3, 0.5, 16, 16);
    glPopMatrix();

    //Conical light
    if (floorLampOn) {
        GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);

        GLfloat lightPos[] = { 0.0, 1.7, 0.2, 1.0 };
        GLfloat lightDir[] = { 0.0, -1.0, 0.5 };
        GLfloat lightColor[] = { 2.5, 2.2, 1.8, 1.0 };    
        GLfloat lightSpec[] = { 2.0, 2.0, 2.0, 1.0 };     

        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);

        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);           // Keep the original spotlight angle
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);          
        glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.03);    
    }
    else {
        GLfloat noLight[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat lowAmbient[] = { 0.1, 0.1, 0.1, 1.0 };   
        glLightfv(GL_LIGHT1, GL_DIFFUSE, noLight);
        glLightfv(GL_LIGHT1, GL_SPECULAR, noLight);
        glLightfv(GL_LIGHT1, GL_AMBIENT, lowAmbient);
    }

    glPopMatrix();
}

// Bed function
void drawBed() {
    // Bed frame 
    glPushMatrix();
    glTranslatef(-3.5, 0.3, 7.5);

    // Bed bottom frame 
    setMaterial(0.4, 0.25, 0.1, 32.0, 0.3);  
    glPushMatrix();
    glScalef(2.0, 0.2, 4.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // Mattress 
    setMaterial(0.9, 0.9, 0.9, 8.0, 0.1); 
    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.0);
    glScalef(1.9, 0.2, 4.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Headboard 
    setMaterial(0.4, 0.25, 0.1, 32.0, 0.3);
    glPushMatrix();
    glTranslatef(0.0, 0.8, -2.2);
    glScalef(2.0, 1.4, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Quilt 
    setMaterial(0.2, 0.3, 0.7, 8.0, 0.1);
    glPushMatrix();
    glTranslatef(0.0, 0.45, 0.2);
    glScalef(1.8, 0.1, 3.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Pillows 
    setMaterial(1.0, 1.0, 1.0, 8.0, 0.1);
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(-0.4 + i * 0.8, 0.5, -1.5);
        glScalef(0.6, 0.1, 0.8);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();
}

// computer desk function
void drawComputerDesk() {
    glPushMatrix();
    glTranslatef(0.0, 0.8, 14.0);
    glRotatef(180.0, 0.0, 1.0, 0.0);

    // Draw desktop 
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.5);  
    glPushMatrix();
    glScalef(3.0, 0.06, 1.5);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw table legs
    glPushMatrix();
    float legWidth = 0.05;
    float legHeight = 0.75;

    // Front left leg 
    glPushMatrix();
    glTranslatef(-0.9, -legHeight / 2, 0.5);
    glScalef(legWidth, legHeight, legWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    // Front right leg 
    glPushMatrix();
    glTranslatef(0.9, -legHeight / 2, 0.5);
    glScalef(legWidth, legHeight, legWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    // Back left leg 
    glPushMatrix();
    glTranslatef(-0.9, -legHeight / 2, -0.5);
    glScalef(legWidth, legHeight, legWidth);
    glutSolidCube(1.0);
    glPopMatrix();

    // Back right leg 
    glPushMatrix();
    glTranslatef(0.9, -legHeight / 2, -0.5);
    glScalef(legWidth, legHeight, legWidth);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    // Monitor 
    setMaterial(0.1, 0.1, 0.1, 16.0, 0.3); 
    // Monitor base 
    glPushMatrix();
    glTranslatef(0.0, 0.03, -0.2);
    glScalef(0.3, 0.02, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Monitor stand 
    glPushMatrix();
    glTranslatef(0.0, 0.15, -0.3);
    glScalef(0.05, 0.3, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Monitor screen 
    glPushMatrix();
    glTranslatef(0.0, 0.35, -0.2);
    glScalef(0.8, 0.5, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Keyboard 
    setMaterial(0.2, 0.2, 0.2, 16.0, 0.2);
    glPushMatrix();
    glTranslatef(0.0, 0.03, 0.2);
    glScalef(0.4, 0.02, 0.15);
    glutSolidCube(1.0);
    glPopMatrix();

    // Mouse pad 
    setMaterial(0.2, 0.2, 0.2, 16.0, 0.1);
    glPushMatrix();
    glTranslatef(0.4, 0.03, 0.2);
    glScalef(0.2, 0.01, 0.25);
    glutSolidCube(1.0);
    glPopMatrix();

    // Mouse 
    setMaterial(0.3, 0.3, 0.3, 16.0, 0.3);
    glPushMatrix();
    glTranslatef(0.4, 0.04, 0.2);
    glScalef(0.06, 0.02, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Left side decorations 
    // Small plant 
    setMaterial(0.6, 0.3, 0.1, 16.0, 0.3);  // Pot material 
    glPushMatrix();
    glTranslatef(-1.2, 0.1, 0.0);
    // Pot 
    glutSolidCube(0.15);
    // Plant (cone) 
    setMaterial(0.2, 0.5, 0.2, 16.0, 0.3);  
    glTranslatef(0.0, 0.15, 0.0);
    glutSolidCone(0.1, 0.2, 10, 10);
    glPopMatrix();


    // Right side decorations 
    // Table lamp 
    setMaterial(0.4, 0.4, 0.4, 32.0, 0.7);  
    glPushMatrix();
    glTranslatef(1.2, 0.03, 0.0);
    // Lamp base 
    glPushMatrix();
    glScalef(0.2, 0.02, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    // Lamp rod 
    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.0);
    glRotatef(30.0, 0.0, 0.0, 1.0);
    glScalef(0.02, 0.4, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();
    // Lamp head 
    setMaterial(0.8, 0.8, 0.8, 16.0, 0.3);
    glPushMatrix();
    glTranslatef(-0.1, 0.35, 0.0);
    glRotatef(60.0, 0.0, 0.0, 1.0);
    glScalef(0.2, 0.05, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

// Wardrobe function
void drawWardrobe() {
    glPushMatrix();
    glTranslatef(3.0, 1.6, 5.8);  

    // Wardrobe body 
    setMaterial(0.6, 0.4, 0.2, 32.0, 0.5);
    glPushMatrix();
    glScalef(2.4, 4.4, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Left door 
    setMaterial(0.65, 0.45, 0.25, 32.0, 0.5);
    glPushMatrix();
    glTranslatef(-0.48, 0.36, 0.52);
    glScalef(0.96, 3.6, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Right door 
    glPushMatrix();
    glTranslatef(0.48, 0.36, 0.52);
    glScalef(0.96, 3.6, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Left door handle 
    setMaterial(0.7, 0.7, 0.7, 32.0, 0.8); 
    glPushMatrix();
    glTranslatef(-0.8, 0.0, 0.6);
    glScalef(0.05, 0.35, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Right door handle 
    glPushMatrix();
    glTranslatef(0.8, 0.0, 0.6);
    glScalef(0.05, 0.35, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Bottom legs 
    setMaterial(0.3, 0.3, 0.3, 32.0, 0.5);

    glPushMatrix();
    glTranslatef(-0.9, -1.95, 0.4);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9, -1.95, 0.4);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9, -1.95, -0.4);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9, -1.95, -0.4);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

// Pendulum clock
float pendulumAngle = 12.0;  //angle
float pendulumSpeed = 0.1;  // speed
bool pendulumDirection = true;  // direction

void drawPendulumClock() {
    glPushMatrix();
    glTranslatef(4.2, 3.0, 9.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);

    // Clock body 
    setMaterial(0.45, 0.25, 0.15, 32.0, 0.6);  
    glPushMatrix();
    glScalef(1.2, 3.0, 0.4);
    glutSolidCube(1.0);
    glPopMatrix();

    // Clock face 
    setMaterial(0.95, 0.93, 0.88, 16.0, 0.3);
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.25);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutSolidCylinder(0.4, 0.1, 32, 32);
    glPopMatrix();

    // Clock face decorative border 
    setMaterial(0.8, 0.6, 0.2, 32.0, 0.8);  
    glPushMatrix();
    glTranslatef(0.0, 0.7, 0.27);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutSolidTorus(0.03, 0.4, 16, 32);
    glPopMatrix();

    // Pendulum glass door 
    setMaterial(0.9, 0.95, 1.0, 16.0, 0.1);  
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.21);
    glScalef(1.1, 2.9, 0.02);
    glutSolidCube(1.0);
    glPopMatrix();

    // Pendulum pivot 
    setMaterial(0.85, 0.65, 0.2, 32.0, 0.9);  
    glPushMatrix();
    glTranslatef(0.0, 0.75, 0.0);
    glutSolidSphere(0.05, 16, 16);
    glPopMatrix();

    // Pendulum rod 
    setMaterial(0.85, 0.65, 0.2, 32.0, 0.9);  
    glPushMatrix();
    glTranslatef(0.0, 0.75, 0.2);
    glRotatef(pendulumAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.75, 0.0);
    glScalef(0.05, 1.5, 0.05);
    glutSolidCube(1.0);
    glPopMatrix();

    // Pendulum weight 
    setMaterial(0.82, 0.62, 0.18, 32.0, 1.0);  
    glPushMatrix();
    glTranslatef(0.0, 0.75, 0.2);
    glRotatef(pendulumAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.5, 0.0);
    glutSolidSphere(0.15, 16, 16);
    glPopMatrix();

    // Clock top decoration 
    setMaterial(0.43, 0.23, 0.13, 32.0, 0.6);  
    glPushMatrix();
    glTranslatef(0.0, 1.6, 0.0);
    glScalef(1.4, 0.3, 0.5);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}
// Update pendulum animation 
void updatePendulum() {
    const float maxAngle = 30.0;  // Maximum swing angle 

    if (pendulumDirection) {
        pendulumAngle += pendulumSpeed;
        if (pendulumAngle >= maxAngle) {
            pendulumDirection = false;
        }
    }
    else {
        pendulumAngle -= pendulumSpeed;
        if (pendulumAngle <= -maxAngle) {
            pendulumDirection = true;
        }
    }
}

// Bedroom lamp function
void drawBedroomLamp() {
    glPushMatrix();
    glTranslatef(0.0, 4.5, 10.5);

    // Ceiling lamp rod 
    setMaterial(0.4, 0.4, 0.4, 32.0, 0.8);
    glPushMatrix();
    drawCylinder(0.05, 1.0, 20);
    glPopMatrix();

    // Lamp shade
    if (bedroomLightOn) {
        // Brighter material when light is on, simulating glow
        setMaterial(1.0, 1.0, 0.9, 16.0, 0.2);
    }
    else {
        // Dimmer material when light is off
        setMaterial(0.8, 0.8, 0.8, 16.0, 0.1);
    }

    glPushMatrix();
    glTranslatef(0.0, -0.6, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glutSolidCone(0.4, 0.6, 16, 16);
    glPopMatrix();


    if (bedroomLightOn) {
        GLfloat lightPos[] = { 0.0, -0.8, 0.0, 1.0 };
        GLfloat lightColor[] = { 2.5, 2.4, 2.0, 1.0 };    
        GLfloat lightSpec[] = { 2.0, 2.0, 2.0, 1.0 };     
        GLfloat lightDir[] = { 0.0, -1.0, 0.0 };
        GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };  

        glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpec);
        glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);

        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 85.0);  
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.5);  
        glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.03);  
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDir);
    }
    else {
        GLfloat noLight[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat lowAmbient[] = { 0.1, 0.1, 0.1, 1.0 };  
        glLightfv(GL_LIGHT2, GL_DIFFUSE, noLight);
        glLightfv(GL_LIGHT2, GL_SPECULAR, noLight);
        glLightfv(GL_LIGHT2, GL_AMBIENT, lowAmbient);
    }
    glPopMatrix();
}

// Door animation update function
void updateDoor() {
    if (isDoorOpening) {
        doorAngle += DOOR_SPEED;
        if (doorAngle >= 90.0) {
            doorAngle = 90.0;
            isDoorOpening = false;
        }
    }
    else if (isDoorClosing) {
        doorAngle -= DOOR_SPEED;
        if (doorAngle <= 0.0) {
            doorAngle = 0.0;
            isDoorClosing = false;
        }
    }
}

// Add a timer function to handle gate animation
void timer(int value) {
    updateDoor();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // Update rate of about 60fps
}

// Prompt text drawing function
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// HUD drawing function
void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);

    float doorX = 0.0;
    float doorZ = 4.5;
    float distanceToDoor = sqrt(pow(cameraX - doorX, 2) + pow(cameraZ - doorZ, 2));

    if (distanceToDoor < 1.5) {
        glColor3f(0.0, 0.0, 0.0);
        const char* message = doorAngle > 0 ? "Press E to close" : "Press E to open the door";
        renderBitmapString(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50,
            glutGet(GLUT_WINDOW_HEIGHT) / 2 - 100,
            GLUT_BITMAP_HELVETICA_18,
            message);
    }

    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

//Collision detection
bool checkCollision(float nextX, float nextZ) {
    // Position of door and wall
    float doorX = 0.0f;
    float doorZ = 5.0f;
    float wallLeftStartX = -5.0f;
    float wallLeftEndX = -0.5f;
    float wallRightStartX = 0.5f;
    float wallRightEndX = 5.0f;
    float wallZ = 4.9f; 

    // Player size (assumed to be a point)
    float playerRadius = 0.5f;

    // Collision detection: middle divider wall (left)
    if (nextX >= wallLeftStartX && nextX <= wallLeftEndX && fabs(nextZ - wallZ) < playerRadius) {
        return true; // collide
    }

    // Middle divider wall (right)
    if (nextX >= wallRightStartX && nextX <= wallRightEndX && fabs(nextZ - wallZ) < playerRadius) {
        return true; 
    }

    // Closed door
    if (doorAngle == 0.0f) {
        if (nextX >= -0.5f && nextX <= 0.5f && fabs(nextZ - doorZ) < playerRadius) {
            return true; 
        }
    }

    return false;
}

//Texture
static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;

void loadTexture(const char* filename, int textureIndex) {
    FILE* pfile = NULL;
    fopen_s(&pfile, filename, "rb");
    if (pfile == 0) {
        printf("Failed to open texture file '%s'\n", filename);
        return;
    }

    fseek(pfile, 0x0012, SEEK_SET);
    fread(&imagewidth, sizeof(imagewidth), 1, pfile);
    fread(&imageheight, sizeof(imageheight), 1, pfile);

    pixellength = imagewidth * 3;
    while (pixellength % 4 != 0)
        pixellength++;
    pixellength *= imageheight;

    pixeldata = (GLubyte*)malloc(pixellength);
    if (pixeldata == 0) exit(0);

    fseek(pfile, 54, SEEK_SET);
    fread(pixeldata, pixellength, 1, pfile);
    fclose(pfile);

    // Create texture
    glGenTextures(1, &textureIDs[textureIndex]);
    glBindTexture(GL_TEXTURE_2D, textureIDs[textureIndex]);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagewidth, imageheight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);

    // Release pixel data
    free(pixeldata);
}

// Textured rectangles on the walls as baseboards
void drawTextureWall(int textureIndex) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIDs[textureIndex]);

    // Set material
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    // Draw rectangle
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Create four picture drawing functions in different positions
void drawPicture1() {
    glPushMatrix();
    glTranslatef(0.0, 3.0, -4.8);
    glScalef(1.6, 1.6, 1.0);
    drawTextureWall(0); 
    glPopMatrix();
}

void drawPicture2() {
    glPushMatrix();
    glTranslatef(-4.8, 3.0, 12.0);
    glRotatef(90.0, 0, 1, 0);
    glScalef(1.4, 1.4, 1.0);
    drawTextureWall(1);
    glPopMatrix();
}

void drawPicture3() {
    glPushMatrix();
    glTranslatef(4.8, 3.0, 12.0);
    glRotatef(-90.0, 0, 1, 0);
    glScalef(1.4, 1.4, 1.0);
    drawTextureWall(2);
    glPopMatrix();
}

void drawPicture4() {
    glPushMatrix();
    glTranslatef(0.0, 3.0, 14.8);
    glRotatef(180.0, 0, 1, 0); 
    glScalef(1.6, 1.6, 1.0);
    drawTextureWall(3);
    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the basic ambient light
    GLfloat ambientLight[] = { 0.16f, 0.16f, 0.16f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Set the base light color
    GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);

    glEnable(GL_LIGHTING);

    // Camera conversion
    glRotatef(cameraRotX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraRotY, 0.0f, 1.0f, 0.0f);
    glTranslatef(-cameraX, -cameraY, -cameraZ);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Draw the base scene
    drawRoom();
    drawSofa();
    drawTable();
    drawChair();
    drawFlowerPot();
    drawTV();
    drawDoor();
    drawComputerDesk();
    drawWardrobe();
    updatePendulum();
    drawPendulumClock();
    drawHUD();
    drawBed();
    drawBedroomLamp();
    drawCeilingLamp();
    drawFloorLamp();

    drawPicture1();
    drawPicture2();
    drawPicture3();
    drawPicture4();
   
    glutSwapBuffers();
    glutWarpPointer(windowCenterX, windowCenterY);
}

// Window resizing
void reshape(int w, int h) {
    windowCenterX = w / 2;
    windowCenterY = h / 2;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouseMove(int x, int y) {
    if (firstMouse) {
        windowCenterX = x;
        windowCenterY = y;
        firstMouse = false;
        return;
    }

    float deltaX = x - windowCenterX;
    float deltaY = y - windowCenterY;

    cameraRotY += deltaX * mouseSensitivity;
    cameraRotX += deltaY * mouseSensitivity;

    // Restricted vertical view
    if (cameraRotX > 89.0) cameraRotX = 89.0;
    if (cameraRotX < -89.0) cameraRotX = -89.0;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    float moveX = sin(cameraRotY * 3.14159 / 180.0) * moveSpeed;
    float moveZ = cos(cameraRotY * 3.14159 / 180.0) * moveSpeed;
    float nextX = cameraX;
    float nextZ = cameraZ;

    // Check to see if it's near the door
    float doorX = 0.0;
    float doorZ = 4.5;
    float distanceToDoor = sqrt(pow(cameraX - doorX, 2) + pow(cameraZ - doorZ, 2));

    switch (key) {
    case 'w':
        nextX += moveX;
        nextZ -= moveZ;
        break;
    case 's':
        nextX -= moveX;
        nextZ += moveZ;
        break;
    case 'a':
        nextX -= moveZ;
        nextZ -= moveX;
        break;
    case 'd':
        nextX += moveZ;
        nextZ += moveX;
        break;
    case 'e':
        // Open and close the door only when near the door
        if (distanceToDoor < 2.0) {
            if (doorAngle == 0.0) {
                isDoorOpening = true;
                isDoorClosing = false;
            }
            else if (doorAngle == 90.0) {
                isDoorClosing = true;
                isDoorOpening = false;
            }
        }
        break;
    case '1': // Switching ceilingLight
        ceilingLightOn = !ceilingLightOn;
        break;
    case '2': // Switching floorLamp
        floorLampOn = !floorLampOn;
        break;
    case '3': // Switching bedroomLight
        bedroomLightOn = !bedroomLightOn;
        break;
    case '4': // close all the light
        ceilingLightOn = false;
        floorLampOn = false;
        bedroomLightOn = false;
        break;
    case 27:  // ESC
        exit(0);
        break;
    }

    // Collision detection
    if (!checkCollision(nextX, nextZ)) {
        cameraX = nextX;
        cameraZ = nextZ;
    }

    if (cameraX < -4.5) cameraX = -4.5;
    if (cameraX > 4.5) cameraX = 4.5;
    if (cameraZ < -5.0) cameraZ = -5.0;
    if (cameraZ > 15.0) cameraZ = 15.0;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("3D Living Room & Bedroom");

    // Start color material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Example Initialize the OpenGL state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  
    glEnable(GL_LIGHT1);  
    glEnable(GL_LIGHT2);  
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    // Set light attenuation
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.02f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005f);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.005f);

    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.003f);

    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMove);
    glutTimerFunc(16, timer, 0);

    // Hide the mouse cursor
    glutSetCursor(GLUT_CURSOR_NONE);

    loadTexture("1.bmp", 0);
    loadTexture("2.bmp", 1);
    loadTexture("3.bmp", 2);
    loadTexture("4.bmp", 3);
    loadTexture("5.bmp", 4);  // Wallpaper texture
    loadTexture("6.bmp", 5);  // Floor texture
    loadTexture("7.bmp", 6);  // Backwall texture
    loadTexture("8.bmp", 7); // ceiling texture

    glutMainLoop();
    return 0;
}