#ifndef __ITEM_HH
#define __ITEM_HH

#include <string>
#include "Thingy.hh"
#include "Container.hh"
#include "WorldDriver.hh"
#include "Player.hh"

class Item : public Thingy {
private:
  string name;
  string description;
  Container *location;
  WorldDriver *world;

public:
  Item( WorldDriver *wd, string n, Container *where, string desc );

  void setDescription( string desc ) { description = desc; }
  void setName( string n ) { name = n; }

  string getDescription( void ) { return description; }
  string getName( void ) { return name; }

  Container *getContainer( void ) { return location; }
  bool handleEvent( string event, Player *p, int remaining, string *rest );
};

#endif
