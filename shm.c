/*
   +----------------------------------------------------------------------+
   | eAccelerator project                                                 |
   +----------------------------------------------------------------------+
   | Copyright (c) 2004 - 2005 eAccelerator                               |
   | http://eaccelerator.net                                  			  |
   +----------------------------------------------------------------------+
   | This program is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU General Public License          |
   | as published by the Free Software Foundation; either version 2       |
   | of the License, or (at your option) any later version.               |
   |                                                                      |
   | This program is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        |
   | GNU General Public License for more details.                         |
   |                                                                      |
   | You should have received a copy of the GNU General Public License    |
   | along with this program; if not, write to the Free Software          |
   | Foundation, Inc., 59 Temple Place - Suite 330, Boston,               |
   | MA  02111-1307, USA.                                                 |
   |                                                                      |
   | A copy is availble at http://www.gnu.org/copyleft/gpl.txt            |
   +----------------------------------------------------------------------+
   | Author(s): Dmitry Stogov <dstogov@users.sourceforge.net>             |
   +----------------------------------------------------------------------+
   $Id$
*/

#include "eaccelerator.h"
#include "eaccelerator_version.h"

#ifdef HAVE_EACCELERATOR
#ifdef WITH_EACCELERATOR_SHM

#include "cache.h"
#include "shm.h"

#include "zend.h"
#include "zend_API.h"
#include "zend_extensions.h"

/* where to cache the keys */
eaccelerator_cache_place eaccelerator_keys_cache_place =
	eaccelerator_shm_and_disk;

/* set the eaccelerator_keys_cache_place */
PHP_INI_MH (eaccelerator_OnUpdateKeysCachePlace)
{
	if (strncasecmp ("shm_and_disk", new_value, sizeof ("shm_and_disk")) == 0)
		eaccelerator_keys_cache_place = eaccelerator_shm_and_disk;

	else if (strncasecmp ("shm", new_value, sizeof ("shm")) == 0)
		eaccelerator_keys_cache_place = eaccelerator_shm;

	else if (strncasecmp ("shm_only", new_value, sizeof ("shm_only")) == 0)
		eaccelerator_keys_cache_place = eaccelerator_shm_only;

	else if (strncasecmp ("disk_only", new_value, sizeof ("disk_only")) == 0)
		eaccelerator_keys_cache_place = eaccelerator_disk_only;

	else if (strncasecmp ("none", new_value, sizeof ("none")) == 0)
		eaccelerator_keys_cache_place = eaccelerator_none;

	return SUCCESS;
}

/******************************************************************************/
/* PHP function entries														  */
/******************************************************************************/

PHP_FUNCTION (eaccelerator_lock)
{
	char *key;
	int key_len;

	if (zend_parse_parameters (ZEND_NUM_ARGS ()TSRMLS_CC, "s", &key, &key_len)
		== FAILURE)
		return;

	if (eaccelerator_lock (key, key_len TSRMLS_CC)) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}

PHP_FUNCTION (eaccelerator_unlock)
{
	char *key;
	int key_len;

	if (zend_parse_parameters (ZEND_NUM_ARGS ()TSRMLS_CC, "s", &key, &key_len)
		== FAILURE)
		return;

	if (eaccelerator_unlock (key, key_len TSRMLS_CC)) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}

PHP_FUNCTION (eaccelerator_put)
{
	char *key;
	int key_len;
	zval *val;
	time_t ttl = 0;
	long where = eaccelerator_keys_cache_place;

	if (zend_parse_parameters (ZEND_NUM_ARGS ()TSRMLS_CC, "sz|ll", &key, 
								&key_len, &val, &ttl, &where) == FAILURE)
		return;

	if (eaccelerator_put (key, key_len, val, ttl, where TSRMLS_CC)) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}

PHP_FUNCTION (eaccelerator_get)
{
	char *key;
	int key_len;
	long where = eaccelerator_keys_cache_place;

	if (zend_parse_parameters (ZEND_NUM_ARGS ()TSRMLS_CC,
							   "s|l", &key, &key_len, &where) == FAILURE)
		return;

	if (eaccelerator_get (key, key_len, return_value, where TSRMLS_CC)) {
		return;
	} else {
		RETURN_NULL ();
	}
}

PHP_FUNCTION (eaccelerator_rm)
{
	char *key;
	int key_len;
	long where = eaccelerator_keys_cache_place;

	if (zend_parse_parameters (ZEND_NUM_ARGS ()TSRMLS_CC,
							   "s|l", &key, &key_len, &where) == FAILURE)
		return;

	if (eaccelerator_rm (key, key_len, where TSRMLS_CC)) {
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}

PHP_FUNCTION (eaccelerator_gc)
{
	if (ZEND_NUM_ARGS () != 0)
		WRONG_PARAM_COUNT;

	eaccelerator_gc (TSRMLS_C);
	RETURN_TRUE;
}
#endif							/* WITH_EACCELERATOR_SHM */
#endif							/* HAVE_EACCELERATOR */