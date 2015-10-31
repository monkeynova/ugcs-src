#include <stdio.h>
#include <math.h>
#include "xstuff.h"

#define SQ(X) ((X)*(X))
#define WIDTH  100
#define HEIGHT 100

void DrawWin( WIN_INFO );

void main( void ) {
  WIN_INFO win;
  XEvent e;
  int done = 0;

  InitX( NULL );

  win = NewBaseWin( 100, 100, WIDTH, HEIGHT, "Spiral" );

  while ( ! done ) {
    XNextEvent( display, &e );
    switch ( e.type ) {
    case Expose:
      DrawWin( win );
      break;
    case ConfigureNotify:
      win.width  = e.xconfigure.width;
      win.height = e.xconfigure.height;
      break;
    case MotionNotify:
      break;
    case ButtonPress:
    case ButtonRelease:
    case KeyPress:
    case KeyRelease:
      done = 1;
      break;
    default:
      break;
    }
  }
  CloseWin( &win );
  CloseX();
}

#define RADIUS     100
#define POINTX     -50
#define POINTY     -50
#define POINTZ       0
#define VIEWANGLE  70.
#define T_START      0
#define P_START      0
#define PIC_HEIGHT  64
#define PIC_WIDTH   64

void DrawWin( WIN_INFO win ) {
  float theta, phi, t, x, y, z, alpha;
  float cos_sqr_phi, tan_theta;
  
  XSetForeground( display, win.gc, BlackPixel( display, screen_num ) );

  for ( phi = P_START; phi < P_START + VIEWANGLE; phi += VIEWANGLE / win.height ) {
    cos_sqr_phi = SQ(cos( phi * M_PI / 180 ));
    tan_theta = tan( theta * M_PI / 180 );
    for ( theta = T_START; theta < T_START + VIEWANGLE; theta += VIEWANGLE / win.width ) {

      t = sqrt( SQ(RADIUS) - SQ(POINTX) - SQ(POINTY) +  SQ(POINTX + POINTY) * cos_sqr_phi);
      t -= (POINTX + POINTY) * cos_sqr_phi;

      x = POINTX + t;
      y = POINTY + t * tan( phi * M_PI / 180);
      z = (int)(POINTZ + t * tan_theta) % PIC_HEIGHT;

      alpha = atan2( y, x ) * PIC_WIDTH / 2 / M_PI;

      if ( alpha < 4 || z < 4 ) {
	XDrawPoint( display, win.win, win.gc, (theta - T_START) * win.width / VIEWANGLE, 
		    (phi - P_START) * win.height / VIEWANGLE );
      }
    }
  }
}









