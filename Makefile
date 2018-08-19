all: hostip

hostip: hostip.c
	gcc -Wall -Werror -Os -o $@ $<
	strip $@

.PHONY: all
