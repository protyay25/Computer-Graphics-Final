#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

enum Scene { Menu, CatchGame, ShipAnimation };
Scene currentScene = Menu;

constexpr float FallingSpeed = 0.015f;
constexpr float MoveSpeed = 0.12f;
constexpr float PI = 3.1416f;

float catcherX = 0.0f;
float objX = 0.0f;
float objY = 1.1f;
int shapeType = 0;
bool gameOver = false;
int score = 0;

//Ship


void drawText(const string& text, float x, float y)
{
    glRasterPos2f(x, y);
    for (int i = 0; i < text.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}


//Catch

//catch



void drawBasketball()
{

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++)
    {
        float angle = 2.0f * PI * i / 30.0f;
        glVertex2f(0.05f * cos(angle), 0.05f * sin(angle));
    }
    glEnd();
    
    //BallLines
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.05f);
    glVertex2f(0.0f, -0.05f);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glEnd();
}