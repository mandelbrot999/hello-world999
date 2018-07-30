<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/tod.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//tod.inc--FboPrime Time of Day Functions
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
//********************************************************************************
//This contains functions that deal with time of day (as opposed to date).
//--------------------------------------------------------------------------------------------------------------
require_once("config.inc");
//--------------------------------------------------------------------------------------------------------------
//
//Determines, for a given time of day, which panel in an array is a best fit.
//The method used is to find in which of any panels the given time is closest
//to the center.
//  $hour        :  Integer hour, 0-23.
//  $minute      :  Integer minute, 0-59.
//  return value :  Which panel (integer).  A return value of 2 would indicate array subscripts 4 and 5
//                  in the actual array.
//
//Unit tested 20060414.
//
function TOD_best_panel($hour, $minute, $panel_array)
  {
  $best = 0;
  $least_center_square = 1.0;

  $nelem = count($panel_array);
  
  for ($i=0; $i<$nelem; $i+=2)  //For each panel.
     {
     if (($hour >= $panel_array[$i]) && ($hour <= $panel_array[$i+1]))  //Must be in the panel.
                                                                        //With integers, test above on right
                                                                        //side of interval is correct.
                                                                        //"a < (b+1)" is equivalent to
                                                                        //"a <= b" when integers are involved.
        {
        $decimal_time     =      (float)$hour + ((float)$minute/60.0);  
           //Convert time to decimal hours.
        $span             =      (float)($panel_array[$i+1] + 1.0 - $panel_array[$i]);  
           //Use span to normalize.  1.0 added because panel actually goes to end of hour.
        $midpoint         =      ((float)$panel_array[$i] + (float)$panel_array[$i+1] + 1.0) / 2.0;
           //Find the midpoint.
        $center_base      =      ($decimal_time - $midpoint) / $span;
           //Find the normalized distance from the midpoint.
        $center_square    =      $center_base * $center_base;
           //Square it to get a monotonic function of distance..  Perhaps cheaper than absolute value.
        
        if ($center_square < $least_center_square)  //If we have a winner.
           {
           $best = $i/2;                            //Record the subscript.
           $least_center_square = $center_square;   //Record the best square.
           }     
        }
     }

  return($best);  
  }
//
//--------------------------------------------------------------------------------------------------------------
//For a given panel (numbered starting at 0), returns the time midpoint expressed as a T4.
//
function TOD_panel_center_t4($panel)
  {
  global $CONFIG_SCHED_DAY_PANELS;

  $ll = $CONFIG_SCHED_DAY_PANELS[$panel * 2];
  $ul = $CONFIG_SCHED_DAY_PANELS[$panel * 2 + 1];

  $midpoint_whole = (int)(($ll + $ul + 1) / 2);
  $midpoint_frac  = ($ll + $ul + 1) % 2;         //0 if whole, 1 if half.

  $whole_string = sprintf("%02d", $midpoint_whole);
 
  if ($midpoint_frac)
     $frac_string = "30";
  else
     $frac_string = "00";

  return($whole_string . $frac_string);
  }
//
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: tod.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
