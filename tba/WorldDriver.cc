#include <ctype.h>
#include <string.h>
#include "WorldDriver.hh"
#include "Player.hh"

const char *ignoreWords[] = { 
  "a", 
  "an", 
  "the",
  "at",
  "to"
};

const char *prompt = "> ";

WorldDriver:: WorldDriver(istream &_in, ostream &_out ) {
  in = &_in; out = &_out;
}

void WorldDriver::addVerb( Thingy *t, string cmd, MentionMeans how ) {
  actions[how].push_front( new Action( cmd, t ) );
}

void WorldDriver::mainLoop( void ) {
  char line[ MAXCHARS ];
  string words[ MAXWORDS ];
  char *tmp;
  unsigned int i, j;

  while( true ) {
    *this << endl<< p->getContainer()->getName() << endl;
    p->heartbeat();
    *this << prompt << flush;

    in->getline( line, 1024 );

    if ( in->eof() ) {
      *this << endl;
      return;
    }

    for( tmp = line; *tmp != '\0'; tmp++ )
      *tmp = tolower( *tmp );

    for( i = 0; (tmp = strtok( (i)?NULL:line, " \t\r\n" )) != NULL; i++ ) {
      for( j = 0; j < sizeof( ignoreWords )/sizeof( char* ); j++ )
	if ( ! strcmp( tmp, ignoreWords[ j ] ) ) {
	  i--;
	  break;
	} 
      if ( j == sizeof( ignoreWords ) / sizeof( char* ) )
	words[i] = string( tmp );
    }

    actOnVerb( words[0], i - 1, words + 1 );
  }
}

void WorldDriver::actOnVerb( string verb, int remain, string *rest ) {
  list<Action *>::iterator it;

  try {
    for( it = actions[ OBJECT ].begin(); it != actions[ OBJECT ].end(); it++ ) {
      string lookup = rest[0];
      Thingy *tmp;
      
      for( int i = 0; i < remain; i++ ) {
	if ( (tmp = resolve( lookup )) != NULL ) {
	  if ( tmp->handleEvent( verb, p, remain - i - 1, rest + i + 1 ) ) 
	    return;
	}
	lookup += " " + rest[ i + 1 ];
      }
    }
  } catch ( string s ) {
    *this << s;
    return;
  }

  for( it = actions[ NOMENTION ].begin(); it != actions[ NOMENTION ].end(); it++ ) {
    if ( (*it)->t == p->getContainer() && (*it)->s == verb )
      if ( (*it)->t->handleEvent( verb, p, remain, rest ) )
	return;    
  }

  for( it = actions[ GLOBAL ].begin(); it != actions[ GLOBAL ].end(); it++ ) {
    if ( (*it)->s == verb )
      if ( (*it)->t->handleEvent( verb, p, remain, rest ) )
	return;    
  }

  *this << "Hunh?" << endl;
}

Thingy *WorldDriver::resolve( string name ) {
  Thingy *roomt = p->getContainer()->lookup( name );
  if ( roomt != NULL ) 
    return roomt;

  return p->lookup( name );
}
