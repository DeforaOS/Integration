TARGETS	= $(OBJDIR)notify.so $(OBJDIR)pulseaudio.so
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W `pkg-config --cflags libDesktop`
CFLAGS	= -Wall -g -O2 -pedantic -fPIC
LDFLAGSF= `pkg-config --libs libDesktop`
AR	= ar
RANLIB	= ranlib
CCSHARED= $(CC) -shared
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

notify_OBJS = $(OBJDIR)notify.o
notify_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS) `pkg-config --cflags Panel`
notify_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)notify.so: $(notify_OBJS)
	$(CCSHARED) -o $(OBJDIR)notify.so $(notify_OBJS) $(notify_LDFLAGS)

pulseaudio_OBJS = $(OBJDIR)pulseaudio.o
pulseaudio_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS) `pkg-config --cflags libpulse`
pulseaudio_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) `pkg-config --libs libpulse`

$(OBJDIR)pulseaudio.so: $(pulseaudio_OBJS)
	$(CCSHARED) -o $(OBJDIR)pulseaudio.so $(pulseaudio_OBJS) $(pulseaudio_LDFLAGS)

$(OBJDIR)notify.o: notify.c
	$(CC) $(notify_CFLAGS) -o $(OBJDIR)notify.o -c notify.c

$(OBJDIR)pulseaudio.o: pulseaudio.c
	$(CC) $(pulseaudio_CFLAGS) -o $(OBJDIR)pulseaudio.o -c pulseaudio.c

clean:
	$(RM) -- $(notify_OBJS) $(pulseaudio_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(LIBDIR)/Phone/plugins
	$(INSTALL) -m 0644 $(OBJDIR)notify.so $(DESTDIR)$(LIBDIR)/Phone/plugins/notify.so
	$(MKDIR) $(DESTDIR)$(LIBDIR)/Phone/plugins
	$(INSTALL) -m 0644 $(OBJDIR)pulseaudio.so $(DESTDIR)$(LIBDIR)/Phone/plugins/pulseaudio.so

uninstall:
	$(RM) -- $(DESTDIR)$(LIBDIR)/Phone/plugins/notify.so
	$(RM) -- $(DESTDIR)$(LIBDIR)/Phone/plugins/pulseaudio.so

.PHONY: all clean distclean install uninstall
