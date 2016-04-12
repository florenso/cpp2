#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2013
# 
#############################################################################

# Specify the location of the bmptk library
BMPTK      := ../../..

# Specify target chip or board or system, default is nds
TARGET     := win

# Specify the project name, the default is main (.cpp, .c, or .asm)
# this is also the main .cpp file to compile
# the default is main.cpp (or main.c, or main.asm)
PROJECT    := 

# Specify project-specific files (other than the main, if any)
OBJECTS    := 
SOURCES    := graphics.cpp font.cpp
HEADERS    := graphics.hpp font.hpp output.hpp
LIBRARIES  := 
SEARCH     := ../libraries/graphics

# specify (extra) results you want to get (if any)
RESULTS    := 

.PHONY: one two

one: 
	cp lines1.txt lines.txt
	
two: 
	cp lines2.txt lines.txt
	
output.hpp: lines.txt
		lines2header lines.txt output.hpp

# The Makefile.inc does all the work
include $(BMPTK)/Makefile.inc
