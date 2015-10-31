#ifndef __ROOM_HH
#define __ROOM_HH

#include "Thingy.hh"
#include "WorldDriver.hh"
#include "Player.hh"

enum dirs {
  NORTHWEST,
  NORTH,
  NORTHEAST,
  EAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  WEST,
  UP,
  DOWN
};

class Room : public Thingy {
private:
  string name;
  string sortDesc;
  string longDesc;

  WorldDriver *world;

  Room *neighbors[10];

public:
  Room( WorldDriver *wd, string n, string sDesc, string lDesc );

  void setDescription( string desc ) { longDesc = desc; }
  void setName( string n ) { name = n; }

  string getDescription( void ) { return description; }
  string getName( void ) { return name; }

  string handleEvent( string event, Player *p, string *rest );
};

#endif



