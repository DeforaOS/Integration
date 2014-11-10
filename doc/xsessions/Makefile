OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
MKDIR	= mkdir -m 0755 -p
INSTALL	= install
RM	= rm -f


all:

clean:

distclean: clean

install:
	$(MKDIR) $(DESTDIR)$(PREFIX)/share/xsessions
	$(INSTALL) -m 0644 DeforaOS.desktop $(DESTDIR)$(PREFIX)/share/xsessions/DeforaOS.desktop

uninstall:
	$(RM) -- $(DESTDIR)$(PREFIX)/share/xsessions/DeforaOS.desktop

.PHONY: all clean distclean install uninstall
