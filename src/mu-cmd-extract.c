/*
** Copyright (C) 2008-2010 Dirk-Jan C. Binnema <djcb@djcbsoftware.nl>
**
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License as published by the
** Free Software Foundation; either version 3, or (at your option) any
** later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software Foundation,
** Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
**
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /*HAVE_CONFIG_H*/

#include <stdlib.h>

#include "mu-msg.h"
#include "mu-msg-part.h"
#include "mu-msg-str.h"
#include "mu-cmd.h"

static gboolean
save_part (const char* path, unsigned idx)
{
	MuMsg* msg;
	
	msg = mu_msg_new (path, NULL);
	if (!msg)
		return FALSE;
	
	mu_msg_mime_part_save (msg, idx, NULL, TRUE); /* FIXME */
	
	mu_msg_destroy (msg);
	
	return TRUE;
}



static void
each_part (MuMsgPart *part, gpointer user_data)
{
	g_print ("%u %s %s/%s [%s]\n",
		 part->index,
		 part->file_name ? part->file_name : "<none>",
		 part->type ? part->type : "",
		 part->subtype ? part->subtype : "",
		 part->disposition ? part->disposition : "<none>");
}


static gboolean
show_parts (const char* path)
{
	MuMsg* msg;
	
	msg = mu_msg_new (path, NULL);
	if (!msg)
		return FALSE;

	mu_msg_msg_part_foreach (msg, each_part, NULL);

	mu_msg_destroy (msg);
	
	return TRUE;
	
}

gboolean
mu_cmd_extract (MuConfigOptions *opts)
{
	gboolean rv;
	
	g_return_val_if_fail (opts, FALSE);

	/* note: params[0] will be 'view' */
	if (!opts->params[0] || !opts->params[1]) {
		g_warning ("missing mail file to extract something from");
		return FALSE;
	}
	mu_msg_init();

	rv = TRUE;
	if (!opts->params[2]) /* no explicit part, show, don't save */
		rv = show_parts (opts->params[1]);
	else {
		int i;
		for (i = 2; opts->params[i]; ++i) {
			unsigned idx = atoi (opts->params[i]);
			if (idx == 0) {
				g_warning ("not a valid index: %s", opts->params[i]);
				rv = FALSE;
				break;
			}
			if (!save_part (opts->params[1], idx)) {
				g_warning ("failed to save part %d of %s", idx,
					    opts->params[1]);
				rv = FALSE;
				break;
			}
		}
	}

	mu_msg_uninit();
	
	return rv;
}
