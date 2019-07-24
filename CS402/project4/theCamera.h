#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h> // For OpenGL framework library

#include <iostream>
#include <math.h> // For sin and cos usage

#include "theVec3.hpp" // Custom Vec3 class
// #include "theVolumes.cpp" // Volumes created by Zane Freakin' Paksi

const double TO_RADS = 3.141592654 / 180.0;

class Camera {
  protected:
    // Camera rotation
    Vec3<double> rotation;
    //Camera movement speed -Used when move() function is called
    Vec3<double> speed;

    double movementSpeedFactor; // How fast the camera moves
    double pitchSensitivity; // Affects mouse movement on y-axis
    double yawSensitivity; // Affects mouse movement on x-axis

    // Window size info, height width, midpoints(x, y)
    int windowWidth, windowHeight;
    int windowMidX, windowMidY;

  public:
    // Camera position
    Vec3<double> position;

    double a, b, c; // Will use these to store xyz at collision


    // Holding keys down
    bool holdForward;
    bool holdBackward;
    bool holdLeft;
    bool holdRight;
    bool holdSpace;
    bool addGravity;

    //Collision
    bool collision;

    // Constructor
    Camera(float theWindowWidth, float theWindowHeight) {
      // set position and rotation values to zero
      position.zero();
      rotation.zero();
      speed.zero();

      windowWidth = theWindowWidth;
      windowHeight = theWindowHeight;

      // Calculate middle of window
      windowMidX = windowWidth / 2.0;
      windowMidY = windowHeight / 2.0;

      // Set movement movement speed
      movementSpeedFactor = 15.0;

      pitchSensitivity = 0.2; // Y-axis sensitivity
      yawSensitivity = 0.2; // X-axis sensitivity

      // Set all keys to false initially
      holdForward = false;
      holdBackward = false;
      holdLeft = false;
      holdRight = false;
      holdSpace = false;
      addGravity = true;

      collision = false;

      /* Additional troubleshooting messages
      std::cout << ":: Camera Initialized ::\n";
      std::cout << "windowMidX: " << windowMidX << std::endl;
      std::cout << "windowMidY: " << windowMidY << "\n\n";
      std::cout << "RotationX: " << rotation.getX() << "\n";
      std::cout << "RotationY: " << rotation.getY() << "\n";
      */
    }

    /*
    void cameraInfo() {
      std::cout << "Mid window values: " << windowMidX << "\t" << windowMidY << "\n";
      std::cout << "Mouse values: " << mouseX << "\t" << mouseY << "\n";
      std::cout << hMovement << "\t" << vMovement << "\n\n";
    }
    */

    // Destructor
    ~Camera();

    void windowResize(float newWidth, float newHeight) {
      //Updating both sections of the object, mostly for mouse movement if resized
      windowWidth = newWidth;
      windowHeight = newHeight;

      windowMidX = windowWidth / 2.0;
      windowMidY = windowHeight / 2.0;
    }

    // Mouse movement handler to look around
    void handleMouseMove(int mouseX, int mouseY) {
      // Calculate horizontal and vertical mouse movements from middle of window
      double hMovement = ((mouseX - windowMidX+1) * yawSensitivity);
      double vMovement = ((mouseY - windowMidY+1) * pitchSensitivity);

      // Applying mouse movement to the rotation vector
      rotation.addX(vMovement);
      rotation.addY(hMovement);


      // Limit the vertical looking to +/- 90 degrees
      if (rotation.getX() > 90.0) {
        rotation.setX(90.0);
      } else if (rotation.getX() < -90.0) {
        rotation.setX(-90.0);
      }

      // Left and right, keeping the angles from 0.0 to 360.0
      // I like being able to do 360's though.
      if (rotation.getY() >= 360.0) {
        rotation.addY(-360.0);
      }
      if (rotation.getY() <= -360.0) {
        rotation.addY(360.0);
      }
    }

    // Method to convert angle from degrees to radians
    const double toRads(const double &angleInDegrees) const {
      return angleInDegrees * TO_RADS;
    }

