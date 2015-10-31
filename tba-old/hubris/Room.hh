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
  DOWN,
  DIRSIZE
};

extern const char *dirNames[];

class Room : public Container {
private:
  string name;
  string desc;

  WorldDriver *world;

  Room *neighbors[DIRSIZE];

public:
  Room( WorldDriver *wd, string n, string _desc );

  void setDescription( string _desc ) { desc = _desc; }
  void setName( string n ) { name = n; }

  string getContDescription( void ) { return desc; }
  string getName( void ) { return name; }

  void setRoom( Room *r, dirs d ) { neighbors[ d ] = r; }

  bool handleEvent( string event, Player *p, int remain, string *rest );
};

#endif



