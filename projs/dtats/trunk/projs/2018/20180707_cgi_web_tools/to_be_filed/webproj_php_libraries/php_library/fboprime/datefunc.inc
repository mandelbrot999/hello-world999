<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/datefunc.inc 205 2018-07-15 19:00:51Z dashley $
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
//Dave Ashley, 04/06
//
//This source file contains date and time calculation and
//manipulation functions.
//
require_once("config.inc");            //Scheduling configuration.
require_once("confighard.inc");        //Necessary for date minimums and maximums.
//
//================================================================================
//================================================================================
//====  R A W    C A L C U L A T I O N  ==========================================
//================================================================================
//================================================================================
//Returns the number of days in the year.
//
//Unit-tested 20060408.
//
function DATEFUNC_year_days($year)
   {
   //May need to be changed if confighard.inc is modified for a longer calendar
   //range.
   $mod_4   = $year %   4;
   $mod_100 = $year % 100;
   $mod_400 = $year % 400;

   if ($mod_4 != 0)
      {
      //We can't have a leap year unless it is divisible by 4.
      return(365);
      }
   else if (($mod_100 == 0) && ($mod_400 != 0))
      {
      //Divisible by 100 and not divible by 400.  Not a leap year.
      return(365);
      }
   else
      {
      //Divisible by 4 and not meeting the exception case:  leap year.
      return(366);
      }
   }
//
//
//--------------------------------------------------------------------------------
//Returns the number of days in all years preceding but not including the
//start year.  This is used for modulo arithmetic to determine day of week
//and so on.  An array is much faster (I think and hope) than an iterative method
//involving summing the years.
//
//Note:  this function has not yet been unit-tested (after it was changed from
//a lookup table).  This is still todo.
//
function DATEFUNC_year_predecessor_sum($year_in)
   {
   //Customized for lower limit of 1700, upper limit if 2300.
   //
   if (($year_in >= CONFIGHARD_DATEFUNC_MINYEAR) && ($year_in < CONFIGHARD_DATEFUNC_MAXYEAR))
      {
      //In year $year_in, the number of prior years where the year was divisible
      //by 4 is given by the expression below.
      if ($year_in == CONFIGHARD_DATEFUNC_MINYEAR)
         {
         $years_prior_div_4 = 0;   
         }
      else
         {
         $years_prior_div_4 = (int)(($year_in - 1 - CONFIGHARD_DATEFUNC_MINYEAR) / 4);   
            //Verified in the PHP docs that cast to int from float behaves with classic
            //div behavior (rounding down), so will be OK.
         }

      //Correct for the fact that 1800, 1900, 2100, and 2200 are not leap years, but 2000 is.
      if (($year_in > 1800) && ($year_in <= 1900))
         {
         //1800 was not a leap year, so we need to deduct 1 from the total leap years encountered.
         $years_prior_div_4 -= 1;
         }
      else if (($year_in > 1900) && ($year_in <= 2100))
         {
         //1800 was not a leap year, and 1900 was not a leap year (but 2000 was),
         //so we need to deduct 2 from the total leap years encountered.
         $years_prior_div_4 -= 2;
         }
      else if (($year_in > 2100) && ($year_in <= 2200))
         {
         //1800, 1900, and 2100 were not leap years (but 2000 was),
         //so we need to deduct 3 from the total leap years encountered.
         $years_prior_div_4 -= 3;
         }
      else /* if (($year_in > 2200) && ($year_in <= 2300)) */
         {
         //1800, 1900, 2100, and 2200 were not leap years (but 2000 was),
         //so we need to deduct 4 from the total leap years encountered.
         $years_prior_div_4 -= 4;
         }

      //The total number of days in years prior is going to be 365 times the number
      //of years prior, except we need to add a day for each leap year prior.
      if ($year_in == CONFIGHARD_DATEFUNC_MINYEAR)
         {
         return(0);
         }
      else
         {
         return((int)(($year_in - CONFIGHARD_DATEFUNC_MINYEAR) * 365 + $years_prior_div_4));
         }
      }
   else
      {
      //Not a year we can calculate about.  Don't want to error-trap at such a 
      //low level.  Just return zero.
      return(0);
      }
   }
