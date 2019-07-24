#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/glut.h>
#include <iostream>
#include <map>

using namespace std;

int nos = 3;
double angle, increment, a, b;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.5, 0.5, 0.0);

  glBegin(GL_POLYGON);
  angle = ((360 / nos) * M_PI) / 180;
  increment = angle; // this is how we travel around the unit circle.

  for (int i =0; i < nos; i++) {
    //calculate x and y, then add to dictionary
    a = cos(angle); //x
    b = sin(angle); //y
    glVertex2f(a,b);
    angle += increment; //Move to the next point
  }
  glEnd();
  //Flush drawing to screen
  glFlush();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 27:
      exit(EXIT_SUCCESS);
    case 'q':
      nos = 3;
      break;
      //change number of vertices and pass to calculate
    case 'w':
      nos = 4;
      break;
      //change number of vertices
    case 'e':
      nos = 5;
      break;
      //change number of vertices
    case 'r':
      nos = 6;
      break;
      //change number of vertices
    case 't':
      nos = 8;
      break;
      //change number of vertices
    case 'y':
      nos = 9;
      break;
      //change number of vertices
  }
}

int main(int argc, char** argv) {
  glutInit(&argc,argv);
  glutCreateWindow("Geometric Shapes");
  glutKeyboardFunc(keyboard);
  glutIdleFunc(display); //REFERENCE THE DISPLAY FUNCTION HERE
  glutMainLoop();
  return (EXIT_SUCCESS);
}

//g++ geometricShapes0.cpp -o geo -lglut -lGLU -lGL