    void lastPos(double e, double f, double g) {
      a = e;
      b = f;
      c = g;
    }

    // Method for moving camera based on the current direction
    void move(double deltaTime) {
      // Vector to break up movements along the x-axis
      Vec3<double> movement;

      // Get sin and cos of x and y axis rotation
      double sinXrot = sin( toRads(rotation.getX()));
      double cosXrot = cos( toRads(rotation.getX()));

      double rotY = toRads(rotation.getY());
      double rotX = toRads(rotation.getX());

      double sinYrot = sin( toRads(rotation.getY()));
      double cosYrot = cos( toRads(rotation.getY()));

      double pitchLimitFactor = cosXrot; // this grounds the camera to the x axis

      std::cout << "Y: " << rotY << std::endl;
      // std::cout << "X: " << rotX << std::endl;
      switch (collision) {
        case false:
          if (holdForward) {
            // cout << sinYrot << endl;
            movement.addX(sinYrot);
            // movement.addY(-sinXrot);
            movement.addZ(-cosYrot);
          }

          if (holdBackward) {
            movement.addX(-sinYrot);
            // movement.addY(sinXrot);
            movement.addZ(cosYrot);
          }

          if (holdLeft) {
            movement.addX(-cosYrot);
            movement.addZ(-sinYrot);
          }

          if (holdRight) {
            movement.addX(cosYrot);
            movement.addZ(sinYrot);
          }

          if (holdSpace) {
            movement.addY(1.0);
          }

          if (addGravity) {
            movement.addY(-0.5);
          }
          break;
        case true:
          if (holdForward) {
            if (a < 0.0) {
              position.set(a + 0.5, b, c);
            } else {
              position.set(a -0.5, b, c);
            }

            if (c < 0.0) {
              position.set(a, b, c + 0.5);
            } else {
              position.set(a, b, c - 0.5);
            }
          }
          if (holdBackward) {
            if (a < 0.0) {
              position.set(a - 0.5, b, c);
            } else {
              position.set(a + 0.5, b, c);
            }

            if (c < 0.0) {
              position.set(a, b, c - 0.5);
            } else {
              position.set(a, b, c + 0.5);
            }
          }
          if (holdRight) {
            if (a < 0.0) {
              position.set(a - 0.5, b, c);
            } else {
              position.set(a + 0.5, b, c);
            }

            if (c < 0.0) {
              position.set(a, b, c + 0.5);
            } else {
              position.set(a, b, c - 0.5);
            }
          }
          if (holdLeft) {
            if (a < 0.0) {
              position.set(a + 0.5, b, c);
            } else {
              position.set(a - 0.5, b, c);
            }

            if (c < 0.0) {
              position.set(a, b, c + 0.5);
            } else {
              position.set(a, b, c - 0.5);
            }
          }
          if (holdSpace) {
            if (a < -10) {
              position.set(a, b + 0.5, c);
            } else {
              position.set(a, b, c);
            }
          }



          collision = false;
          break;

    }
      // Normalize movement vector
      movement.normalize();

      // Calculate value to keep the movement speed constant
      double framerateFactor = movementSpeedFactor * deltaTime;

      // Apply that to movement vector
      movement *= framerateFactor;

      // Now apply movement to position
      position += movement;
    }

    // Setters and Getters

    float getPitchSensitivity() {return pitchSensitivity;}

    float setPitchSensitivity(float value) {
      pitchSensitivity = value;
    }

    float addPitchSensitivity(float value) {
      pitchSensitivity += value;
    }


    float getYawSensitivity() {return yawSensitivity;}

    float setYawSensitivity(float value) {
      yawSensitivity = value;
    }

    // Position getters
    Vec3<double> getPosition() const {return position;}
    double getXPos() const {return position.getX();}
    double getYPos() const {return position.getY();}
    double getZPos() const {return position.getZ();}

    // Rotation getters
    Vec3<double> getRotation() const {return rotation;}
    double getXRot() const {return rotation.getX();}
    double getYRot() const {return rotation.getY();}
    double getZRot() const {return rotation.getZ();}

};

// Camera Template class


#endif // CAMERA_H
