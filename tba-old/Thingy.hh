#ifndef __THINGY_HH
#define __THINGY_HH

#include <string>

class Player;

class Thingy {
private:

public:
  Thingy() { }
  virtual ~Thingy() { }

  virtual void setDescription( string desc ) = NULL;
  virtual void setName( string name ) = NULL;
  
  virtual string getDescription( void ) = NULL;
  virtual string getName( void ) = NULL;

  virtual bool isCalled( string name ) { return name == getName(); }

  virtual string handleEvent( string event, Player *p, string *rest ) { }
};

#endif
