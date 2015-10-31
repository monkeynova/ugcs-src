#ifndef __THINGY_HH
#define __THINGY_HH

#include <iostream.h>
#include <string>

class Player; // foreward refferencing
class Container;

/*
  Thingy

  This is the basic Object for everything in the world
  It describes what everything in the world needs to do. That is
  set and get descriptions and names. It also sets up the event
  handler which is through the handleEvent methof, which is called
  when particular verbs are called
*/

class Thingy {
private:

public:
  Thingy() { }
  virtual ~Thingy() { }

  virtual void setDescription( string desc ) = NULL;
  virtual void setName( string name ) = NULL;
  
  virtual string getDescription( void ) = NULL;
  virtual string getName( void ) = NULL;

  virtual Container *getContainer( void ) { return NULL; }

  virtual bool isCalled( string name ) { return name == getName(); }

  virtual bool handleEvent( string event, Player *p, int remaining, string *rest ) { }
};

#endif
