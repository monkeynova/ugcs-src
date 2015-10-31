#include "mandle.h"
#include <stdio.h>

void init_bounds( float *bounds ) {
  bounds[0] = -2.5; bounds[1] = -2;
  bounds[2] = 1.5; bounds[3] = 2;
}

void set_bounds( float *data ) {
  MAXL = data[0]; MAXR = data[2];
  MAXD = data[1]; MAXU = data[3];
}

void set_bounds_screen( WIN_INFO w, int x1, int y1, int x2, int y2 ) {
  float b[4];
  float xfactor, yfactor;
  int tmp;

  if ( x1 > x2 ) {
    tmp = x2;
    x2 = x1;
    x1 = tmp;
  }
  if ( y1 > y2 ) {
    tmp = y2;
    y2 = y1;
    y1 = tmp;
  }

  xfactor = (MAXR - MAXL) / w.width;
  yfactor = (MAXU - MAXD) / w.height;

  b[0] = x1 * xfactor + MAXL;
  b[1] = MAXU - y2 * yfactor;
  b[2] = x2 * xfactor + MAXL;
  b[3] = MAXU - y1 * yfactor;

  set_bounds( b );
}
#define FAST

void draw_box( WIN_INFO win, int wx, int wy, int ww, int wh )
{
  float l_x, l_y, u_x, u_y;
  float x_diff, y_diff;
  float x,y;
  float xfactor, yfactor;
  int width, height;
#ifdef FAST
  int half_w, half_h;
  int subdivide = 0;
  int c1, c2, c;
#endif

  width = win.width;
  height = win.height;

  xfactor = (MAXR - MAXL) / width;
  yfactor = (MAXU - MAXD) / height;

  l_x = wx * xfactor + MAXL;
  l_y = MAXU - wy * yfactor;
  u_x = (wx+ww) * xfactor + MAXL;
  u_y = MAXU - (wy+wh) * yfactor;

  x_diff = u_x - l_x;
  y_diff = u_y - l_y;

#ifdef FAST
  c = mandle_set( l_x, l_y );

  half_w = (ww + 1) / 2;
  half_h = (wh + 1) / 2;

  if ( (ww < BOX_GRAIN && wh < BOX_GRAIN)  
       || (ww == half_w && wh == half_h) ) {
    XSetForeground( display, win.gc, color_map[c] );
    XFillRectangle( display, win.win, win.gc, wx - 1, wy - 1, ww + 2, wh + 2);
    return;
  }

  for ( x = l_x; x <= u_x && !subdivide; x += x_diff / PARTITIONS ) {
    c1 = mandle_set( x, l_y );
    c2 = mandle_set( x, u_y );
    if ( c1 != c2 || c1 != c )
      subdivide = 1;
  }
  for ( y = l_y; y <= u_y && !subdivide; y += y_diff / PARTITIONS ) {
    c1 = mandle_set( l_x, y );
    c2 = mandle_set( u_x, y );
    if ( c1 != c2 || c1 != c )
      subdivide = 1;
  }

  if ( !subdivide ) {
    XSetForeground( display, win.gc, color_map[c] );
    XFillRectangle( display, win.win, win.gc, wx - 1, wy - 1, ww + 3, wh + 3);
    return;
  }

  draw_box( win, wx, wy, half_w, half_h);
  draw_box( win, wx, wy + half_h, half_w, half_h);
  draw_box( win, wx + half_w, wy, half_w, half_h);
  draw_box( win, wx + half_w, wy + half_h, half_w, half_h); 
  return;
#else

  for ( x = l_x; x < u_x; x += (x_diff / width) ) {
    for ( y = l_y; y < u_y; y += (y_diff / height) ) {
      XSetForeground( display, win.gc, color_map[mandle_set( x, y )] );
      XDrawPoint( display, win.win, win.gc,  
		  (x - MAXL) / xfactor,
		  (MAXU - y) / yfactor);
    }
  }
#endif
}

int mandle_set( float x, float y ) {
  int i;
  float z1;
  float z2 ;
  float tz1, tz2;

  z1 = x; z2 = y;

  for ( i = 0; i < ACCURACY; i++) {

    tz1 = (z1 * z1 - z2 * z2) + x;
    tz2 = 2 * z2 * z1 + y;

    z1 = tz1; z2 = tz2;
    if ( (z1 * z1 + z2 * z2) > 4 ) break;
  }

  if ( i == ACCURACY) 
    return 0;

  return (i % (COLORS - 1)) + 1;
}


