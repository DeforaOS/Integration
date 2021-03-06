/* $Id$ */
/* Copyright (c) 2013-2020 Pierre Pronchery <khorben@defora.org> */
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



#include <libintl.h>
#include <System.h>
#include <Desktop.h>
#include <Desktop/Player.h>
#include <Desktop/Panel/applet.h>
#define _(string) gettext(string)


/* Player */
/* private */
/* types */
typedef struct _PanelApplet
{
	PanelAppletHelper * helper;
	GtkWidget * widget;
} Player;


/* prototypes */
static Player * _player_init(PanelAppletHelper * helper,
		GtkWidget ** widget);
static void _player_destroy(Player * player);

/* callbacks */
static void _player_on_forward(void);
static void _player_on_next(void);
static void _player_on_pause(void);
static void _player_on_play(void);
static void _player_on_previous(void);
static void _player_on_rewind(void);
static void _player_on_stop(void);


/* public */
/* variables */
PanelAppletDefinition applet =
{
	"Player",
	"multimedia",
	NULL,
	_player_init,
	_player_destroy,
	NULL,
	FALSE,
	TRUE
};


/* private */
/* functions */
/* player_init */
static void _init_add(GtkWidget * box, char const * stock, GtkIconSize iconsize,
		char const * tooltip, GCallback callback);

static Player * _player_init(PanelAppletHelper * helper, GtkWidget ** widget)
{
	Player * player;
	GtkOrientation orientation;
	GtkIconSize iconsize;

	if((player = object_new(sizeof(*player))) == NULL)
		return NULL;
	player->helper = helper;
	orientation = panel_window_get_orientation(helper->window);
#if GTK_CHECK_VERSION(3, 0, 0)
	player->widget = gtk_box_new(orientation, 0);
#else
	player->widget = (orientation == GTK_ORIENTATION_HORIZONTAL)
		? gtk_hbox_new(FALSE, 0) : gtk_vbox_new(FALSE, 0);
#endif
	iconsize = panel_window_get_icon_size(helper->window);
	_init_add(player->widget, GTK_STOCK_MEDIA_PREVIOUS, iconsize,
			_("Previous"), _player_on_previous);
	_init_add(player->widget, GTK_STOCK_MEDIA_REWIND, iconsize, _("Rewind"),
			_player_on_rewind);
	_init_add(player->widget, GTK_STOCK_MEDIA_PLAY, iconsize, _("Play"),
			_player_on_play);
	_init_add(player->widget, GTK_STOCK_MEDIA_PAUSE, iconsize, _("Pause"),
			_player_on_pause);
	_init_add(player->widget, GTK_STOCK_MEDIA_STOP, iconsize, _("Stop"),
			_player_on_stop);
	_init_add(player->widget, GTK_STOCK_MEDIA_FORWARD, iconsize,
			_("Forward"), _player_on_forward);
	_init_add(player->widget, GTK_STOCK_MEDIA_NEXT, iconsize, _("Next"),
			_player_on_next);
	gtk_widget_show_all(player->widget);
	*widget = player->widget;
	return player;
}

static void _init_add(GtkWidget * box, char const * stock, GtkIconSize iconsize,
		char const * tooltip, GCallback callback)
{
	GtkWidget * button;
	GtkWidget * image;

	button = gtk_button_new();
	image = gtk_image_new_from_stock(stock, iconsize);
	gtk_button_set_image(GTK_BUTTON(button), image);
	gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
#if GTK_CHECK_VERSION(2, 12, 0)
	gtk_widget_set_tooltip_text(button, tooltip);
#endif
	g_signal_connect(button, "clicked", callback, NULL);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, TRUE, 0);
}


/* player_destroy */
static void _player_destroy(Player * player)
{
	gtk_widget_destroy(player->widget);
	object_delete(player);
}


/* callbacks */
/* player_on_forward */
static void _player_on_forward(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_FORWARD, 0,
			0);
}


/* player_on_next */
static void _player_on_next(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_NEXT, 0, 0);
}


/* player_on_pause */
static void _player_on_pause(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_PAUSE, 0, 0);
}


/* player_on_play */
static void _player_on_play(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_PLAY, 0, 0);
}


/* player_on_previous */
static void _player_on_previous(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_PREVIOUS, 0,
			0);
}


/* player_on_rewind */
static void _player_on_rewind(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_REWIND, 0,
			0);
}


/* player_on_stop */
static void _player_on_stop(void)
{
	desktop_message_send(PLAYER_CLIENT_MESSAGE, PLAYER_MESSAGE_STOP, 0, 0);
}
