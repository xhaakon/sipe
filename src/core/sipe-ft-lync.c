/**
 * @file sipe-ft.c
 *
 * pidgin-sipe
 *
 * Copyright (C) 2014 SIPE Project <http://sipe.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <glib.h>

#include "sipe-ft-lync.h"

#include "sipe-common.h"
#include "sipe-media.h"

void sipe_ft_lync_init_incoming(struct sipe_core_private *sipe_private,
				struct sipmsg *msg,
				struct sipe_lync_filetransfer_data *ft_data) {
	process_incoming_invite_call(sipe_private, msg);
	// TODO: Use filename and size, connect to libpurple data read methods

	g_free(ft_data->file_name);
	g_free(ft_data->sdp);
	g_free(ft_data->id);
	g_free(ft_data);
}

/*
  Local Variables:
  mode: c
  c-file-style: "bsd"
  indent-tabs-mode: t
  tab-width: 8
  End:
*/
