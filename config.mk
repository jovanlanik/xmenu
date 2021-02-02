# program name
PROG = xmenu

# paths
PREFIX    ?= /usr
MANPREFIX ?= ${PREFIX}/share/man

# SHELL variable (mainly for non-GNU make)
SHELL ?= /bin/sh

# includes and libs
LIBS := -lfontconfig -lXft -lX11 -lXinerama -lImlib2

# flags
CFLAGS   += -I /usr/include/freetype2 -Wall -Wextra
LDFLAGS  += ${LIBS}

# compiler and linker
CC ?= cc
