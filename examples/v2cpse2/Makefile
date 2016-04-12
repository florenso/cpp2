#############################################################################
# 
# Makefile for bmptk v2cpse1 examples 
#
# (c) Wouter van Ooijen (www.voti.nl) 2012, 2013
# 
#############################################################################

SUBDIRS += hello lines subframes decorators tee week1-make

BUILDDIRS = $(SUBDIRS:%=build-%)
CLEANDIRS = $(SUBDIRS:%=clean-%)

.phony: clean build $(BUILDDIRS) $(CLEANDIRS)

build: $(BUILDDIRS)
$(BUILDDIRS):
		make -C $(@:build-%=%) build

clean: $(CLEANDIRS)
$(CLEANDIRS):
		make -C $(@:clean-%=%) clean

