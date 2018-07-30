#!/usr/bin/php -q
<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbtestpop.php 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//dbtestpop.php--Populates the FBO-Prime Database for Testing
//Copyright (C) 2006  David T. Ashley
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
//--------------------------------------------------------------------------------
//This script populates an FBO-Prime database for testing.  This program was
//used to populate the database after dropping and recreating the database to
//avoid the trouble of manually re-entering data using web forms.
//--------------------------------------------------------------------------------
//Set the include file path.  This is necessary to get to the configuration
//information, including how to try to connect to the database.
set_include_path("/var/www/php_library/fboprime");
//
require_once("config.inc");
require_once("passwd.inc");
require_once("rscsx.inc");
require_once("resvx.inc");
require_once("sguid.inc");
require_once("usrsx.inc");
//
//--------------------------------------------------------------------------------
//Writes a horizontal line.
//
function hline()
   {
   for ($i=0; $i<80; $i++)
      {
      echo "-";
      }
   echo "\n";
   }
//
//--------------------------------------------------------------------------------
//Errors out.
//
function error_out()
   {
   echo "FATAL ERROR\n";
   exit(1);
   }
//--------------------------------------------------------------------------------
//Returns a version control string.  Used for randomness.
//
function vc_info()
   {
   return("\$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbtestpop.php 205 2018-07-15 19:00:51Z dashley $");
   }
//
//--------------------------------------------------------------------------------
function random_alpha_character()
   {
   $s = "abcdefghijklmnopqrstuvwxyz";

   $l = strlen($s);

   $p = rand(0, $l-1);

   return(SubStr($s, $p, 1));
   }
//
//--------------------------------------------------------------------------------
function random_alphanum_character()
   {
   $s = "abcdefghijklmnopqrstuvwxyz0123456789";

   $l = strlen($s);

   $p = rand(0, $l-1);

   return(SubStr($s, $p, 1));
   }
