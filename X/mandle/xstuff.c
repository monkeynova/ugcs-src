#include "xstuff.h"
#include <stdio.h>
#include <stdlib.h>

Display *display = (Display *) NULL;
int screen_num;
long color_map[COLORS];

void error( char *s ) {
  printf( "%s\n", s );
  exit( -1 );
}

void InitX( char *display_name ) {
  if ( (display = XOpenDisplay( display_name)) == NULL )
    error( "Cannot connect to X server!" );

  screen_num = DefaultScreen( display );
}

WIN_INFO NewBaseWin( int x, int y, int width, int height, char *wname ) {
  XTextProperty name;
  XSizeHints sh;
  XWMHints wmh;
  XClassHint ch;
  unsigned long valuemask = 0;
  XGCValues values;

  Window w;
  GC win_gc;

  WIN_INFO ret;

  if ( display == NULL ) 
    error( "Cannot create window without a connection to an X server" );

  w = XCreateSimpleWindow( display, RootWindow( display, screen_num ), x, y,
			   width, height, BORDER_WIDTH, 
			   BlackPixel( display, screen_num ),
			   WhitePixel( display, screen_num ) );

  if (XStringListToTextProperty( &wname, 1, &name ) == 0)
    error( "Cannot create window name!" );

  sh.flags = PPosition | PSize | PMinSize;
  sh.min_width = width;
  sh.min_height = height;

  wmh.initial_state = NormalState;
  wmh.input = True;
  wmh.flags = StateHint | InputHint;

  ch.res_name = ch.res_class = wname;

  XSetWMProperties( display, w, &name, &name, &wname, 1, &sh, &wmh, &ch );
  
  XSelectInput( display, w, ExposureMask | KeyPressMask | ButtonPressMask |
		StructureNotifyMask | PointerMotionMask | ButtonReleaseMask );

  win_gc = XCreateGC( display, w, valuemask, &values );
  XSetForeground( display, win_gc, BlackPixel( display, screen_num ) );

  XMapWindow( display, w );

  ret.win = w;
  ret.gc = win_gc;
  ret.width = width;
  ret.height = height;

  return ret;
}

void SetupXColorMap( long *colors ) {
  XColor clrs[COLORS];
  Colormap cmap;
  char color_str[8];
  int i;
  long pm[1];

  cmap = DefaultColormap( display, screen_num );

  if (! XAllocColorCells( display, cmap, False, pm, 0, colors, COLORS) )
    error( "Could not allocate colors!" );
  
  for ( i = 0; i < COLORS; i++ ) {
    if ( i )
      sprintf( color_str, "#%02X%02X%02X", rand() % 256, 
	       rand() % 256, rand() % 256);
    else 
      strcpy( color_str, "black" );
    if ( !XParseColor( display, cmap, color_str, clrs + i ) )
      error( "Color name not in database!" );
    clrs[i].pixel = colors[i];
    clrs[i].flags = DoRed | DoGreen | DoBlue;
  }

  XStoreColors( display, cmap, clrs, COLORS );

}

void DrawXorBox( WIN_INFO wi, int x, int y, int w, int h) {
  int ux, uy, uw, uh;

  if ( w > 0 ) {
    ux = x;
    uw = w;
  } else {
    ux = x + w;
    uw = -w;
  }

  if ( h > 0 ) {
    uy = y;
    uh = h;
  } else {
    uy = y + h;
    uh = -h;
  }

  XSetFunction( display, wi.gc, GXxor );
  XSetForeground( display, wi.gc, WhitePixel( display, screen_num ));
  XDrawRectangle( display, wi.win, wi.gc, ux, uy, uw, uh );
  XSetFunction( display, wi.gc, GXcopy );
}

void CloseWin( WIN_INFO *w ) {
  XFreeGC( display, w->gc );
}

void CloseX( void ) {
  XCloseDisplay( display );
}

