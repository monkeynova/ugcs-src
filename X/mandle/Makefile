CC=gcc
CFLAGS=-Wall 
LIBS=-L/usr/X11R6/lib -lX11
OBJS=Xmandle.o mandle.o xstuff.o

Xmandle: $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o Xmandle

Xmandle.o: Xmandle.c mandle.h xstuff.h

mandle.o: mandle.c mandle.h xstuff.h

xstuff.o: xstuff.c xstuff.h

clean:
	rm -f *~ core

fullclean:
	rm -f *~ *.o core
