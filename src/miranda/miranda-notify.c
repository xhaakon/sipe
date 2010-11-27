/**
 * @file miranda.c
 *
 * pidgin-sipe
 *
 * Copyright (C) 2010 SIPE Project <http://sipe.sourceforge.net/>
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

#include <windows.h>
#include <stdio.h>

#include <glib.h>

#include "newpluginapi.h"
#include "m_protosvc.h"
#include "m_protoint.h"

#include "sipe-backend.h"
#include "sipe-core.h"
#include "miranda-private.h"

void sipe_backend_notify_message_error(struct sipe_core_public *sipe_public,
				       struct sipe_backend_chat_session *backend_session,
				       const gchar *who,
				       const gchar *message)
{
	_NIF();
}

void sipe_backend_notify_message_info(struct sipe_core_public *sipe_public,
				      struct sipe_backend_chat_session *backend_session,
				      const gchar *who,
				      const gchar *message)
{
	_NIF();
}

void sipe_backend_notify_error(const gchar *title, const gchar *msg)
{
	_NIF();
}

/*
  Local Variables:
  mode: c
  c-file-style: "bsd"
  indent-tabs-mode: t
  tab-width: 8
  End:
*/