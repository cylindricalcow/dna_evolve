EXENAME = evolve
EX_1 = dna
EX_2 = energy
EX_3 = phase

OBJS = dna.o energy.o phase_transition.o
OBJS_1 = dna.o 
OBJS_2 = dna.o energy.o
OBJS_3 = dna.o phase_transition.o

CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : $(EXENAME)

dna : $(EX_1)

energy : $(EX_2)

phase_transition : $(EX_3)

$(EXENAME) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXENAME)

$(EX_1) : $(OBJS_1)
	$(CC) $(LFLAGS) $(OBJS_1) -o $(EX_1)

$(EX_2) : $(OBJS_2)
	$(CC) $(LFLAGS) $(OBJS_2) -o $(EX_2)

$(EX_3) : $(OBJS_3)
	$(CC) $(LFLAGS) $(OBJS_3) -o $(EX_3)

dna.o : dna.cc dna.h
	$(CC) $(CFLAGS) dna.cc
energy.o : energy.cc dna.cc dna.h
	$(CC) $(CFLAGS) energy.cc
phase_transition.o : phase_transition.cc dna.cc dna.h
	$(CC) $(CFLAGS) phase_transition.cc
clean:
	-rm -f *.o $(EXENAME)