//
//
//--------------------------------------------------------------------------------
//Calculates the number of days in a given month of a given year.  Years are
//2000 ... (i.e. full-sized integer), and months are referenced in the traditional 
//way, 1..12.
//
//Unit-tested 20060408.
//
function DATEFUNC_year_month_days($year, $month)
   {
   switch ($month)
      {
      default:
      case 1:
         return(31);
         break;
      case 2:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(28);
            }
         else
            {
            return(29);
            }
         break;
      case 3:
         return(31);
         break;
      case 4:
         return(30);
         break;
      case 5:
         return(31);
         break;
      case 6:
         return(30);
         break;
      case 7:
         return(31);
         break;
      case 8:
         return(31);
         break;
      case 9:
         return(30);
         break;
      case 10:
         return(31);
         break;
      case 11:
         return(30);
         break;
      case 12:
         return(31);
         break;
      }
   }
//
//
//--------------------------------------------------------------------------------
//Calcualtes the Julian offset of a date within a certain year.  The offset
//of January 1 of any year is 0.  Year, month, and day are 2000 ..., 1 ..., and
//1 ..., respectively.
//
//Unit-tested 20060408.
//
function DATEFUNC_year_julian_offset($year, $month, $day)
   {
   switch ($month)
      {
      default:
      case 1:
         return($day - 1);
         break;
      case 2:
         return(31 + $day - 1);
      case 3:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(59 + $day - 1);
            }
         else
            {
            return(59 + $day);
            }
         break;
      case 4:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(90 + $day - 1);
            }
         else
            {
            return(90 + $day);
            }
         break;
      case 5:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(120 + $day - 1);
            }
         else
            {
            return(120 + $day);
            }
         break;
      case 6:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(151 + $day - 1);
            }
         else
            {
            return(151 + $day);
            }
         break;
      case 7:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(181 + $day - 1);
            }
         else
            {
            return(181 + $day);
            }
         break;
      case 8:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(212 + $day - 1);
            }
         else
            {
            return(212 + $day);
            }
         break;
      case 9:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(243 + $day - 1);
            }
         else
            {
            return(243 + $day);
            }
         break;
      case 10:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(273 + $day - 1);
            }
         else
            {
            return(273 + $day);
            }
         break;
      case 11:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(304 + $day - 1);
            }
         else
            {
            return(304 + $day);
            }
         break;
      case 12:
         if (DATEFUNC_year_days($year) == 365)
            {
            return(334 + $day - 1);
            }
         else
            {
            return(334 + $day);
            }
         break;
      }
   }
//
//
//--------------------------------------------------------------------------------
//Given year, month, and day (2000 ..., 1 ..., 1 ...), returns an integer
//representing the day of the week.
//   0   : Sunday
//   1   : Monday
//   2   : Tuesday
//   3   : Wednesday
//   4   : Thursday
//   5   : Friday
//   6   : Saturday
//
//Unit-tested 20060408.
//
function DATEFUNC_intdayofweek_intdate($year, $month, $day)
   {
   $int_differential =     CONFIGHARD_DATEFUNC_EPOCH_DOW
                        +  DATEFUNC_year_predecessor_sum($year)
                        +  DATEFUNC_year_julian_offset($year, $month, $day);
   return($int_differential % 7);
   }
//--------------------------------------------------------------------------------
//Compares two dates, expressed as integers.  Both must be properly formatted
//(i.e. valid years, months, and days).  Returns:
//   -1 if a  < b.
//    0 if a == b.
//    1 if a  > b.
//
function DATEFUNC_cmp($ya, $ma, $da, $yb, $mb, $db)
   {
   if ($ya < $yb)
      {
      return(-1);
      }
   else if ($ya > $yb)
      {
      return(1);
      }
   else
      {
      if ($ma < $mb)
         {
         return(-1);
         }
      else if ($ma > $mb)
         {
         return(1);
         }
      else
         {
         if ($da < $db)
            {
            return(-1);
            }
         else if ($da > $db)
            {
            return(1);
            }
         else
            {
            return(0);
            }
         }
      }
   }
