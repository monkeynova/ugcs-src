#include <local/cs1.h>

main() {
  /* the window we will make */
  CS1_Window window;

  /* Create a window with background color "peach puff", sized 120 pixels
     by 50 pixels, located 10 pixels from the upper-left corner of the
     screen. */
  window = cs1_make_window("peach puff",100,100,120,50);

  /* Set the window title. */
  cs1_window_title(window,"Hello World");

  /* Set the drawing color to "maroon" for the text. */
  cs1_set_color("maroon");

  /* Print "Hello World!" in the window at 20 pixels from the left and 30
     pixels from the top edge. */
  cs1_printf(window,20,30,"Hello World!");

  /* Wait until the user has pressed a key -- we don't care what. */
  while (cs1_inkey() == '\0') { }

  /* Program termination will close the window. */
}
