#ifndef __ROOM_HH
#define __ROOM_HH

#include "Thingy.hh"
#include "WorldDriver.hh"
#include "Player.hh"

/*
  Room (is-a container)

  This is a specific container to hold just about everything. It also
  maintains the directional movement commands. In order to affect howw
  the world works, you can use setRoom to dynamically change the room,
  or derive a specific room class off of this
*/

/*
  These are the possible directions to go in and this is easier than
  a whole bunch of #define's
*/
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

/* This is an array of directoin strings */
extern const char *dirNames[];

class Room : public Container {
private:
  string name;
  string desc;

  WorldDriver *world;

  Room *neighbors[DIRSIZE];

public:
  Room( WorldDriver *wd, string n, string _desc );

  virtual void setDescription( string _desc ) { desc = _desc; }
  virtual void setName( string n ) { name = n; }

  virtual string getContDescription( void ) { return desc; }
  virtual string getName( void ) { return name; }

  virtual void setRoom( Room *r, dirs d ) { neighbors[ d ] = r; }

  virtual bool handleEvent( string event, Player *p, int remain, string *rest );
};

#endif