//
//
//--------------------------------------------------------------------------------
//Given a year, a month, and a month offset, moves the passed date backward
//(in the case of negative month offset) or forward (in the case of positive
//month offset) and calculates a new year and month.  The calculated returned
//value will not go outside the range set in CONFIGHARD.INC for the
//scheduling range.
//
//A result flag is set to:
//   -1 : If the result had to be clipped because it went outside the calendar
//        functionality window.
//    0 : If the result did not have to be clipped.
//    1 : If the result had to be clipped because it went outside the calendar
//        functionality window.
//
//The values passed in must be valid.
//
//The ordinal month approach is used because integer math tends to be
//very fast.
//
function DATEFUNC_offset_month($year_in, $month_in, $month_offset_in, &$year_out, &$month_out, &$result_out)
   {
   //Default value of result.
   $result_out = 0;

   //Create ordinal month representations of the min and max allowable months.  Using this
   //scheme, the 0'th month would be January of 0 A.D.
   $min_ordinal_month   = CONFIGHARD_DATEFUNC_MINYEAR * 12;
   $max_ordinal_month   = CONFIGHARD_DATEFUNC_MAXYEAR * 12 - 1;

   //Create ordinal month representation of the input year, month.
   $in_ordinal_month    = $year_in * 12 + $month_in - 1;

   //Create the ordinal month reprsentation of the input + offset.
   $calcd_ordinal_month = $in_ordinal_month + $month_offset_in;

   //Clip the result to be within the scheduling range of the FBO-prime software.
   if ($calcd_ordinal_month < $min_ordinal_month)
      {
      $calcd_ordinal_month = $min_ordinal_month;
      $result_out = -1;
      }
   else if ($calcd_ordinal_month > $max_ordinal_month)
      {
      $calcd_ordinal_month = $max_ordinal_month;
      $result_out = 1;
      }

   //Convert back to calendar year and month format.
   $year_out  =  (int) ($calcd_ordinal_month / 12);
   $month_out =  ($calcd_ordinal_month % 12) + 1;
   }
//
//
//--------------------------------------------------------------------------------
//Calculates the date one week ago.  The date passed in must be within the
//calendaring range and the date one week before must be also within
//calendaring range.
//
function DATEFUNC_one_week_ago($year_in, $month_in, $day_in, &$year_out, &$month_out, &$day_out)
   {
   if (($day_in - 7) > 0)
      {
      //Simplest case.  Different date within the same month.
      $year_out  = $year_in;
      $month_out = $month_in;
      $day_out   = $day_in - 7;
      }
   else
      {
      //Have to roll the month backwards.
      if ($month_in > 1)
         {
         //Have to roll day and month backwards, but not the year.
         $year_out  = $year_in;
         $month_out = $month_in - 1;
         $day_out   = $day_in - 7 + DATEFUNC_year_month_days($year_in, $month_in - 1);
         }
      else
         {
         //Have to roll back the day, month, and year.
         $year_out  = $year_in - 1;
         $month_out = 12;
         $day_out   = $day_in - 7 + DATEFUNC_year_month_days($year_in - 1, 12);
         }
      }
   }
//
//--------------------------------------------------------------------------------
//Calculates the date one week in the future.  The date passed in must be within the
//calendaring range and the date one week in the future must be also within
//calendaring range.
//
function DATEFUNC_one_week_future($year_in, $month_in, $day_in, &$year_out, &$month_out, &$day_out)
   {
   $days_in_month = DATEFUNC_year_month_days($year_in, $month_in);

   if (($day_in + 7) <= $days_in_month)
      {
      //Simplest case.  Different date within the same month.
      $year_out  = $year_in;
      $month_out = $month_in;
      $day_out   = $day_in + 7;
      }
   else
      {
      //Have to roll the month forward.
      if ($month_in < 12)
         {
         //Have to roll day and month forward, but not the year.
         $year_out  = $year_in;
         $month_out = $month_in + 1;
         $day_out   = $day_in + 7 - $days_in_month;
         }
      else
         {
         //Have to roll forward the day, month, and year.
         $year_out  = $year_in + 1;
         $month_out = 1;
         $day_out   = $day_in + 7 - $days_in_month;
         }
      }
   }
