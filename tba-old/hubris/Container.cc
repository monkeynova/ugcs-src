#include "Container.hh"

bool Container::contains( Thingy *t ) {
  for( list<Thingy*>::iterator i = l.begin(); i != l.end(); i++ ) {
    if ( *i == t )
      return true;
  }
  
  return false;
}

Thingy *Container::lookup( string name ) {
  Thingy *ret = NULL;

  for( list<Thingy*>::iterator i = l.begin(); i != l.end(); i++ ) {
    if ( (*i)->isCalled( name ) ) {
      if ( ret != NULL ) {
	throw string( "Which " + name + "?\n" );
      } else {
	ret = *i;
      }
    }
  }

  return ret;
}

string Container::getDescription( void ) {
  string ret;

  ret = getContDescription();
  if ( ! empty() ) {
    ret += "\nIt contains:\n";
    for( list<Thingy*>::iterator i = l.begin(); i != l.end(); i++ ) {
      ret += "  " + ((Thingy *)*i)->getName() + "\n";
    }
  }
  return ret;
}
