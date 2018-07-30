<?php
//********************************************************************************
//Copyright (C)2006 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or 
//modify it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or (at your 
//option) any later version.
//
//This program or source file is distributed in the hope that it will 
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//Dave Ashley, 01/06
//
//This source file contains cryptographic hash functions.
//
//This constant is the hashing key.  This must be concealed from all users of the system.
//Knowledge of this key would allow a user to forge hashes.  The key consists of random
//typing, digits of PI, verbiage from the PHP website, and Thoreau quotes.
//
define("CRHSH_KEY_A", "kdj376xhadfhl134g;;hv adfhlLLL:::341324hdbvjkahsdfgh2834gigwreeiqrbuibwqvgzzxxaqkhlkagdviab;;" .
                      "wikiwikiboomboomWhen you remove constant in your pool.14159265358979323846264338hgiik123435 /" .
                      "628034825342117067982160631558817488152092096282925409171536436789259next greatest happiness " .
                      "always 762876110927543725 clear understanding that I do not attain //76234767960bbbhgquickbro" .
                      "hgalshdfthequickdoglazytheoverjumpedfoxquickbrownfox---mind was all undusted still,.........." );

//All of the functions below calculate an MD5 hash with various numbers of arguments.  A
//function accepting a variable number of arguments is also provided.  The return value
//in all cases is an MD5 hash of the arguments intermingled with the key.
//
//The functions are in all cases deterministic (same inputs will always produce same output).
//
//Once a database system is in operation, the key must not be changed, or it may render the database
//system unusable.
//
function CRHSH_hash01($arg)
   {
   $arg = (string) $arg;

   $input =  CRHSH_KEY_A . $arg . CRHSH_KEY_A;

   //echo "<br>\n";
   //echo $input;
   //echo "<br>\n";

   $rv = md5($input);

   return($rv);
   }
//
function CRHSH_hash02($arg01, $arg02)
   {
   $arg01 = (string) $arg01;
   $arg02 = (string) $arg02;

   $input =  CRHSH_KEY_A . $arg01 . CRHSH_KEY_A . $arg02 . CRHSH_KEY_A;

   //echo "<br>\n";
   //echo $input;
   //echo "<br>\n";

   $rv = md5($input);

   return($rv);
   }
//
function CRHSH_hash03($arg01, $arg02, $arg03)
   {
   $arg01 = (string) $arg01;
   $arg02 = (string) $arg02;
   $arg03 = (string) $arg03;

   $input =  CRHSH_KEY_A . $arg01 . CRHSH_KEY_A . $arg02 . CRHSH_KEY_A . $arg03 . CRHSH_KEY_A;

   $rv = md5($input);

   return($rv);
   }
//
function CRHSH_hash04($arg01, $arg02, $arg03, $arg04)
   {
   $arg01 = (string) $arg01;
   $arg02 = (string) $arg02;
   $arg03 = (string) $arg03;
   $arg04 = (string) $arg04;

   $input =  CRHSH_KEY_A . $arg01 . CRHSH_KEY_A . $arg02 . CRHSH_KEY_A . $arg03 . CRHSH_KEY_A . $arg04 . CRHSH_KEY_A;

   $rv = md5($input);

   return($rv);
   }
//
function CRHSH_hashva()
   {
   $input = CRHSH_KEY_A;

   $num_args = func_num_args();

   for ($i=0; $i<$num_args; $i++)
      {
      $input .= ((string) func_get_arg($i));
      $input .= CRHSH_KEY_A;
      }

   $rv = md5($input);

   return($rv);
   }
?>
