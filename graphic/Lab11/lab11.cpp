#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include "windows.h"
#define MAX_CHAR 128
typedef struct { GLfloat x, y; } point;
point P1 = { 130,270 }, P2 = { 350,350 };
GLfloat win_x = 600, win_y = 600;
GLfloat win_x_left = win_x / 3, win_x_right = win_x / 3 * 2, win_y_bottom = win_y / 3, win_y_top = win_y / 3 * 2;

// Outcode definitions for Cohen-Sutherland
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

// Get outcode for a point
int computeOutcode(point p, GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax) {
    int code = INSIDE;
    if (p.x < xmin) code |= LEFT;
    else if (p.x > xmax) code |= RIGHT;
    if (p.y < ymin) code |= BOTTOM;
    else if (p.y > ymax) code |= TOP;
    return code;
}

// Draw a line with stipple (dashed line)
void PlotDashedLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF); // Dashed pattern
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

// Cohen-Sutherland Line Clipping
void CohenSutherlandClip(point P1, point P2) {
    int outcode1 = computeOutcode(P1, win_x_left, win_x_right, win_y_bottom, win_y_top);
    int outcode2 = computeOutcode(P2, win_x_left, win_x_right, win_y_bottom, win_y_top);
    bool accept = false;

    while (true) {
        if (!(outcode1 | outcode2)) { // Both points inside
            accept = true;
            break;
        }
        else if (outcode1 & outcode2) { // Both points share an outside region
            break;
        }
        else {
            GLfloat x, y;
            int outcodeOut = outcode1 ? outcode1 : outcode2;
            if (outcodeOut & TOP) {
                x = P1.x + (P2.x - P1.x) * (win_y_top - P1.y) / (P2.y - P1.y);
                y = win_y_top;
            }
            else if (outcodeOut & BOTTOM) {
                x = P1.x + (P2.x - P1.x) * (win_y_bottom - P1.y) / (P2.y - P1.y);
                y = win_y_bottom;
            }
            else if (outcodeOut & RIGHT) {
                y = P1.y + (P2.y - P1.y) * (win_x_right - P1.x) / (P2.x - P1.x);
                x = win_x_right;
            }
            else if (outcodeOut & LEFT) {
                y = P1.y + (P2.y - P1.y) * (win_x_left - P1.x) / (P2.x - P1.x);
                x = win_x_left;
            }

            if (outcodeOut == outcode1) {
                P1.x = x;
                P1.y = y;
                outcode1 = computeOutcode(P1, win_x_left, win_x_right, win_y_bottom, win_y_top);
            }
            else {
                P2.x = x;
                P2.y = y;
                outcode2 = computeOutcode(P2, win_x_left, win_x_right, win_y_bottom, win_y_top);
            }
        }
    }

    if (accept) {
        // Draw the clipped part as a solid line
        glColor3f(0, 1, 0); // Green for clipped line
        PlotDashedLine(P1.x, P1.y, P2.x, P2.y);
    }

    // Draw the outside portion as dashed line
    glColor3f(1, 0, 0); // Red for outside line
    if (computeOutcode(P1, win_x_left, win_x_right, win_y_bottom, win_y_top) != INSIDE)
        PlotDashedLine(P1.x, P1.y, P2.x, P2.y);
}

// Drawing function
void renderScene(void) {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw regions with dashed lines
    glColor3f(1, 1, 1);
    PlotDashedLine(0, win_y_top, win_x, win_y_top);
    PlotDashedLine(0, win_y_bottom, win_x, win_y_bottom);
    PlotDashedLine(win_x_left, 0, win_x_left, win_y);
    PlotDashedLine(win_x_right, 0, win_x_right, win_y);

    // Perform line clipping
    CohenSutherlandClip(P1, P2);

    glutSwapBuffers();
}

// Initialization
void myinit(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, win_x, 0, win_y);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(win_x, win_y);
    glutCreateWindow("Cohen-Sutherland 2D Line Clipping");
    myinit();
    glutDisplayFunc(renderScene);
    glutMainLoop();
    return 0;
}
