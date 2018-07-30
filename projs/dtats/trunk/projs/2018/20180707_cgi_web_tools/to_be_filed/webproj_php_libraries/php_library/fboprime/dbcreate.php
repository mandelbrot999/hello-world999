#!/usr/bin/php -q
<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbcreate.php 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//dbcreate.php--Creates The FBO-Prime Database (Unpopulated)
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
//Set the include file path.  This is necessary to get to the configuration
//information, including how to try to connect to the database.
set_include_path("/var/www/php_library/fboprime");
//
//Include the configuration information.
require_once("config.inc");
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
//
//--------------------------------------------------------------------------------
//Returns a version control string.  Used for randomness.
//
function vc_info()
   {
   return("\$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dbcreate.php 205 2018-07-15 19:00:51Z dashley $");
   }
//
//--------------------------------------------------------------------------------
//
function populate_db($handle, $dbdesign)
   {
   //Figure out how many tables are in the database, and get their names.
   hline();

   $result = mysql_query("show tables", $handle);

   if ($result === FALSE)
      error_out();

   //Figure out the results.
   $ntables = mysql_num_rows($result);
   for ($i=0; $i<$ntables; $i++)
      {
      $temp             = mysql_fetch_row($result);
      $tables_array[$i] = $temp[0];
      }

   //$ntables = count($tables_array);

   //Tell how many tables.
   if ($ntables > 1)
      echo $ntables . " tables found in database:\n";
   else if ($ntables == 1)
      echo $ntables . " table found in database:\n";
   else
      echo "No tables found in database.\n";

   //Emit the table names.
   for ($i = 0; $i < $ntables; $i++)
      {
      echo "   " . $tables_array[$i] . "\n";
      }

   //Loop through the necessary database design.  For any tables that do not
   //exist, create them in their entirety.  Every row in the lookup table that
   //is used (i.e. implemented) is marked by changing the fifth column
   //to "Y".
   for ($i = 0; $i < count($dbdesign); $i += 5)
      {
      if ($dbdesign[$i+4] != "Y")
         {
	   if ($ntables)
              $found = array_search($dbdesign[$i], $tables_array);
           else
	      $found = FALSE;

         if (($found === FALSE) || ($found === NULL))
            {
	    //The cited table does not exist.  Form the SQL query to make it.
	    $query = "create table " . $dbdesign[$i] . " (";
            $first = 1;

            for ($j = 0; $j < count($dbdesign); $j += 5)
	       {
	       if ($dbdesign[$j] == $dbdesign[$i])
	          {
	          if (! $first)
	             {
		     $query .= " , ";
		     }
	          else
		     {
		     $first = 0;
		     }

	          $query = $query . " " . $dbdesign[$j+1] . " " . $dbdesign[$j+2] . " " . $dbdesign[$j+3] . " ";

                  $dbdesign[$j+4] = "Y";
	          }
	       }

            $query .= " )";

            //Echo the query to the console for review.
            hline();
            echo "The table \"" . $dbdesign[$i] . "\" does not exist and will be created.  The SQL query is:\n\n";
            echo $query . "\n";

            //Run the query and bug out if it fails.
            $result = mysql_query($query, $handle);

            if ($result === FALSE)
               error_out();
	    }
         }  //end if not marked
      } // end for
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
//This describes the overall database design.  The parts are:
//   a)Table name.
//   b)Field name.
//   c)Field type.
//   d)Field attributes.
//
$dbdesign = array 
(
   //=====================================================================================================
   //=====================================================================================================
   //====  U S R S  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each user.
   //=====================================================================================================
   "usrs",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of the user.  This is used as a key throughout the software to uniquely
      //identify a user (for example, in "edit user" screens and so on).  MySQL ensures that the
      //first index will be 1, so 0 can be used as an error code or for other special flags.
   "usrs",            "status",          "int",                "",                                     "",
      //An integer describing the status of the user.  This is an integer constant defined in the
      //source code.  Possible values are active or inactive.  The transition to inactive based on
      //expiration of BFR time or medical can be done only in maintenance scripts or manually--
      //automatic actions involving this kind of state change are not taken during normal
      //page viewing.
   "usrs",            "seclvl",          "int",                "",                                     "",
      //The security level of the user.  This is defined by integer constants in the CONFIG.INC file.
      //The general scheme is that a user may not modify information about a user with a security
      //integer equal to or less than the user's.  A lesser integer means a higher security level.
   "usrs",            "userid",          "varchar(20)",        "",                                     "",
      //The ID of the user when logging in.  This is stored in the database in all lower case, but in
      //logins a user may accidentally mix case, so this is treated as case-insensitive when
      //authenticating.
      //
      //Restrictions:
      //  a)Id as stored may contain only a-z and 0-9 (i.e. no weird characters).
      //  b)Must be at least of length 1.
      //  c)Must begin with a letter (not a number).
      //  d)Must be unique.
   "usrs",            "role",            "int",                "",                                     "",
      //An integer describing the role of the user (flight instructor, user, whatever).  The values
      //are defined by constants in the CONFIG.INC file.  This integer is used for description only
      //and does not affect the privileges of the user in any way.
   "usrs",            "perm",            "varchar(2000)",      "",                                     "",
      //A permission string expressing the precise database permissions the user has.  This is an
      //unordered set of values separated by backslashes.  The string format is used because it combines
      //simplicity with speed.  String operations, which call into 'C'-compiled code, are fast.
   "usrs",            "sex",             "int",                "",                                     "",
      //The gender of the user.  The possible values of this integer are defined in constants in the
      //code.
   "usrs",            "title",           "varchar(20)",        "",                                     "",
      //The title of the user (optional), including a trailing ".", if appropriate.  Titles are strings 
      //such as "Dr.", "Mr.", etc.  This may have 'a-z', 'A-Z', spaces, apostrophes, "," and ".".
   "usrs",            "fname",           "varchar(20)",        "",                                     "",
      //The first name of the user (optional).  No casing is enforced due to the possibility of foreign names such as
      //"ug Limu" (I made that up).  Spaces are allowed in the name (only one contiguously) to accommodate 
      //foreign names.  Before storage in the database:
      //  a)Must have no leading or trailing spaces.
      //  b)Must be at least of length 1.
      //  c)May contain only 'a-z', 'A-Z', spaces, and apostrophes.
      //  d)If spaces appear within the name, there can be only one contiguously.
   "usrs",            "mname",           "varchar(20)",        "",                                     "",
      //The middle name of the user (optional), or the middle initial, or the middle initial followed by
      //a period.  Characters allowed are 'a-z', 'A-Z', spaces, and apostrophes, with no more than one
      //contiguous space.
   "usrs",            "lname",           "varchar(20)",        "",                                     "",
      //The last name of the user.  No casing is enforced due to the possibility of foreign names such as
      //"de Raspide".  Spaces are allowed in the name (only one contiguously) to accommodate foreign names.
      //Before storage in the database:
      //  a)Must have no leading or trailing spaces.
      //  b)Must be at least of length 1.
      //  c)May contain only 'a-z', 'A-Z', spaces, and apostrophes.
      //  d)If spaces appear within the name, there can be only one contiguously.
   "usrs",            "suffix",          "varchar(20)",        "",                                     "",
      //The suffix, such as "Jr.", "Sr.", etc. (optional).  This may have 'a-z', 'A-Z', spaces,
      //apostrophes, commas, and periods, with no more than one contiguous space.
   "usrs",            "adl1",            "varchar(50)",        "",                                     "",
      //The first line of the street address of the user.  This may include 'a-z', 'A-Z', digits, spaces,
      //apostrophes, periods, and '#', with no more than one contiguous space.  Optional.
   "usrs",            "adl2",            "varchar(50)",        "",                                     "",
      //Second line of address.  Same rules as first.                                                    
   "usrs",            "city",            "varchar(20)",        "",                                     "",
      //City (optional).  Same rules as first name and last name.                                        
   "usrs",            "stateprovince",   "varchar(20)",        "",                                     "",
      //Same rules as last name/first name.  For someone in a foreign country, this may not be a 2-letter
      //code.  Optional.
   "usrs",            "zippostalcode",   "varchar(20)",        "",                                     "",
      //Postal code.  Same rules as address lines.  Optional.  In the case of foreign countries, the
      //zip/postal code may be longer than 9 digits or contain letters, etc.
   "usrs",            "country",         "varchar(20)",        "",                                     "",
      //The country, in English.  Same rules as first or last names.  Optional.
   "usrs",            "pwhash",          "varchar(64)",        "",                                     "",
      //The salt and hash of the primary password.  The primary password is the one the user normally 
      //uses to log in.  If both this and the lostpwhash are not set, it would not be possible to log in.
   "usrs",            "lostpwhash",      "varchar(64)",        "",                                     "",
      //The salt and hash of the password that may be e-mailed to the user if the password is lost.  
      //It is done that way to avoid e-mailing existing passwords in the clear (the password mailed
      //to the user is a randomly-generated one).
   "usrs",            "lostpwgentime",   "varchar(22)",        "",                                     "",
      //A UTIME flagging the time at which the e-mailed password was generated.  There are two behaviors
      //associated with this:
      //  a)A new password cannot be e-mailed too often (i.e. there needs to be a minimum spacing).
      //  b)A password that is e-mailed is only valid for a finite period of time.
   "usrs",            "ratings",         "varchar(200)",       "",                                     "",
      //A string describing the ratings that the user has.  The format of this is up to the FBO.
      //Generally, this would be a comma-separated list of acronyms.  For storage in the database,
      //blanks and tabs would be trimmed from both ends.
   "usrs",            "bfrlicexpdate",   "varchar(8)",         "",                                     "",
      //The date, as a DT8, on which the user's license becomes invalid if the pilot does not receive
      //a BFR.
   "usrs",            "medexpdate",      "varchar(8)",         "",                                     "",
      //The date, as a DT8, on which the user's medical becomes invalid.  The user must obtain a new
      //medical by this date or can't fly as PIC or required crewmember.
   "usrs",            "restrictions",    "varchar(2000)",      "",                                     "",
      //A textual description of the restrictions that the user is under.  A typical string might be
      //"Medical prohibits user from flying at night.".  The format of this is up to the FBO.
   "usrs",            "dayphone",        "varchar(50)",        "",                                     "",
      //The daytime phone number of the user.  This is essentially the work phone number.
      //All phone numbers are optional.  Character set and rules same as address lines.
   "usrs",            "eveningphone",    "varchar(50)",        "",                                     "",
      //The evening phone number of the user.  This is essentially the home phone number.
   "usrs",            "cellphone",       "varchar(50)",        "",                                     "",
      //The mobile phone number of the user. 
   "usrs",            "em1",             "varchar(100)",       "",                                     "",
      //First notification e-mail address of the user.                                     
   "usrs",            "em2",             "varchar(100)",       "",                                     "",
      //Second notification e-mail address of the user.                                     
   "usrs",            "acctexpdate",     "varchar(8)",         "",                                     "",
      //The date, as a DT8, on which the user's account should expire.  On this date the user becomes
      //inactive and can't log in any more.
   "usrs",            "mostrecentlogin", "varchar(8)",         "",                                     "",
      //The date on which the most recent login by the user occurred.
   "usrs",            "schedalonerscs",  "varchar(2000)",      "",                                     "",
      //A comma-separated integer list of resources that the user can schedule without a flight
      //instructor.  (All resources can be scheduled WITH a flight instructor.)  The first character
      //will be a comma and the final entry will be ended with a comma, subject to the rules of 
      //comma-separated integer lists.
   "usrs",            "fboremarks",      "varchar(4000)",      "",                                     "",
   "usrs",            "userremarks",     "varchar(4000)",      "",                                     "",
      //Remarks editable by the FBO and user respectively.  Both sets of remarks are visible by both
      //parties, but the FBO remarks can be edited only by the FBO and the user remarks can be edited
      //only by the user.
   "usrs",            "crmodsguid",      "varchar(32)",        "",                                     "",
      //The SGUID from when the record was created or last modified.  This may be used to avoid browser
      //editing collisions.  The way that collisions are avoided is that when the record is modified
      //(perhaps by another user while a given user has the record displayed in a browser form), a new
      //SGUID is placed in the record.  When a new commit of the record is attempted, the lower-level
      //functions will detect that the underlying SGUID has changed, as they will compare the
      //one provided by the browser (usually stored as a hidden field) against the one currently
      //in the database.  The two will definitely be different, as SGUIDs have guaranteed uniqueness
      //throughout the lifetime of the server.
   //=====================================================================================================
   //=====================================================================================================
   //====  R E S V  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each reservation.  A reservation can consist of multiple slots.
   //=====================================================================================================
   "resv",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of reservation.  Used to identify it uniquely.
   "resv",            "type",            "int",                "",                                     "",
      //An integer identifying the type of the reservation.  This is defined by constants in source
      //code.  Possibilities are:
      //    0  :  Banner reservation.  This does nothing, interferes with nothing, etc.  It just
      //          displays information that is visible.
      //    1  :  Ordinary reservation that is active (not standby).
      //    2  :  Standby reservation.  This is an ordinary reservation that can't be made active
      //          because of a conflict.
   "resv",            "crsguid",         "varchar(32)",        "",                                     "",
      //An SGUID identifying the time at which the reservation was created.  This is used to break any
      //ties for priority.  Because of the way an SGUID is constructed, this is guaranteed to be
      //unique.  After the reservation is created, this SGUID is not modified 
   "resv",            "createtimest",    "varchar(22)",        "",                                     "",
      //An STIME identifying the time at which the reservation is created.  This is used for reporting
      //the date and time in human-friendly terms (but can't be used for tie-breaking).
   "resv",            "useridx",         "int",                "",                                     "",
      //An integer identifying the owner of the reservation.  As every reservation must have an owner,
      //this index must be > 0.
   "resv",            "alias",           "int",                "",                                     "",
      //Integer identifying the alias, if any.  Alias is the pseudo-name that should be displayed as the
      //owner, such as "Line", "Maintenance", etc.  A value of zero here indicates no alias to be used.
   "resv",            "finstid",         "int",                "",                                     "",
      //An integer identifying the resource record (not the user record!) corresponding to the flight 
      //instructor for the reservation.  If no flight instructor is included in the reservation, 0 is
      //stored.
   "resv",            "finsttimestart",  "varchar(22)",        "",                                     "",
      //The STIME corresponding to the start with the instructor.  If no instructor on the reservation,
      //this should be the empty string.
   "resv",            "finsttimeend",    "varchar(22)",        "",                                     "",
      //The STIME corresponding to the with the instructor.  If no instructor on the reservation,
      //this should be the empty string.
   "resv",            "acftsimid",       "int",                "",                                     "",
      //An integer identifying the resource record corresponding to the aircraft or simulator that is
      //being reserved.  If no aircraft or simulator is included in the reservation, 0 is stored.
   "resv",            "acftsimtimestart","varchar(22)",        "",                                     "",
      //The STIME corresponding to the start with the aircraft or simulator.  If no aircraft or simulator
      //is on the reservation, this should be the empty string.
   "resv",            "acftsimtimeend",  "varchar(22)",        "",                                     "",
      //The STIME corresponding to the end the aircraft or simulator.  If no aircraft or simulator is on 
      //the reservation, this should be the empty string.
   "resv",            "resvtimestart",   "varchar(22)",        "",                                     "",
      //The STIME corresponding to the start time of the reservation.  The start time is the minimum of 
      //the start of the flight instructor, if any, and the aircraft or simulator, if any.  For any
      //reservation, this always exists, because the reservation must have a flight instructor or
      //aircraft/simulator.  This database field is provided to simplify some queries.
   "resv",            "resvtimeend",     "varchar(22)",        "",                                     "",
      //The STIME corresponding to the end time of the reservation.  The start time is the maximum of 
      //the end of the flight instructor, if any, and the aircraft or simulator, if any.  For any
      //reservation, this always exists, because the reservation must have a flight instructor or
      //aircraft/simulator.  This database field is provided to simplify some queries.
   "resv",            "usrprivdesc",     "varchar(4000)",      "",                                     "",
      //User-private textual description of the appointment.  This can only appear on reservations
      //where:
      //   a)The reservation does not involve an aircraft.
      //   b)The reservation is by a flight instructor reserving the resource corresponding to
      //     themselves.
      //
      //User-private text is intended to allow for doctor's appointments, etc. and to keep the details
      //of this absolutely private to the individual private.
   "resv",            "fboprivdesc",     "varchar(4000)",      "",                                     "",
      //Description private to the FBO employees (not shared with the general user population).
      //Note that a reservation (such as a doctor's appointment) may have a certain description that is
      //user private, but a separate description for the FBO employees.
   "resv",            "comprivdesc",     "varchar(4000)",      "",                                     "",
      //Description private to the user community (those with login accounts who are logged in).
      //Note that any reservation may have an FBO-private component and a community-private
      //component.
   "resv",            "publicdesc",      "varchar(4000)",      "",                                     "",
      //Description that is fully public (visible to web page visitors who have not logged in).  
      //Currently only banner reservations support this field.
      //
   "resv",            "crmodsguid",      "varchar(32)",        "",                                     "",
      //An SGUID from whenever the reservation is created or modified.  This is used to detect editing
      //collisions.  This field is modified whenever the record is committed back (unlike the field
      //somewhat earlier in the definition that is never changed after record creation).
   //
   //=====================================================================================================
   //====  R S C S  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //The resources (aircraft, simulators, flight instructors).
   //=====================================================================================================
   "rscs",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of the resource.  This can be a unique way to identify the record.
   "rscs",            "type",            "int",                "",                                     "",
      //The type of the resource.  This is an integer constant defined in the code.  The values may be
      //aircraft, simulator, or flight instructor.
   "rscs",            "status",          "int",                "",                                     "",
      //The status of the resource.  This is an integer constant defined in the code.  The values
      //may be online or offline.
   "rscs",            "disporder",       "int",                "",                                     "",
      //An integer used to govern the order in which resources are displayed, smallest integer first.
      //This is used (as it is also in ORS) because the preferred display order (for the scheduler
      //and other places) may not correlate with any other fields.
   "rscs",            "initials",        "varchar(25)",        "",                                     "",
      //The shortest description, i.e. "N12345" or "J.F.".
   "rscs",            "shortdesc",       "varchar(50)",        "",                                     "",
      //A shorter description, i.e. "N12345" or "J. Flightinstructor".
   "rscs",            "longdesc",        "varchar(100)",       "",                                     "",
      //The long description of the resource.
      //
      //For a flight instructor, this would normally be the full name, i.e. "Flightinstructor, Jane Q.".
      //For a simulator I'm not sure how it would typically be described.   For an aircraft, this would
      //typically be the tail number followed by the aircraft model number, i.e. "N12345 Cessna 172P".
      //
      //In any case, this field is up to the discretion of the FBO, except that it cannot contain
      //any HTML markup. 
   "rscs",            "rstdtime",        "varchar(48)",       "",                                     "",
      //An array of 48 characters, each of which should be a R or a U, and corresponding to the   
      //half-hour time slots during a day.  The first character corresponds to the slot between 
      //12:00 a.m. and 12:30 a.m., the second character to the time slot between 12:30 a.m. and 1:00 a.m.,
      //etc.  A "R" in the corresponding position indicates that the time slot is restricted and that
      //there must be some interaction with the FBO to schedule the time slot.  A "U" in the
      //position indicates that the time slot may be scheduled freely.  For flight instructors,
      //this may be set up to prevent students from arbitrarily scheduling appointments in the
      //middle of the night.  For aircraft, it is unclear how this would help.  For simulators, this
      //would prevent users from scheduling the simulator when it is unavailable (such as when the 
      //building it is in is closed for business).
   "rscs",            "schedaheadhrs",   "int",                "",                                     "",
      //For a resource, the minimum number of hours that a user must schedule it ahead of time
      //with no interaction with the FBO.  There is also a similar limit in CONFIG.INC.  The
      //scheduling software uses the more restrictive (i.e. larger) of the two.
   "rscs",            "usercorres",      "int",                "",                                     "",
      //For a resource that is a flight instructor, the index of the user corresponding to the
      //resource.  For other types of resources, this will be 0.
   "rscs",            "crmodsguid",      "varchar(32)",        "",                                     "",
      //The SGUID from when the record was created or last modified.  This may be used to avoid browser
      //editing collisions.  The way that collisions are avoided is that when the record is modified
      //(perhaps by another user while a given user has the record displayed in a browser form), a new
      //SGUID is placed in the record.  When a new commit of the record is attempted, the lower-level
      //functions will detect that the underlying SGUID has changed, as they will compare the
      //one provided by the browser (usually stored as a hidden field) against the one currently
      //in the database.  The two will definitely be different, as SGUIDs have guaranteed uniqueness
      //throughout the lifetime of the server.
   //
   //=====================================================================================================
   //=====================================================================================================
   //====  S E S S  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each active session.  If a user does not explicitly log out or get canned for a page
   //hit after expiry, these are reaped by cron processes.
   //=====================================================================================================
   "sess",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of session.
   "sess",            "usrsidx",         "int",                "",                                     "",
      //The integer index of the user with whom the session is associated.
   "sess",            "sguid",           "char(32)",           "",                                     "",
      //An SGUID created when the session is opened.  This is guaranteed to be unique.  This is never
      //revealed to the client.  The reason it isn't revealed is that it may be used in cases
      //as part of a hash key.
   "sess",            "ip",              "varchar(32)",        "",                                     "",
      //The connecting IP as known to the server.  This is the string provided by the server.  With
      //IPV6, there can be up to 31 characters.
   "sess",            "sid",             "varchar(66)",        "",                                     "",
      //The session identifier.  This is formed when the session is opened and never changed
      //thereafter until the session is reaped.  This is provided to the user's browser as a cookie.
   "sess",            "revaltime",       "char(22)",           "",                                     "",
      //The time at which the session was created or revalidated (revalidation occurs when another page is
      //loaded with a valid SID), expressed as a UTIME.  This allows a user to continue activity 
      //and as long as there is activity the session won't expire.
   "sess",            "lifetime",        "int",                "",                                     "",
      //The lifetime of the session.  This is effectively the allowed inactivity time before an automatic
      //logout.  This lifetime could, in principle, be a function of who the user is.  In any case,
      //the lifetime can be modified in some cases to give a longer time until logout (useful for
      //line employees).
   "sess",            "loginfailures",   "int",                "",                                     "",
      //The number of consecutive times during the session that the wrong password for the userid has
      //been entered (on pages that perform sensitive operations where the operation must be
      //confirmed.  After a certain number of consecutive bad password entries, the user is forcibly
      //logged out.  The purpose of this behavior is to allow one or two typos without trashing a
      //user's typing in a form, but to not allow password guessing to go on indefinitely.  This counter
      //is reset back to zero on a successful correct password entry.
   "sess",            "menulvl",         "int",                "",                                     "",
      //The menu level at which the session is currently operating.  "0" is the default menu level, and
      //larger integers represent more options displayed on the menu.
   "sess",            "pagereloadtime",  "int",                "",                                     "",
      //If this value is >0, is the interval (in seconds) at which certain scheduling pages should be
      //automatically reloaded.  This is to assist line employees who might open the dayview scheduling
      //page and want it to refresh with changes periodically.
   "sess",            "sddt",            "varchar(8)",         "",                                     "",
      //The date, as a DT8, carried through as we decide which information to display.  This avoids
      //to tacking GET parameters on everywhere.  On the scheduler pages that will display with no user
      //logged in, the GET/POST parameters take precedence over anything stored in the session
      //state record, if any.  If this doesn't apply, the empty string is stored.
   "sess",            "sdtim",           "varchar(4)",         "",                                     "",
      //The time, as a T4, carried through as we decide which information to display.  This avoids
      //to tacking GET parameters on everywhere.  On the scheduler pages that will display with no user
      //logged in, the GET/POST parameters take precedence over anything stored in the session
      //state record, if any.  If this doesn't apply, the empty string is stored.
   "sess",            "logicalpage",     "int",                "",                                     "",
      //An enumerated constant, identifying which logical page in the tree of pages is the current page.
      //This is set on traversals by the "logpage=" GET/POST parameter.  A given physical page may
      //exist at more than location in the logical page hierarchy.  The entire hierarchy is on a
      //diagram in the documentation.  If there is no current context, the value of 0 is stored.
   "sess",            "curuser",         "int",                "",                                     "",
      //The user that is currently being edited or is otherwise of interest, by the index.  If there is
      //no user of interest, zero is stored.
   "sess",            "userlistactive",  "int",                "",                                     "",
      //1 if the user list to return to is the active user list, or 0 if the list to return to is the
      //inactive user list.
   "sess",            "curresource",     "int",                "",                                     "",
      //The resource that is currently being edited or is otherwise of interest, by the index.  If there
      //is no resource of interest, zero is stored.
   "sess",            "curreservation",     "int",             "",                                     "",
      //The reservation that is currently being edited or is otherwise of interest, by the index.  If
      //there is no reservation of interest, zero is stored.
   //=====================================================================================================
   //=====================================================================================================
   //====  L O G E  ======================================================================================
   //=====================================================================================================
   //=====================================================================================================
   //One record for each log entry.  This table should be pruned by the daily maintenance script, so that
   //it stays a reasonable size.
   //=====================================================================================================
   "loge",            "idx",             "int",                "AUTO_INCREMENT NOT NULL PRIMARY KEY",  "",
      //The integer index of the log entry.  This is used for uniqueness and to give an ordering.
      //An SGUID could also be used.
   "loge",            "type",            "int",                "",                                     "",
      //An integer (these constants are defined in log.inc and/or logview.inc) giving what type of
      //record this is.  There are many differen types.
   "loge",            "utime",           "varchar(22)",        "",                                     "",
      //A UTIME stamp gathered at the time the log entry is made.  This is a definitive reference
      //as to Unix time.  If for some reason a UTIME is not available, the empty string is used.
   "loge",            "stime",           "varchar(22)",        "",                                     "",
      //An STIME stamp gathered at the time the script starts execution.  Note that this time is more
      //sloppy than the Unix time, because it is gathered at the start of the page.  The UTIME
      //above is authoritative.  If there are any extremely weird problems (such as a page hanging
      //or executing slowly, the UTIME would give more insight than this STIME.
   "loge",            "ip",              "varchar(40)",        "",                                     "",
      //The IP address as reported by the server.  With IP version 6 coming up, the IP
      //address could be over 20 characters--define it as 40 to be safe.
   "loge",            "userid",          "varchar(20)",        "",                                     "",
      //The userid of anyone authenticated at the time the entry is made.  If nobody is
      //authenticated, the empty string is used.
   "loge",            "sid",             "varchar(66)",        "",                                     "",
      //Any session identifier that was passed in by cookie or was swapped in by authentication
      //at the time the log entry was made. 
   "loge",            "scriptfile",      "varchar(1024)",      "",                                     "",
      //The main file being executed, including the path from the document root.  This will be one
      //of the main script files of FBO-Prime.
   "loge",            "getpostpars",     "varchar(1024)",      "",                                     "",
      //The GET and/or POST parameters that are relevant to the log entry.
   "loge",            "phpfilek",        "varchar(1024)",      "",                                     "",
      //The caller's value of __FILE__ when the log-making function is called.
   "loge",            "phplinek",        "int",                "",                                     "",
      //The caller's value of __LINE__ when the log-making function is called. 
   "loge",            "logentry",        "varchar(4000)",      "",                                     ""
      //The text of the log entry.  This adds any needed description to the event.
) ;

if ($argc == 1)
   {
   //The no-parameters case, as expected.

   $handle = mysql_connect(CONFIG_MYSQL_SERVER, CONFIG_MYSQL_USERNAME, CONFIG_MYSQL_PASSWORD);
   $handle_copy = $handle;
   if ($handle === FALSE)
      {
      echo "ERROR:  Unable to connect and/or authenticate to MySQL database.\n";
      exit(1);
      }

   $result = mysql_select_db(CONFIG_MYSQL_DATABASE, $handle);
   if ($result === FALSE)
      {
      echo "ERROR:  Unable to select MySQL database \"" . CONFIG_MYSQL_DATABASE . "\".\n";
      exit(1);
      }

   populate_db($handle, $dbdesign);
   hline();

   $result = mysql_close($handle);
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
//End of $RCSfile: dbcreate.php,v $.
//--------------------------------------------------------------------------------
?>
