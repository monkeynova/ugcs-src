#include "Sconce.hh"

Sconce::Sconce( WorldDriver *wd, string n, Room *where, string desc, Room *to, dirs d ) {
  world = wd;
  name = n;
  location = where;
  description = desc;
  whereto = to;
  whichway = d;

  location->add( this );

  world->addVerb( this, "turn", OBJECT );
  world->addVerb( this, "look", OBJECT );
  world->addVerb( this, "take", OBJECT );
}

bool Sconce::handleEvent( string event, Player *p, int remaining, string *rest ) {
  if ( event == "look" ) {
    *world << getDescription();
    return true;
  }

  if ( event == "turn" ) {
    if ( remaining == 0 ) {
      *world << "Which direction?" << endl;
    } else {
      if ( rest[ 0 ] == "left" ) {
	if ( whereto != NULL ) {
	  *world << "As you turn the sconce to the left there is a rumbling, and" +
	    string( "a passage to the " ) + dirNames[ whichway * 2 ] + 
	    " is revealed." << endl;
	
	  location->setRoom( whereto, whichway );
	} else {
	  *world << "The sconce won't budge." << endl;
	}
	
      } else if ( rest[ 0 ] == "right" ) {
	*world << "The sconce doesn't turn that way." << endl;
      } else {
	*world << "You don't turn a sconce like that!!!" << endl;
      }
    }

    return true;
  }

  if ( event == "take" ) {
    *world << "It's firmly attached to the wall!" << endl;
    return true;
  }

  return false;
}
