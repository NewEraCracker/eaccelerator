/*
   +----------------------------------------------------------------------+
   | eAccelerator project                                                 |
   +----------------------------------------------------------------------+
   | Copyright (c) 2004 - 2005 eAccelerator                               |
   | http://eaccelerator.net                                              |
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

#ifndef EA_RESTORE_H
#define EA_RESTORE_H

#define FIXUP(x) if((x)!=NULL) {(x) = (void*)(((char*)(x)) + ((long)(EAG(mem))));}
void fixup_op_array (eaccelerator_op_array * from TSRMLS_DC);
void fixup_class_entry (eaccelerator_class_entry * from TSRMLS_DC);

void restore_class(mm_fc_entry *p TSRMLS_DC);
void restore_function(mm_fc_entry *p TSRMLS_DC);
zend_op_array* restore_op_array(zend_op_array *to, eaccelerator_op_array *from TSRMLS_DC);
zend_class_entry *restore_class_entry(zend_class_entry * to, eaccelerator_class_entry *from TSRMLS_DC);
void restore_class_parent(char *parent, int len, zend_class_entry *to TSRMLS_DC);
#ifdef ZEND_ENGINE_2
void restore_class_methods(zend_class_entry *to TSRMLS_DC);
#endif

dtor_func_t get_zend_destroy_property_info(TSRMLS_D);

#endif /* EA_RESTORE_H */