#ifndef __ITEM_HH
#define __ITEM_HH

#include <string>
#include "Thingy.hh"
#include "Container.hh"
#include "WorldDriver.hh"
#include "Player.hh"

/*
  Item (is-a Thingy)

  This is a basic item which allows for picking up and putting down
  And it allows for looking

*/

class Item : public Thingy {
private:
  string name;
  string description;
  Container *location;
  WorldDriver *world;

public:
  Item( WorldDriver *wd, string n, Container *where, string desc );

  virtual void setDescription( string desc ) { description = desc; }
  virtual void setName( string n ) { name = n; }

  virtual string getDescription( void ) { return description; }
  virtual string getName( void ) { return name; }

  Container *getContainer( void ) { return location; }
  virtual bool handleEvent( string event, Player *p, int remaining, string *rest );
};

#endif
