#include "Room.hh"

const char *dirNames[] = { 
  "northwest", 
  "nw",
  "north", 
  "n",
  "northeast",
  "ne",
  "east",
  "e",
  "southeast",
  "se",
  "south",
  "s",
  "southwest",
  "sw",
  "west",
  "w",
  "up",
  "u",
  "down",
  "d"
};

Room::Room( WorldDriver *wd, string n, string _desc ) {
  world = wd;
  name = n;
  desc = _desc;

  world->addVerb( this, "n", NOMENTION );
  world->addVerb( this, "north", NOMENTION );
  world->addVerb( this, "ne", NOMENTION );
  world->addVerb( this, "northeast", NOMENTION );
  world->addVerb( this, "nw", NOMENTION );
  world->addVerb( this, "northwest", NOMENTION );
  world->addVerb( this, "s", NOMENTION );
  world->addVerb( this, "south", NOMENTION );
  world->addVerb( this, "se", NOMENTION );
  world->addVerb( this, "southeast", NOMENTION );
  world->addVerb( this, "sw", NOMENTION );
  world->addVerb( this, "southwest", NOMENTION );
  world->addVerb( this, "e", NOMENTION );
  world->addVerb( this, "east", NOMENTION );
  world->addVerb( this, "w", NOMENTION );
  world->addVerb( this, "west", NOMENTION );
  world->addVerb( this, "u", NOMENTION );
  world->addVerb( this, "up", NOMENTION );
  world->addVerb( this, "d", NOMENTION );
  world->addVerb( this, "down", NOMENTION );

  world->addVerb( this, "go", NOMENTION );
  world->addVerb( this, "head", NOMENTION );

  world->addVerb( this, "look", NOMENTION );

  for( int i = 0; i < DIRSIZE; i++ )
    neighbors[i] = NULL;
}

bool Room::handleEvent( string event, Player *p, int remain, string *rest ) {
  string dir;

  if ( event == "look" ) {
    if ( remain == 0 ) {
      *world << getDescription() << endl;
      return true;
    } else {
      return false;
    }
  }

  if ( event == "head" || event == "go" ) {
    if ( remain == 1 ) {
      dir = rest[0];
    } else {
      return false;
    }
  } else {
    dir = event;
  }

  for( int i = 0; i < DIRSIZE * 2; i++ ) {
    if ( dir == dirNames[ i ] ) {
      if ( neighbors[ i / 2 ] != NULL ) {
	p->setContainer( neighbors[ i / 2 ] );

      } else {
	*world << "There is no passage " << dirNames[ 2 * (i / 2) ] << "-wards.\n";
      }

      return true;
    }
  }

  return false;
}
