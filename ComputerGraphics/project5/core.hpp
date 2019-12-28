#ifndef CORE_H
#define CORE_H

// OpenGL Libraries
#include <GL/glut.h>

// Additional Libraries
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

// Global variables
const double TO_RADS = 3.141592654 / 180.0;
float _angle = 30.0;

class Core {
  public:
    //Window Attributes
    // Default set window to 800 X 600
    GLint windowWidth = 800;
    GLint windowHeight = 600;
    GLint midX = windowWidth / 2;
    GLint midY = windowHeight / 2;


    float randomVal[500];

    // Constructor
    Core() {
      // Generating random values for this session
      srand(static_cast<unsigned int>(clock()));
      for (int i=0; i <= 500; i++) {
        randomVal[i] = double(rand()) / (double(RAND_MAX) + 1.0);
      }
    }

    // Destructor
    ~Core() {}

    // Method to handle screen resizing
    void windowResize(GLint width, GLint height) {
      //Updating both sections of the object, mostly for mouse movement if resized
      windowWidth = width;
      windowHeight = height;

    }

    // Getters and Setters
    int getWinW() {return windowWidth;}
    int getWinH() {return windowHeight;}
    int getMidX() {return midX;}
    int getMidY() {return midY;}


};

template <class T> class Vec3 {
  public:
    T x, y, z;

    // Constructor
    Vec3() {
      x = y = z = 0;
    }

    // Three parameter constructor
    Vec3(T xVal, T yVal, T zVal) {
      x = xVal;
      y = yVal;
      z = zVal;
    }

    // Setters and Getters
    void set(const T &xValue, const T &yValue, const T &zValue) {
      x = xValue;
      y = yValue;
      z = zValue;
    }

    T getX() const {return x;}
    T getY() const {return y;}
    T getZ() const {return z;}

    void setX(const T &xValue) {x = xValue;}
    void setY(const T &yValue) {x = yValue;}
    void setZ(const T &zValue) {x = zValue;}

    // Helper method
    void zero() {
      x = y = z = 0.0;
    }

    void normalize() {
      // Calculate magnitude of vector
      T magnitude = sqrt((x * x) + (y * y) + (z * z));

      // if the magnitude isn't zero, then divide
      if (magnitude != 0) {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
      }
    }

    // Easy adders
    void addX(T value) {x += value;}
    void addY(T value) {y += value;}
    void addZ(T value) {z += value;}

    // Method to display the vector to easily check the values
    void display() {
      std::cout << "X: " << x << "\t Y: " << y << "\t Z: " << z << std::endl;
    }

    // Overloaded add and assign operator to add Vec3's together
    Vec3 operator+=(const Vec3 &vector) {
      x += vector.x;
      y += vector.y;
      z += vector.z;
    }

    // Overloaded multiply and assign operator
    Vec3 operator*=(const T value) {
      x *= value;
      y *= value;
      z *= value;
    }

};

class Volume:public Core {
  protected:
    double x, y, z;

  public:
    // Position of volume
    Vec3<double> volumePos;

    float *randVal = Core::randomVal;

    // Constructor
    Volume() {
      // Set initial posiiton to (0,0,0)
      volumePos.zero();
    }

    void updatePos(double a, double b, double c) {
      // Using this to keep track of positions after glPushMatrix()
      volumePos.set(a, b, c);
    }

    void displayPos() {
      // Referencing Vec3 method here
      volumePos.display();
    }

    // Position getters
    Vec3<double> getPosition() const {return volumePos;}
    double getXPos() const {return volumePos.getX();}
    double getYPos() const {return volumePos.getY();}
    double getZPos() const {return volumePos.getZ();}
};

class Cube:public Volume {
  private:
    double v, w;

  public:
    float *rVal = Volume::randVal;

    // Constructor - Not using right now
    Cube() {}

