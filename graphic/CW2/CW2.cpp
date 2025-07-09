#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global variable definitions
int intWinWidth = 800;    // Default window width
int intWinHeight = 600;   // Default window height

// Animation-related variables
float fltAnimationOffset = 0.0f;    // Road animation offset
float fltTreeOffset = -2500.0f;     // Trees animation offset
float fltBuildingOffset = -2500.0f; // Buildings animation offset
float fltAcceleration = 4.0f;       // Animation speed
float fltColourVal1 = 0.5f;         // First color value
float fltColourVal2 = 0.7f;         // Second color value
float fltColourVal3 = 0.4f;         // Third color value
float fltFOV = 70.0f;               // Field of View

// Camera parameter adjustments
float fltX0 = 0.0f;     // Camera position X
float fltY0 = 20.0f;    // Camera position Y
float fltZ0 = -100.0f;  // Camera position Z
float fltXRef = 0.0f;   // Reference point X
float fltYRef = 0.0f;   // Reference point Y
float fltZRef = -200.0f; // Reference point Z

float fltXUp = 0.0f;    // Up vector X
float fltYUp = 1.0f;    // Up vector Y
float fltZUp = 0.0f;    // Up vector Z

// Camera lateral offset (left/right movement)
float fltXOffset = 0.0f; // Camera lateral offset

// Structure to represent a pedestrian
struct Pedestrian {
    float x;      // X position
    float y;      // Y position
    float z;      // Z position
    float speed;  // Movement speed
};

// Vector to hold multiple pedestrians
std::vector<Pedestrian> pedestrians;

// Initialize pedestrians
void initPedestrians(int count) {
    for (int i = 0; i < count; ++i) {
        Pedestrian p;
        p.x = ((rand() % 100) - 50); // Random X between -50 and 50
        p.y = 0.0f;
        p.z = (rand() % 5000) - 2500.0f; // Random Z position along the road
        p.speed = 1.0f + (rand() % 5) * 0.5f; // Random speed between 1.0 and 3.5
        pedestrians.push_back(p);
    }
}

