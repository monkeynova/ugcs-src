#ifndef __CONTAINER_HH
#define __CONTAINER_HH

#include <list>
#include "Thingy.hh"

/*
  Container (is-a Thingy)

  This is an abstractoin of a bag. You can add stuff, remove stuff
  and look for stuff in it.

*/

class Container : public Thingy {
private:
  list<Thingy *> l;

public:
  void add( Thingy *t ) { l.push_front( t ); }
  void remove( Thingy *t ) { l.remove( t ); }
  bool contains( Thingy *t ); // Look for thingy in the list
  bool empty() { return l.empty(); }

  Thingy *lookup( string name ); // Check to see if there is something
                                 // called name in the contaziner

  virtual string getDescription( void );

  virtual string getContDescription( void ) = NULL;
};

#endif
