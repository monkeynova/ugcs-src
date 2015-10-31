#include <local/cs1.h>

/* Draw the paddle at location pos. */

void draw_paddle(CS1_Window window,int pos)
{
  cs1_set_color("lime green");
  cs1_draw_box(window,pos,490,pos+99,499);
  cs1_set_color("dark green");
  cs1_fill_box(window,pos+1,491,pos+98,498);
}

/* Erase the paddle drawn at location pos. */

void erase_paddle(CS1_Window window,int pos)
{
  cs1_set_color("steel blue");
  cs1_fill_box(window,pos,490,pos+99,499);
}

/* Draw the ball at location x,y. */

void draw_ball(CS1_Window window,int x,int y)
{
  cs1_set_color("orange");
  cs1_fill_box(window,x,y,x+9,y+9);
}

/* Erase the ball drawn at location x,y. */

void erase_ball(CS1_Window window,int x,int y)
{
  cs1_set_color("steel blue");
  cs1_fill_box(window,x,y,x+9,y+9);
}

/* Draw a brick at location x,y and with color c. */

void draw_brick(CS1_Window window,int x,int y,char *c)
{
  cs1_set_color(c);
  cs1_fill_box(window,x,y,x+19,y+14);
}

/* Erase a brick drawn at location x,y. */

void erase_brick(CS1_Window window,int x,int y)
{
  cs1_set_color("steel blue");
  cs1_fill_box(window,x,y,x+19,y+14);
}

/* Draw the score. */

void draw_score(CS1_Window window,int score,int lives)
{
  /* Clear score region. */
  cs1_set_color("steelblue3");
  cs1_fill_box(window,0,510,499,549);
  /* Draw the score itself. */
  cs1_set_font("*-times-medium-r-*-*-20-*");
  cs1_set_color("white");
  cs1_printf(window,10,540,"Score: %d",score);
  /* Draw the lives. */
  cs1_set_color("orange");
  while (lives--)
    draw_ball(window,450 - lives * 30,530);
}

/* The game board. */

int bricks[20][12];

/* The number of bricks left. */

int nbricks;

int main()
{
  /* The game window. */
  CS1_Window window;
  /* The current X position of the game paddle. */
  int paddle;
  /* The new position of the paddle. */
  int new_paddle;
  /* The position of the ball. */
  int bx,by;
  /* The velocity of the ball. */
  int vx,vy;
  /* Brick indexes. */
  int i,j;
  /* Flag if we hit a brick. */
  int bonk;
  /* Score ! */
  int score;
  /* Number of balls left. */
  int lives;

  /* Create the game window. */
  window = cs1_make_window("steel blue",100,100,500,550);
  cs1_window_title(window,"Pong!");

  /* Draw the paddle. */
  paddle = 0;
  draw_paddle(window,paddle);

  /* Draw the bricks. */
  for (i=0; i<20; i++) {
    for (j=0; j<4; j++) {
      draw_brick(window,i*25+2,j*20+2,"yellow");
      bricks[i][j] = 3;
    }
    for (j=4; j<8; j++) {
      draw_brick(window,i*25+2,j*20+2,"green");
      bricks[i][j] = 2;
    }
    for (j=8; j<12; j++) {
      draw_brick(window,i*25+2,j*20+2,"red");
      bricks[i][j] = 1;
    }
  }
  nbricks = 20*12;

  /* Draw the ball. */
  bx = 245;
  by = 375;
  /* Start it moving straight down at a stately pace. */
  vx = 0;
  vy = 7;
  draw_ball(window,bx,by);

  /* Set the score. */
  score = 0;
  lives = 5;
  draw_score(window,score,lives);

  /* Initialize the game timer.  We move the ball every 1/20th second;
     that's 50,000 microseconds. */
  cs1_set_timer(50000);
  while (cs1_inkey() == 0) {
    /* Check if the paddle has been moved. */
    new_paddle = cs1_mouse_x(window) - 50;
    if (new_paddle < 0)
      new_paddle = 0;
    if (new_paddle > 400)
      new_paddle = 400;
    if (new_paddle != paddle) {
      erase_paddle(window,paddle);
      paddle = new_paddle;
      draw_paddle(window,paddle);
    }
    /* Check if the game timer has expired yet. */
    if (cs1_timer_done()) {
      /* Move the ball. */
      erase_ball(window,bx,by);
      bx = bx + vx;
      by = by + vy;
      /* Bounce off the left and right sides of the screen if necessary. */
      if (bx > 490) {
        vx = -vx;
        bx = 490;
      }
      if (bx < 0) {
        vx = -vx;
        bx = 0;
      }
      /* Bounce off the top of the screen if necessary. */
      if (by < 0) {
        vy = -vy;
        by = 0;
      }
      /* The bottom of the screen is more complicated. */
      if (by > 480) {
        /* Check if the ball hit the paddle. */
        if (bx > paddle - 10 && bx < paddle + 100) {
          /* Bounce off the paddle. */
          by = 480;
          vy = -vy;
          /* Put some "english" on the ball depending on where it was hit. */
          vx = vx + (bx - paddle - 45) / 4;
        } else {
          /* Oops!  Start over. */
          if (lives--) {
            bx = 245;
            by = 375;
            vx = 0;
            vy = 7;
            draw_score(window,score,lives);
          } else {
            printf("Good game!  Your final score was %d\n",score);
            return 0;
          }
        }
      }
      /* Check if we hit a brick.  This is fairly tricky; the ball itself can
         intersect four places a brick might be. */
      bonk = 0;
      for (i = bx / 25; i <= (bx + 9) / 25; i++)
        for (j = by / 20; j <= (by + 9) / 20; j++)
          if (i >= 0 && j >= 0 && i < 20 && j < 12 && bricks[i][j] != 0) {
            erase_brick(window,i*25+2,j*20+2);
            score = score + bricks[i][j];
            bricks[i][j] = 0;
            bonk = 1;
            nbricks--;
          }
      /* Reverse direction and update score if we hit a brick. */
      if (bonk) {
        vy = -vy;
        draw_score(window,score,lives);
      }
      /* See if they won. */
      if (!nbricks) {
        printf("You did it!  Yay!\n");
        return 0;
      }
      /* Finally, draw the ball in its new location. */
      draw_ball(window,bx,by);
      /* Reset the timer for next time. */
      cs1_set_timer(50000);
    }
  }
  return 0;
}
