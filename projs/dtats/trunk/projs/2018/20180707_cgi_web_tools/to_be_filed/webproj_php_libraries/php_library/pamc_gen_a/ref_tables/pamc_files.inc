<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/ref_tables/pamc_files.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//pamc_files.inc -- PAMC reference file list.  This provides a list of all files
//                  for modification, copying, and checking.
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
$config['filelist'] 
   = array(
          "phplibrary" => array(
                               "config/config_hard.inc",
                               "config/config.inc",
                               "config/config_maint.inc",
                               "hash/crhsh.inc",
                               "hash/hashkey.inc",
                               "string/strfunc_charset.inc",
                               "string/strfunc_htmlformat.inc",
                               "string/strfunc_int.inc",
                               "ref_tables/apps_pages_navlines.inc",
                               "ref_tables/db_design.inc",
                               "ref_tables/db_design_tablelistonly.inc",
                               "ref_tables/pamc_files.inc",
                               "time/autime.inc",
                               "time/autimelp.inc",
                               "time/timeraw.inc",
                               "unique_id/sguid.inc"
                               ),
          "webfiles"   => array(
                               "index.php",
                               "left_nav.php",
                               "main.php",
                               "unittest/autime.php",
                               "unittest/crhsh.php",
                               "unittest/index.php",
                               "unittest/sguid.php",
                               "unittest/timeraw.php"
                               )
          );
//--------------------------------------------------------------------------------
//End of $RCSfile: pamc_files.inc,v $.
//--------------------------------------------------------------------------------
?>
