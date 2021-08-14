


src := $(wildcard *.c)

FILES = $(src)

all: test.map

test1: test?.c
	echo $?
test2: [t]*
	echo $?
test3: *.c
	echo $?
test4: ~
	echo $?
	@echo $(src)  
test.map: test1.c test2.c test3.c
	echo $@     
	echo $<
	echo $?
	echo $^
# @command --> not show command on the commandline
# $@ target file name
# $< first dependentcy
# $? newer dependentcy than target
# $^ all dependentcy than target
test:
	for file in $(FILES); do \
		echo $$file; \
	done
clean:
	rm *.o

#PHONY targets are used when target should not be file
.PHONY: install update clean2

install: clean2
	echo "install..."
update:
	echo "update...."
clean2:
	echo "clean2..."
	
# Single $  variable for make file double $$ variable for shell
# make -n  just print command, not execute
# make -s  just print command and remove echo, not execute
# MAKEFLAGS variable is used to pass the options to sub-make