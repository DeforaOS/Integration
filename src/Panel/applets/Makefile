TARGETS	= $(OBJDIR)keyboard.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W -fPIC `pkg-config --cflags Panel`
CFLAGS	= -Wall -g -O2 -pedantic
LDFLAGSF= `pkg-config --libs Panel`
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

keyboard_OBJS = $(OBJDIR)keyboard.o
keyboard_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
keyboard_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)keyboard.so: $(keyboard_OBJS)
	$(CCSHARED) -o $(OBJDIR)keyboard.so $(keyboard_OBJS) $(keyboard_LDFLAGS)

$(OBJDIR)keyboard.o: keyboard.c
	$(CC) $(keyboard_CFLAGS) -o $(OBJDIR)keyboard.o -c keyboard.c

clean:
	$(RM) -- $(keyboard_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)/Panel/applets
	$(INSTALL) -m 0755 $(OBJDIR)keyboard.so $(DESTDIR)$(LIBDIR)/Panel/applets/keyboard.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/Panel/applets/keyboard.so

.PHONY: all clean distclean install uninstall