//
//--------------------------------------------------------------------------------
//Calculates the date one day ago.  The date passed in must be within the
//calendaring range and the date one day before must be also within
//calendaring range.
//
function DATEFUNC_one_day_ago($year_in, $month_in, $day_in, &$year_out, &$month_out, &$day_out)
   {
   if ($day_in > 1)
      {
      //Simplest case.  Different date within the same month.
      $year_out  = $year_in;
      $month_out = $month_in;
      $day_out   = $day_in - 1;
      }
   else
      {
      //Have to roll the month backwards.
      if ($month_in > 1)
         {
         //Have to roll day and month backwards, but not the year.
         $year_out  = $year_in;
         $month_out = $month_in - 1;
         $day_out   = DATEFUNC_year_month_days($year_in, $month_in - 1);
         }
      else
         {
         //Have to roll back the day, month, and year.
         $year_out  = $year_in - 1;
         $month_out = 12;
         $day_out   = DATEFUNC_year_month_days($year_in - 1, 12);
         }
      }
   }
//
//--------------------------------------------------------------------------------
//Calculates the date one day in the future.  The date passed in must be within the
//calendaring range and the date one day in the future must be also within
//calendaring range.
//
function DATEFUNC_one_day_future($year_in, $month_in, $day_in, &$year_out, &$month_out, &$day_out)
   {
   $days_in_month = DATEFUNC_year_month_days($year_in, $month_in);

   if ($day_in < $days_in_month)
      {
      //Simplest case.  Different date within the same month.
      $year_out  = $year_in;
      $month_out = $month_in;
      $day_out   = $day_in + 1;
      }
   else
      {
      //Have to roll the month forwards.
      if ($month_in < 12)
         {
         //Have to roll day and month forward, but not the year.
         $year_out  = $year_in;
         $month_out = $month_in + 1;
         $day_out   = 1;
         }
      else
         {
         //Have to roll forward the day, month, and year.
         $year_out  = $year_in + 1;
         $month_out = 1;
         $day_out   = 1;
         }
      }
   }
//
//--------------------------------------------------------------------------------
//Given a year and a month, indicates whether it is within the window of
//what should be viewable for scheduling.
//
//The criteria for displaying the month are:
//  a)The month is not outside the calendaring functionality window.
//  b)The month is not outside the parameters set by the 
//    configuration constants CONFIG_SCHED_SCHEDACC_PREV_MO or
//    CONFIG_SCHED_SCHEDACC_FUTU_MO, which specify how many months
//    previous and future may be viewed.
//
//Returns:
//    -1     :   If the year/month is too early to be
//               schedulable.
//     0     :   If the year/month should be schedulable.
//     1     :   If the year/month is too late to be schedulable.
//
function DATEFUNC_is_not_displayable($year_in, $month_in)
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;

   //If the year is out of bounds, it is a no-go.
   if ($year_in < CONFIGHARD_DATEFUNC_MINYEAR)
      return(-1);
   else if ($year_in >= CONFIGHARD_DATEFUNC_MAXYEAR)
      return(1);

   //If the month is out of bounds, it is a no-go.
   if (($month_in < 1) || ($month_in > 12))
      return(1);  //Arbitrary, as long as it isn't 0.

   //For reference, find the year/month that is CONFIG_SCHED_SCHEDACC_PREV_MO
   //behind the passed year/month.  If this is clipped, no harm done.
   DATEFUNC_offset_month($GLOBAL_stime_year, 
                         $GLOBAL_stime_month, 
                         -CONFIG_SCHED_SCHEDACC_PREV_MO, 
                         $year_lower_limit, 
                         $month_lower_limit, 
                         $result_flag);

   //For reference, find the year/month that is CONFIG_SCHED_SCHEDACC_FUTU_MO
   //ahead of the passed year/month.  If this is clipped, no harm done.
   DATEFUNC_offset_month($GLOBAL_stime_year, 
                         $GLOBAL_stime_month, 
                         CONFIG_SCHED_SCHEDACC_FUTU_MO, 
                         $year_upper_limit, 
                         $month_upper_limit, 
                         $result_flag);

   //echo " year upper limit : " . $year_upper_limit . " month_upper_limit : " . $month_upper_limit . " ";

   //If the passed year/month are below the lower limit, this means it isn't
   //displayable.
   if (DATEFUNC_cmp($year_in, $month_in, 1, $year_lower_limit, $month_lower_limit, 1) == -1)
      return(-1);

   //If the passed year/month are above the upper limit, this means it isn't
   //displayable.
   if (DATEFUNC_cmp($year_in, $month_in, 1, $year_upper_limit, $month_upper_limit, 1) == 1)
      return(1);
   
   //If we're here, it is displayable.
   return(0);
   }
