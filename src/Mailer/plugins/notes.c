/* $Id$ */
/* Copyright (c) 2015-2024 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Desktop Notes */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include <stdlib.h>
#include <Desktop/Mailer/plugin.h>
#include <Desktop/Notes.h>


/* Notes */
/* private */
/* types */
typedef struct _MailerPlugin NotesPlugin;

struct _MailerPlugin
{
	MailerPluginHelper * helper;

	Notes * notes;

	/* widgets */
	GtkWidget * widget;
	GtkWidget * view;
};


/* protected */
/* prototypes */
/* plug-in */
static MailerPlugin * _notes_init(MailerPluginHelper * helper);
static void _notes_destroy(NotesPlugin * notes);
static GtkWidget * _notes_get_widget(NotesPlugin * notes);


/* public */
/* variables */
/* plug-in */
MailerPluginDefinition plugin =
{
	"Notes",
	"notes",
	NULL,
	_notes_init,
	_notes_destroy,
	_notes_get_widget,
	NULL
};


/* protected */
/* functions */
/* plug-in */
/* notes_init */
static MailerPlugin * _notes_init(MailerPluginHelper * helper)
{
	NotesPlugin * notes;
	GtkWidget * widget;
	GtkTreeViewColumn * column;
	size_t i;

	if((notes = malloc(sizeof(*notes))) == NULL)
		return NULL;
	if((notes->notes = notes_new(NULL, NULL)) == NULL)
	{
		_notes_destroy(notes);
		return NULL;
	}
	notes->helper = helper;
	notes->widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
	widget = notes_get_widget(notes->notes);
	gtk_box_pack_start(GTK_BOX(notes->widget), widget, TRUE, TRUE, 0);
	widget = notes_get_view(notes->notes);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(widget), FALSE);
	for(i = 0; i < ND_COL_COUNT; i++)
		if((column = notes_get_view_column(notes->notes, i)) == NULL)
			continue;
		else if(i != ND_COL_TITLE)
			gtk_tree_view_column_set_visible(column, FALSE);
	gtk_widget_show_all(notes->widget);
	return notes;
}


/* notes_destroy */
static void _notes_destroy(NotesPlugin * notes)
{
	if(notes->notes != NULL)
		notes_delete(notes->notes);
	free(notes);
}


/* notes_get_widget */
static GtkWidget * _notes_get_widget(NotesPlugin * notes)
{
	return notes->widget;
}
