#ifndef __WORLDDRIVER_HH
#define __WORLDDRIVER_HH

#include <iostream.h>
#include <string>
#include <list>
#include "Thingy.hh"

class Player; // foreward refferencing

#define MAXCHARS   1024
#define MAXWORDS     32

enum MentionMeans {
  OBJECT,
  NOMENTION,
  GLOBAL,
  MENTINOMEANSSIZE
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

  void addVerb( Thingy *t, string cmd, MentionMeans how );
  void mainLoop();

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
