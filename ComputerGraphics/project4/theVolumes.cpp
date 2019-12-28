#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <GL/glut.h>
#include "theVec3.hpp" // Custom Vec3 class

class Volume {
  protected:
    float x, y, z; //coordinates
    double offset[3]; // Might have to worry about destructor of this later on
    float c[18]; // array of color values

  public:
    Vec3<double> vPosition;

    Volume() { // Constructor and color generator
      srand(static_cast<unsigned int>(clock()));
      for (int i=0; i <= 17; i++) {
        c[i] = double(rand()) / (double(RAND_MAX) + 1.0);
      }

      vPosition.zero(); // Initially set positions to zero
    }

    void setOffset(double a, double b, double c) {
      glTranslatef(a, b, c);
      offset[0] = a;
      offset[1] = b;
      offset[2] = c;

      vPosition.set(a, b, c);

      //offset.clear()
    }

    void updatePosition(double a, double b, double c) {
      vPosition.set(a, b, c);
    }

    void displayPosition() {
      //calcVolumePos();
      vPosition.display();
    }

    // Position getters
    Vec3<double> getPosition() const {return vPosition;}
    double getXPos() const {return vPosition.getX();}
    double getYPos() const {return vPosition.getY();}
    double getZPos() const {return vPosition.getZ();}

};

class Cube:public Volume {
 private:
   double v, w; // vertices and width

 public:
   void drawCube(float width) {
     w = width;
     v = width/2.0;

     glBegin(GL_QUADS);
       // Top
       glColor3f(c[0], c[1], c[2]);
       glNormal3f(v, v, -v);
       glVertex3f(v, v, -v);
       glNormal3f(-v, v, -v);
       glVertex3f(-v, v, -v);
       glNormal3f(-v, v, v);
       glVertex3f(-v, v, v);
       glNormal3f(v, v, v);
       glVertex3f(v, v, v);
       // Bottom
       glColor3f(c[3], c[4], c[5]);
       glNormal3f(v, -v, v);
       glVertex3f(v, -v, v);
       glNormal3f(-v, -v, v);
       glVertex3f(-v, -v, v);
       glNormal3f(-v, -v, -v);
       glVertex3f(-v, -v, -v);
       glNormal3f(v, -v, -v);
       glVertex3f(v, -v, -v);
       // Front
       glColor3f(c[6], c[7], c[8]);
       glNormal3f(v, v, v);
       glVertex3f(v, v, v);
       glNormal3f(-v, v, v);
       glVertex3f(-v, v, v);
       glNormal3f(-v, -v, v);
       glVertex3f(-v, -v, v);
       glNormal3f(v, -v, v);
       glVertex3f(v, -v, v);
       // Back
       glColor3f(c[9], c[10], c[11]);
       glNormal3f(v, -v, -v);
       glVertex3f(v, -v, -v);
       glNormal3f(-v, -v, -v);
       glVertex3f(-v, -v, -v);
       glNormal3f(-v, v, -v);
       glVertex3f(-v, v, -v);
       glNormal3f(v, v, -v);
       glVertex3f(v, v, -v);
       // Left
       glColor3f(c[12], c[13], c[14]);
       glNormal3f(-v, v, v);
       glVertex3f(-v, v, v);
       glNormal3f(-v, v, -v);
       glVertex3f(-v, v, -v);
       glNormal3f(-v, -v, -v);
       glVertex3f(-v, -v, -v);
       glNormal3f(-v, -v, v);
       glVertex3f(-v, -v, v);
       // Right
       glColor3f(c[15], c[16], c[17]);
       glNormal3f(v, v, -v);
       glVertex3f(v, v, -v);
       glNormal3f(v, v, v);
       glVertex3f(v, v, v);
       glNormal3f(v, -v, v);
       glVertex3f(v, -v, v);
       glNormal3f(v, -v, -v);
       glVertex3f(v, -v, -v);
     glEnd();

   }

   double getSize() const {return w;}

};

class Tetrahedron: public Volume {

  public:
    Tetrahedron() { // Constructor
      //nothing
    }

    void drawTetrahedron() {
      glBegin(GL_TRIANGLE_STRIP);
        glColor3f(c[2], c[3], c[4]);
        glVertex3f(0, 2, 0);
        glColor3f(c[5], c[6], c[7]);
        glVertex3f(-1, 0, 1);
        glColor3f(c[8], c[9], c[10]);
        glVertex3f(1, 0, 1);
        glColor3f(c[11], c[12], c[13]);
        glVertex3f(0, 0, -1.4);
        glColor3f(c[5], c[6], c[7]);
        glVertex3f(0, 2, 0);
        glColor3f(c[5], c[6], c[7]);
        glVertex3f(-1, 0, 1);
      glEnd();
    }
};

class wireSphere: public Volume {
  private:
    float radius;

  public:
    wireSphere() {
      lines = 10.0;
      stack = 10.0;
    }
    float lines;
    float stack;

    void drawSphere(float r) {
      glutWireSphere(r, lines, stack);
      r = radius;
    }

};


//I3WM - window managers
