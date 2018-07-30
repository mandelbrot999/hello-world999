<?php
//
//********************************************************************************
//Copyright (C) 2003 David T. Ashley
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
//
//Dave Ashley, 01/03
//
//This defines a simple PHP class to make it easier to implement a page statistic
//that indicates how much CPU time was used by a page or a portion of a page.
//The statistics are not always straightforward because each load of a page
//may just add more used time to the same process.  Stats must be obtained
//by subtraction.
//
//The basic strategy is that a clock is constructed then may be alternatively
//started, stopped, and polled.  It is necessary to stop a clock before 
//polling it.
//
class Cpuusagestatclock
   {
   //The fields below are updated each time the clock is stopped.
   var $utime_s;
      //The seconds portion of the amount of user time consumed.
   var $utime_m;
      //The microseconds portion of the amount of user time consumed.
   var $stime_s;
      //The seconds portion of the amount of system time consumed.
   var $stime_m;
      //The microseconds portion of the amount of system time consumed.

   //The following fields are analogous to the ones above, except they
   //hold time snapshot values from when the clock was most recently
   //started.
   var $ss_utime_s;
   var $ss_utime_m;
   var $ss_stime_s;
   var $ss_stime_m;

   //This is the constructor function. 
   function Cpuusagestatclock()
     {
     //All that is required at construction is to set the cumulative
     //values to zero.
     $this->utime_s = 0;
     $this->utime_m = 0;
     $this->stime_s = 0;
     $this->stime_m = 0;
     }

   //This starts the clock.  This just records a static time usage mark.
   function start()
      {
      //Get the snapshot from the system.
      $snapshot = getrusage();

      //Record the values of interest.
      $this->ss_utime_s = $snapshot["ru_utime.tv_sec"];
      $this->ss_utime_m = $snapshot["ru_utime.tv_usec"];
      $this->ss_stime_s = $snapshot["ru_stime.tv_sec"];
      $this->ss_stime_m = $snapshot["ru_stime.tv_usec"];
      } 


   //This stops the clock.  This calculates the used time and adds it in to
   //the totals.
   function stop()
      {
      //Get the snapshot from the system.
      $snapshot = getrusage();

      //Calculate and add in the elapsed user time usage since the snapshot.
      $this->utime_s += ($snapshot["ru_utime.tv_sec"] - $this->ss_utime_s);
      $this->utime_m += ($snapshot["ru_utime.tv_usec"] - $this->ss_utime_m);
      while ($this->utime_m < 0)
	{
	$this->utime_m += 1000000;
	$this->utime_s--;
	}

      //Calculate and add in the elapsed system time usage since the snapshot.
      $this->stime_s += ($snapshot["ru_stime.tv_sec"] - $this->ss_stime_s);
      $this->stime_m += ($snapshot["ru_stime.tv_usec"] - $this->ss_stime_m);
      while ($this->stime_m < 0)
	 {
	 $this->stime_m += 1000000;
	 $this->stime_s--;
	 }
      } 

   //This returns the user time microseconds elapsed of a stopped clock, with no padding.
   function utime_raw_us()
      {
	return($this->utime_m);
      }

   //This returns the user time microseconds elapsed of a stopped clock, padded
   //with leading zeros to be six digits long.
   function utime_formatted_us()
      {
      $rv = $this->utime_raw_us();

      while(strlen($rv) < 6)
	 $rv = "0" . $rv;

      return($rv);
      }

   //This returns the system time microseconds elapsed of a stopped clock, with no padding.
   function stime_raw_us()
      {
	return($this->stime_m);
      }

   //This returns the system time microseconds elapsed of a stopped clock, padded
   //with leading zeros to be six digits long.
   function stime_formatted_us()
      {
      $rv = $this->stime_raw_us();

      while(strlen($rv) < 6)
	 $rv = "0" . $rv;

      return($rv);
      }

   //This returns the total time microseconds elapsed of a stopped clock, with no padding.
   function ttime_raw_us()
      {
      $rv = $this->stime_m + $this->utime_m;

      if ($rv >= 1000000)
	 $rv -= 1000000;

      return($rv);
      }

   //This returns the total time microseconds elapsed of a stopped clock, padded
   //with leading zeros to be six digits long.
   function ttime_formatted_us()
      {
      $rv = $this->ttime_raw_us();

      while(strlen($rv) < 6)
	 $rv = "0" . $rv;

      return($rv);
      }

   //This returns the user time seconds elapsed of a stopped clock.
   function utime_s()
      {
      return($this->utime_s);
      }

   //This returns the system time seconds elapsed of a stopped clock.
   function stime_s()
      {
      return($this->stime_s);
      }

   //This returns the total time seconds elapsed of a stopped clock.
   function ttime_s()
      {
      $rv = $this->stime_s + $this->utime_s;

      $us_total = $this->stime_m + $this->utime_m;

      if ($us_total >= 1000000)
	 $rv++;
      
      return($rv);
      }

   //This returns the standard string for a footer of a web page.  No HTML formatting tags
   //are included.
   function std_web_page_cpu_time_usage_footer()
      {
      return
	 (
         "This page required approximately "
         .
         $this->ttime_s()
         .
         "."
         .
         Substr($this->ttime_formatted_us(), 0, 2)
         .
         "s ("
         .
         $this->stime_s()
         .
         "."
         .
         Substr($this->stime_formatted_us(), 0, 2)
         .
         "s system, "
         .
         $this->utime_s()
         .
         "."
         .
         Substr($this->utime_formatted_us(), 0, 2)
         .
         "s user) of CPU time on the server to generate."
         );
      } 
   }
?>
