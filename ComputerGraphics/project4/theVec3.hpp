#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

template <class T> class Vec3 {
  public:
    // Vec3 has three properties: x, y, z
    T x, y, z;

    // Default constructor
    Vec3() {
      x = y = z = 0;
    }

    // Three parameter constructor
    Vec3(T xValue, T yValue, T zValue) {
      x = xValue;
      y = yValue;
      z = zValue;
    }

    // Getter and setters
    void set(const T &xValue, const T &yValue, const T &zValue) {
      // Setting the private variables through reference -I think
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

    // Helper Methods
    void zero() { // Set vector to zero
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

    /* Method to calculate scalar dot product -Not sure if i'll utilize this.
    * --Dot products of two vectors tells info about the angle between the vectors
    * -- It tells if they are parallel or perpendicular.
    * parallel returns 1, perpendicular returns 0, opposite directions returns -1.
    * Usage: double foo = Vec3<double>::dotProduct(vectorA, vectorB);
    */
    static T dotProduct(const Vec3 &vec1, const Vec3 &vec2) {
      return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
    }

    // Non-static method to calculate scalar dot product
    // Usage: double foo = vectorA.dotProduct(vectorB);
    T dotProduct(const Vec3 &vec) const {
      return x * vec.x + y * vec.y + z * vec.z;
    }

    /* Static method to calculate the cross product of two vectors.
    * The site explains what this is well, so I'm going to paste the example in:
    *
    * Note: The cross product is simply a vector which is perpendicular
    * to the plane formed by the first two vectors. Think of a desk like
    * the one your laptop or keyboard is sitting on. If you put one pencil
    * pointing directly away from you, and then another pencil pointing to the
    * right so they form a "L" shape, the vector perpendicular to the plane
    * made by these two pencils points directly upwards.
    * Further reading: http://en.wikipedia.org/wiki/Cross_product
    * Usage: Vec3<double> crossVect = Vec3<double>::crossproduct(vectorA, vectorB);
    */
    static Vec3 crossProduct(const Vec3 &vec1, const Vec3 &vec2) {
      return vec3(vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x);
    }

    // Easy adders
    void addX(T value) {x += value;}
    void addY(T value) {y += value;}
    void addZ(T value) {z += value;}

    // Get distance between two vectors
    static T getDistance(const Vec3 &v1, const Vec3 &v2) {
      T dx = v2.x - v1.x;
      T dy = v2.y - v1.y;
      T dz = v2.z - v1.z;
      return sqrt(dx * dx + dy * dy + dz * dz);
    }

    // Method to display the vector to easily check the values
    void display() {
      std::cout << "X: " << x << "\t Y: " << y << "\t Z: " << z << std::endl;
    }

    // Overloaded Operators

    //Addition
    Vec3 operator+(const Vec3 &vector) const {
      return Vec3<T>(x + vector.x, y + vector.y, z + vector.z);
    }

    // Overloaded add and assign operator to add Vec3's together
    Vec3 operator+=(const Vec3 &vector) {
      x += vector.x;
      y += vector.y;
      z += vector.z;
    }

    /* Subtraction
    Vec3 operator-(const Vec3 &vector) const {
      return Vec3<T>(x - vector.x, y - vector.y, z - vector.z);
    }

    // Overloaded subtract and assign operator
    Vec3 operator-=(const Vec3 &vector) {
      x -= vector.x;
      y -= vector.y;
      z -= vector.z;
    }
    */

    // Multiply two vectors together
    Vec3 operator-(const Vec3 &vector) const {
      return Vec3<T>(x * vector.x, y * vector.y, z * vector.z);
    }

    // Multiply vector by a scalar
    Vec3 operator*(const T &value) {
      return Vec3<T>(x * value, y * value, z * value);
    }

    // Overloaded multiply and assign operator
    Vec3 operator*=(const T value) {
      x *= value;
      y *= value;
      z *= value;
    }

    // Division
    Vec3 operator/(const T &value) const {
      return Vec3<T>(x / value, y / value, z / value);
    }

    // Overloaded division and assign operator
    void operator/=(const T &value) {
      x /= value;
      y /= value;
      z /= value;
    }
};

#endif



/* This is where I referenced this templated class:
* https://r3dux.org/2012/12/vec3-a-simple-vector-class-in-c/
*
* I didnt't know much about templates, but they're really cool.
* I read up on them here:
* http://www.cplusplus.com/doc/oldtutorial/templates/
*
* I didn't understand what normalization was either, so I looked it up here:
* https://stackoverflow.com/questions/11644356/what-does-it-mean-to-normalize-a-value
*/
