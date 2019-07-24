#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Terrain {
  protected:
    float colors[11];

  public:
    int scale = -2;


    // constructor
    Terrain() {

    }


    // Destructor
    ~Terrain() {
      //nothing
    }

    void generateTerrain(int cols, int rows) {
      // Nested loop for generating terrain
      // Trying to use triangle strips
      for (int z = 0; z < rows; z++) { // Y
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < cols; x++) { // X
          // glColor3f(colors[0], colors[1], colors[2]);
          glVertex3f(float(x*scale), 0.0, float(z*scale));
          // glColor3f(colors[3], colors[4], colors[5]);
          glVertex3f(float(x*scale), 0.0, float(z+1)*scale);
        }
        glEnd();
      }

    } // End of generateTerrain

};
