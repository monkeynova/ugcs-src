#ifndef __THINGY_HH
#define __THINGY_HH

#include <iostream.h>
#include <string>

class Player; // foreward refferencing
class Container;

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
