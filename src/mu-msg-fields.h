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

#ifndef __MU_MSG_FIELDS_H__
#define __MU_MSG_FIELDS_H__

#include <glib.h>

G_BEGIN_DECLS

/* don't change the order, add new types at the end, as these numbers
 * are used in the database */
enum _MuMsgFieldId {	
 	MU_MSG_FIELD_ID_BODY_TEXT   = 0,
	MU_MSG_FIELD_ID_BODY_HTML,
	MU_MSG_FIELD_ID_CC,
	MU_MSG_FIELD_ID_DATE,
	MU_MSG_FIELD_ID_FLAGS,
	MU_MSG_FIELD_ID_FROM,
	MU_MSG_FIELD_ID_PATH,
	MU_MSG_FIELD_ID_MAILDIR, 
	MU_MSG_FIELD_ID_PRIO,
	MU_MSG_FIELD_ID_SIZE,
	MU_MSG_FIELD_ID_SUBJECT,
	MU_MSG_FIELD_ID_TO,
	MU_MSG_FIELD_ID_MSGID,
	MU_MSG_FIELD_ID_TIMESTAMP,

	MU_MSG_FIELD_ID_NUM
};

static const guint MU_MSG_FIELD_ID_NONE = (guint)-1; 
typedef guint MuMsgFieldId;

#define mu_msg_field_id_is_valid(MFID) \
	((MFID) < MU_MSG_FIELD_ID_NUM)



/* don't change the order, add new types at the end (before _NUM)*/
enum _MuMsgFieldType {
	MU_MSG_FIELD_TYPE_STRING,

	MU_MSG_FIELD_TYPE_BYTESIZE, 
	MU_MSG_FIELD_TYPE_TIME_T,
	MU_MSG_FIELD_TYPE_INT,

	MU_MSG_FIELD_TYPE_NUM
};
typedef enum _MuMsgFieldType MuMsgFieldType;
static const guint MU_MSG_FIELD_TYPE_NONE = (guint)-1;



typedef void (*MuMsgFieldForEachFunc) (MuMsgFieldId id,
				       gconstpointer data);

/**
 * iterator over all possible message fields
 * 
 * @param func a function called for each field
 * @param data a user data pointer passed the callback function
 */
void mu_msg_field_foreach (MuMsgFieldForEachFunc func, gconstpointer data);


/**
 * get the name of the field -- this a name that can be use in queries,
 * ie. 'subject:foo', with 'subject' being the name
 * 
 * @param id a MuMsgFieldId
 *  
 * @return the name of the field as a constant string, or
 * NULL if the field is unknown
 */
const char*  mu_msg_field_name (MuMsgFieldId id) G_GNUC_PURE;

/**
 * get the shortcut of the field -- this a shortcut that can be use in
 * queries, ie. 's:foo', with 's' meaning 'subject' being the name
 * 
 * @param id a MuMsgFieldId
 * 
 * @return the shortcut character, or 0 if the field is unknown
 */
char mu_msg_field_shortcut (MuMsgFieldId id) G_GNUC_PURE;

/**
 * get the xapian prefix of the field -- that is, the prefix used in
 * the Xapian database to identify the field
 * 
 * @param id a MuMsgFieldId
 * 
 * @return the xapian prefix char or 0 if the field is unknown
 */
char  mu_msg_field_xapian_prefix (MuMsgFieldId id) G_GNUC_PURE;


/**
 * get the type of the field (string, size, time etc.)
 * 
 * @param field a MuMsgField
 * 
 * @return the type of the field (a #MuMsgFieldType), or
 * MU_MSG_FIELD_TYPE_NONE if it is not found
 */
MuMsgFieldType mu_msg_field_type (MuMsgFieldId id) G_GNUC_PURE;


/**
 * is the field numeric (has type MU_MSG_FIELD_TYPE_(BYTESIZE|TIME_T|INT))?
 * 
 * @param id a MuMsgFieldId
 * 
 * @return TRUE if the field is numeric, FALSE otherwise
 */
gboolean mu_msg_field_is_numeric (MuMsgFieldId id) G_GNUC_PURE;


/**
 * is the field Xapian-indexable? That is, should this field be
 * indexed in the in the Xapian database, so we can use the all the
 * phrasing, stemming etc. magic
 * 
 * @param id a MuMsgFieldId
 * 
 * @return TRUE if the field is Xapian-enabled, FALSE otherwise
 */
gboolean mu_msg_field_xapian_index (MuMsgFieldId id) G_GNUC_PURE;

/**
 * should this field be stored as a xapian term?
 * 
 * @param id a MuMsgFieldId 
 * 
 * @return TRUE if the field is Xapian-enabled, FALSE otherwise
 */
gboolean mu_msg_field_xapian_term (MuMsgFieldId id) G_GNUC_PURE;

/**
 * should this field be stored as a xapian value?
 * 
 * @param field a MuMsgField
 * 
 * @return TRUE if the field is Xapian-enabled, FALSE otherwise
 */
gboolean mu_msg_field_xapian_value (MuMsgFieldId id) G_GNUC_PURE;

/**
 * should this field be stored as contact information? This means that
 * e-mail address will be stored as terms, and names will be indexed
 * 
 * @param id a MuMsgFieldId
 * 
 * @return TRUE if the field should be stored as contact information,
 * FALSE otherwise
 */
gboolean mu_msg_field_xapian_contact (MuMsgFieldId id) G_GNUC_PURE;

/**
 * is the field gmime-enabled? That is, can be field be retrieved
 * using GMime?
 * 
 * @param id a MuMsgFieldId
 * 
 * @return TRUE if the field is Gmime-enabled, FALSE otherwise
 */
gboolean mu_msg_field_gmime (MuMsgFieldId id) G_GNUC_PURE;


/**
 * get the corresponding MuMsgField for a name (as in mu_msg_field_name)
 * 
 * @param str a name
 * @param err, if TRUE, when the shortcut is not found, will issue a
 * g_critical warning
 * 
 * @return a MuMsgField, or NULL if it could not be found
 */
MuMsgFieldId mu_msg_field_id_from_name (const char* str,
					gboolean err)  G_GNUC_PURE;


/**
 * get the corresponding MuMsgField for a shortcut (as in mu_msg_field_shortcut)
 * 
 * @param kar a shortcut character
 * @param err, if TRUE, when the shortcut is not found, will issue a
 * g_critical warning
 * 
 * @return a MuMsgField, or NULL if it could not be found
 */
MuMsgFieldId  mu_msg_field_id_from_shortcut (char kar,
					     gboolean err) G_GNUC_PURE;


G_END_DECLS

#endif /*__MU_MSG_FIELDS_H__*/
