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

#ifndef __MU_QUERY_H__
#define __MU_QUERY_H__

#include <glib.h>
#include "mu-msg-iter.h"

G_BEGIN_DECLS

struct _MuQuery;
typedef struct _MuQuery MuQuery;

/**
 * create a new MuQuery instance. 
 * 
 * @param path path to the xapian db to search
 * @param err receives error information (if there is any)
 *
 * @return a new MuQuery instance, or NULL in case of error.
 * when the instance is no longer needed, use mu_query_destroy
 * to free it
 */
MuQuery  *mu_query_new  (const char* path) G_GNUC_WARN_UNUSED_RESULT;

/**
 * destroy the MuQuery instance
 * 
 * @param self a MuQuery instance, or NULL
 */
void mu_query_destroy  (MuQuery *self);


/**
 * get a version string for the database
 * 
 * @param store a valid MuQuery
 * 
 * @return the version string (free with g_free), or NULL in case of error
 */
char* mu_query_version (MuQuery *store) G_GNUC_WARN_UNUSED_RESULT;

/**
 * run a Xapian query; for the syntax, please refer to the mu-find
 * manpage, or http://xapian.org/docs/queryparser.html
 * 
 * @param self a valid MuQuery instance
 * @param expr the search expression
 * @param sortfield the field to sort by
 * @param ascending if TRUE sort in ascending (A-Z) order, otherwise,
 * sort in descending (Z-A) order
 * @param batchsize the size of batches to receive; this is mainly for
 * reasons - it's best to get the size one wants to show the user at once.
 * If you pass '0' as the batchsize, mu will use the maximum size (the count
 * of documents in the database)
 *
 * @return a MuMsgIter instance you can iterate over, or NULL in
 * case of error
 */
MuMsgIter* mu_query_run (MuQuery *self, 
				const char* expr,
				const MuMsgField* sortfield,
				gboolean ascending,
				size_t batchsize) G_GNUC_WARN_UNUSED_RESULT;

/**
 * get a string representation of the Xapian search query
 * 
 * @param self a MuQuery instance 
 * @param searchexpr a xapian search expression
 * 
 * @return the string representation of the xapian query, or NULL in case of
 * error; free the returned value with g_free
 */
char* mu_query_as_string (MuQuery *self,
			  const char* searchexpr) G_GNUC_WARN_UNUSED_RESULT;


G_END_DECLS

#endif /*__MU_QUERY_H__*/