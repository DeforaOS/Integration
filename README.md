DeforaOS Integration
====================

About Integration
-----------------

Integration gathers additions and plug-ins to different projects of the
DeforaOS desktop, which would otherwise create circular dependencies, or bring
too many optional dependencies.

Compiling Integration
---------------------

Integration depends on the following components:

 * Gtk+ 2.4 or newer, or Gtk+ 3.0 or newer
 * DeforaOS libDesktop
 * an implementation of `make`
 * DeforaOS Locker
 * DeforaOS Panel
 * DeforaOS Phone
 * DeforaOS Surfer
 * libpurple
 * Pulseaudio
 * sofia-sip

Optionally, for the DeforaOS desktop session file:

 * DeforaOS Desktop
 * Optionally, the GNOME icon theme for Gtk+
 * Optionally, the Metacity window manager

With the corresponding dependencies installed, the following command should be
enough to compile and install Integration on most systems:

    $ make install

To install (or package) Integration in a different location, use the `PREFIX`
option as follows:

    $ make PREFIX="/another/prefix" install

Integration also supports `DESTDIR`, to be installed in a staging directory;
for instance:

    $ make DESTDIR="/staging/directory" PREFIX="/another/prefix" install

The compilation process supports a number of other options, such as OBJDIR for
compilation outside of the source tree for instance.

On some systems, the Makefiles shipped may have to be re-generated accordingly.
This can be performed with the DeforaOS configure tool.

Features included
-----------------

For DeforaOS Locker:

 * Integration with DeforaOS Panel, to automatically show and hide the panels
   if necessary

For DeforaOS Panel:

 * Pop-up applet for the DeforaOS Keyboard virtual keyboard
 * Information display for DeforaOS Phone (operator, reception...)
 * Remote control for the DeforaOS Player media player

For DeforaOS Phone:

 * libpurple modem backend for Instant Messaging capability (experimental)
 * SIP modem backend for VoIP communication (experimental)
 * Integration with the DeforaOS Locker screensaver for power management
 * Integration with the DeforaOS Panel for notifications
 * Audio output through Pulseaudio

For DeforaOS Surfer:

 * Calculator application from a stand-alone HTML file
 * Stopwatch application from a stand-alone HTML file

Distributing Integration
------------------------

Plug-ins for DeforaOS desktop components are subject to the corresponding
licensing terms; please refer to their respective source code files.

Additions specific to DeforaOS Integration are subject to the terms of the
2-clause BSD license; please see the `COPYING` file for more information.
