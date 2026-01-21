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

//catch


void drawCatcher()
{
    //Stand
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.015f, 0.04f);
    glVertex2f(0.015f, 0.04f);
    glVertex2f(0.015f, -0.15f);
    glVertex2f(-0.015f, -0.15f);
    glEnd();

    //FrontSqure
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.07f, 0.18f);
    glVertex2f(0.07f, 0.18f);
    glVertex2f(0.07f, 0.06f);
    glVertex2f(-0.07f, 0.06f);
    glEnd();

    //Line
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(-0.12f, 0.06f);
    glVertex2f(0.12f, 0.06f);
    glEnd();

    //Net
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    glVertex2f(-0.10f, 0.06f);
    glVertex2f(-0.06f, -0.08f);

    glVertex2f(-0.06f, 0.06f);
    glVertex2f(-0.036f, -0.08f);

    glVertex2f(-0.02f, 0.06f);
    glVertex2f(-0.012f, -0.08f);

    glVertex2f(0.02f, 0.06f);
    glVertex2f(0.012f, -0.08f);

    glVertex2f(0.06f, 0.06f);
    glVertex2f(0.036f, -0.08f);

    glVertex2f(0.10f, 0.06f);
    glVertex2f(0.06f, -0.08f);

    //Horizontal line
    glVertex2f(-0.08f, -0.01f);
    glVertex2f(0.08f, -0.01f);

    glEnd();
}

//ship

//ship

//ship

//ship

//ship

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (currentScene == Menu)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText("--- MAIN Menu ---", -0.2f, 0.4f);
        drawText("Press '1' for Catch Game", -0.3f, 0.1f);
        drawText("Press '2' for Ship Animation", -0.3f, -0.1f);
    }
    else if (currentScene == CatchGame)
    {
        drawBackground();
        if (!gameOver)
        {
            string scoreTxt = "Catch Score : " + to_string(score);
            glColor3f(1.0f, 1.0f, 1.0f);
            drawText(scoreTxt, -0.9f, 0.8f);
            drawText("Press 'M' for Menu", -0.9f, 0.7f);

            glPushMatrix();
            glTranslatef(catcherX, -0.7f, 0);
            drawCatcher();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(objX, objY, 0);
            if (shapeType == 0) drawBottle();
            else drawBasketball();
            glPopMatrix();
        }
        else
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            drawText("GAME OVER", -0.15f, 0.0f);
            drawText("Press 'R' to Restart or 'M' for Menu", -0.35f, -0.15f);
        }
    }

//ship

}

void update(int value)
{
    if (currentScene == CatchGame && !gameOver)
    {
        objY -= FallingSpeed;
        if (objY <= -0.58f && objY >= -0.72f)
        {
            if (objX >= catcherX - 0.15f && objX <= catcherX + 0.15f)
            {
                score++;
                objY = 1.1f;
                objX = ((rand() % 160) - 80) / 100.0f;
                shapeType = rand() % 2;
            }
        }
        if (objY < -1.0f) gameOver = true;
    }

    //ship


}
