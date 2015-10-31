#include <local/cs1.h>

/* The color palette, indexed by number 0-7 */

char *colors[8] = {
  "black",
  "red",
  "green",
  "yellow",
  "blue",
  "magenta",
  "cyan",

  /* This next one would be white if we followed the pattern above, but
     the drawing window itself is white, so that would be rather silly. */
  "lemon chiffon"
};

main() 
{
  /* The windows we will display. */
  CS1_Window drawing, palette;
  /* Random integer. */
  int i;
  /* Mouse click coordinates. */
  int x,y;
  /* The last place they drew something. */
  int dx,dy;
  /* Whether or not they're currently drawing. */
  int bf;

  /* Create a largish window for the actual scribbling. */
  drawing = cs1_make_window("white",10,10,600,600);
  cs1_window_title(drawing,"Drawing Window");

  /* Create the palette window. */
  palette = cs1_make_window("grey40",620,10,50,400);
  cs1_window_title(palette,"Palette");

  /* Draw the colors in the palette window. */
  for (i=0; i<8; i++) {
    cs1_set_color(colors[i]);
    cs1_fill_box(palette,5,5+i*50,45,45+i*50);
  }

  /* Draw the divider lines in the palette window. (Stylish, ain't they?) */
  cs1_set_color("grey20");
  for (i=1; i<8; i++)
    cs1_draw_line(palette,0,i*50,50,i*50);

  /* Default color is black. */
  cs1_set_color("black");

  /* Repeat as long as no keys are pressed. */
  while (cs1_inkey() == 0) {
    /* Check if they're drawing something. */
    if (cs1_mouse_button(drawing,cs1_left_button)) {
      /* Find out where the mouse is. */
      x = cs1_mouse_x(drawing); y = cs1_mouse_y(drawing);
      if (bf) {
        /* They were already drawing; extend the line. */
        cs1_draw_line(drawing,dx,dy,x,y);
        dx = x; dy = y;
      } else {
        /* They just started drawing. */
        dx = x; dy = y;
      }
      bf = 1;
    } else
      bf = 0;
    /* Check to see if they selected a color. */
    if (cs1_mouse_press(palette,cs1_left_button,&x,&y)) {
      /* Change the drawing color if so. */
      cs1_set_color(colors[y / 50]);
    }
  }
}
