CXX=g++
CXXFLAGS=-Wall -g
OBJS=Container.o WorldDriver.o Room.o Player.o Item.o Sconce.o main.o
LIBS=
EXE=tba

tba: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(EXE)

main.o: main.cc WorldDriver.hh Player.hh Sconce.hh Makefile

WorldDriver.o: WorldDriver.cc WorldDriver.hh Player.hh Thingy.hh Makefile

Player.o: Player.cc Player.hh Container.hh WorldDriver.hh Makefile

Room.o: Room.cc Room.hh Thingy.hh WorldDriver.hh Player.hh Makefile

Container.o: Container.cc Container.hh Thingy.hh Makefile

Item.o: Item.cc Item.hh Thingy.hh Container.hh WorldDriver.hh Player.hh Makefile

Sconce.o: Sconce.cc Sconce.hh Room.hh Player.hh WorldDriver.hh Thingy.hh Makefile

clean:
	rm -f *~ \#*\# *.o

neat:
	rm -f *~ \#*\#