<?php
//------------------------------------------------------------------------
//Marshall Aviation Center FBO Management Software
//Copyright (C)2005 David T. Ashley
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//The author (David T. Ashley) may be contacted by e-mail at dta@e3ft.com
//and by postal mail at P.O. Box 918, Marshall MI 49068.
//------------------------------------------------------------------------
//Configuration file.  This file assigns configuration constants that
//might easily change in the operation of the site.
//------------------------------------------------------------------------
// C A L E N D A R I N G
//------------------------------------------------------------------------
$conf_calen_year_max = 2036;
   /* The largest year that the scheduling system or any other calendaring
   ** functionality will deal with.  This avoids the Unix 2037 problem.
   ** When the 2037 problem is cured, this constant can be upped.
   ** However, it is anybody's guess whether fossil fuels, general
   ** aviation, Unix, or PHP will be around decades in the future.
   */
$conf_calen_year_min = 2000;
   /* The smallest year that the scheduling system or other calendaring
   ** functionality will deal with.
   */
//------------------------------------------------------------------------
// H T M L   F O R M A T
//------------------------------------------------------------------------
$conf_htmlformat_human_readable = 1;
   /* Used primarily for debugging.  If this is set true, the HTML
   ** generated will often be nicely indented and commented.  This kind
   ** of formatting for HTML is helpful for development and debugging
   ** (for example, when viewing the source HTML for a web page),
   ** but otherwise won't help the browser and will slow down page
   ** loads, especially for those with modem connections.  This
   ** configuration tweak should probably be turned off after all the
   ** kinks are worked out.
   */
//------------------------------------------------------------------------
// M y S Q L    D A T A B A S E    A C C E S S
//------------------------------------------------------------------------
$conf_mysqldbaccess_name = "dbmacntr01";
   /* The name of the MySQL database used.
   */
$conf_mysqldbaccess_userid = "macntr01";
   /* The userid used to access the MySQL database.
   */
$conf_mysqldbaccess_passwd = "fa3338sugg0estion7x";
   /* The password associated with the MySQL database.  The
   ** userid/password pair must allow full access.
   */  
//------------------------------------------------------------------------
?>
