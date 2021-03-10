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

dateFunctions.o : dateFunctions.c dateFunctions.h
	gcc -c dateFunctions.c

validateFunctions.o : validateFunctions.c dateFunctions.h validateFunctions.h
	gcc -c validateFunctions.c

HotelFunctions.o : HotelFunctions.c validateFunctions.h HotelFunctions.h
	gcc -c HotelFunctions.c

UserInterface.o : UserInterface.c HotelFunctions.h
	gcc -c UserInterface.c

UserInterface : UserInterface.o HotelFunctions.o validateFunctions.o dateFunctions.o
	gcc -o UserInterface UserInterface.o HotelFunctions.o validateFunctions.o dateFunctions.o

clean : 
	-rm *.o
	-rm dateFunctions
	-rm validateFunctions
	-rm HotelFunctions
	-rm UserInterface
