//Zane Paksi Project 3
#include "new_camera.h"

//#include "terrain.cpp"

using namespace std;

Cube cube1;
Tetrahedron tet1;

GLint windowWidth = 800;
GLint windowHeight = 600;

Camera *userCamera;

GLint windowMidX = windowWidth / 2;
GLint windowMidY = windowHeight / 2;

void handleDownKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 27:
      exit(EXIT_SUCCESS);
    case 'w':
      glutIgnoreKeyRepeat('w');
      userCamera->holdForward = true;
      break;
    case 'a':
      glutIgnoreKeyRepeat('a');
      userCamera->holdLeft = true;
      break;
    case 's':
      glutIgnoreKeyRepeat('s');
      userCamera->holdBackward = true;
      break;
    case 'd':
      glutIgnoreKeyRepeat('d');
      userCamera->holdRight = true;
      break;
    default:
      // Do nothing
      break;
  }
}

void handleUpKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      userCamera->holdForward = false;
      break;
    case 'a':
      userCamera->holdLeft = false;
      break;
    case 's':
      userCamera->holdBackward = false;
      break;
    case 'd':
      userCamera->holdRight = false;
      break;
    default:
      // Do nothing
      break;
  }
}

void mouseMove(int mouseX, int mouseY) {
  userCamera->handleMouseMove(mouseX, mouseY);

}

void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glClearColor(1.0, 0.0, 0.0, 0.0);
}

void handleResize(int w, int h) {

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
  windowMidX = w / 2.0;
  windowMidY = h / 2.0;
}

float _cameraAngle = 10.0;
float _angle = 30.0;

void drawScene() {
  //Clears info from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW); // Switches to the drawing perspective
  glLoadIdentity(); // Resets the drawing perspective

  // Camera movements
  glRotatef(userCamera->getXRot(), 1.0, 0.0, 0.0); //Rotate camera on x-axis
  glRotatef(userCamera->getYRot(), 0.0, 1.0, 0.0); //Rotate camera on y-axis

  // Translate ModelView Matrix to the position of our camera
  glTranslatef(-userCamera->getXPos(), -userCamera->getYPos(), -userCamera->getZPos());
  //glRotatef(-_cameraAngle, 0.0, 1.0, 0.0);

  //glTranslatef(0.0, -10.0, 0.0);

  glPushMatrix();
  cube1.setOffset(0.0, 0.0, -10.0);
  glRotatef(_angle, 0.0, 1.0, 0.0);
  cube1.drawCube(2.0);
  glPopMatrix();

  tet1.setOffset(-5.0, 0.0, -5.0);
  glPushMatrix();
  glRotatef(_angle, 0.0, 1.0, 0.0);
  tet1.drawTetrahedron();
  glPopMatrix();

  glTranslatef(10.0, 0.0, 0.0);
  glPushMatrix();
    glRotatef(_angle, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(2.0, 50.0, 50.0);
    glColor3f(1.0, 0.5, 0.5);
    glutSolidSphere(2.0, 100.0, 100.0);
  glPopMatrix();

  //glFrustum(-2, 2, -1.5, 1.5, 1, 40);

  glPushMatrix(); // Failed attempt to draw certain grid
  glBegin(GL_LINES);
  glColor3f(1.0, 1.0, 1.0);
  for(int i = 0; i <= 1000; i++) {
    glVertex3f((float)i, 0.0f, 0.0f);
    glVertex3f((float)i, 0.0f, 0.0f);
    glVertex3f(0.0f, (float)i, 0.0f);
    glVertex3f(100.0f, (float)i, 0.0f);
  }
  glEnd();
  glPopMatrix();
  /* Terrain drawing, scaling and translations (Multiple different attempts)

  float scale = 5.0 / max(_terrain->width() - 1, _terrain->length() - 1);
  glScalef(scale, scale, scale);
  glTranslatef(-float(_terrain->width()) / 2, 0.0, -float(_terrain->length()) / 2);

  glColor3f(0.3, 0.9, 0.0);
  for (int z = 0; z < _terrain->length() - 1; z++) {
    // Drawing triangle every 3 vertices
    glBegin(GL_TRIANGLE_STRIP);
      for (int x; x < _terrain->width(); x++) {
        Vec3f normal = _terrain->getNormal(x, z);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(x, _terrain->getHeight(x, z), z);

        normal = _terrain->getNormal(x, z + 1);
        glNormal3f(normal[0], normal[1], normal[2]);
        glVertex3f(x, _terrain->getHeight(x, z + 1), z + 1);
      }
    glEnd();
  }
  */


  glutSwapBuffers(); //This sends the 3D scene to the screen

}

void update(int value) {
  _angle += 1.0;
  if (_angle > 360) {
    _angle -= 360;
  }

  glutPostRedisplay(); //Tell GLUT the scene had changed

  userCamera->move(0.01);
  //Tell glut to call the update again in 16 milliseconds
  glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
  //Initializing GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  userCamera = new Camera(windowWidth, windowHeight);
  //_terrain = loadTerrain("heightmap.png", 20);
  glutInitWindowSize(windowWidth, windowHeight);

  // Here is for creating the window
  glutCreateWindow("Project 3");
  initRendering();

  //Setting Handler functions
  glutDisplayFunc(drawScene);
  glutPassiveMotionFunc(mouseMove);
  glutKeyboardFunc(handleDownKeys);
  glutKeyboardUpFunc(handleUpKeys);
  glutReshapeFunc(handleResize);
  glutTimerFunc(25, update, 0);

  glutMainLoop(); //Start the main loop
  return 0;

}
