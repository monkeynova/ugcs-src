#include <iostream.h>
#include "WorldDriver.hh"
#include "Player.hh"
#include "Room.hh"
#include "Item.hh"
#include "Sconce.hh"

void createWorld( WorldDriver *wd, Player *p ) {
  Room *path = new Room( wd, "Pathway",
			 string( "You see a path leading to th north, but in all other " ) +
			 "directions there is nothing but darkness..." );
  Room *doorway = new Room( wd, "Doorway",
			    string( "You are standing at an immense doorway to the " ) +
			    "north. Ornate symbols are carved into the stone " +
			    "surrounding the door, and the wood appears to be " +
			    "made of a heavy oak." );
  Room *entry = new Room( wd, "Entrance",
			  string( "This is a grand room with great tapestries on all " ) +
			  "sides, but the lighting gives the room an eerie " +
			  "feel and you'ld sear the shadows were circling you " +
			  "looking for a weakness. Exits lie to the north, " +
			  "south, northeast, and northwest." );
  Room *dining = new Room( wd, "Dining Room",
			   string( "You see a long table with fine china on it, and " ) +
			   "burning candles are centered upon it. Exits lie to " +
			   "the southwest and north." );
  Room *kitchen = new Room( wd, "Kitchen",
			    string( "As opposed to the rest of the gothic nature of the " ) +
			    "house this room seams a bit light an clean, well " +
			    "except for the boiling blood on the stove. The " +
			    "only exit lies to the south." );
  Room *library = new Room( wd, "Library",
			    string( "This room is littered with books. They cover the " ) +
			    "walls and are strewn across the floor. There is " +
			    "also a pair of sitting chairs around a fireplace " +
			    "with well worn cushions, the only exit lies to the " +
			    "south." );
  Room *arbor = new Room( wd, "Arboritum",
			  string( "You are in what once could have been full of life " ) +
			  "but now is a souce of dead plants, and overgrown " +
			  "vines. There is a hole in the class enclosing the " +
			  "room to the west, and a door to the southeast." );
  Room *graveyard = new Room( wd, "Graveyard",
			      string( "Talk about creepy, you are in a dark, damp " ) +
			      "graveyard with gravestones every which way. " +
			      "Well at least you are out of the house. Exits " +
			      "are to the east (back into the house) and there " +
			      "is a gate to the north." );
  Room *exit = new Room( wd, "Exit",
			 string( "You've done it, you've gotten out of the house and " ) +
			 "are now free." );
  Room *crypt = new Room( wd, "Crypt",
			  "It's a crypt and I'm bored with writing." );

  path->setRoom( doorway, NORTH );
  doorway->setRoom( path, SOUTH );
  doorway->setRoom( entry, NORTH );
  entry->setRoom( doorway, SOUTH );
  entry->setRoom( dining, NORTHEAST );
  entry->setRoom( library, NORTH );
  entry->setRoom( arbor, NORTHWEST );
  dining->setRoom( entry, SOUTHWEST );
  dining->setRoom( kitchen, NORTH );
  kitchen->setRoom( dining, SOUTH );
  library->setRoom( entry, SOUTH );
  //  library->setRoom( crypt, DOWN );
  crypt->setRoom( library, UP );
  arbor->setRoom( entry, SOUTHEAST );
  arbor->setRoom( graveyard, WEST );
  graveyard->setRoom( arbor, EAST );
  graveyard->setRoom( exit, NORTH );
  exit->setRoom( graveyard, SOUTH );

  Item *rock = new Item( wd, "rock", path,
			 "It's a rock, get over it" );
  Item *garlic = new Item( wd, "garlic", kitchen,
			   "Pffew it smells strong." );
  Sconce *left = new Sconce( wd, "left sconce", library, "It's the candle holder on the left", crypt, DOWN );
  Sconce *right = new Sconce( wd, "right sconce", library, "It's the candle holder on the right", NULL, DOWN );

  p->setContainer( path );
}

int main( void ) {
  WorldDriver god( cin, cout );
  Player *me = new Player( &god, NULL); // I need to know god's address :)

  god.setPlayer( me );

  createWorld( &god, me );

  god.mainLoop();
}
