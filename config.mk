# program name
PROG = xmenu

# paths
PREFIX    ?= /usr
MANPREFIX ?= $(PREFIX)/share/man

# includes and libs
LIBS := -lfontconfig -lXft -lX11 -lXinerama -lImlib2 -lconfig

# flags
CFLAGS   += -I /usr/include/freetype2 -Wall -Wextra -DNAME=$(PROG)
LDFLAGS  += $(LIBS)

# compiler and linker
CC ?= gcc
