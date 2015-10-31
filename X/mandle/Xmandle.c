#include <stdio.h>
#include "xstuff.h"
#include "mandle.h"

void main_draw( WIN_INFO, int, int, int, int, int );

/* Main stuff */

#define WIDTHHINT    300
#define HEIGHTHINT   300

void main( int argc, char **argv ) {
  WIN_INFO wi;
  XEvent e;
  float init[4];
  int first_draw = 1;
  char *progname = argv[0];
  int mouse_sx, mouse_sy;
  int mouse_ex, mouse_ey;
  int dragging = 0;
  
  init_bounds( init );
  set_bounds( init );

  InitX( (char *)NULL );
  wi = NewBaseWin( 100, 100, WIDTHHINT, HEIGHTHINT, progname );

  SetupXColorMap( color_map );

  while ( 1 ) {
    XNextEvent( display, &e );
    switch ( e.type ) {
    case Expose:
      main_draw( wi, first_draw, e.xexpose.x, e.xexpose.y, 
		 e.xexpose.width, e.xexpose.height );
      first_draw = 0;
      break;
    case ConfigureNotify:
      wi.width = e.xconfigure.width;
      wi.height = e.xconfigure.height;
      first_draw = 1;
      break;
    case ButtonPress:
      switch ( e.xbutton.button ) {
      case 1: /* Left Button */
	mouse_ex = mouse_sx = e.xbutton.x;
	mouse_ey = mouse_sy = e.xbutton.y;
	dragging = 1;
	break;
      case 2: /* Middle Button */
	printf( "Resetting default boundaries\n");
	set_bounds( init );
	main_draw( wi, 1, 0, 0, wi.width, wi.height );
	break;
      case 3: /* Right Button */
	printf("Exiting\n");
	CloseWin( &wi );
	CloseX();
	exit ( 0 );
	break;
      }
      break; 
    case ButtonRelease:
      if ( dragging ) {
	if ( e.xbutton.button == 1 ) {
	  DrawXorBox( wi, mouse_sx, mouse_sy, 
		      mouse_ex - mouse_sx, mouse_ey - mouse_sy ); 
	  if ( mouse_ex != mouse_sx && mouse_ey != mouse_sy ) {
	    printf( "Zooming in\n");
	    set_bounds_screen( wi, mouse_sx, mouse_sy, mouse_ex, mouse_ey );
	    main_draw( wi, 1, 0, 0, wi.width, wi.height );
	  }
	  dragging = 0;
	}      
      }
      break;
    case MotionNotify:
      if ( dragging ) {
	DrawXorBox( wi, mouse_sx, mouse_sy, 
		    mouse_ex - mouse_sx, mouse_ey - mouse_sy );
	mouse_ex = e.xmotion.x;
	mouse_ey = e.xmotion.y;
	DrawXorBox( wi, mouse_sx, mouse_sy, 
		    mouse_ex - mouse_sx, mouse_ey - mouse_sy );
      }
      break;
    case KeyPress:
      CloseWin( &wi );
      CloseX();
      exit ( 0 );
      break;
    default:
      break;
    }
  }

}

void main_draw( WIN_INFO wi, int first_draw, int x, int y, int w, int h ) {
  printf( "Drawing...\n");
  if ( first_draw ) {
    draw_box(wi, x, y, w / 2, h / 2 ); 
    draw_box(wi, w / 2, y, w / 2, h / 2 ); 
    draw_box(wi, x, h / 2, w / 2, h / 2 ); 
    draw_box(wi, w / 2, h / 2, w / 2, h / 2); 
  } else {
    draw_box( wi, x, y, w, h );
  }
  printf( "Done\n" );
}



