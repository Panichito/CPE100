# This makefile is intended to build the two test programs for
# CPE100 Project2 Thai Hotel Database System
# makefile
#
# Note that this makefile assumes a Linux environment. The executables
# have no extension.
#
# Panithi Suwanno 63070503426 (Big) 15 NOV 2020
#  

EXECUTABLES=userinterface

all : $(EXECUTABLES)

datefunctions.o : datefunctions.c datefunctions.h
	gcc -c datefunctions.c

validatefunctions.o : validatefunctions.c datefunctions.h validatefunctions.h
	gcc -c validatefunctions.c

hotelfunctions.o : hotelfunctions.c validatefunctions.h hotelfunctions.h
	gcc -c hotelfunctions.c

userinterface.o : userinterface.c hotelfunctions.h
	gcc -c userinterface.c

userinterface : userinterface.o hotelfunctions.o validatefunctions.o datefunctions.o
	gcc -o userinterface userinterface.o hotelfunctions.o validatefunctions.o datefunctions.o

clean : 
	-rm *.o
	-rm datefunctions
	-rm validatefunctions
	-rm hotelfunctions
	-rm userinterface
