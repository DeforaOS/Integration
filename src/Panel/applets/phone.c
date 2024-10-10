/* $Id$ */
/* Copyright (c) 2011-2020 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Desktop Integration */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <System.h>
#include <Desktop.h>
#if defined(GDK_WINDOWING_X11)
# if GTK_CHECK_VERSION(3, 0, 0)
#  include <gtk/gtkx.h>
# else
#  include <gdk/gdkx.h>
# endif
#endif
#include <Desktop/Panel/applet.h>
#include <Desktop/Phone/phone.h>

#define N_(string) string


/* PhoneApplet */
/* private */
/* types */
typedef struct _PanelApplet
{
	PanelAppletHelper * helper;
#if defined(GDK_WINDOWING_X11)
	GtkWidget * widget;
	gulong source;
#endif
} PhoneApplet;


/* prototypes */
static PhoneApplet * _phone_init(PanelAppletHelper * helper,
		GtkWidget ** widget);
static void _phone_destroy(PhoneApplet * phone);

#if defined(GDK_WINDOWING_X11)
static void _phone_embed(GtkWidget * widget, unsigned long window);

/* callbacks */
static int _phone_on_message(void * data, uint32_t value1, uint32_t value2,
		uint32_t value3);
static void _phone_on_plug_added(GtkWidget * widget);
static gboolean _phone_on_plug_removed(GtkWidget * widget);
static void _phone_on_screen_changed(GtkWidget * widget, GdkScreen * previous);
#endif


/* public */
/* variables */
PanelAppletDefinition applet =
{
	N_("Phone"),
	"phone-dialer",
	NULL,
	_phone_init,
	_phone_destroy,
	NULL,
	FALSE,
	TRUE
};


/* private */
/* functions */
/* PhoneApplet */
/* phone_init */
static PhoneApplet * _phone_init(PanelAppletHelper * helper,
		GtkWidget ** widget)
{
#if defined(GDK_WINDOWING_X11)
	PhoneApplet * phone;

	if((phone = malloc(sizeof(*phone))) == NULL)
	{
		error_set("%s: %s", applet.name, strerror(errno));
		return NULL;
	}
	phone->helper = helper;
	phone->widget = gtk_socket_new();
	g_signal_connect(phone->widget, "plug-added", G_CALLBACK(
				_phone_on_plug_added), NULL);
	g_signal_connect(phone->widget, "plug-removed", G_CALLBACK(
				_phone_on_plug_removed), NULL);
	phone->source = g_signal_connect(phone->widget, "screen-changed",
			G_CALLBACK(_phone_on_screen_changed), NULL);
	*widget = phone->widget;
	return phone;
#else
	(void) helper;
	(void) widget;

	error_set_code(-ENOSYS, "%s", "X11 support not detected");
	return NULL;
#endif
}


/* phone_destroy */
static void _phone_destroy(PhoneApplet * phone)
{
#if defined(GDK_WINDOWING_X11)
	if(phone->source != 0)
		g_signal_handler_disconnect(phone->widget, phone->source);
	phone->source = 0;
	desktop_message_unregister(NULL, _phone_on_message, phone->widget);
	gtk_widget_destroy(phone->widget);
	free(phone);
#else
	(void) phone;
#endif
}


#if defined(GDK_WINDOWING_X11)
/* phone_embed */
static void _phone_embed(GtkWidget * widget, unsigned long window)
{
	gtk_socket_add_id(GTK_SOCKET(widget), window);
}


/* callbacks */
/* phone_on_message */
static int _phone_on_message(void * data, uint32_t value1, uint32_t value2,
		uint32_t value3)
{
	GtkWidget * widget = data;
	(void) value2;
	(void) value3;

	_phone_embed(widget, value1);
	return 0;
}


/* phone_on_plug_added */
static void _phone_on_plug_added(GtkWidget * widget)
{
	gtk_widget_show(widget);
}


/* phone_on_plug_removed */
static gboolean _phone_on_plug_removed(GtkWidget * widget)
{
	gtk_widget_hide(widget);
	return TRUE;
}


/* phone_on_screen_changed */
static void _phone_on_screen_changed(GtkWidget * widget, GdkScreen * previous)
{
	if(previous != NULL)
		return;
	desktop_message_unregister(NULL, _phone_on_message, widget);
	desktop_message_register(NULL, PHONE_EMBED_MESSAGE, _phone_on_message,
			widget);
}
#endif
