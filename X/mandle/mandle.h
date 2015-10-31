/* Mandle Stuff */

#ifndef ACCURACY

#include "xstuff.h"

#define ACCURACY       500   /* Number of steps in z^2+c calculations       */
#define PARTITIONS       5   /* Points on Box to say if it's all one color  */
#define BOX_GRAIN        2   /* Size of smallest block of color (in pixels) */

void init_bounds( float * );
void draw_box( WIN_INFO, int, int, int, int );
void set_bounds( float * );
void set_bounds_screen( WIN_INFO, int, int, int, int );
int mandle_set( float, float );

float MAXL, MAXR, MAXU, MAXD;

#endif


