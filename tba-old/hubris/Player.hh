#ifndef __PLAYER_HH
#define __PLAYER_HH

#include "Container.hh"
#include "WorldDriver.hh"

class Player : public Container {
private:
  Container *r;
  WorldDriver *world;

public:
  Player( WorldDriver *wd, Container *_r );

  void setContainer( Container *_r ) { r = _r; }
  Container *getContainer() { return r; }

  string getContDescription() { return "You have a bag."; }
  string getName() { return "Me"; }
  void setDescription( string ) { }
  void setName( string ) { }
  bool handleEvent( string event, Player *p, int remaining, string *rest );
  void heartbeat() { }
};

#endif
