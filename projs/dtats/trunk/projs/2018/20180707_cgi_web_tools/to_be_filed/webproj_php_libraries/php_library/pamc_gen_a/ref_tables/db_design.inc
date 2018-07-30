<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/ref_tables/db_design.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//db_design.inc -- PAMC MySQL database design reference information.  This is used
//                 to create the database, to access the database, and to print
//                 human-readable information about the design of the database.
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
$config_hard['dbdesign']['detailed'] =
   array
      (
      array
         (
         'name'       => 'tokens',
         'desc_short' => 'Cryptographic Tokens',
         'desc_long'  => 'Each record in this table is an individual cryptographic ' .
                         'token (Cryptocard\'s KT-1 keychain token, for example).',
         'fields' => array
                        (
                        array
                           (
                           'name'              => 'idx',
                           'type'              => 'int',
                           'dimension'         => 0,
                           'primarykey'        => TRUE,
                           'autoincrement'     => TRUE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Integer Index',
                           'desc_long'         => 'Automatically-assigned integer index of token.'
                           ),
                        array
                           (
                           'name'              => 'manufacturer',
                           'type'              => 'varchar',
                           'dimension'         => 100,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Token Manufacturer',
                           'desc_long'         => 'Company that manufactured the cryptographic token.'
                           ),
                        array
                           (
                           'name'              => 'modelnumber',
                           'type'              => 'varchar',
                           'dimension'         => 100,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Model Number',
                           'desc_long'         => 'Model number of token.'
                           ),
                        array
                           (
                           'name'              => 'serialnumber',
                           'type'              => 'varchar',
                           'dimension'         => 100,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Serial Number',
                           'desc_long'         => 'Serial number of token as assigned by manufacturer.'
                           ),
                        array
                           (
                           'name'              => 'tokenkey',
                           'type'              => 'varchar',
                           'dimension'         => 255,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Key',
                           'desc_long'         => 'Cryptographic key with which token is programmed.&nbsp; (This is ' .
                                                  'normally a secret known only to the token to the server which must authenticate ' .
                                                  'the token.)'
                           ),
                        array
                           (
                           'name'              => 'options',
                           'type'              => 'varchar',
                           'dimension'         => 100,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Options',
                           'desc_long'         => 'Token options.  Currently, this field is not used.&nbsp; In the future, more ' .
                                                  'flexible support for Cryptocard tokens in particular may be added'
                           )
                        )
         ),
      array
         (
         'name'       => 'logentries',
         'desc_short' => 'Log Entries',
         'desc_long'  => 'Each record in this table is a log entry.&nbsp; The system log holds information about system events ' .
                         'and can be sorted and reviewed.',
         'fields' => array
                        (
                        array
                           (
                           'name'              => 'idx',
                           'type'              => 'bigint',
                           'dimension'         => 0,
                           'primarykey'        => TRUE,
                           'autoincrement'     => TRUE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Integer Index',
                           'desc_long'         => 'Automatically-assigned integer index of the log entry.'
                           )
                        )
         ),
      array
         (
         'name' => 'users',
         'desc_short' => 'Users',
         'desc_long'  => 'Each record in this table is an user who can log in ' .
                         'to the PAMC system.',
         'fields' => array
                        (
                        array
                           (
                           'name'              => 'idx',
                           'type'              => 'int',
                           'dimension'         => 0,
                           'primarykey'        => TRUE,
                           'autoincrement'     => TRUE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Integer Index',
                           'desc_long'         => 'Automatically-assigned integer index of the user record.'
                           ),
                        array
                           (
                           'name'              => 'userid',
                           'type'              => 'varchar',
                           'dimension'         => 20,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => TRUE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Userid',
                           'desc_long'         => 'Login name of the user.'
                           ),
                        array
                           (
                           'name'              => 'pwhash',
                           'type'              => 'varchar',
                           'dimension'         => 40,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Password Hash (SHA1)',
                           'desc_long'         => 'Password hash of the user\'s password.&nbsp; This is the system hash function ' .
                                                  'of the user\'s password (SHA1, with the system hash key concatenated).'
                           ),
                        array
                           (
                           'name'              => 'lname',
                           'type'              => 'varchar',
                           'dimension'         => 25,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => TRUE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Last Name',
                           'desc_long'         => 'Last name of the user.&nbsp; May not be empty.'
                           ),
                        array
                           (
                           'name'              => 'fname',
                           'type'              => 'varchar',
                           'dimension'         => 25,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'First Name',
                           'desc_long'         => 'First name of the user.&nbsp; May not be empty.'
                           ),
                        array
                           (
                           'name'              => 'mnameinitial',
                           'type'              => 'varchar',
                           'dimension'         => 25,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Middle Name or Initial',
                           'desc_long'         => 'Middle name or initial of the user.&nbsp; If the column is an initial, it must ' .
                                                  'be in upper-case, with a \'.\' appended.&nbsp; May be empty.'
                           ),
                        array
                           (
                           'name'              => 'salutationshort',
                           'type'              => 'varchar',
                           'dimension'         => 100,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Salutation (Short)',
                           'desc_long'         => 'The short salutation used to address the user ' .
                                                  '(example: \'John\' in \'Good morning, John\').&nbsp; ' .
                                                  'May not be empty.&nbsp; Specified separately rather than automatically calculated ' .
                                                  'because of individual and international variability.'
                           ),
                        array
                           (
                           'name'              => 'salutationlong',
                           'type'              => 'varchar',
                           'dimension'         => 100,
                           'primarykey'        => FALSE,
                           'autoincrement'     => FALSE,
                           'index'             => FALSE,
                           'indexprefixlength' => 0,
                           'desc_short'        => 'Salutation (Long)',
                           'desc_long'         => 'The long salutation used to address the user ' .
                                                  '(example: \'John J. Smith\' in \'You are logged in as John J. Smith\').&nbsp; ' .
                                                  'May not be empty.&nbsp; Specified separately rather than automatically calculated ' .
                                                  'because of individual and international variability.'
                           )
                        )
         )
      );
//--------------------------------------------------------------------------------
//End of $RCSfile: db_design.inc,v $.
//--------------------------------------------------------------------------------
?>
