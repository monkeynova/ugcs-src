#ifndef __PLAYER_HH
#define __PLAYER_HH

#include "Container.hh"
#include "WorldDriver.hh"

/*
  Player (is-a container)

  The games represntation of the user. It has the standard container 
  stuff, but there is also a heartbeat function. This gets called
  right before the prompt is printed out. This is to do any updating 
  that needs to be done that isn't command driven.

  The global commands should probably go here or in a specialized thingy.
  (e.g. save, quit, etc.)
*/

class Player : public Container {
private:
  Container *r;
  WorldDriver *world;

public:
  Player( WorldDriver *wd, Container *_r );

  void setContainer( Container *_r ) { r = _r; }
  Container *getContainer() { return r; }

  // This is a kludge in order to handle the inventory command
  string getContDescription() { return "You have a bag."; }
  string getName() { return "Me"; }
  void setDescription( string ) { }
  void setName( string ) { }
  bool handleEvent( string event, Player *p, int remaining, string *rest );

  // Write the function if you want it to do something interresting
  void heartbeat() { }
};

#endif
