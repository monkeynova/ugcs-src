#ifndef __CONTAINER_HH
#define __CONTAINER_HH

#include <list>
#include "Thingy.hh"

class Container : public Thingy {
private:
  list<Thingy *> l;

public:
  void add( Thingy *t ) { l.push_front( t ); }
  void remove( Thingy *t ) { l.remove( t ); }
  bool contains( Thingy *t );
  bool empty() { return l.empty(); }

  Thingy *lookup( string name );

  string getDescription( void );

  virtual string getContDescription( void ) = NULL;
};

#endif
