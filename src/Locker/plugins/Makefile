TARGETS	= $(OBJDIR)panel.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W -fPIC
CFLAGS	= -Wall -g -O2 -pedantic
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

panel_OBJS = $(OBJDIR)panel.o
panel_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS) `pkg-config --cflags Panel`
panel_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) `pkg-config --libs Panel`

$(OBJDIR)panel.so: $(panel_OBJS)
	$(CCSHARED) -o $(OBJDIR)panel.so $(panel_OBJS) $(panel_LDFLAGS)

$(OBJDIR)panel.o: panel.c
	$(CC) $(panel_CFLAGS) -o $(OBJDIR)panel.o -c panel.c

clean:
	$(RM) -- $(panel_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)/Locker/plugins
	$(INSTALL) -m 0755 $(OBJDIR)panel.so $(DESTDIR)$(LIBDIR)/Locker/plugins/panel.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/Locker/plugins/panel.so

.PHONY: all clean distclean install uninstall
