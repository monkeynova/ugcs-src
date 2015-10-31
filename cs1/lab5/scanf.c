#include <local/cs1.h>
#include <stdarg.h>

#define BUFSIZE 256

/* CS 1 Graphics Library line input routine.
 *
 * Call with the following parameters:
 *
 * prompt -- string to appear in the input window
 *    example: "Input value please:"
 * fmt -- scanf-style format string
 *    example: "%lf"
 * ... -- scanf-style arguments
 *    example: &val
 *
 * The function will pop up a small blue window with the prompt string in it.
 * The user will be able to enter a string of characters (just like for
 * scanf itself).  When they press Return it will be scanned and any values
 * returned in the appropriate arguments (just like scanf); the window will
 * be removed.
 */

int cs1_scanf(char *prompt,char *fmt,...) {
  va_list pvar;
  CS1_Window popup;
  char buf[BUFSIZE+1];
  int len;
  char ch;
  int ret;

  /* Create the popup window. */
  popup = cs1_make_window("light slate blue",490,473,300,70);
  cs1_window_title(popup,"Enter Value");
  /* Print the prompt string. */
  cs1_set_color("white");
  cs1_printf(popup,20,30,"%s",prompt);
  buf[len = 0] = 0;
  do {
    do
      ch = cs1_inkey();
    while (ch == '\0');
    if (ch != '\r') {
      switch (ch) {
        case 8:
          if (len > 0)
            --len;
          break;
        default:
          if (len < BUFSIZE)
            buf[len++] = ch;
      }
      buf[len] = 0;
      cs1_set_color("light slate blue");
      cs1_fill_box(popup,10,35,300,70);
      cs1_set_color("white");
      cs1_printf(popup,20,50,"%s",buf);
    }
  } while (ch != '\r');
  /* Remove the popup window now that we're done. */
  cs1_remove_window(popup);

  /* Magic stuff happens here -- close your eyes. */
  va_start(pvar,fmt);
  ret = vsscanf(buf,fmt,pvar);
  va_end(pvar);

  return (ret);
}

#undef BUFSIZE
