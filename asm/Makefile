PROJECT=cdpasm
CC = gcc
INCDIR=
INCS=
DEFS= -Wall
LIBDIR=
LIBS =
OBJS = \
	adddefine.o \
	assemble.o \
	assemblypass.o \
	evaluate.o \
	finddefine.o \
	findlabel.o \
	flush.o \
	frombinary.o \
	fromdec.o \
	fromhex.o \
	isrreg.o \
	lookupdefine.o \
	lookuplabel.o \
	lookupopcode.o \
	main.o \
	opcode.o \
	output.o \
	parse.o \
	preif.o \
	readfile.o \
	readline.o \
	reduce.o \
	setup.o \
	setup1805.o \
	showerror.o \
	tokenize.o \
	undef.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

asm.o: header.h
support.o: header.h

clean:
	-rm *.o
	-rm $(PROJECT)
	-rm *.prg

adddefine.o:    header.h adddefine.c
assemble.o:     header.h assemble.c
assemblypass.o: header.h assemblypass.c
evaluate.o:     header.h evaluate.c
finddefine.o:   header.h finddefine.c
findlabel.o:    header.h findlabel.c
flush.o:        header.h flush.c
frombinary.o:   header.h frombinary.c
fromdec.o:      header.h fromdec.c
fromhex.o:      header.h fromhex.c
isrreg.o:       header.h isrreg.c
lookupdefine.o: header.h lookupdefine.c
lookuplabel.o:  header.h lookuplabel.c
lookupopcode.o: header.h lookupopcode.c
main.o:         header.h main.c
opcode.o:       header.h opcode.c
output.o:       header.h output.c
parse.o:        header.h parse.c
preif.o:        header.h preif.c
readfile.o:     header.h readfile.c
readline.o:     header.h readline.c
reduce.o:       header.h reduce.c
setup.o:        header.h setup.c
setup1805.o:    header.h setup1805.c
showerror.o:    header.h showerror.c
tokenize.o:     header.h tokenize.c
undef.o:        header.h undef.c

