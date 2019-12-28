//Zane Paksi Project 2

#include <iostream>
#include <GL/glut.h>

using namespace std;

void handleKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 27:
      exit(EXIT_SUCCESS);
  }
}

void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

void handleResize(int w, int h) {

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _cameraAngle = 10.0;
float _angle = 30.0;

void drawScene() {
  //Clears info from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW); // Switches to the drawing perspective
  glLoadIdentity(); // Resets the drawing perspective
  //glRotatef(-_cameraAngle, 0.0, 1.0, 0.0);
  glTranslatef(5.0, 0.0, -20.0);
  glRotatef(_angle, 0.0, -2.0, 0.0);
  glPushMatrix();
    glutWireDodecahedron();
  glPopMatrix();

  glLoadIdentity();
  //sets the initial position of before the rotations
  glPushMatrix(); //saves the current translation
  glTranslatef(0.0, -3.0, -20.0);

  glRotatef(_angle, 1.0, 5.0, 0.0);

  glBegin(GL_TRIANGLES);
    // Front
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f( 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    // Right
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Back
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    // Left
    glColor3f(1.0,0.0,0.0);
    glVertex3f( 0.0, 1.0, 0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(-1.0,-1.0, 1.0);
  glEnd();   // Done drawing the pyramid

  glPopMatrix();

  glLoadIdentity(); // Reset model-view matrix
  glTranslatef(0, 1.0, -25.0);

  //This is the motion for the shape, and the center of rotation or orbit is the above translation.
  glRotatef(_angle, 2.0, -4.0, -3.0);

  glTranslatef(0.0, -4.0, 8.0); // this affects the orbit around the triangle

  glBegin(GL_QUADS);
    // Define vertices counter-clockwise
    //Top
    glColor3f(0.0, 1.0, 0.5);
    glVertex3f( 1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0,  1.0);
    glVertex3f( 1.0, 1.0,  1.0);
    //Bottom
    glColor3f(1.0, 0.5, 1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    //Front
    glColor3f(1.0, 0.0, 0.5);
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);
    //Back
    glColor3f(1.0, 1.0, 0.0);     // Yellow
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    //Left
    glColor3f(0.0, 0.0, 1.0);     // Blue
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    //Right
    glColor3f(1.0, 0.0, 1.0);     // Magenta
    glVertex3f(1.0,  1.0, -1.0);
    glVertex3f(1.0,  1.0,  1.0);
    glVertex3f(1.0, -1.0,  1.0);
    glVertex3f(1.0, -1.0, -1.0);
  glEnd();

  glutSwapBuffers(); //This sends the 3D scene to the screen

}

void update(int value) {
  _angle += 2.0;
  if (_angle > 360) {
    _angle -= 360;
  }
  glutPostRedisplay(); //Tell GLUT the scene had changed

  //Tell glut to call the update again in 25 milliseconds
  glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
  //Initializing GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);

  // Here is for creating the window
  glutCreateWindow("Project 2 | Zane Paksi");
  initRendering();

  //Setting Handler functions
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeys);
  glutReshapeFunc(handleResize);
  glutTimerFunc(25, update, 0);

  glutMainLoop(); //Start the main loop
  return 0;

}
