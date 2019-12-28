#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <GL/glut.h>

class Cube {
  private:
    double v, w; // vertices and width
    float x, y, z; //coordinates
    float offset[3]; // Might have to worry about destructor of this later on
    float c[18]; // array of color values

  public:
    Cube() { // Constructor and color generator
      srand(static_cast<unsigned int>(clock()));
      for (int i=0; i <= 17; i++) {
        c[i] = double(rand()) / (double(RAND_MAX) + 1.0);
      }
    }

    void setOffset(float a, float b, float c) {
      glTranslatef(a, b, c);
      offset[0] = a;
      offset[1] = b;
      offset[2] = c;
    }

    void drawCube(float width) {
      w = width;
      v = width/2.0;

      glBegin(GL_QUADS);
        // Top
        glNormal3f(0.0, 1.0, 0.0);
        glColor3f(c[0], c[1], c[2]);
        glVertex3f(v, v, -v);
        glVertex3f(-v, v, -v);
        glVertex3f(-v, v, v);
        glVertex3f(v, v, v);
        // Bottom
        glNormal3f(0.0, -1.0, 0.0);
        glColor3f(c[3], c[4], c[5]);
        glVertex3f(v, -v, v);
        glVertex3f(-v, -v, v);
        glVertex3f(-v, -v, -v);
        glVertex3f(v, -v, -v);
        // Front
        glNormal3f(0.0, 0.0, 1.0);
        glColor3f(c[6], c[7], c[8]);
        glVertex3f(v, v, v);
        glVertex3f(-v, v, v);
        glVertex3f(-v, -v, v);
        glVertex3f(v, -v, v);
        // Back
        glNormal3f(0.0, 0.0, -1.0);
        glColor3f(c[9], c[10], c[11]);
        glVertex3f(v, -v, -v);
        glVertex3f(-v, -v, -v);
        glVertex3f(-v, v, -v);
        glVertex3f(v, v, -v);
        // Left
        glNormal3f(-1.0, 0.0, 0.0);
        glColor3f(c[12], c[13], c[14]);
        glVertex3f(-v, v, v);
        glVertex3f(-v, v, -v);
        glVertex3f(-v, -v, -v);
        glVertex3f(-v, -v, v);
        // Right
        glNormal3f(1.0, 0.0, 0.0);
        glColor3f(c[15], c[16], c[17]);
        glVertex3f(v, v, -v);
        glVertex3f(v, v, v);
        glVertex3f(v, -v, v);
        glVertex3f(v, -v, -v);
      glEnd();

    }

    void getCoordinates() {
      x = (w - v) + offset[0];
      y = (w - v) + offset[1];
      z = (w - v) + offset[2];
      std::cout << x << ", " << y << ", " << z << "," << std::endl;
    }

};


class Tetrahedron {
  private:
    float x, y, z; // Hopefully use to track coordinates
    float offset[3]; // x, y, z of offset
    float c[12]; // Color values

  public:
    Tetrahedron() { // Constructor and color generator
      srand(static_cast<unsigned int>(clock()));
      for (int i=0; i <= 11; i++) {
        c[i] = double(rand()) / (double(RAND_MAX) + 1.0);
      }
    }


    void setOffset(float a, float b, float c) {
      glTranslatef(a, b, c);

      offset[0] = a;
      offset[1] = b;
      offset[2] = c;
    }

    void drawTetrahedron() {
      glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0, 1.0, 0.5);
        glVertex3f(0, 2, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(-1, 0, 1);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(1, 0, 1);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(0, 0, -1.4);
        glVertex3f(0, 2, 0);
        glVertex3f(-1, 0, 1);
      glEnd();
    }
};
