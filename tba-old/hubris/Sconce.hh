#ifndef __SCONCE_HH
#define __SCONCE_HH

#include "Thingy.hh"
#include "WorldDriver.hh"
#include "Player.hh"
#include "Room.hh"

class Sconce : public Thingy {
private:
  string description;
  string name;
  Room *location;
  Room *whereto;
  dirs whichway;
  WorldDriver *world;

public:
  Sconce( WorldDriver *wd, string n, Room *where, string desc, Room *to, dirs d);

  void setDescription( string d ) { description = d; }
  void setName( string n ) { name = n; }
  string getDescription( void ) { return description; }
  string getName( void ) { return name; }

  bool isCalled( string n ) { return n == "sconce" ||  n == name; }

  bool handleEvent( string event, Player *p, int remaining, string *rest );
};

#endif
