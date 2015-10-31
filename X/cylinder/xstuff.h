/* X11 Stuff */

#ifndef BORDER_WIDTH

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#define BORDER_WIDTH       0
#define COLORS            50

typedef struct win_info_typ {
  Window win;
  GC gc;
  int width, height;
} WIN_INFO;

extern long color_map[COLORS];

extern Display *display;
extern int screen_num;

void InitX( char * );
WIN_INFO NewBaseWin( int, int, int, int, char * );
void SetupXColorMap( long *colors );
void DrawXorBox( WIN_INFO, int, int, int, int );
void CloseWin( WIN_INFO * );
void CloseX( void );

#endif
