/* 
** Copyright (C) 2008-2010 Dirk-Jan C. Binnema <djcb@djcbsoftware.nl>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
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

#ifndef __MU_MSG_STATUS_H__
#define __MU_MSG_STATUS_H__

/* what kind of message is this; use by the indexer */
enum _MuMsgStatus {
	MU_MSG_STATUS_NEW,	  /* message is new */
	MU_MSG_STATUS_UPDATE,	  /* message is to be updated */
	MU_MSG_STATUS_CLEANUP,	  /* message is to be cleaned up from db */
	MU_MSG_STATUS_CLEANED_UP, /* message has been cleaned up from db */
	MU_MSG_STATUS_EXISTS,	  /* message exists (will not be cleaned up) */
	MU_MSG_STATUS_UPTODATE	  /* message is up-to-date */
};
typedef enum _MuMsgStatus MuMsgStatus;

#endif /*__MU_MSG_STATUS_H__*/