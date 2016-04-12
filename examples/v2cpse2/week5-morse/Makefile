#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2013
# 
#############################################################################

# Specify the project name, this is also the main .cpp file to compile
PROJECT    := main

# Specify target chip or board or system
TARGET     := db103

# Specify the location of the bmptk library
BMPTK      := ../../..

# Specify project files (other than $(PROJECT).cpp) (if any)
OBJECTS    := 
SOURCES    := switch_to.asm pRTOS.cpp
HEADERS    := switch_to.h pRTOS.h
LIBRARIES  := 
SEARCH     := 

# specify (extra) results you want to get (if any)
RESULTS    := 

# The Makefile.inc does all the work
include $(BMPTK)/Makefile.inc
