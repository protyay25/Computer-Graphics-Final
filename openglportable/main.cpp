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