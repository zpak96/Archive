#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h> // For sin and cos usage

#include <GL/glut.h> // For OpenGL framework library
#include "Vec3.hpp" // Custom Vec3 class
#include "volumeObjects.cpp"

const double TO_RADS = 3.141592654 / 180.0;

class Camera {
  private:
    // Camera position
    Vec3<double> position;
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
    // Holding keys down
    bool holdForward;
    bool holdBackward;
    bool holdLeft;
    bool holdRight;

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
      movementSpeedFactor = 10.0;

      pitchSensitivity = 0.001; // Y-axis sensitivity
      yawSensitivity = 0.001; // X-axis sensitivity

      // Set all keys to false initially
      holdForward = false;
      holdBackward = false;
      holdLeft = false;
      holdRight = false;

      std::cout << ":: Camera Initialized ::\n";
      std::cout << "windowMidX: " << windowMidX << std::endl;
      std::cout << "windowMidY: " << windowMidY << "\n\n";
      std::cout << "RotationX: " << rotation.getX() << "\n";
      std::cout << "RotationY: " << rotation.getY() << "\n";
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


    // Mouse movement handler to look around
    void handleMouseMove(int mouseX, int mouseY) {
      // Calculate horizontal and vertical mouse movements from middle of window
      double hMovement = ((mouseX - windowMidX+1) * yawSensitivity);
      double vMovement = ((mouseY - windowMidY+1) * pitchSensitivity);

      // Applying mouse movement to the rotation vector
      rotation.addX(vMovement);
      rotation.addY(hMovement);

      // Limit the vertical looking to +/- 90 degrees
      if (rotation.getX() > 100.0) {
        rotation.setX(-100.0);
      }

      if (rotation.getX() < -100.0) {
        rotation.setX(100.0);
      }


      // Left and right, keeping the angles from 0.0 to 360.0
      if (rotation.getY() < -360.0) {
        rotation.setY(360.0);
      }

      if (rotation.getY() > 360.0) {
        rotation.addY(-360.0);
      }

      // Reset mouse position to the center of the window each frame
      //glutWarpPointer(windowMidX, windowMidY);
    }

    // Method to convert angle from degrees to radians
    const double toRads(const double &angleInDegrees) const {
      return angleInDegrees * TO_RADS;
    }

    // Method for moving camera based on the current direction
    void move(double deltaTime) {
      // Vector to break up movements along the x-axis
      Vec3<double> movement;

      // Get sin and cos of x and y axis rotation
      double sinXrot = sin( toRads(rotation.getX()));
      double cosXrot = cos( toRads(rotation.getX()));

      double sinYrot = sin( toRads(rotation.getY()));
      double cosYrot = cos( toRads(rotation.getY()));

      double pitchLimitFactor = cosXrot; // this grounds the camera to the x axis

      if (holdForward) {
        movement.addX(sinYrot);
        movement.addY(-sinXrot);
        movement.addZ(-cosYrot);
      }

      if (holdBackward) {
        movement.addX(-sinYrot);
        movement.addY(sinXrot);
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
