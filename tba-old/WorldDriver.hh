#ifndef __WORLDDRIVER_HH
#define __WORLDDRIVER_HH

#include <string>
#include "Thingy.hh"

enum MentionMeans {
  PREPOSITION,
  OBJECT,
  NOMENTION
}

class WorldDriver {
private:
  istream &in;
  ostream &out;

public:
  WorldDriver( istream &_in, ostream &_out ) {
    in = _in; out = _out;
  }
  ~WorldDriver();

  void register( Thingy *t, string cmd, MentionMeans how );
  void mainLoop();
};

#endif