// Initialize lighting
void initLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = { 0.0f, 100.0f, -100.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Enable color material so that glColor affects material properties
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Set global material properties
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

// Function to draw a pedestrian with more detail
void drawPedestrian(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    // Draw the body
    glColor3f(0.0f, 0.0f, 1.0f); // Blue shirt
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f);
    glScalef(2.0f, 5.0f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the head
    glColor3f(1.0f, 0.8f, 0.6f); // Skin color
    glPushMatrix();
    glTranslatef(0.0f, 12.0f, 0.0f);
    glutSolidSphere(1.5f, 16, 16);
    glPopMatrix();

    // Draw the legs
    glColor3f(0.0f, 0.0f, 0.0f); // Black pants
    // Left leg
    glPushMatrix();
    glTranslatef(-0.5f, 5.0f, 0.0f);
    glScalef(0.5f, 5.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Right leg
    glPushMatrix();
    glTranslatef(0.5f, 5.0f, 0.0f);
    glScalef(0.5f, 5.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the arms
    glColor3f(0.0f, 0.0f, 1.0f); // Blue shirt
    // Left arm
    glPushMatrix();
    glTranslatef(-1.5f, 12.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 3.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    // Right arm
    glPushMatrix();
    glTranslatef(1.5f, 12.0f, 0.0f);
    glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 3.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Animation function
void animateScene()
{
    // Increase animation variables
    fltAnimationOffset += fltAcceleration;
    if (fltAnimationOffset >= 200.0f)
        fltAnimationOffset = 0.0f;

    fltTreeOffset += fltAcceleration;
    if (fltTreeOffset >= 2500.0f)
        fltTreeOffset = -2500.0f;

    fltBuildingOffset += fltAcceleration;
    if (fltBuildingOffset >= 2500.0f)
        fltBuildingOffset = -2500.0f;

    // Animate pedestrians
    for (auto& p : pedestrians) {
        p.z += fltAcceleration; // Move pedestrian forward
        if (p.z > 2500.0f) {    // Reset position if out of view
            p.z = -2500.0f;
            p.x = ((rand() % 100) - 50); // Random X position
            p.speed = 1.0f + (rand() % 5) * 0.5f; // Random speed
        }
    }

    glutPostRedisplay();
}

// Draw the road
void drawRoad()
{
    // Draw the road
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, fltAnimationOffset);
    glScalef(120.0f, 2.0f, 5000.0f);
    glColor3f(0.2f, 0.2f, 0.2f); // Dark gray road
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw lane markings
    glColor3f(1.0f, 1.0f, 1.0f); // White lane markings
    for (int i = -2500; i < 2500; i += 100)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.1f, i + fltAnimationOffset);
        glScalef(3.0f, 0.1f, 50.0f); // Adjust the width and thickness of the lane markings
        glutSolidCube(1.0f);
        glPopMatrix();
    }
}

// Draw the speed limit sign
void drawSign()
{
    // Draw the pole
    glColor3f(0.5f, 0.5f, 0.5f); // Gray pole
    glPushMatrix();
    glTranslatef(0.0f, 10.0f, 0.0f); // Pole height is 20 units, so translate Y by 10 units
    glScalef(1.0f, 20.0f, 1.0f); // Pole dimensions
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw the sign face, changed to circular shape
    glColor3f(1.0f, 1.0f, 1.0f); // White sign face
    glPushMatrix();
    glTranslatef(0.0f, 20.0f, 0.0f); // Sign face is at the top of the pole
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate to face forward
    glutSolidCylinder(5.0f, 0.2f, 32, 1); // Use a thin cylinder to simulate a disk
    glPopMatrix();

    // Draw the lamp bulb (spherical)
    glEnable(GL_LIGHTING); // Enable lighting
    glEnable(GL_LIGHT1);   // Enable second light
    GLfloat light1Pos[] = { 0.0f, 24.0f, 0.0f, 1.0f };
    GLfloat light1Color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Color);

    glColor3f(1.0f, 1.0f, 0.0f); // Set bulb color to yellow
    glPushMatrix();
    glTranslatef(0.0f, 24.0f, 0.0f); // Place bulb on top of the sign
    glutSolidSphere(4.0f, 32, 32);    // Draw sphere (bulb)
    glPopMatrix();

    glDisable(GL_LIGHT1);  // Disable light source
}

// Draw the scene (buildings, trees, ground)
void drawScene()
{
    // Draw buildings on both sides of the road
    glColor3f(fltColourVal1, fltColourVal2, fltColourVal3); // Building color
    glPushMatrix();
    glTranslatef(-300.0f, 50.0f, fltBuildingOffset);
    glScalef(100.0f, 100.0f, 1000.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(fltColourVal3, fltColourVal1, fltColourVal2); // Building color
    glPushMatrix();
    glTranslatef(300.0f, 50.0f, fltBuildingOffset);
    glScalef(100.0f, 100.0f, 1000.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw speed limit signs on both sides of the road
    for (int i = -10; i < 10; i++)
    {
        // Left side sign
        glPushMatrix();
        glTranslatef(-100.0f, 0.0f, i * 500 + fltTreeOffset);
        drawSign();
        glPopMatrix();

        // Right side sign
        glPushMatrix();
        glTranslatef(100.0f, 0.0f, i * 500 + fltTreeOffset);
        drawSign();
        glPopMatrix();
    }

    // Draw trees on both sides of the road
    glColor3f(0.55f, 0.27f, 0.07f); // Trunk color
    for (int i = -25; i < 25; i++)
    {
        // Left side trees
        glPushMatrix();
        glTranslatef(-150.0f, 0.0f, i * 100 + fltTreeOffset);

        // Draw trunk
        glPushMatrix();
        glTranslatef(0.0f, 15.0f, 0.0f);
        glScalef(5.0f, 30.0f, 5.0f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Draw canopy
        glColor3f(0.0f, 0.6f, 0.0f); // Base layer canopy color
        for (int j = 0; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(0.0f, 30.0f + j * 10.0f, 0.0f); // Base height 30, increase per layer
            float scale = 1.0f - j * 0.2f; // Canopy gets smaller per layer
            glScalef(scale, scale, scale);
            glutSolidSphere(15.0f, 16, 16);
            glPopMatrix();

            glColor3f(0.0f, 0.6f + j * 0.1f, 0.0f); // Slightly lighter color for upper layers
        }
        glPopMatrix();

        // Right side trees
        glPushMatrix();
        glTranslatef(150.0f, 0.0f, i * 100 + fltTreeOffset);

        // Draw trunk
        glPushMatrix();
        glTranslatef(0.0f, 15.0f, 0.0f);
        glScalef(5.0f, 30.0f, 5.0f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Draw canopy
        glColor3f(0.0f, 0.6f, 0.0f); // Base layer canopy color
        for (int j = 0; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(0.0f, 30.0f + j * 10.0f, 0.0f); // Base height 30, increase per layer
            float scale = 1.0f - j * 0.2f; // Canopy gets smaller per layer
            glScalef(scale, scale, scale);
            glutSolidSphere(15.0f, 16, 16);
            glPopMatrix();

            glColor3f(0.0f, 0.6f + j * 0.1f, 0.0f); // Slightly lighter color for upper layers
        }
        glPopMatrix();
    }

    // Draw the ground
    glColor3f(0.3f, 1.0f, 0.2f); // Green grass
    glPushMatrix();
    glTranslatef(0.0f, -10.0f, 0.0f);
    glScalef(5000.0f, 10.0f, 5000.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw pedestrians
    for (const auto& p : pedestrians) {
        drawPedestrian(p.x, p.y, p.z);
    }
}

// Display callback function
void displayObject()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fltFOV, (float)intWinWidth / (float)intWinHeight, 0.1, 5000);

    // Set modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Update camera position and reference point based on lateral offset
    float fltCameraX = fltX0 + fltXOffset;
    float fltCameraXRef = fltXRef + fltXOffset;

    gluLookAt(fltCameraX, fltY0, fltZ0, fltCameraXRef, fltYRef, fltZRef, fltXUp, fltYUp, fltZUp);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set background color
    glClearColor(0.5f, 0.8f, 0.92f, 0.0f); // Sky blue background

    // Draw the scene
    drawScene();
    drawRoad();

    glutSwapBuffers();
}

// Window reshape callback function
void reshapeWindow(GLint intNewWidth, GLint intNewHeight)
{
    intWinWidth = intNewWidth;
    intWinHeight = intNewHeight;
    glViewport(0, 0, intNewWidth, intNewHeight);
}

// Keyboard input callback function
void adjustDisplay(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '-':
    case '_':
        fltAcceleration -= 0.5f; // Decelerate
        if (fltAcceleration < 0.0f)
            fltAcceleration = 0.0f; // Prevent negative speed
        break;
    case '=':
    case '+':
        fltAcceleration += 0.5f; // Accelerate
        break;
    case 's':
    case 'S':
        if (fltY0 > 10.0f)
            fltY0 -= 5.0f; // Move camera down
        break;
    case 'w':
    case 'W':
        if (fltY0 < 100.0f)
            fltY0 += 5.0f; // Move camera up
        break;
    case 'a':
    case 'A':
        fltXOffset -= 5.0f; // Move left
        if (fltXOffset < -50.0f)
            fltXOffset = -50.0f; // Limit left movement
        break;
    case 'd':
    case 'D':
        fltXOffset += 5.0f; // Move right
        if (fltXOffset > 50.0f)
            fltXOffset = 50.0f; // Limit right movement
        break;
    }
    glutPostRedisplay();
}

// Initialize the scene
void initScene()
{
    // Initialize pedestrians
    initPedestrians(20); // Add 20 pedestrians
}

// Main function
int main(int argc, char** argv)
{
    // Initialize GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(intWinWidth, intWinHeight);
    glutCreateWindow("First-Person Driving Simulation with Pedestrians");

    // Initialize lighting
    initLighting();

    // Initialize scene objects
    initScene();

    // Register callback functions
    glutDisplayFunc(displayObject);
    glutReshapeFunc(reshapeWindow);
    glutKeyboardFunc(adjustDisplay);
    glutIdleFunc(animateScene);

    glutMainLoop();
    return 0;
}
