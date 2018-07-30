<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/config/config.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//config.inc -- PAMC User-Modifiable Configuration
//Copyright (C) 2007  David T. Ashley
//--------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------
//Author contact information:
//   David T. Ashley
//   P.O. Box 918
//   Marshall, Michigan, 49068
//   dta@e3ft.com
//--------------------------------------------------------------------------------
//********************************************************************************
//****    D I R E C T O R Y    P A T H S    **************************************
//********************************************************************************
$config['path']['phplibrary']     = "/var/www/php_library/pamc_gen_a";
   //The place where the PHP library .inc files for this product are located.
   //This path should not be directly servable by the web server or
   //directly readable by users because of the presence database userid/password,
   //the hash key, and perhaps other sensitive information.
$config['path']['webfiles']       = "/hl/webroots/cequent_pamc_443a";
   //The path to the root of the web space used by this product.
$config['path']['filerepository'] = "/hl/filereproots/fr_cequent_pamc_443a";
   //The path to the file repository.  This path should not be directly
   //servable by the web server or be directly readable by users because
   //for a given user, many of the files may, by security rules, not be
   //readable.
//********************************************************************************
//****    M Y S Q L    I N F O R M A T I O N    **********************************
//********************************************************************************
$config['mysql']['server']       = "localhost";
$config['mysql']['authuserid']   = "pamcdevel01user";
$config['mysql']['authpassword'] = "lithium39foam";
   //The MySQL authentication credentials.
$config['mysql']['dbname']       = "pamcdevel01";
   //Once the userid has authenticated into MySQL, the name of the database to
   //use.  All PAMC information resides in one database.
//--------------------------------------------------------------------------------
//End of $RCSfile: config.inc,v $.
//--------------------------------------------------------------------------------
?>
