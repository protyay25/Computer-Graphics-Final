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

float shipX = -1.4f;
float shipY = 0.12f;
float sink = 0.0f;
float angle_ship = 0.0f;
float waveOffset = 0.0f;
bool hit = false;


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



void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float rad = i * 3.1416f / 180.0f;
        glVertex2f(cx + cos(rad) * r, cy + sin(rad) * r);
    }
    glEnd();
}

void beautifulBackground()
{
    glBegin(GL_QUADS);
    glColor3f(0.01f, 0.01f, 0.1f);
    glVertex2f(-1, 1);
    glVertex2f( 1, 1);
    glColor3f(0.1f, 0.1f, 0.3f);
    glVertex2f( 1, -0.3f);
    glVertex2f(-1, -0.3f);
    glEnd();

    glPointSize(1.5);
    glBegin(GL_POINTS);
    for (float x = -1; x <= 1; x += 0.12f)
    {
        for (float y = -0.1f; y <= 1; y += 0.15f)
        {
            float blink = 0.5f + 0.5f * sin(x * 10 + waveOffset);
            glColor3f(blink, blink, blink);
            glVertex2f(x, y);
        }
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 0.8f);
    drawCircle(-0.6f, 0.7f, 0.08f);
}

void iceberg()
{
    glColor3f(0.8f, 0.95f, 1.0f);
    glRectf(0.50f, -0.3f, 0.68f, 0.15f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(0.65f, -0.3f, 0.85f, 0.40f);
}

void sea()
{
    float blockWidth = 0.05f;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (float x = -1.0f; x <= 1.0f; x += blockWidth)
    {
        float h = 0.025f * sin(x * 7.0f + waveOffset);
        glColor4f(0.0f, 0.3f, 0.6f, 0.9f);
        glBegin(GL_QUADS);
        glVertex2f(x, -0.3f + h);
        glVertex2f(x + blockWidth, -0.3f + h);
        glVertex2f(x + blockWidth, -1.0f);
        glVertex2f(x, -1.0f);
        glEnd();
    }
    glDisable(GL_BLEND);
}

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

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1') currentScene = CatchGame;
    if (key == '2') currentScene = ShipAnimation;
    if (key == 'm' || key == 'M') currentScene = Menu;

    if (currentScene == CatchGame)
    {
        if (key == 'a' && catcherX > -0.8f) catcherX -= MoveSpeed;
        if (key == 'd' && catcherX < 0.8f)  catcherX += MoveSpeed;
        if ((key == 'r' || key == 'R') && gameOver)
        {
            gameOver = false;
            score = 0;
            objY = 1.1f;
            catcherX = 0.0f;
            objX = ((rand() % 160) - 80) / 100.0f;
        }
    }
}

