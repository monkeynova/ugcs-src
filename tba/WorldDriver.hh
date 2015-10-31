#ifndef __WORLDDRIVER_HH
#define __WORLDDRIVER_HH

#include <iostream.h>
#include <string>
#include <list>
#include "Thingy.hh"

class Player; // forward referencing

#define MAXCHARS   1024
#define MAXWORDS     32

/*
  WorldDriver

  This is the thing which handles all io from the user and dolling
  out events to sub-classes. Modifications to this should be avoided
  unless you want to profoundly change the workings of the game.

  WorldDriver overrides the << operator for just about everything so
  you can print stuff out easily and the outputstream is not limitted
  to cout
*/

/*
  MentionMeans is the list of how verbs should be treated in terms
  of what Thingys should have there event handlers called

  OBJECT - the Thingy is the object of the command (take the rock)
  NOMENTION - the Thingy is implied by the players container (go north)
  GLOBAL - called regardless of what's going on (quit)

  These are tried in the order of the enum
 */
enum MentionMeans {
  OBJECT,
  NOMENTION,
  GLOBAL,
  MENTINOMEANSSIZE // This number represents the size of the enum
};

class WorldDriver {
private:
  // So we can print and read
  istream *in;
  ostream *out;

  struct Action {
    string s;
    Thingy *t;

    Action( string _s, Thingy *_t ) { s = _s; t = _t; }
  };

  // Command tables
  list<Action*> actions[ MENTINOMEANSSIZE ];

  // So we can get info on the human
  Player *p;

  void actOnVerb( string, int, string * );

public:
  WorldDriver( istream &_in, ostream &_out );
  ~WorldDriver() { }

  void setPlayer( Player *_p ) { p = _p; }

  // add something else the listner
  void addVerb( Thingy *t, string cmd, MentionMeans how );

  // go in user input mode
  void mainLoop();

  // This is primarily used internally but it tries to
  // turn a string into a Thingy * based on where the
  // character is
  Thingy *resolve( string name );


  WorldDriver &operator <<( string s ) { *out << s; return (*this); }
  WorldDriver &operator <<( double d ) { *out << d; return (*this); }
  WorldDriver &operator <<( int i ) { *out << i; return (*this); }
  // endl / flush / ...
  WorldDriver &operator <<( ostream &o(ostream &) ) { 
    *out << o; return (*this); 
  }
};

#endif
