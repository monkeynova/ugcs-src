#ifndef __VECTOR_HH
#define __VECTOR_HH

#include <stdio.h>
#include <math.h>
#include <string>

typedef string String;

class Vector {
private:
  int adder;
  float cvect[ 4 ];

public:
  float x,y,z,f;

public:
  Vector() { x = y = z = f = 0; adder = 1; }
  Vector( float _x, float _y, float _z = 0, float _f = 0) {
    x = _x; y = _y; z = _z; f = _f; adder = 4;
  }

  String toString() const {
    char tmp[80];
    String ret( "<" );
    
    sprintf( tmp, "%f", x );
    ret += String( tmp ) + String( ", " );
    sprintf( tmp, "%f", y );
    ret += String( tmp ) + String( ", " );
    sprintf( tmp, "%f", z );
    ret += String( tmp ) + String( ", " );

    if ( f != 0 ) {
      sprintf( tmp, "%f", f );
      ret += String( tmp ) + String( ", " );
    }

    ret += String( ">" );

    return ret;
  }

  float *toCVector() {
    cvect[ 0 ] = x;
    cvect[ 1 ] = y;
    cvect[ 2 ] = z;
    cvect[ 3 ] = f;
    return cvect;
  }

  void add( float fl ) {
    switch ( adder ) {
    case 1:
      x = fl;
      break;
    case 2:
      y = fl;
      break;
    case 3:
      z = fl;
      break;
    default:
      f = fl;
    }
    adder++;
  }
  
  void normalize() { if ( norm2() != 0 ) *this /= norm(); }
  float norm() const { return sqrt( norm2() ); }
  float norm2() const { return dot( *this ); }

  float dot( const Vector &other ) const { 
    return x * other.x + y * other.y + z * other.z;
  }

  Vector cross( const Vector &other ) const {
    return Vector( y * other.z - z * other.y,
		   z * other.x - x * other.z,
		   x * other.y - y * other.x );
  }

  Vector operator *=( float fl ) { 
    x *= fl; y *= fl; z *= fl;
    return (*this);
  }

  Vector operator *( Vector other ) {
    return Vector( x * other.x, y * other.y, z * other.z );
  }

  Vector operator *( float fl ) const { return  Vector( *this ) *= fl; }
  Vector operator /=( float fl ) { return (*this *= 1 / fl);  }
  Vector operator /( float fl ) const { return Vector( *this ) /= fl; }
  Vector operator +=( const Vector &other ) {
    x += other.x; y += other.y; z += other.z;
    return (*this);
  }
  Vector operator -() const  { return (*this * -1); }
  Vector operator -=( const Vector &other ) { return Vector(*this) += -other; }
  Vector operator +( const Vector &other ) const { return Vector( *this ) += other; }
  Vector operator -( const Vector &other ) const { return Vector( *this ) -= other; }
};

inline Vector operator *( float f, Vector v ) { return v * f; }

#endif
