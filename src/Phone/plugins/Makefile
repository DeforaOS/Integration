TARGETS	= $(OBJDIR)pulseaudio.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W `pkg-config --cflags libSystem gtk+-2.0`
CFLAGS	= -Wall -g -O2 -pedantic -fPIC
LDFLAGSF= `pkg-config --libs libSystem gtk+-2.0`
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

pulseaudio_OBJS = $(OBJDIR)pulseaudio.o
pulseaudio_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS) `pkg-config --cflags libpulse`
pulseaudio_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) `pkg-config --libs libpulse`

$(OBJDIR)pulseaudio.so: $(pulseaudio_OBJS)
	$(CCSHARED) -o $(OBJDIR)pulseaudio.so $(pulseaudio_OBJS) $(pulseaudio_LDFLAGS)

$(OBJDIR)pulseaudio.o: pulseaudio.c
	$(CC) $(pulseaudio_CFLAGS) -o $(OBJDIR)pulseaudio.o -c pulseaudio.c

clean:
	$(RM) -- $(pulseaudio_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)/Phone/plugins
	$(INSTALL) -m 0644 $(OBJDIR)pulseaudio.so $(DESTDIR)$(LIBDIR)/Phone/plugins/pulseaudio.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/Phone/plugins/pulseaudio.so

.PHONY: all clean distclean install uninstall