//
//--------------------------------------------------------------------------------
function random_nameish_string($maxlen)
   {
   if ($maxlen == 0)
      {
      return("");
      }
   else
      {
      $tgt = rand(1,$maxlen);
      $rv = StrToUpper(random_alpha_character());
      while(strlen($rv) < $tgt)
	 {
	 $rv .= random_alpha_character();
	 }

      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------
function random_useridish_string($maxlen)
   {
   if ($maxlen == 0)
      {
      return("");
      }
   else
      {
      $tgt = rand(1,$maxlen);
      $rv = random_alpha_character();
      while(strlen($rv) < $tgt)
	 {
	 $rv .= random_alphanum_character();
	 }

      return($rv);
      }
   }
//
//--------------------------------------------------------------------------------
function add_random_user()
   {
   //Get a userid.
   $v["userid"]          = random_useridish_string(20);
   
   //Get a password hash.
   $v["pwhash"]          = PASSWD_stored_hash_gen($v["userid"]);

   //Get a sex.
   $v["sex"]             = rand(0,2);

   //Get a first name.
   $v["fname"]           = random_nameish_string(10);

   //Get a last name.
   $v["lname"]           = random_nameish_string(12);

   $trash = rand(0,2);
   if ($trash == 0)
      $v["schedalonerscs"] = ",1,5,";
   else if ($trash  == 1)
      $v["schedalonerscs"] = ",3,2,4,7,12,";
   else
      $v["schedalonerscs"] = ",9,";

   //Add the user.
   USRS_record_add_modify("A", $v, $result_code_out, $errors_out, $warnings_out);
   }
//
//--------------------------------------------------------------------------------
function add_random_users()
   {
   //Decide how many users.
   $nusers = rand(0,50);

   for ($i=0; $i<$nusers; $i++)
      add_random_user();
   }
//
//--------------------------------------------------------------------------------
function populate_usrs_table()
   {
   global $GLOBAL_dbhandle;

   $lut = array(
	       //-------------------------------------------------------------
               //Theresa Whiting
               //
	       "twhiting",
               "twhiting",
               USRS_SEX_FEMALE,
               "Theresa",
               "Whiting",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "limeshoes@yahoo.com",
               "theresa@metzgersaircraft.com",
	       //-------------------------------------------------------------
               //Daniel Wynja
               //
               "dwynja",
               "dwynja",
               USRS_SEX_MALE,
               "Daniel",
               "Wynja",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "danielwynja@hotmail.com",
               "",
               //-------------------------------------------------------------
               //Sun Hee Metzger
               //
               "smetzger",
               "smetzger",
               USRS_SEX_FEMALE,
               "Sun Hee",
               "Metzger",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "eric@metzgersaircraft.com",
               "",
               //-------------------------------------------------------------
               //Eric Metzger
               //
               "emetzger",
               "emetzger",
               USRS_SEX_MALE,
               "Eric",
               "Metzger",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "eric@metzgersaircraft.com",
               "",
               //-------------------------------------------------------------
               //Nicki MacDonald
               //
               "nmacdona",
               "nmacdona",
               USRS_SEX_FEMALE,
               "Nicki",
               "MacDonald",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "nicki@metzgersaircraft.com",
               "",
               //-------------------------------------------------------------
               //Josh Hodge
               //
               "jhodge",
               "jhodge",
               USRS_SEX_MALE,
               "Josh",
               "Hodge",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "bcbruin26@aol.com",
               "10jrhodge@alma.edu",
               //-------------------------------------------------------------
               //Peter Ferencz
               //
               "pferencz",
               "pferencz",
               USRS_SEX_MALE,
               "Peter",
               "Ferencz",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "",
               "",
               //-------------------------------------------------------------
               //Michael Butson
               //
               "mbutson",
               "mbutson",
               USRS_SEX_MALE,
               "Michael",
               "Butson",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "",
               "",
               //-------------------------------------------------------------
               //Bob Buttrick
               //
               "bbuttrick",
               "bbuttrick",
               USRS_SEX_MALE,
               "Bob",
               "Buttrick",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "pyro_2232@hotmail.com",
               "",
               //-------------------------------------------------------------
               //Sean Ferencz
               //
               "sferencz",
               "sferencz",
               USRS_SEX_MALE,
               "Sean",
               "Ferencz",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "",
               "",
               //-------------------------------------------------------------
               //David Ashley
               //
               "dashley",
               "dashley",
               USRS_SEX_MALE,
               "David",
               "Ashley",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "dtashley@aol.com",
               "dta@e3ft.com",
               //-------------------------------------------------------------
               //Barry Bruns
               //
               "bbruns",
               "bbruns",
               USRS_SEX_MALE,
               "Barry",
               "Bruns",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "bbruns6831@aol.com",
               "",
               //-------------------------------------------------------------
               //Noah Belcher
               //
               "nbelcher",
               "nbelcher",
               USRS_SEX_MALE,
               "Noah",
               "Belcher",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "",
               "",
               //-------------------------------------------------------------
               //Erv Brinker
               //
               "ebrinker",
               "ebrinker",
               USRS_SEX_MALE,
               "Erv",
               "Brinker",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "erv@summitpointe.org",
               "",
               //-------------------------------------------------------------
               //Doug Motts
               //
               "dmotts",
               "dmotts",
               USRS_SEX_MALE,
               "Doug",
               "Motts",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "drmotts@comcast.net",
               "dmotts@cequentgroup.com",
               //-------------------------------------------------------------
               //Candice Young
               //
               "cyoung",
               "cyoung",
               USRS_SEX_FEMALE,
               "Candice",
               "Young",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "young.candice@gmail.com",
               "",
               //-------------------------------------------------------------
               //Jason Duca
               //
               "jduca",
               "jduca",
               USRS_SEX_MALE,
               "Jason",
               "Duca",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "jason.duca@wmich.edu",
               "duca47@hotmail.com",
               //-------------------------------------------------------------
               //Keith Rhoades
               //
               "krhoades",
               "krhoades",
               USRS_SEX_MALE,
               "Keith",
               "Rhoades",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "keith.rhoades@comcast.net",
               "",
               //-------------------------------------------------------------
               //Marilyn Ashley
               //
               "mashley2",
               "mashley2",
               USRS_SEX_FEMALE,
               "Marilyn",
               "Ashley",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "mashley2@aol.com",
               "",
               //-------------------------------------------------------------
               //Ed Shumway
               //
               "eshumway",
               "eshumway",
               USRS_SEX_MALE,
               "Ed",
               "Shumway",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "shumwaypopcorn@aol.com",
               "",
               //-------------------------------------------------------------
               //Pat Traster
               //
               "ptraster",
               "ptraster",
               USRS_SEX_MALE,
               "Pat",
               "Traster",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "trasterp@calhounisd.org",
               "",
               //-------------------------------------------------------------
               //Rob Williams
               //
               "rwilliams",
               "rwilliams",
               USRS_SEX_MALE,
               "Rob",
               "Williams",
               USRS_STATUS_ACTIVE,
               "\\canviewuserslist=\"\"\\canviewuserinfo=\"\"\\canedituserinfo=\"\"\\canresetuserpasswords=\"\""    .
                  "\\candeleteusers=\"\"\\canaddusers=\"\"\\canviewforeignresvexistence=\"\""                       .
                  "\\canviewforeignresvdetails=\"\"\\canmodifyforeignresvlesspriv=\"\""                             .
                  "\\canmodifyforeignresvpeerpriv=\"\"\\canmodifyforeignresvmorepriv=\"\"\\canviewdbstats=\"\""     .
                  "\\canviewlogentries=\"\"\\canvieweditresources=\"\"",
               "",
               "",
               //-------------------------------------------------------------
               //Unprivileged User
               //
               "uprivuser",
               "uprivuser",
               USRS_SEX_MALE,
               "Unprivileged",
               "User",
               USRS_STATUS_ACTIVE,
               "",
               "",
               "",
               );

   $n = count($lut);
   for ($i=0; $i<$n; $i+=9)
      {
      //Add a random number of users to the database.
      add_random_users();

      $v["userid"]       = $lut[$i];
      $v["pwhash"]       = PASSWD_stored_hash_gen($lut[$i+1]);
      $v["sex"]          = $lut[$i+2];
      $v["fname"]        = $lut[$i+3];
      $v["lname"]        = $lut[$i+4];
      $v["status"]       = $lut[$i+5];
      $v["perm"]         = $lut[$i+6];
      $v["em1"]          = $lut[$i+7];
      $v["em2"]          = $lut[$i+8];
      
      $trash = rand(0,2);
      if ($trash == 0)
	$v["schedalonerscs"] = ",1,2,5,9,";
      else if ($trash  == 1)
	$v["schedalonerscs"] = ",3,2,4,";
      else
	$v["schedalonerscs"] = "";

      
      $v["crmodsguid"]   = SGUID_sguid();
 
      echo "Making call to add user \"" . $v["userid"] . "\".\n";

      USRS_record_add_modify("A", $v, $result_code_out, $errors_out, $warnings_out);

      if ($result_code_out == 0)
	echo "Return value was 0, indicating an error.\n";
      else
        echo "Return value was " . $result_code_out . ".\n";
      unset($v);
      }
   }
//
//--------------------------------------------------------------------------------
//
function populate_rscs_table()
   {
   global $GLOBAL_dbhandle;

   $lut = array(
	       //-------------------------------------------------------------
               //N30348 J4 Cub Coupe
               //
	       RSCS_TYPE_AIRCRAFT,
               RSCS_STATUS_ONLINE,
               5,
               "NC30348 J4 Cub Coupe",
               "NC30348",
               "NC30348",
               "",
	       //-------------------------------------------------------------
               //N52341 Cessna 172P
               //
	       RSCS_TYPE_AIRCRAFT,
               RSCS_STATUS_ONLINE,
               10,
               "N52341 Cessna 172P",
               "N52341",
               "N52341",
               "",
	       //-------------------------------------------------------------
               //N6258K Cessna 172P
               //
	       RSCS_TYPE_AIRCRAFT,
               RSCS_STATUS_ONLINE,
               15,
               "N6258K Cessna 172P",
               "N6258K",
               "N6258K",
               "",
	       //-------------------------------------------------------------
               //N3024S Piper Warrior
               //
	       RSCS_TYPE_AIRCRAFT,
               RSCS_STATUS_ONLINE,
               20,
               "N3024S Piper Warrior",
               "N3024S",
               "N3024S",
	       "",
	       //-------------------------------------------------------------
               //N2009Y Beechcraft Duchess
               //
	       RSCS_TYPE_AIRCRAFT,
               RSCS_STATUS_ONLINE,
               25,
               "N2009Y Beechcraft Duchess",
               "N2009Y",
               "N2009Y",
               "",
	       //-------------------------------------------------------------
               //Barry Bruns
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               100,
               "Bruns, Barry",
               "B. Bruns",
               "B.B.",
               "bbruns",
	       //-------------------------------------------------------------
               //Ed Shumway
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               110,
               "Shumway, Ed",
               "E. Shumway",
               "E.S.",
               "eshumway",
	       //-------------------------------------------------------------
               //Pat Traster
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               112,
               "Traster, Pat",
               "P. Traster",
               "P.T.",
               "ptraster",
	       //-------------------------------------------------------------
               //Theresa Whiting
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               115,
               "Whiting, Theresa",
               "T. Whiting",
               "T.W.",
               "twhiting",
	       //-------------------------------------------------------------
               //Rob Williams
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               117,
               "Williams, Rob",
               "R. Williams",
               "R.W.",
               "rwilliams",
	       //-------------------------------------------------------------
               //Daniel Wynja
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               120,
               "Wynja, Daniel",
               "D. Wynja",
               "D.W.",
               "dwynja",
	       //-------------------------------------------------------------
               //Candice Young
               //
	       RSCS_TYPE_FLIGHTINSTRUCTOR,
               RSCS_STATUS_ONLINE,
               130,
               "Young, Candice",
               "C. Young",
               "C.Y.",
               "cyoung",
	       //-------------------------------------------------------------
               );

   $n = count($lut);
   for ($i=0; $i<$n; $i+=7)
      {
      $v["type"]         = $lut[$i];
      $v["status"]       = $lut[$i+1];
      $v["disporder"]    = $lut[$i+2];
      $v["longdesc"]     = $lut[$i+3];
      $v["shortdesc"]    = $lut[$i+4];
      $v["initials"]     = $lut[$i+5];
      $v["usercorres"]   = USRS_userid_idx_map($lut[$i+6]);
      if ($v["usercorres"] === FALSE)
         $v["usercorres"] = 0;
      $v["crmodsguid"]   = SGUID_sguid();
 
      echo "Making call to add resource \"" . $v["longdesc"] . "\".\n";
      $rv = RSCS_insert($v);
      if ($rv === FALSE)
	echo "Return value was FALSE.\n";
      else
        echo "Return value was " . $rv . ".\n";
      unset($v);
      }
   }
//
//--------------------------------------------------------------------------------
function random_reservation_description($res_no_in)
   {
   $lut = array(
	       "RMY->BTL because of my toothache.",
	       "Trip to Coldwater to use the cleaner restrooms.",
               "Woman-chasing at the beach.",
               "Man-chasing at the beach.",
               "I'm going to get my underarms shaved.",
               "Teaching my cat to fly.",
               "Teaching my hamster to fly.",
               "Teaching my dog to fly.",
               "Circles about a point.",
               "Squares about a pretty girl.",
               "My cat will teach me to appreciate mice.",
               "Ovals about a circle, while programming the GPS."
               );

   return($lut[rand(0, count($lut)-1)]);
   }
//--------------------------------------------------------------------------------
function test_populate_resv_table()
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_string;

   $make_output = TRUE;

   echo "Adding test reservations.\n";

   //Get the indices corresponding to the complete set of flight instructor resources,
   //or FALSE if non exist.
   $fi_indices = RSCS_get_fi_online_idxs();
   //print_r($fi_indices);

   //Get the indices corresponding to the complete set of aircraft / simulator resources,
   //or FALSE if non exist.
   $acftsim_indices = RSCS_get_acftsim_online_idxs();
   //print_r($acftsim_indices);

   //Get the indices corresponding all active users.    
   $usrs_indices = USRS_get_user_online_idxs();

   //Get the current Unix time.
   $unix_time_secs = time();

   //Get the lower limit of what we should pick for a date.
   $lower_limit_secs = $unix_time_secs - (31 * 24 * 3600 * (CONFIG_SCHED_SCHEDACC_PREV_MO+1));

   //Figure out how many seconds should be in the range.  This should be kept to a manageable number because
   //I don't have too much confidence in the rand() function.
   //
   $range_secs = (CONFIG_SCHED_SCHEDACC_PREV_MO + CONFIG_SCHED_SCHEDACC_FUTU_MO + 2) * 31 * 24 * 3600;

   for ($test_res_cntr = 0; $test_res_cntr < (7 * 30 * 100); $test_res_cntr++)
      {
      echo "Adding test reservation #" . (string)($test_res_cntr+1) . ".\n";

      //Pick a random starting point.
      $start_secs = $lower_limit_secs + rand(0, $range_secs);

      //Pick a random duration.  The distribution should be mostly 1-3 hour reservations with
      //a small number that can be as long as 1 week.
      if (rand(0,100) == 0)
	$duration_secs = rand(1,7*3600*24);
      else
        $duration_secs = rand(1,3*3600);

      //Compute the endpoint.
      $end_secs = $start_secs + $duration_secs;

      //Compute the aircraft start year, month, day, hour, and minute.
      $acft_start_year       = (int) date("Y", $start_secs);
      $acft_start_month      = (int) date("n", $start_secs);
      $acft_start_day        = (int) date("j", $start_secs);
      $acft_start_hour       = (int) date("G", $start_secs);
      $acft_start_minute     =       date("i", $start_secs);
      if ((strlen($acft_start_minute) == 2) && (SubStr($acft_start_minute, 0, 1) == "0"))
	 $acft_start_minute  = SubStr($acft_start_minute, 1, 1);
      $acft_start_minute     = (int) $acft_start_minute;
      if ($acft_start_minute < 30)
	 $acft_start_minute = 0;
      else
         $acft_start_minute = 30;

      //Compute the aircraft end year, month, day, hour, and minute.
      $acft_end_year         = (int) date("Y", $end_secs);
      $acft_end_month        = (int) date("n", $end_secs);
      $acft_end_day          = (int) date("j", $end_secs);
      $acft_end_hour         = (int) date("G", $end_secs);
      $acft_end_minute       =       date("i", $end_secs);
      if ((strlen($acft_end_minute) == 2) && (SubStr($acft_end_minute, 0, 1) == "0"))
	 $acft_end_minute  = SubStr($acft_end_minute, 1, 1);
      $acft_end_minute     = (int) $acft_end_minute;
      if ($acft_end_minute < 30)
	 $acft_end_minute = 0;
      else
         $acft_end_minute = 30;

      //Write the results
      echo "  "
           . "Acft  "
           . sprintf("%02d/%02d/%04d %02d:%02d:00", $acft_start_month, $acft_start_day, $acft_start_year, $acft_start_hour, $acft_start_minute)
           . " - "
           . sprintf("%02d/%02d/%04d %02d:%02d:00", $acft_end_month, $acft_end_day, $acft_end_year, $acft_end_hour, $acft_end_minute)
	   . "\n";

      //Need to discard any reservations that are of zero duration.
      if (
            ($acft_start_year   == $acft_end_year) 
            && 
            ($acft_start_month  == $acft_end_month) 
            && 
            ($acft_start_day    == $acft_end_day) 
            && 
            ($acft_start_hour   == $acft_end_hour) 
            && 
            ($acft_start_minute == $acft_end_minute)
         )
	 {
	 //The items are identical, need to discard.
	 echo "   Start and end times identical--test reservation discarded.\n";
	 }
      else
	 {
	 //Offset the flight instructor start time and end time by a random amount
         //and get new times for that.
	 $start_secs = $start_secs - rand(0, 3600 * 2);
         $end_secs   = $end_secs   + rand(0, 3600 * 2);

         //Compute the flight instructor start year, month, day, hour, and minute.
         $finst_start_year       = (int) date("Y", $start_secs);
         $finst_start_month      = (int) date("n", $start_secs);
         $finst_start_day        = (int) date("j", $start_secs);
         $finst_start_hour       = (int) date("G", $start_secs);
         $finst_start_minute     =       date("i", $start_secs);
         if ((strlen($finst_start_minute) == 2) && (SubStr($finst_start_minute, 0, 1) == "0"))
	    $finst_start_minute  = SubStr($finst_start_minute, 1, 1);
         $finst_start_minute     = (int) $finst_start_minute;
         if ($finst_start_minute < 30)
	    $finst_start_minute = 0;
         else
            $finst_start_minute = 30;

         //Compute the aircraft end year, month, day, hour, and minute.
         $finst_end_year         = (int) date("Y", $end_secs);
         $finst_end_month        = (int) date("n", $end_secs);
         $finst_end_day          = (int) date("j", $end_secs);
         $finst_end_hour         = (int) date("G", $end_secs);
         $finst_end_minute       =       date("i", $end_secs);
         if ((strlen($finst_end_minute) == 2) && (SubStr($finst_end_minute, 0, 1) == "0"))
	    $finst_end_minute  = SubStr($finst_end_minute, 1, 1);
         $finst_end_minute     = (int) $finst_end_minute;
         if ($finst_end_minute < 30)
	    $finst_end_minute = 0;
         else
            $finst_end_minute = 30;

         //Write the results
         echo "  "
              . "Finst "
              . sprintf("%02d/%02d/%04d %02d:%02d:00", $finst_start_month, $finst_start_day, $finst_start_year, $finst_start_hour, $finst_start_minute)
              . " - "
              . sprintf("%02d/%02d/%04d %02d:%02d:00", $finst_end_month, $finst_end_day, $finst_end_year, $finst_end_hour, $finst_end_minute)
	      . "\n";


         //Set up for the database commit.
         //
         $type                  = rand(0,2);
         $crsguid               = SGUID_sguid();
         $createtimest          = $GLOBAL_stime_string;
         $useridx               = $usrs_indices[rand(0, count($usrs_indices) - 1)];
         $alias                 = 0;
         if ($fi_indices !== FALSE)
	    {
	    $finstid               = $fi_indices[rand(0, count($fi_indices) - 1)];
            $finsttimestart        = "ST" 
                                     . 
                                     sprintf("%04d%02d%02d%02d%02d", 
                                             $finst_start_year, 
                                             $finst_start_month, 
                                             $finst_start_day, 
                                             $finst_start_hour, 
                                             $finst_start_minute)
                                     .
                                     "00000000";
            $finsttimeend          = "ST" 
                                     . 
                                     sprintf("%04d%02d%02d%02d%02d", 
                                             $finst_end_year, 
                                             $finst_end_month, 
                                             $finst_end_day, 
                                             $finst_end_hour, 
                                             $finst_end_minute)
                                     .
                                     "00000000";
            }
         else
	    {
            $finstid               = 0;
            $finsttimestart        = "";
            $finsttimeend          = "";
            }

         if ($acftsim_indices !== FALSE)
	    {
	    $acftsimid             = $acftsim_indices[rand(0, count($acftsim_indices) - 1)];
            $acftsimtimestart      = "ST" 
                                     . 
                                     sprintf("%04d%02d%02d%02d%02d", 
                                             $acft_start_year, 
                                             $acft_start_month, 
                                             $acft_start_day, 
                                             $acft_start_hour, 
                                             $acft_start_minute)
                                     .
                                     "00000000";
            $acftsimtimeend        = "ST" 
                                     . 
                                     sprintf("%04d%02d%02d%02d%02d", 
                                             $acft_end_year, 
                                             $acft_end_month, 
                                             $acft_end_day, 
                                             $acft_end_hour, 
                                             $acft_end_minute)
                                     .
                                     "00000000";
            }
         else
	    {
            $acftsimid             = 0;
            $acftsimtimestart      = "";
            $acftsimtimeend        = "";
            }

         $usrprivdesc           = "";
         $fboprivdesc           = "";
	 $comprivdesc           = random_reservation_description($test_res_cntr + 1);
         $publicdesc            = "";
         $crmodsguid            = $crsguid;

         //Randomly blank out reservation components to represent aircraft-only or flight-instructor-only
         //reservations.
         if (rand(0,5)==0)
	    {
	    //Kill the flight instructor info.  Aircraft-only reservation.
            $finstid               = 0;
            $finsttimestart        = "";
            $finsttimeend          = "";
            }
         else if (rand(0,5)==0)
	    {
	    //Kill the aircraft info.  Flight-instructor-only reservation.
            $acftsimid             = 0;
            $acftsimtimestart      = "";
            $acftsimtimeend        = "";
            }

	 //Calculate the reservation minimum and maximum.
         $resvtimestart = "";
         $resvtimeend   = "";
         if (($acftsimid != 0) && ($finstid != 0))
	    {
	    //Both a/c and flight instructor exist.  Gotta do some fancy stuff to figure out how to assign.
	    if (strcmp($finsttimestart, $acftsimtimestart) < 0)
	       {
	       $resvtimestart = $finsttimestart;
               }
            else
	       {
	       $resvtimestart = $acftsimtimestart;
               }

	    if (strcmp($finsttimeend, $acftsimtimeend) > 0)
	       {
	       $resvtimeend = $finsttimeend;
               }
            else
	       {
	       $resvtimeend = $acftsimtimeend;
               }
            }
         else if ($acftsimid != 0)
	    {
	    //Aircraft/simulator, but no flight instructor.
	    $resvtimestart = $acftsimtimestart;
	    $resvtimeend   = $acftsimtimeend;
            }
         else if ($finstid != 0)
	    {
	    //Flight instructor, but no aircraft/simulator.
	    $resvtimestart = $finsttimestart;
	    $resvtimeend   = $finsttimeend;
            }

         //Form the query string.
	 $query_string = "INSERT INTO resv SET "
                         .
                         "type=\""                   . mysql_real_escape_string((string)$type, $GLOBAL_dbhandle)       . "\", "
                         .
                         "crsguid=\""                . mysql_real_escape_string($crsguid, $GLOBAL_dbhandle)            . "\", "
                         .
                         "createtimest=\""           . mysql_real_escape_string($createtimest, $GLOBAL_dbhandle)       . "\", "
                         .
                         "useridx=\""                . mysql_real_escape_string((string)$useridx, $GLOBAL_dbhandle)    . "\", "
                         .
                         "alias=\""                  . mysql_real_escape_string((string)$alias, $GLOBAL_dbhandle)      . "\", "
                         .
                         "finstid=\""                . mysql_real_escape_string((string)$finstid, $GLOBAL_dbhandle)    . "\", "
                         .
                         "finsttimestart=\""         . mysql_real_escape_string($finsttimestart, $GLOBAL_dbhandle)     . "\", "
                         .
                         "finsttimeend=\""           . mysql_real_escape_string($finsttimeend, $GLOBAL_dbhandle)       . "\", "
                         .
                         "acftsimid=\""              . mysql_real_escape_string((string)$acftsimid, $GLOBAL_dbhandle)  . "\", "
                         .
                         "acftsimtimestart=\""       . mysql_real_escape_string($acftsimtimestart, $GLOBAL_dbhandle)   . "\", "
                         .
                         "acftsimtimeend=\""         . mysql_real_escape_string($acftsimtimeend, $GLOBAL_dbhandle)     . "\", "
                         .
                         "resvtimestart=\""          . mysql_real_escape_string($resvtimestart, $GLOBAL_dbhandle)      . "\", "
                         .
                         "resvtimeend=\""            . mysql_real_escape_string($resvtimeend, $GLOBAL_dbhandle)        . "\", "
                         .
                         "usrprivdesc=\""            . mysql_real_escape_string($usrprivdesc, $GLOBAL_dbhandle)        . "\", "
                         .
                         "fboprivdesc=\""            . mysql_real_escape_string($fboprivdesc, $GLOBAL_dbhandle)        . "\", "
                         .
                         "comprivdesc=\""            . mysql_real_escape_string($comprivdesc, $GLOBAL_dbhandle)        . "\", " 
                         .
                         "publicdesc=\""             . mysql_real_escape_string($publicdesc, $GLOBAL_dbhandle)         . "\", "
                         .
                         "crmodsguid=\""             . mysql_real_escape_string($crmodsguid, $GLOBAL_dbhandle)         . "\""
                         ;

         //echo "\n\n" . $query_string . "\n\n";
         //sleep(10);

	 $result = mysql_query($query_string, $GLOBAL_dbhandle);
         }
      }
   }
//
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//------  M A I N    S C R I P T  ------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//
//
//This is the list of the database tables.  For each one, this script will try to
//trash it if it exists.
//
if ($argc == 1)
   {
   //The no-parameters case, as expected.
   //Set up the global variables.
   GLOBAL_init();

   $GLOBAL_dbhandle = mysql_connect(CONFIG_MYSQL_SERVER, CONFIG_MYSQL_USERNAME, CONFIG_MYSQL_PASSWORD);
   if ($GLOBAL_dbhandle === FALSE)
      {
      echo "ERROR:  Unable to connect and/or authenticate to MySQL database.\n";
      exit(1);
      }

   $result = mysql_select_db(CONFIG_MYSQL_DATABASE, $GLOBAL_dbhandle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to select MySQL database \"" . CONFIG_MYSQL_DATABASE . "\".\n";
      exit(1);
      }

   hline();

   //Populate the usrs table.
   populate_usrs_table();
   hline();

   //Populate the rscs table.
   populate_rscs_table();
   hline();

   //Populate reservations.
   test_populate_resv_table();
   hline();

   //Try to close the database.
   $result = mysql_close($GLOBAL_dbhandle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to close MySQL connection.\n";
      exit(1);
      }
   
   exit(0);
   }
else
   {
   echo "ERROR:  This command accepts no command-line parameters.\n";
   exit(1);
   }

//If we're here, success.  Per the standard Unix way of thinking
//say nothing.  Silence means OK.
exit(0);
//
//--------------------------------------------------------------------------------
//End of $RCSfile: dbtestpop.php,v $.
//--------------------------------------------------------------------------------
?>