//
//================================================================================
//================================================================================
//====  S T R I N G    M A P P I N G  ============================================
//================================================================================
//================================================================================
//
//Returns the string associated with an ordinal month number 1-12.
//
function DATEFUNC_string_month_long($month_no)
   {
   $lookup = array("January",
                   "February",
                   "March",
                   "April",
                   "May",
                   "June",
                   "July",
                   "August",
                   "September",
                   "October",
                   "November",
                   "December");

   if (($month_no < 1) || ($month_no > 12))
      {
      return("INVALID");
      }
   else
      {
      return($lookup[$month_no - 1]);
      } 
   }
//
//--------------------------------------------------------------------------------
//Returns the string associated with a day of the week 0-6.
//
function DATEFUNC_string_dow_long($dow_no)
   {
   $lookup = array("Sunday",
                   "Monday",
                   "Tuesday",
                   "Wednesday",
                   "Thursday",
                   "Friday",
                   "Saturday");

   if (($dow_no < 0) || ($dow_no > 6))
      {
      return("INVALID");
      }
   else
      {
      return($lookup[$dow_no]);
      } 
   }
//--------------------------------------------------------------------------------
//Returns a string representing the standard date, i.e. "January 19, 2009" or 
//whatever.
//
function DATEFUNC_stdlongdate($year, $month, $day)
   {
   return(DATEFUNC_string_month_long($month) . " " . $day . ", " . $year);
   }
//
//--------------------------------------------------------------------------------
//Returns a string representing the standard date with day of the week, 
//i.e. "Friday, January 19, 2009" or whatever.
//
function DATEFUNC_stdlongdate_w_dow($year, $month, $day)
   {
   $dow = DATEFUNC_intdayofweek_intdate($year, $month, $day);
   return(  DATEFUNC_string_dow_long($dow) 
          . ", " 
          . DATEFUNC_string_month_long($month) 
          . " " 
          . $day 
          . ", " 
          . $year);
   }
//
//--------------------------------------------------------------------------------
//Returns a string representing the standard time.  In non-military format,
//this will be something like 5:04 p.m.  In military time, something like
//17:04.
//
function DATEFUNC_stdtimenosec($hour, $minute)
   {
   if (CONFIG_TIME_FORMAT_24HR)
      {
      //24-hour format.
      return(sprintf("%02d", $hour) . ":" . sprintf("%02d", $minute));
      }
   else
      {
      //12-hour format.
      if ($hour == 0)
         {
         return(sprintf("%d", 12)    . ":" . sprintf("%02d", $minute) . " a.m.");
         }
      else if ($hour < 12)
         {
         return(sprintf("%d", $hour) . ":" . sprintf("%02d", $minute) . " a.m.");
         }
      else if ($hour == 12)
         {
         return(sprintf("%d", $hour) . ":" . sprintf("%02d", $minute) . " p.m.");
         }
      else
         {
         return(sprintf("%d", $hour - 12) . ":" . sprintf("%02d", $minute) . " p.m.");
         }
      }
   }