    // Have to pass width of cube and a pointer to a array of color values
    void genCube(float width) {
      w = width;
      v = width/2.0;

      glBegin(GL_QUADS);
        // Top
        glColor3f(rVal[0], rVal[1], rVal[2]);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        // Bottom
        glColor3f(rVal[3], rVal[4], rVal[5]);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
        // Front
        glColor3f(rVal[6], rVal[7], rVal[8]);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        // Back
        glColor3f(rVal[9], rVal[10], rVal[11]);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        // Left
        glColor3f(rVal[12], rVal[13], rVal[14]);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        // Right
        glColor3f(rVal[15], rVal[16], rVal[17]);
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

class Rectangle:public Volume {
  private:
    double v, w;

  public:
    float *rVal = Volume::randVal;

    // Constructor - Not using right now
    Rectangle() {}

    // Making rectangle out of two cubes, and passing pointer to array of colors
    // I do this because it's easier to calculate collision in my current understanding
    void genRectangle(float width) {
      w = width;
      v = width/2.0;

      // First Cube
      glBegin(GL_QUADS);
        // Top
        glColor3f(rVal[0], rVal[1], rVal[2]);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        // Bottom
        glColor3f(rVal[3], rVal[4], rVal[5]);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
        // Front
        glColor3f(rVal[6], rVal[7], rVal[8]);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        // Back
        glColor3f(rVal[9], rVal[10], rVal[11]);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        // Left
        glColor3f(rVal[12], rVal[13], rVal[14]);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        // Right
        glColor3f(rVal[15], rVal[16], rVal[17]);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
      glEnd();
      // Translate second cube w along the Y axis
      glTranslatef(0.0, w, 0.0);

      // Second cube
      glBegin(GL_QUADS);
        // Top
        glColor3f(rVal[0], rVal[1], rVal[2]);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        // Bottom
        glColor3f(rVal[3], rVal[4], rVal[5]);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
        // Front
        glColor3f(rVal[6], rVal[7], rVal[8]);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        // Back
        glColor3f(rVal[9], rVal[10], rVal[11]);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        // Left
        glColor3f(rVal[12], rVal[13], rVal[14]);
        glNormal3f(-v, v, v);
        glVertex3f(-v, v, v);
        glNormal3f(-v, v, -v);
        glVertex3f(-v, v, -v);
        glNormal3f(-v, -v, -v);
        glVertex3f(-v, -v, -v);
        glNormal3f(-v, -v, v);
        glVertex3f(-v, -v, v);
        // Right
        glColor3f(rVal[15], rVal[16], rVal[17]);
        glNormal3f(v, v, -v);
        glVertex3f(v, v, -v);
        glNormal3f(v, v, v);
        glVertex3f(v, v, v);
        glNormal3f(v, -v, v);
        glVertex3f(v, -v, v);
        glNormal3f(v, -v, -v);
        glVertex3f(v, -v, -v);
      glEnd();

    glTranslatef(0.0, w, 0.0);

    // Third cube
    glBegin(GL_QUADS);
      // Top
      glColor3f(rVal[0], rVal[1], rVal[2]);
      glNormal3f(v, v, -v);
      glVertex3f(v, v, -v);
      glNormal3f(-v, v, -v);
      glVertex3f(-v, v, -v);
      glNormal3f(-v, v, v);
      glVertex3f(-v, v, v);
      glNormal3f(v, v, v);
      glVertex3f(v, v, v);
      // Bottom
      glColor3f(rVal[3], rVal[4], rVal[5]);
      glNormal3f(v, -v, v);
      glVertex3f(v, -v, v);
      glNormal3f(-v, -v, v);
      glVertex3f(-v, -v, v);
      glNormal3f(-v, -v, -v);
      glVertex3f(-v, -v, -v);
      glNormal3f(v, -v, -v);
      glVertex3f(v, -v, -v);
      // Front
      glColor3f(rVal[6], rVal[7], rVal[8]);
      glNormal3f(v, v, v);
      glVertex3f(v, v, v);
      glNormal3f(-v, v, v);
      glVertex3f(-v, v, v);
      glNormal3f(-v, -v, v);
      glVertex3f(-v, -v, v);
      glNormal3f(v, -v, v);
      glVertex3f(v, -v, v);
      // Back
      glColor3f(rVal[9], rVal[10], rVal[11]);
      glNormal3f(v, -v, -v);
      glVertex3f(v, -v, -v);
      glNormal3f(-v, -v, -v);
      glVertex3f(-v, -v, -v);
      glNormal3f(-v, v, -v);
      glVertex3f(-v, v, -v);
      glNormal3f(v, v, -v);
      glVertex3f(v, v, -v);
      // Left
      glColor3f(rVal[12], rVal[13], rVal[14]);
      glNormal3f(-v, v, v);
      glVertex3f(-v, v, v);
      glNormal3f(-v, v, -v);
      glVertex3f(-v, v, -v);
      glNormal3f(-v, -v, -v);
      glVertex3f(-v, -v, -v);
      glNormal3f(-v, -v, v);
      glVertex3f(-v, -v, v);
      // Right
      glColor3f(rVal[15], rVal[16], rVal[17]);
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


    double getHeight() const {return w;}
};

class Sphere:public Volume {
  public:
    double radius;

    Sphere() {
      radius = 1.00;
    };

    void genSphere(int lo, int la) {
        glutSolidSphere(radius, lo, la);
    }

    void genWireSphere(int lo, int la) {
        glutWireSphere(radius, lo, la);
    }

    void setRadius(double r) {
      radius = r;
    }

    int getRadius() {
      return radius;
    }

};

class Tpot:public Volume {
  public:
    Tpot() {}

    void genTPot(double scale) {

        glutWireTeapot(scale);

    }
};

class Terrain: public Core {
  private:
    int scale;

  public:
    float *randFloat = Core::randomVal;

    // Constructor
    Terrain() {
      // Set default scale to 1 (negative to translate in front of camera)
      scale = -1;
    }

    // Destructor
    ~Terrain() {}

    void setScale(int s) {
      scale = s;
    }

    void genTerrain(int cols, int rows) {
      // Generating terrain using triangle strips
      for (int z = 0; z < rows; z++) { // Moving outward row by row
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < cols; x++) {
          glVertex3f(float(x*scale), (randFloat[x])*-scale, float(z)*scale);
          glNormal3f(float(x*scale), (randFloat[x])*-scale, float(z)*scale);
          glVertex3f(float(x*scale), (randFloat[x])*-scale, float(z+1)*scale);
          glNormal3f(float(x*scale), (randFloat[x])*scale, float(z+1)*scale);
        }
        glEnd();
      }
    } // End of genTerrain
};

class Camera:public Core {
  protected:
    // Camera rotation
    Vec3<double> camRotation;

    // Camera move speed => used when move() is called
    Vec3<double> camSpeed;

    double speedFactor;
    double pitchSensitivity; // Y axis sensitivity
    double yawSensitivity; // X axis sensitivity

  public:
    // Camera Position - not protected because I keep having to manipulate it
    Vec3<double> camPos;

    // vector for storing camPos at collision
    Vec3<double> camColPos;

    // Holding keys down
    bool holdForward;
    bool holdBackward;
    bool holdLeft;
    bool holdRight;
    bool holdSpace;
    bool holdC;
    bool addGravity;

    // Collision - May explore better ways to detect collision
    bool collision;

    // Constructor
    Camera() {
      // Zero out position, colPos, speed and rotation
      camPos.zero();
      camColPos.zero();
      camSpeed.zero();
      camRotation.zero();

      // Set speedFactor
      speedFactor = 15.0;

      pitchSensitivity = 0.2; // Y axis
      yawSensitivity = 0.2; // X axis

      // Set keys to false
      holdForward = false;
      holdBackward = false;
      holdLeft = false;
      holdRight = false;
      holdSpace = false;
      holdC = false;
      addGravity = false;

      collision = false;

    } // End of constructor

    ~Camera();

    // Method for looking around
    void handleMouseMove(int mouseX, int mouseY) {
      // Calculate horizontal and vertical mouse movements from middle of window
      double hMovement = ((mouseX - Core::getMidX() + 1) * yawSensitivity);
      double vMovement = ((mouseY - Core::getMidY() + 1) * pitchSensitivity);

      // Applying mouse movement to the rotation vector
      camRotation.addX(vMovement);
      camRotation.addY(hMovement);

      // Limit the vertical looking to +/- 90 degrees
      if (camRotation.getX() > 90.0) {
        camRotation.setX(90.0);
      } else if (camRotation.getX() < -90.0) {
        camRotation.setX(-90.0);
      }

      // Left and right, keeping the angles from 0.0 to 360.0
      if (camRotation.getY() >= 360.0) {
        camRotation.addY(-360.0);
      } else if (camRotation.getY() <= -360.0) {
        camRotation.addY(360.0);
      }
    }

    // Method to convert angle from degrees to radians
    const double toRads(const double &angleInDegrees) const {
      return angleInDegrees * TO_RADS;
    }

    void lastPos(double e, double f, double g) {
      camColPos.x = e;
      camColPos.y = f;
      camColPos.z = f;
    }

    // Method for moving cam based on current direction
    void move(double deltaTime) {
      // Vector to break up movements along x axis
      Vec3<double> camMovement;

      // Value that keeps movement speed constant
      double framerateFactor;

      // Get sin and cos of x and y axis rotation
      double sinXrot = sin( toRads(camRotation.getX()));
      double cosXrot = cos( toRads(camRotation.getX()));

      // Getting camRotation for testing - may be useful later
      double rotY = toRads(camRotation.getY());
      double rotX = toRads(camRotation.getX());

      double sinYrot = sin( toRads(camRotation.getY()));
      double cosYrot = cos( toRads(camRotation.getY()));


      /* ####### COLLISION ########
        Right now collision is kind of broken. It works, but I need do a lot
        of work to get it right. Below is the code. It has incorrect math. I know.
      */
      switch (collision) {
        case false:
          if (holdForward) {
            // cout << sinYrot << endl;
            camMovement.addX(sinYrot);
            // camMovement.addY(-sinXrot);
            camMovement.addZ(-cosYrot);
          }

          if (holdBackward) {
            camMovement.addX(-sinYrot);
            // camMovement.addY(sinXrot);
            camMovement.addZ(cosYrot);
          }

          if (holdLeft) {
            camMovement.addX(-cosYrot);
            camMovement.addZ(-sinYrot);
          }

          if (holdRight) {
            camMovement.addX(cosYrot);
            camMovement.addZ(sinYrot);
          }

          if (holdSpace) {
            camMovement.addY(1.0);
          }

          if (holdC) {
            camMovement.addY(-0.5);
          }

          if (addGravity) {
            camMovement.addY(-0.5);
          }
          break;
        case true:
          if (holdForward) {
            if (camColPos.x < 0.0) {
              camPos.set(camColPos.x + 0.5, camColPos.y, camColPos.z);
            } else {
              camPos.set(camColPos.x -0.5, camColPos.y, camColPos.z);
            }

            if (camColPos.z < 0.0) {
              camPos.set(camColPos.x, camColPos.y, camColPos.z + 0.5);
            } else {
              camPos.set(camColPos.x, camColPos.y, camColPos.z - 0.5);
            }
          }
          if (holdBackward) {
            if (camColPos.x < 0.0) {
              camPos.set(camColPos.x - 0.5, camColPos.y, camColPos.z);
            } else {
              camPos.set(camColPos.x + 0.5, camColPos.y, camColPos.z);
            }

            if (camColPos.z < 0.0) {
              camPos.set(camColPos.x, camColPos.y, camColPos.z - 0.5);
            } else {
              camPos.set(camColPos.x, camColPos.y, camColPos.z + 0.5);
            }
          }
          if (holdRight) {
            if (camColPos.x < 0.0) {
              camPos.set(camColPos.x - 0.5, camColPos.y, camColPos.z);
            } else {
              camPos.set(camColPos.x + 0.5, camColPos.y, camColPos.z);
            }

            if (camColPos.z < 0.0) {
              camPos.set(camColPos.x, camColPos.y, camColPos.z + 0.5);
            } else {
              camPos.set(camColPos.x, camColPos.y, camColPos.z - 0.5);
            }
          }
          if (holdLeft) {
            if (camColPos.x < 0.0) {
              camPos.set(camColPos.x + 0.5, camColPos.y, camColPos.z);
            } else {
              camPos.set(camColPos.x - 0.5, camColPos.y, camColPos.z);
            }

            if (camColPos.z < 0.0) {
              camPos.set(camColPos.x, camColPos.y, camColPos.z + 0.5);
            } else {
              camPos.set(camColPos.x, camColPos.y, camColPos.z - 0.5);
            }
          }
          if (holdSpace) {
            if (camColPos.y < -10) {
              camPos.set(camColPos.x, camColPos.y + 0.5, camColPos.z);
            } else {
              camPos.set(camColPos.x, camColPos.y, camColPos.z);
            }
          }

          collision = false;
          break;

      } // End of switch statement

      // Normalize movement vector
      camMovement.normalize();

      // Calculate value to keep the movement speed constant
      framerateFactor = speedFactor * deltaTime;

      // Apply that to movement vector
      camMovement *= framerateFactor;

      // Now apply movement to position

      camPos += camMovement;

    } // End of move()

    // ######## SOME GETTERS & SETTERS #########
    float getPitchSensitivity() {
      return pitchSensitivity;
    }

    float setPitchSensitivity(float value) {
      pitchSensitivity = value;
    }

    float addPitchSensitivity(float value) {
      pitchSensitivity += value;
    }

    float getYawSensitivity() {
      return yawSensitivity;
    }

    float setYawSensitivity(float value) {
      yawSensitivity = value;
    }

    // Position getters
    Vec3<double> getPosition() const {return camPos;}
    double getXPos() const {return camPos.getX();}
    double getYPos() const {return camPos.getY();}
    double getZPos() const {return camPos.getZ();}

    // Rotation getters
    Vec3<double> getRotation() const {return camRotation;}
    double getXRot() const {return camRotation.getX();}
    double getYRot() const {return camRotation.getY();}
    double getZRot() const {return camRotation.getZ();}
};

/*
class Model: public Core {
  public:
    bool loadOBJ(
      std::vector < glm::vec3 > & out_vertices,
      std::vector < glm::vec2 > & out_uvs,
      std::vector < glm::vec3 > & out_normals
    )

    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<glm::vec3> temp_vertices;
    vector<glm::vec2> temp_uvs;
    vector<glm::vec3> temp_normals;

    // Constructor
    Model(string path) {
      FILE * file = fopen(path, "r");
      if( file == NULL ){
        printf("Error Opening OBJ file!\n");
        return false;
      }

      while(1) {
        char lineHeader[128];
        // Read first word of line
        int res = fscan(file, "%s", lineHeader);
        if (res == EOF) {
          break;
        }

        if (strcmp(lineHeader, "v") == 0) {
          glm::vec3 vertex;
          fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
          temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
          glm::vec2 uv;
          fscanf(file, "%f %f\n", &uv.x, &uv.y );
          temp_uvs.push_back(uv);
        } else if ( strcmp( lineHeader, "vn" ) == 0 ) {
          glm::vec3 normal;
          fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
          temp_normals.push_back(normal);
        } else if ( strcmp( lineHeader, "f" ) == 0 ) {
          std::string vertex1, vertex2, vertex3;
          unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
          int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
            &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

          if (matches != 9){
            printf("File can't be read\n");
            return false;
          }

          vertexIndices.push_back(vertexIndex[0]);
          vertexIndices.push_back(vertexIndex[1]);
          vertexIndices.push_back(vertexIndex[2]);
          uvIndices.push_back(uvIndex[0]);
          uvIndices.push_back(uvIndex[1]);
          uvIndices.push_back(uvIndex[2]);
          normalIndices.push_back(normalIndex[0]);
          normalIndices.push_back(normalIndex[1]);
          normalIndices.push_back(normalIndex[2]);
        }
      } // End of while

      for( unsigned int i=0; i<vertexIndices.size(); i++ ) {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        out_vertices.push_back(vertex);
      }

      for( unsigned int i=0; i<uvIndices.size(); i++ ) {
        unsigned int uvIndex = uvIndices[i];
        glm::vec3 uv = temp_uvs[ uvIndex-1 ];
        out_uvs.push_back(uv);
      }

      for( unsigned int i=0; i<normalIndices.size(); i++ ) {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[ normalIndex-1 ];
        out_normals.push_back(normal);
      }


    } // End of Constructor

    void parseObj() {

    }

};
*/

/* Collision function that would be put in the .cpp file
void collCheck(double x1, double y1, double z1, float width) { // Collision checking method
  // This is the size of the user
  double sizeSum = 1.5 + (width / 2);

  if (abs(userCamera->getXPos() - x1) < sizeSum) {
    double a = userCamera->getXPos();
    if (abs(userCamera->getYPos() - y1) < sizeSum) {
      double b = userCamera->getYPos();
      if (abs(userCamera->getZPos() - z1) < sizeSum) {
        double c = userCamera->getZPos();
        userCamera->lastPos(a, b, c);
        userCamera->collision = true;
      }
    }
  }
}

// This would go in the refresh function
// Using Axis Aligned Bound Box (AABB) checking for collision
// for (int i = 0; i < 6; i++) {
//   collCheck(cube[i].getXPos(), cube[i].getYPos(), cube[i].getZPos(), cube[i].getSize());
// }
*/

#endif
