<?php
if (!isset($PAMC_A_SECRETS_SSTR_INCLUDED))
   {
   include("pamc_a/secrets/sstr.inc");
   $PAMC_A_SECRETS_SSTR_INCLUDED = 1;
   }
?>
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
//The single function below accepts an arbitrary number of arguments.
//
function CRHSH_hashva()
   {
   $input = SSTR_HASH_KEY;

   $num_args = func_num_args();

   for ($i=0; $i<$num_args; $i++)
      {
      $input .= ((string) func_get_arg($i));
      $input .= SSTR_HASH_KEY;
      }

   $rv = md5($input);

   return($rv);
   }
?>