//
//--------------------------------------------------------------------------------
//Calculate and return an array of Boolean results to determine whether it is OK
//to view/schedule the indicated date/time.  Each Boolean result is TRUE if it is 
//OK to view/schedule or FALSE if not.
//
//   a)[0] A month ago.
//   b)[1] A week ago.
//   c)[2] A day ago.
//   d)[3] One panel back.
//   e)[4] One panel forward.
//   f)[5] One day forward.
//   g)[6] One week forward.
//   h)[7] One month forward.
//
function DATEFUNC_viewschedtime_differential_array($dispyear, $dispmonth, $dispday,
                                                   $disphour, $dispminute)
   {
   global $CONFIG_SCHED_DAY_PANELS;

   //Default to all FALSE so we don't forget anything.
   //
   $rv = array(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);

   //NOW
   //---
   //For reference, determine if the base display date passed in is
   //displayable/schedulable.
   //
   if (DATEFUNC_is_not_displayable($dispyear, $dispmonth) == 0)
      $base_date_is_ok = TRUE;
   else
      $base_date_is_ok = FALSE;

   //A MONTH AGO
   //-----------
   //First, try to back off one month to get to the previous month.  If we fail on this
   //(because we're at the lower limit of what the calendar functionality can handle),
   //then we definitely can't display the previous month.
   //
   DATEFUNC_offset_month($dispyear, $dispmonth, -1, $prev_month_year, $prev_month_month, $prev_month_result_code);

   if ($prev_month_result_code == 0)
      {
      //We are not up against the limit of the calendaring functionality.
      //Evaluate the previous month.
      //
      if (DATEFUNC_is_not_displayable($prev_month_year, $prev_month_month) == 0)
         {
         $rv[0] = TRUE;  //Seems OK.
         }
      else
         {
         $rv[0] = FALSE; //Is outside the viewable range.
         }
      }
   else
      {
      //We couldn't back off because we were at the limit.
      $rv[0] = FALSE;
      }

   //A WEEK AGO
   //-----------
   //The logic for a week ago is that if the day of the month is seven or less, the previous
   //month is relevant, else the current month is relevant.
   if ($dispday <= 7)
      $rv[1] = $rv[0];
   else
      $rv[1] = $base_date_is_ok;

   //A DAY AGO
   //-----------
   //The logic for a day ago is that if the day of the month is 1, the previous
   //month is relevant, else the current month is relevant.
   if ($dispday == 1)
      $rv[2] = $rv[0];
   else
      $rv[2] = $base_date_is_ok;

   //ONE PANEL BACK
   //--------------
   //Get the currently appropriate panel.
   $panel = TOD_best_panel($disphour, $dispminute, $CONFIG_SCHED_DAY_PANELS);
   //
   //If the current panel is not 0, backing off the panel won't change the date,
   //and so the passed date's status is the right thing to look at.
   //
   //If the current panel is 0, backing off will move the date to the previous
   //day, and we use that status.
   if ($panel != 0)
      {
      $rv[3] = $base_date_is_ok;
      }
   else
      {
      $rv[3] = $rv[2];
      }

   //A MONTH IN THE FUTURE
   //---------------------
   //First, try to go forward one month to get to the next month.  If we fail on this
   //(because we're at the upper limit of what the calendar functionality can handle),
   //then we definitely can't display the next month.
   //
   DATEFUNC_offset_month($dispyear, $dispmonth, 1, $next_month_year, $next_month_month, $next_month_result_code);

   if ($next_month_result_code == 0)
      {
      //We are not up against the limit of the calendaring functionality.
      //Evaluate the next month.
      //
      if (DATEFUNC_is_not_displayable($next_month_year, $next_month_month) == 0)
         {
         $rv[7] = TRUE;  //Seems OK.
         }
      else
         {
         $rv[7] = FALSE; //Is outside the viewable range.
         }
      }
   else
      {
      //We couldn't go forward because we were at the limit.
      $rv[7] = FALSE;
      }

   //A WEEK IN THE FUTURE
   //--------------------
   //The logic for a week in the future is that if going forward 7 days will put us
   //into the next month, then the validity of that applies, otherwise the
   //validity for the current month applies.
   $days_in_base_month = DATEFUNC_year_month_days($dispyear, $dispmonth);

   if (($dispday + 7) > $days_in_base_month)
      {
      //Get value from next month.
      $rv[6] = $rv[7];
      }
   else
      {
      //Get value from this month.
      $rv[6] = $base_date_is_ok;
      }

   //A DAY IN THE FUTURE
   //-------------------
   //The logic for a day in the future is that if the current day is the last day of
   //the month, then next month's value applies, otherwise this month's
   //value applies.
   if ($dispday >= $days_in_base_month)
      $rv[5] = $rv[7];               //Next month's value.
   else
      $rv[5] = $base_date_is_ok;     //This month's value.

   //ONE PANEL IN THE FUTURE
   //-----------------------
   //If the current panel is not the last one, going to the next panel won't change 
   //the date, and so the passed date's status is the right thing to look at.
   //
   //If the current panel is the last one, going forward will move the date to the 
   //next day, and we use that status.
   $npanels = (int)(count($CONFIG_SCHED_DAY_PANELS) / 2);
   if ($panel >= ($npanels - 1))         //Last penel test.
      {
      $rv[4] = $rv[5];
      }
   else
      {
      $rv[4] = $base_date_is_ok;
      }

   //Return the return value.
   return($rv);
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: datefunc.inc,v $.
//--------------------------------------------------------------------------------
?>
