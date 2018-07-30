<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/hash/crhsh.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//crhsh.inc -- PAMC cryptographic hash function.
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
require_once("hash/hashkey.inc");
//--------------------------------------------------------------------------------
//The return value is an SHA1 hash of the arguments intermingled with the key.
//This will be 40 hexadecimal digits, in all lower case.
//
//This function is the core of all cryptographic hashing in the system.  Because
//it handles a variable number of arguments, it is used in all contexts.
//
//The function is always deterministic (the same inputs will always produce the same 
//output).
//
function CRHSH_hashva()
   {
   global $config_hard;

   $input = $config_hard['hash']['key'];

   $num_args = func_num_args();

   for ($i=0; $i<$num_args; $i++)
      {
      $input .= ((string) func_get_arg($i));
      $input .= $config_hard['hash']['key'];
      }

   $rv = StrToLower(sha1($input));  //Forced to lower case just in case the
                                    //PHP behavior changes between PHP versions.
   return($rv);
   }
//--------------------------------------------------------------------------------
//End of $RCSfile: crhsh.inc,v $.
//--------------------------------------------------------------------------------
?>
