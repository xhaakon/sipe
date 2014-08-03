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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <glib.h>

#include "sipe-ft-lync.h"

#include "sipmsg.h"
#include "sip-transport.h"
#include "sipe-common.h"
#include "sipe-media.h"
#include "sipe-session.h"
#include "sipe-utils.h"

static gboolean
request_download_file(struct sipe_lync_filetransfer_data *ft_data)
{
	gchar *body;

	static const gchar *SUCCESS_RESPONSE =
		"<response xmlns=\"http://schemas.microsoft.com/rtc/2009/05/filetransfer\" requestId=\"%d\" code=\"success\"/>";

	static const gchar *DOWNLOAD_FILE_REQUEST =
		"<request xmlns=\"http://schemas.microsoft.com/rtc/2009/05/filetransfer\" requestId=\"%d\">"
			"<downloadFile>"
				"<fileInfo>"
					"<id>%s</id>"
					"<name>%s</name>"
				"</fileInfo>"
			"</downloadFile>"
		"</request>";

	body = g_strdup_printf(SUCCESS_RESPONSE, ft_data->request_id);

	sip_transport_info(ft_data->sipe_private,
			   "Content-Type: application/ms-filetransfer+xml\r\n",
			   body,
			   ft_data->dialog,
			   NULL);

	g_free(body);

	body = g_strdup_printf(DOWNLOAD_FILE_REQUEST,
			       ft_data->request_id + 1,
			       ft_data->id,
			       ft_data->file_name);

	sip_transport_info(ft_data->sipe_private,
			   "Content-Type: application/ms-filetransfer+xml\r\n",
			   body,
			   ft_data->dialog,
			   NULL);

	g_free(body);

	g_free(ft_data->file_name);
	g_free(ft_data->sdp);
	g_free(ft_data->id);
	g_free(ft_data);

	return FALSE;
}

void sipe_ft_lync_init_incoming(struct sipe_core_private *sipe_private,
				struct sipmsg *msg,
				struct sipe_lync_filetransfer_data *ft_data) {
	gchar *from = parse_from(sipmsg_find_header(msg, "From"));
	struct sip_session *session = NULL;

	process_incoming_invite_call(sipe_private, msg);
	// TODO: Use filename and size, connect to libpurple data read methods

	session = sipe_session_find_call(sipe_private, from);
	ft_data->dialog = session->dialogs->data;
	ft_data->sipe_private = sipe_private;

	g_free(from);

	g_timeout_add_seconds(10, (GSourceFunc)request_download_file, (gpointer)ft_data);
}

/*
  Local Variables:
  mode: c
  c-file-style: "bsd"
  indent-tabs-mode: t
  tab-width: 8
  End:
*/
