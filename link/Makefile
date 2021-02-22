PROJECT=cdplink
CC = gcc
INCDIR=
INCS=
DEFS= -Wall
LIBDIR=
LIBS =
OBJS = \
	addsymbol.o \
	cleanup.o \
	loadfile.o \
	main.o \
	outputbin.o \
	outputhex.o \
	outputrcs.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

addsymbol.o:    header.h addsymbol.c
cleanup.o:      header.h cleanup.c
loadfile.o:     header.h loadfile.c
main.o:         header.h main.c
outputbin.o:    header.h outputbin.c
outputhex.o:    header.h outputhex.c
outputrcs.o:    header.h outputrcs.c
