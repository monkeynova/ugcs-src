#include "Item.hh"

Item::Item( WorldDriver *wd, string n, Container *where, string desc ) {
  world = wd;
  name = n;
  location = where;
  description = desc;

  location->add( this );

  wd->addVerb( this, "take", OBJECT );
  wd->addVerb( this, "drop", OBJECT );
  wd->addVerb( this, "look", OBJECT );
}

bool Item::handleEvent( string event, Player *p, int remaining, string *rest ) {
  if ( event == "drop" ) {
    if ( location == p ) {
      p->remove( this );
      location = p->getContainer();
      if ( location != NULL ) 
	location->add( this );

    } else {
      *world << "You don't have " << getName() << "." << endl;
    }

    return true;
  }

  if ( event == "take" ) {
    if ( location == p->getContainer() ) {
      if ( location != NULL )
	location->remove( this );
      location = p;
      p->add( this );

      return true;
    } else if ( location == p ) {
      *world << "You already have " << getName() << "." << endl;
      return true;

    } else {
      return false;

    }
  }

  if ( event == "look" ) {
    *world << getDescription() << endl;
    return true;
  }

  return false;
}
