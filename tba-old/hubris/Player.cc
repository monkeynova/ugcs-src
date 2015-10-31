#include "Player.hh"

Player::Player( WorldDriver *wd, Container *_r ) {
  r = _r;
  world = wd;

  world->addVerb( this, "q", GLOBAL );
  world->addVerb( this, "quit", GLOBAL );
  world->addVerb( this, "i", GLOBAL );
  world->addVerb( this, "inventory", GLOBAL );

  world->addVerb( this, "fuck", GLOBAL );
  world->addVerb( this, "say", GLOBAL );
}

bool Player::handleEvent( string event, Player *p, 
			  int remaining, string *rest ) {

  if ( p != this ) // Idiot check if people ever want to change the behavior
    return false;

  if ( event == "quit" || event == "q") {
    *world << "Thank you for playing." << endl;
    exit( 0 );
    return true;
  }

  if ( event == "inventory" || event == "i" ) {
    *world << getDescription() << endl;
    return true;
  }

  if ( event == "say" ) {
    *world << "Talking to yourself is a sign of impending mental collapse...\n";
    return true;
  }

  if ( event == "fuck" ) {
    *world << "We don't tolerate that kind of language here!" << endl;
    return true;
  }

  return false;
}
