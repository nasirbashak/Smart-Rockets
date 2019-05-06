#include "PVector.h"
#include<stdio.h>
#include<math.h>

PVector :: PVector(){

}

PVector :: PVector(float x,float y){

    this->x = x;
    this->y = y;

}

PVector :: PVector(float x,float y,float z){

    this->x = x;
    this->y = y;
    this->z = z;

}

PVector PVector:: add(PVector v) {
    this->x += v.x;
    this->y += v.y;
   
    return PVector(this->x,this->y);
  }


  /**
   * @param x x component of the vector
   * @param y y component of the vector
   */
  PVector PVector:: add(float x, float y) {
    this->x += x;
    this->y += y;
    return PVector(this->x,this->y);
  }

  PVector PVector :: copy() {
    
    return  PVector(this->x, this->y, this->z);
  
  }

  PVector PVector :: mult(float n) {
    this->x *= n;
    this->y *= n;
    this->z *= n;
    return PVector(this->x, this->y, this->z);
  }

 float  PVector ::  magSq() {
    return (x*x + y*y + z*z);
  }

  PVector PVector :: div(float n) {
    x /= n;
    y /= n;
    z /= n;
    return PVector(this->x, this->y, this->z);
  }

PVector PVector :: normalize() {
    float m = mag();
    if (m != 0 && m != 1) {
      div(m);
    }
    return PVector(this->x, this->y, this->z);
  }

 float PVector :: mag() {
    return (float) sqrt(x*x + y*y + z*z);
  }

PVector PVector :: limit(float max) {
    if (magSq() > max*max) {
      normalize();
      mult(max);
    }
    return PVector(this->x, this->y, this->z);
  }

   float PVector ::heading() {
    float angle = (float) atan2(y, x);
    return angle;
  }

PVector PVector :: setMag(float len) {
    normalize();
    mult(len);
    return PVector(this->x, this->y, this->z);
  }

PVector PVector ::  fromAngle(float angle) {
        return PVector((float)cos(angle),(float)sin(angle),0);

  }

PVector PVector :: set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    return PVector(this->x, this->y, this->z);
  }


  /**
   * @param x the x component of the vector
   * @param y the y component of the vector
   */
 PVector PVector :: set(float x, float y) {
    this->x = x;
    this->y = y;
    return PVector(this->x, this->y, this->z);
  }


  /**
   * @param v any variable of type PVector
   */
PVector PVector :: set(PVector v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return PVector(this->x, this->y, this->z);
  }

 PVector   PVector :: random2D(){

   float angle = (rand() * (22/7)*2);

  PVector p = PVector((float)(cos(angle)*100),(float)(sin(angle)*100),0);

  //  printf("random2d = %f,%f\n",p.x,p.y);
   // printf("angle = %f\nrandom2d()= %f,%f\n",angle,p.x,p.y);

  return p;
    
}



