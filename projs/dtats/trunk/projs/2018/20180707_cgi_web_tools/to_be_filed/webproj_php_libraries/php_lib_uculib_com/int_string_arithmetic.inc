<?php
//********************************************************************************
//Copyright (C) 2007 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or
//modify it under the terms of the GNU Lesser General Public License as published
//by the Free Software Foundation; either version 2 of the License, or (at your
//option) any later version.
//
//This program or source file is distributed in the hope that it will
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU Lesser General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//This file implements arithmetic functions on integers (typically large 
//integers) represented as string.  These functions are used as a layer above
//the bcmath functions, in case this set of web pages must be implemented on
//a version of PHP without bcmath compiled in.  In this event, the functions
//in this file can be replaced with (slower) PHP functions that perform
//the arithmetic on strings directly in PHP.  As most of the algorithms on this
//set of web pages are O(log N) this _should_ work, but it hasn't been
//evaluated for speed.
//--------------------------------------------------------------------------------
//Notes on canonical form:  for use with the numerical functions in this
//library, the following conventions apply:
//   a)Zero has one representation, "0".
//   b)On non-zero numbers, no leading 0's are allowed.
//   c)Positive numbers have no leading "+", but negative numbers have a
//     leading "-".
//   d)No commas, spaces, or extraneous characters are allowed.
//   e)The string "INAN" is allowed to indicate that the integer is not a
//     number.  Combining "INAN" with any other number in any other
//     operation results in "INAN".
//
//The notes above apply only to the form used for calculation.  For presentation
//in human-readable form, commas are allowed, and functions are provided to
//convert back and forth.
//--------------------------------------------------------------------------------
//Notes on the "scale" parameter to the bcmath functions ... this is provided on
//all calls that accept it in order to override the default value set via
//the bcscale() function.  Although it should have no effect with natural numbers,
//it is provided to provide a more consistent environment and to head off
//bugs.
//--------------------------------------------------------------------------------
require_once("strfunc.inc");
//
//--------------------------------------------------------------------------------
//Result codes that may be returned from functions.  These are integers designed
//to be masked.  Since all known PHP implementations use 32-bit or larger
//integers, at least 31 bits are available.
define("ISARITH_RC_UPERROR",                                         0x00000001);
   //An unidentified parse error occurred.
define("ISARITH_RC_EMPTY_STRING",                                    0x00000002);
   //A request was made to parse the empty string.
define("ISARITH_RC_ICHAR",                                           0x00000004);
   //Illegal character(s) other than space or tab were encountered as part of 
   //the parse.
define("ISARITH_RC_GAP",                                             0x00000008);
   //The string to be parsed contained space or tab gaps.
define("ISARITH_RC_BADLIMIT",                                        0x00000010);
   //The limits (min, max) passed in were bad or not parseable.
define("ISARITH_RC_NOTWHOLENUM",                                     0x00000020);
   //The number supplied is not an integer (the mantissa and exponent
   //create a number with a fractional part).
define("ISARITH_RC_IINAN",                                           0x00000040);
   //INAN was encountered during the parse, while the parse parameters 
   //indicated that INAN is not allowed.
define("ISARITH_RC_2SMALL",                                          0x00000080);
   //The value as parsed was smaller than allowed.
define("ISARITH_RC_2LARGE",                                          0x00000100);
   //The value as parsed was larger than allowed.
define("ISARITH_RC_SIGNPARSE",                                       0x00000200);
   //Multiple or conflicting mantissa signs were allowed.
define("ISARITH_RC_DPPARSE",                                         0x00000400);
   //Multiple decimal points were found.
define("ISARITH_RC_EXPMPARSE",                                       0x00000800);
   //Multiple exponent markers (e or E) were found.
define("ISARITH_RC_EMSGN",                                           0x00001000);
   //Multiple or conflicting exponent signs were found
//--------------------------------------------------------------------------------
//Codes to specify behavior when non-integers are encountered.
define("ISARITH_NIB_INTEGERSONLY",                                            0);
   //Numbers with fractional parts simply aren't allowed.  Refuse to do the
   //conversion and return ISARITH_RC_NOTWHOLENUM.
define("ISARITH_NIB_ROUNDNEAREST",                                            1);
   //Round to the nearest integer with no exceptions.  Values that are halfway
   //are rounded to the integer of larger magnitude.
   //      3.1   -->   3
   //     -3.1   -->  -3
   //      2.9   -->   3
   //     -2.9   -->  -3
   //      3.5   -->   4
   //     -3.5   -->  -4
define("ISARITH_NIB_ROUNDLESSER",                                             2);
   //Round to the lesser integer, with "lesser" being strictly defined as
   //more to the left on the number line.
   //      3.1   -->   3
   //     -3.1   -->  -4
   //      2.9   -->   2
   //     -2.9   -->  -3
   //      3.5   -->   3
   //     -3.5   -->  -4
define("ISARITH_NIB_ROUNDGREATER",                                            3);
   //Round to the greater integer, with "greater" being strictly defined as
   //more to the right on the number line.
   //      3.1   -->   4
   //     -3.1   -->  -3
   //      2.9   -->   3
   //     -2.9   -->  -2
   //      3.5   -->   4
   //     -3.5   -->  -3
define("ISARITH_NIB_ROUNDLESSERMAG",                                          4);
   //Round to the integer of lesser magnitude.
   //      3.1   -->   3
   //     -3.1   -->  -3
   //      2.9   -->   2
   //     -2.9   -->  -2
   //      3.5   -->   3
   //     -3.5   -->  -3
define("ISARITH_NIB_ROUNDGREATERMAG",                                         5);
   //Round to the integer of greater magnitude.
   //      3.1   -->   4
   //     -3.1   -->  -4
   //      2.9   -->   3
   //     -2.9   -->  -3
   //      3.5   -->   4
   //     -3.5   -->  -4
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//----  S T A T I C  -------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Trims the leading 0's from a string representing a signed or unsigned
//integer.  The string may have a sign, but may have no spaces or commas.
//
//If final result is "-0", changed to "0".
//
function ISARITH_trim_leading_zeros($arg)
   {
   //Be sure the argument is a string.
   $arg = (string)$arg;

   if (strlen($arg) != 0)
      {
      if (SubStr($arg, 0, 1) == "-")
         {
         //Argument has a minus sign.
         while(
                 (strlen($arg) >= 3)
                 &&
                 (SubStr($arg, 1, 1) == "0")
              )
            {
            $arg = "-" . SubStr($arg, 2);
            }

         if (strcmp("-0", $arg) == 0)
            {
            $arg = "0";
            }
         }
      else
         {
         //Argument has no minus sign.
         while(
                 (strlen($arg) >= 2)
                 &&
                 (SubStr($arg, 0, 1) == "0")
              )
            {
            $arg = SubStr($arg, 1);
            }
         }

      return($arg);
      }
   else
      {
      //Empty string?
      return($arg);
      }
   }
//
//--------------------------------------------------------------------------------
//Passed an integer representing the bit mask of error codes from a function
//in this module, returns an array of symbolic tags indicating the
//codes.  If no tags, FALSE is returned.
//
function ISARITH_integer_to_result_code_array($i_in)
   {
   if (!is_int($i_in))
      return(FALSE);
   else if ($i_in == 0)
      return(FALSE);
   else
      {
      if ($i_in & ISARITH_RC_UPERROR)
         $rv[] = "ISARITH_RC_UPERROR";
      if ($i_in & ISARITH_RC_EMPTY_STRING)
         $rv[] = "ISARITH_RC_EMPTY_STRING";
      if ($i_in & ISARITH_RC_ICHAR)
         $rv[] = "ISARITH_RC_ICHAR";
      if ($i_in & ISARITH_RC_GAP)
         $rv[] = "ISARITH_RC_GAP";
      if ($i_in & ISARITH_RC_BADLIMIT)
         $rv[] = "ISARITH_RC_BADLIMIT";
      if ($i_in & ISARITH_RC_NOTWHOLENUM)
         $rv[] = "ISARITH_RC_NOTWHOLENUM";
      if ($i_in & ISARITH_RC_IINAN)
         $rv[] = "ISARITH_RC_IINAN";
      if ($i_in & ISARITH_RC_2SMALL)
         $rv[] = "ISARITH_RC_2SMALL";
      if ($i_in & ISARITH_RC_2LARGE)
         $rv[] = "ISARITH_RC_2LARGE";
      if ($i_in & ISARITH_RC_SIGNPARSE)
         $rv[] = "ISARITH_RC_SIGNPARSE";
      if ($i_in & ISARITH_RC_DPPARSE)
         $rv[] = "ISARITH_RC_DPPARSE";
      if ($i_in & ISARITH_RC_EXPMPARSE)
         $rv[] = "ISARITH_RC_EXPMPARSE";
      if ($i_in & ISARITH_RC_EMSGN)
         $rv[] = "ISARITH_RC_EMSGN";

      if (!isset($rv))
         $rv = FALSE;

      return($rv);
      }   
   }
//
//--------------------------------------------------------------------------------
//Forms a decimal number based on the predecimal and postdecimal parts, which
//may have had leading and trailing zeros (respectively) removed.
//
function ISARITH_form_decimal_number($pre_d, $post_d)
   {
   if (! strlen($pre_d) && ! strlen($post_d))
      {
      //Both strings evaluated to 0's that could be trimmed, 0.0
      //is the right replacement.
      $rv = "0.0";
      }
   else if (! strlen($pre_d) && strlen($post_d))
      {
      //The pre-decimal point value is the empty string, but the
      //post isn't.  0.Y is the right answer.
      $rv = "0." . $post_d;
      }
   else if (strlen($pre_d) && ! strlen($post_d))
      {
      //The post-decimal point value is the empty string, but the
      //pre isn't.  X is the right answer.
      $rv = $pre_d;
      }
   else
      {
      //Both are non-empty.
      $rv = $pre_d . "." . $post_d;
      }

   return($rv);

   }
//
//--------------------------------------------------------------------------------
//Assigns an arbitrarily long integer from a string.  The string is converted
//to a simple integer, if possible.
//
//There are no limits on this function, so it would be possible to cause an
//out of memory or other condition by passing in an argument with an exponent
//of large absolute value.  This function should be reserved for contexts
//where user input isn't the source or where it has already been sanitized.
//
//This function will accept strings to parse in a more relaxed format
//than canonical form (it parses things into canonical form).  The
//specific relaxations are:
//   a)A unary "+" is allowed, even on "0".
//   b)Unary "-" is allowed even on "0".
//   c)Commas are allowed, and need not be properly placed.  Commas may occur
//     even in exponents.
//
//The input string must be sanitized of spaces and tabs, even leading and trailing
//ones.  The responsibility of removing these was deliberately pushed off onto the
//caller.
//
//Allowable formats are:
//   a)Integer format (i.e. "25", "-2,352", "+325", etc.).
//   b)Scientific notation, i.e. "3.12451234e+23".
//   c)Optionally, "INAN".
//
function ISARITH_int_parse_and_separate
   (
    $in_i2parse,
      //The string to parse.  As mentioned above, all characters not to be
      //considered, including leading and trailing blanks and tabs.  The design
      //decision to push this off on the caller was deliberate, as it gives the
      //caller more latitude to decide what is allowed and not.
    $in_inan_allowed,
      //TRUE if INAN is allowed as an input string, or FALSE otherwise.
    $in_debug,
      //Flag, per the rules for PHP Boolean interpretation, that indicates whether to
      //provide debug information per the $debug_out variable.
   &$out_parse_errs,
      //An integer reflecting a bitmask of errors (or lack thereof) encountered during
      //the parse.  Zero is the only value which will result in the output values being
      //all usable.  The output values should not be used (values are undefined) if
      //parse errors were encountered.
   &$out_is_inan,
      //TRUE if the value was parsed as INAN, FALSE otherwise.
   &$out_mant_sign,
      //The sign character of the mantissa.  This will be either "" (no sign specified),
      //"-" (minus sign specified), or "+" (plus sign specified).  
   &$out_mant_pre_dec,
      //The mantissa, with commas removed, before the decimal point.  If no decimal
      //point is specified, this would contain the only digits.  If no digits
      //appear before the decimal point, this may be "".  All leading 0's are
      //removed, so if a number such as "0.9" or "0.0" is specified, this may be "".
   &$out_mant_post_dec,
      //The mantissa, with commas removed, after the decimal point.  All trailing
      //0's are removed, possibly resulting in "".
   &$out_exp_sign,
      //The sign of the exponent, "", "-", or "+".
   &$out_exp_digits,
      //The digits of the exponent, with leading 0's removed.  No exponent specified
      //or a number such as "3.14e+00" will result in an empty string here.
   &$out_display_value_scimatch,
      //If the integer to parse contained errors, the suggested display value to allow the user
      //to correct them.  If the integer to parse contained no errors, the suggested display
      //value.  With this string, the user's choice of scientific notation or not is matched in the
      //output.  Unlike other fields, if there were errors encountered, this will not be
      //FALSE (it will always be a string).
   &$out_debug
       //If $debug_in is TRUE, this will be populated with an array of strings containing
       //debug information, otherwise this variable will be FALSE.
   )
   {
   //Assign initial values.  This sets the type as well.
   $out_parse_errors           = 0;
   $out_is_inan                = FALSE;
   $out_mant_sign              = "";
   $out_mant_pre_dec           = "";
   $out_mant_post_dec          = "";
   $out_exp_sign               = "";
   $out_exp_digits             = "";
   $out_display_value_scimatch = "";

   //Set up for debug information.
   if ($in_debug)
      {
      $debug_separator = "- - - - - - - - - - - - - - - - - - - - - - - - - - -";
      $out_debug[]     = $debug_separator;
      $out_debug[]     = "ISARITH_assign_from_string_nolimit() Debug Information";
      $out_debug[]     = $debug_separator;
      }
   else
      {
      $out_debug   = FALSE;
      }

   //Guard against empty string.
   $in_i2parse = (string)$in_i2parse;
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Empty string.  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = "";
      $out_parse_errs = ISARITH_RC_EMPTY_STRING;
      return;
      }

   //Handle the "INAN" case.
   if (strcmp($in_i2parse, "INAN") == 0)
      {
      if ($in_inan_allowed)
         {
         //INAN is allowed, and we have it.  Return INAN.
         if ($in_debug)
            {
            $out_debug[] = "(Line " . __LINE__ . ") INAN found and allowed.  Returning.";
            $out_debug[] = $debug_separator;
            }

         $out_is_inan = TRUE;
         return;
         }
      else
         {
         //INAN is not allowed, but we have it.  This is an error.
         if ($in_debug)
            {
            $out_debug[] = "(Line " . __LINE__ . ") INAN found and not allowed.  Returning.";
            $out_debug[] = $debug_separator;
            }

         $out_parse_errs = ISARITH_RC_IINAN;
         return;
         }
      }

   //Guard against invalid characters that are strongly disallowed
   //(characters even more illegal than spaces or tabs).
   if (! STRFUNC_is_char_subset($in_i2parse, " \t+-.,eE0123456789"))
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Illegal character (more extreme than space or tab) found.  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = STRFUNC_force_into_subset($in_i2parse, " \t+-.,eE0123456789");
      $out_parse_errs = ISARITH_RC_ICHAR;
      return;
      }

   //Guard against space/tab gaps, which are not allowed.
   if (! STRFUNC_is_char_subset($in_i2parse, "+-.,eE0123456789"))
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Space or tab gaps found.  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = STRFUNC_force_into_subset($in_i2parse, "+-.,eE0123456789");
      $out_parse_errs = ISARITH_RC_GAP;
      return;
      }

   //Trim any commas from the string.  These are by and large ignored.
   $in_i2parse = STRFUNC_force_into_subset($in_i2parse, "+-.eE0123456789");

   //If we created an empty string, this is a gross
   //parse error.
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error (empty string as intermediate result).  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = "";
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Strip off any leading "-" and "+" signs of the mantissa.
   $out_mant_sign              = "";
   while
      (
         (strlen($in_i2parse) != 0)
         &&
         (
            (SubStr($in_i2parse, 0, 1) == "-")
            ||
            (SubStr($in_i2parse, 0, 1) == "+")
         )
      )
      {
      if (SubStr($in_i2parse, 0, 1) == "-")
         {
         if (strlen($out_mant_sign))
            {
            //We are finding a second sign character.  Not allowed.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Second sign character found (illegal).  Returning.";
               $out_debug[] = $debug_separator;
               }

            $out_display_value_scimatch = $in_i2parse;
            $out_parse_errs = ISARITH_RC_SIGNPARSE;
            return;
            }
         else
            {
            //Found a first minus sign.  Record it.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Found a single minus sign (legal).";
               }

            $out_mant_sign = "-";
            }
         }
      else if (SubStr($in_i2parse, 0, 1) == "+")
         {
         if (strlen($out_mant_sign))
            {
            //We are finding a second sign character.  Not allowed.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Second sign character found (illegal).  Returning.";
               $out_debug[] = $debug_separator;
               }

            $out_display_value_scimatch = $in_i2parse;
            $out_parse_errs = ISARITH_RC_SIGNPARSE;
            return;
            }
         else
            {
            //Found a plus sign.  Record it.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Plus sign found (legal).";
               }

            $out_mant_sign = "+";
            }
         }

      //Strip the character.
      $in_i2parse = SubStr($in_i2parse, 1);
      } //End while()

   //If we created an empty string, this is a gross
   //parse error.
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error (empty string as intermediate result).  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = "";
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of mantissa sign is \"" .
                     $in_i2parse . "\".";
      }

   //The next item has to be a decimal point or a digit, otherwise
   //the mantissa is effectively missing.
   if (! STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), ".0123456789"))
      {
      if ($in_debug)
         {
         $debug_out[] = "(Line " . __LINE__ . ") Decimal point or digit not found when starting to parse mantissa.  Returning.";
         }

      $out_display_value_scimatch = $out_mant_sign . $in_i2parse;
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Remove the digits, if any before the decimal point, if any.
   while (
            (strlen($in_i2parse))
            &&
            (STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "0123456789"))
         )
      {
      $out_mant_pre_dec .= SubStr($in_i2parse, 0, 1);
      $in_i2parse        = SubStr($in_i2parse, 1);
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of mantissa pre-decimal digits is \"" .
                     $in_i2parse . "\".";
      }

   //Remove any leading 0's from the string.  This may result in "".
   while 
      (
         (strlen($out_mant_pre_dec))
         &&
         (SubStr($out_mant_pre_dec, 0, 1) == "0")
      )
      {
      $out_mant_pre_dec = SubStr($out_mant_pre_dec, 1);
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") out_mant_pre_dec after removal of leading 0's is \"" .
                     $out_mant_pre_dec . "\".";
      }

   //If we have an empty string, this is a permissible exit point.  This would be an integer with
   //no frills.
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Plain integer detected.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = $out_mant_sign . $out_mant_pre_dec;
      return;
      }

   //Remove the decimal point, if any.
   if (STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "."))
      {
      $in_i2parse = SubStr($in_i2parse, 1);
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of decimal point is \"" .
                     $in_i2parse . "\".";
      }

   //Remove the digits, if any, after the decimal point.
   while (
            (strlen($in_i2parse))
            &&
            (STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "0123456789"))
         )
      {
      $out_mant_post_dec .= SubStr($in_i2parse, 0, 1);
      $in_i2parse         = SubStr($in_i2parse, 1);
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of mantissa post-decimal digits is \"" .
                     $in_i2parse . "\".";
      }

   //Remove any trailing 0's from the string.  This may result in "".
   while 
      (
         (strlen($out_mant_post_dec))
         &&
         (SubStr($out_mant_post_dec, strlen($out_mant_post_dec) - 1, 1) == "0")
      )
      {
      $out_mant_post_dec = SubStr($out_mant_post_dec, 0, strlen($out_mant_post_dec) - 1);
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") out_mant_post_dec after removal of trailing 0's is \"" .
                     $out_mant_post_dec . "\".";
      }

   //If we're here and have an empty string, this is an allowed parsing exit.
   //It corresponds to entering a decimal number without an exponent where an
   //integer is required.  This is probably a misunderstanding of some sort, but
   //the caller should deal with it (not this function).
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Plain decimal number detected.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
      return;
      }

   //The next character has to be an "E" or "e".  If it isn't, this is a gross
   //parsing error.
   if (StrToUpper(SubStr($in_i2parse, 0, 1)) != "E")
      {
      //The character is not an "E" or "e".  Gross parsing error.

      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error, E/e not in place.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
         //Should ignore the stuff we can't parse.  Just form the mantissa.
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }
 
   //Remove the "E" or "e" character.
   $in_i2parse = SubStr($in_i2parse, 1);

   //If we created an empty string, this is a gross
   //parse error.
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error (empty string as intermediate result).  Returning.";
         $out_debug[] = $debug_separator;
         }
 
      $out_display_value_scimatch = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
         //Should ignore the stuff we can't parse.  Just form the mantissa.
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of E/e is \"" .
                     $in_i2parse . "\".";
      }

   //The next character has to be a sign character or a digit.  If not, gross parsing error.
   if (! STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "+-0123456789"))
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error, char after E/e invalid.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
         //Should ignore the stuff we can't parse.  Just form the mantissa.
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Strip off and record the exponent sign, if any.  There can be only one.
   $out_exp_sign              = "";
   while
      (
         (strlen($in_i2parse) != 0)
         &&
         (
            (SubStr($in_i2parse, 0, 1) == "-")
            ||
            (SubStr($in_i2parse, 0, 1) == "+")
         )
      )
      {
      if (SubStr($in_i2parse, 0, 1) == "-")
         {
         if (strlen($out_exp_sign))
            {
            //We are finding a second sign character.  Not allowed.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Second exponent sign character found (illegal).  Returning.";
               $out_debug[] = $debug_separator;
               }

            $out_display_value_scimatch 
               = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
            $out_parse_errs = ISARITH_RC_EMSGN;
            return;
            }
         else
            {
            //Found a first minus sign.  Record it.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Found a single exponent minus sign (legal).";
               }

            $out_exp_sign = "-";
            }
         }
      else if (SubStr($in_i2parse, 0, 1) == "+")
         {
         if (strlen($out_exp_sign))
            {
            //We are finding a second exponent sign character.  Not allowed.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Second exponent sign character found (illegal).  Returning.";
               $out_debug[] = $debug_separator;
               }

            $out_display_value_scimatch 
               = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
            $out_parse_errs = ISARITH_RC_EMSGN;
            return;
            }
         else
            {
            //Found a plus sign.  Record it.
            if ($in_debug)
               {
               $out_debug[] = "(Line " . __LINE__ . ") Exponent plus sign found (legal).";
               }

            $out_exp_sign = "+";
            }
         }

      //Strip the character.
      $in_i2parse = SubStr($in_i2parse, 1);
      } //End while()

   //If we created an empty string, this is a gross
   //parse error.
   if (strlen($in_i2parse) == 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error (empty string as intermediate result).  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = "";
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of exponent sign is \"" .
                     $in_i2parse . "\".";
      }

   //The next character has to be a digit.  If not, gross parsing error.
   if (! STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "0123456789"))
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error, exponent digits not as expected.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = $out_mant_sign . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
         //Should ignore the stuff we can't parse.  Just form the mantissa.
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Remove the exponent digits.
   while (
            (strlen($in_i2parse))
            &&
            (STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "0123456789"))
         )
      {
      $out_mant_exp_digits .= SubStr($in_i2parse, 0, 1);
      $in_i2parse           = SubStr($in_i2parse, 1);
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") String created after removal of exponent digits is \"" .
                     $in_i2parse . "\".";
      }

   //Remove any leading 0's from the exponent.  This may result in "".
   while 
      (
         (strlen($out_exp_digits))
         &&
         (SubStr($out_exp_digits, 0, 1) == "0")
      )
      {
      $out_exp_digits = SubStr($out_exp_digits, 1);
      }

   //At this point, the string must be empty, otherwise there was stuff at the
   //end of the number that is not digits.
   if (strlen($in_i2parse) != 0)
      {
      if ($in_debug)
         {
         $out_debug[] = "(Line " . __LINE__ . ") Gross parsing error (non-digits at end of string).  Returning.";
         $out_debug[] = $debug_separator;
         }

      $out_display_value_scimatch = "";
      $out_parse_errs = ISARITH_RC_UPERROR;
      return;
      }

   //Debug info.
   if ($in_debug)
      {
      $out_debug[] = "(Line " . __LINE__ . ") Setting up for normal non-error return.";
      }

   $out_display_value_scimatch =   $out_mant_sign 
                                 . ISARITH_form_decimal_number($out_mant_pre_dec, $out_mant_post_dec);
   if (strlen($out_exp_digits))
      {
      $out_display_value_scimatch =    $out_display_value_scimatch
                                     . "e"
                                     . $out_exp_sign
                                     . $out_exp_digits;
      }

   //Return fallthrough end of function.
   }
//--------------------------------------------------------------------------------
//Assigns an arbitrarily long integer from a string.  The string is converted
//to a simple integer, if possible.
//
//There are no limits on this function, so it would be possible to cause an
//out of memory or other condition by passing in an argument with an exponent
//of large absolute value.  This function should be reserved for contexts
//where user input isn't the source or where it has already been sanitized.
//
//This function will accept strings to parse in a more relaxed format
//than canonical form (it parses things into canonical form).  The
//specific relaxations are:
//   a)A unary "+" is allowed, even on "0".
//   b)Unary "-" is allowed even on "0".
//   c)Commas are allowed, and need not be properly placed.  Commas may occur
//     even in exponents.
//
//The input string must be sanitized of spaces and tabs, even leading and trailing
//ones.  The responsibility of removing these was deliberately pushed off onto the
//caller.
//
//Allowable formats are:
//   a)Integer format (i.e. "25", "-2,352", "+325", etc.).
//   b)Scientific notation, i.e. "3.12451234e+23".
//   c)Optionally, "INAN".
//
function ISARITH_assign_from_string_nolimit
   (
    $in_i2parse,
       //The string to parse.  As mentioned above, all characters not to be
       //considered, including leading and trailing blanks and tabs.  The design
       //decision to push this off on the caller was deliberate, as it gives the
       //caller more latitude to decide what is allowed and not.
    $in_inan_allowed,
       //TRUE if INAN is allowed as an input string, or FALSE otherwise.
/*    $in_nonint_behavior, */
       //Behavior when non-integers are encountered (this may occur when a number is specified
       //in scientific notation).
   &$out_val,
       //The output value parsed, as a simple integer string.  This value will be
       //FALSE iff there are errors.
   &$out_errs,
       //An integer reflecting a bitmask of errors (or lack thereof) encountered during
       //the parse.
    $debug_in,
       //Flag, per the rules for PHP Boolean interpretation, that indicates whether to
       //provide debug information per the $debug_out variable.
   &$debug_out
       //If $debug_in is TRUE, this will be populated with an array of strings containing
       //debug information, otherwise this variable will be FALSE.
   )
   {

   //Parse any digits before the decimal point, if there are any.
   $parse_digits_pre_dec = "";
   while (
            (strlen($in_i2parse) != 0)
            &&
            (STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "0123456789"))
         )
      {
      $parse_digits_pre_dec = $parse_digits_pre_dec . SubStr($in_i2parse, 0, 1);
      $in_i2parse = SubStr($in_i2parse, 1);
      }

   //Parse the decimal point, if any.  It is OK if we have an empty string
   //at this point.  There can be only one decimal point.
   $parse_decimal_point_found = FALSE;
   while
      (
         (strlen($in_i2parse) != 0)
         &&
         (SubStr($in_i2parse, 0, 1) == ".")
      )
      {
      if ($parse_decimal_point_found)
         {
         //Illegal.  Two decimal points.
         $out_errs = ISARITH_RC_DPARSE;
         return;
         }
      else
         {
         //Found a decimal point.  This is fine, so long as it is the first one.
         $parse_decimal_point_found = TRUE;
         }

      //Strip the character.
      $in_i2parse = SubStr($in_i2parse, 1);
      }

   //Consume any digits that may occur after the decimal point.
   $parse_digits_post_dec = "";
   while (
            (strlen($in_i2parse) != 0)
            &&
            (STRFUNC_is_char_subset(SubStr($in_i2parse, 0, 1), "0123456789"))
         )
      {
      $parse_digits_post_dec = $parse_digits_post_dec . SubStr($in_i2parse, 0, 1);
      $in_i2parse = SubStr($in_i2parse, 1);
      }

   //If the string remaining isn't empty, the only allowable character
   //is an "e" or "E".  Once we have the "e" or "E", we must have an optional
   //sign and the digits.
   $parse_exp_marker_found   = FALSE;
   $parse_exp_m_found        = FALSE;
   $parse_exp_p_found        = FALSE;
   $parse_exp_digits         = "";

   if (strlen($in_i2parse) != 0)
      {
      //Parse the exponent marker, if any.
      if (
            (SubStr($in_i2parse, 0, 1) == "e")
            ||
            (SubStr($in_i2parse, 0, 1) == "E")
         )
         {
         $parse_exp_marker_found = TRUE;

         //Strip the character.
         $in_i2parse = SubStr($in_i2parse, 1);
         }

      //If we created an empty string, this is a gross
      //parse error.
      if (strlen($in_i2parse) == 0)
         {
         $out_errs = ISARITH_RC_UPERROR;
         return;
         }

      //If there is a second exponent marker, this is a parse failure.
      if (
            (SubStr($in_i2parse, 0, 1) == "e")
            ||
            (SubStr($in_i2parse, 0, 1) == "E")
         )
         {
         $out_errs = ISARITH_RC_EXPMPARSE;
         return;
         }

      //Remove the optional sign from the exponent.  There can be only one.
      while
         (
            (strlen($in_i2parse) != 0)
            &&
            (
               (SubStr($in_i2parse, 0, 1) == "-")
               ||
               (SubStr($in_i2parse, 0, 1) == "+")
            )
         )
         {
         if (SubStr($in_i2parse, 0, 1) == "-")
            {
            if ($parse_exp_m_found || $parse_exp_p_found)
               {
               //We are finding a second sign character.  Not allowed.
               $out_errs = ISARITH_RC_EMSGN;
               return;
               }
            else
               {
               //Found a minus sign.  Record it.
               $parse_exp_m_found = TRUE;
               }
            }
         else if (SubStr($in_i2parse, 0, 1) == "+")
            {
            if ($parse_exp_m_found || $parse_exp_p_found)
               {
               //We are finding a second sign character.  Not allowed.
               $out_errs = ISARITH_RC_EMSGN;
               return;
               }
            else
               {
               //Found a plus sign.  Record it.
               $parse_exp_p_found = TRUE;
               }
            }

         //Strip the character.
         $in_i2parse = SubStr($in_i2parse, 1);
         }

      //If we created an empty string, this is a gross
      //parse error.
      if (strlen($in_i2parse) == 0)
         {
         $out_errs = ISARITH_RC_UPERROR;
         return;
         }

      //There have to be some digits now, after the "e"/"E" and the optional sign.
      if (!STRFUNC_is_char_subset($in_i2parse, "0123456789"))
         {
         $out_errs = ISARITH_RC_UPERROR;
         return;
         }
      else
         {
         //We have all digits left.  Just assign them and rip off the leading 0's
         //if any.
         $parse_exp_digits = $in_i2_parse;

         //TODO:  Rip off the 0's.  Will need to add a function to STRFUNCS.
         }

      } //End if characters remaining.
   else
      {
      //No exponent field.
      }


   //At this point, the following variables are assigned.
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //
   //

   }

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//----  A S S I G N M E N T  -----------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Assigns an arbitrarily long integer from a string.  The formats accepted are:
//  a)Integer format (i.e. "25", "-2,352", etc.).
//  b)Scientific notation, i.e. "3.12451234e+23".
//  c)Optionally, "INAN".
//
//It is the caller's responsibility to sanitize the string, including removing
//leading and trailing blanks or tabs.  This function by design requires a 
//string strictly as described above.
//
//The limits supplied should be chosen sanely to head off trouble with memory
//blowups.  The min and max limits will place limits on how exponents on the
//value to parsed are expanded.
//
function ISARITH_assign_from_string
   (
    $in_i2parse,
       //The string to parse.  As mentioned above, all characters not to be
       //considered, including leading and trailing blanks and tabs.  The design
       //decision to push this off on the caller was deliberate, as it gives the
       //caller more latitude to decide what is allowed and not.
    $in_inan_allowed,
       //TRUE if INAN is allowed as an input string, or FALSE otherwise.
    $in_pval_min,
    $in_pval_max,
       //The minimum and maximum values that the parsed input may attain.
       //If the parsed value goes outside this range, an error is returned.
   &$out_val,
       //The output value parsed, as a simple integer string.  This value will be
       //FALSE iff there are errors.
   &$out_errs
       //An integer reflecting the errors (or lack thereof) encountered during
       //the parse.
   )
   {
   //Assign default outputs.
   $out_val  = FALSE;
   $out_errs = 0;

   //Try to parse and assign the lower limit.  If this can't be parsed,
   //can't continue.
   ISARITH_assign_from_string_nolimit(
                                        $in_pval_min,
                                        FALSE,                   //INAN is invalid as a limit, lower or upper.
                                        $pval_min_expanded,
                                        $local_conversion_errs
                                     );

   if ($local_conversion_errs != 0)
      {
      //The minimum wouldn't parse successfully.  Repackage this error for the
      //caller and return.
      $out_errs = ISARITH_RC_BADLIMIT;
      return;
      }   

   //Try to parse and assign the upper limit.  If this can't be parsed,
   //can't continue.
   ISARITH_assign_from_string_nolimit(
                                        $in_pval_max,
                                        FALSE,                   //INAN is invalid as a limit, lower or upper.
                                        $pval_max_expanded,
                                        $local_conversion_errs
                                     );

   if ($local_conversion_errs != 0)
      {
      //The maximum wouldn't parse successfully.  Repackage this error for the
      //caller and return.
      $out_errs = ISARITH_RC_BADLIMIT;
      return;
      }   



   //Guts here.
   }

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
function ISARITH_cmp($in_n1, $in_n2)
   {
   $rv = bccomp($in_n1, $in_n2);

   return($rv);
   }
 
function ISARITH_add($in_n1, $in_n2)
   {
   $rv = bcadd($in_n1, $in_n2, 0);

   return($rv);
   }
 
function ISARITH_sub($in_n1, $in_n2)
   {
   $rv = bcsub($in_n1, $in_n2, 0);

   return($rv);
   } 

function ISARITH_mul($in_n1, $in_n2)
   {
   $rv = bcmul($in_n1, $in_n2, 0);

   return($rv);
   }
 
function ISARITH_div($in_n1, $in_n2)
   {
   $rv = bcdiv($in_n1, $in_n2, 0);

   return($rv);
   }
 
function ISARITH_mod($in_n1, $in_n2)
   {
   $rv = bcmod($in_n1, $in_n2);

   return($rv);
   }
 
function ISARITH_pow($in_base, $in_exponent)
   {
   $rv = bcpow($in_base, $in_exponent, 0);

   return($rv);
   }
 
function ISARITH_powmod($in_base, $in_exponent, $in_modulus)
   {
   $rv = bcpowmod($in_base, $in_exponent, $in_modulus, 0);

   return($rv);
   }

function ISARITH_sqrt($in_arg)
   {
   $rv = bcsqrt($in_arg, 0);

   //Untested ... will need to sure above does not round.

   return($rv);
   }

//Commanates.
//
function ISARITH_commanate($in_arg)
   {
   $prefix = "";
   if (SubStr($in_arg, 0, 1) == "-")
      {
      $prefix = "-";
      $in_arg = SubStr($in_arg, 1);
      }

   $rv = "";
   while (strlen($in_arg) > 3)
      {
      $rv = "," . SubStr($in_arg, strlen($in_arg)-3) . $rv;
      $in_arg = SubStr($in_arg, 0, strlen($in_arg)-3);
      }

   $rv = $prefix . $in_arg . $rv;

   return($rv);
   }

//Commanates, but adds a string passed at the end of every
//groupcount of groups of 3 digits, as a separator.
//
function ISARITH_commanate_wtext($in_arg, $in_groupcount, $in_groupsuffix)
   {
   $prefix = "";
   if (SubStr($in_arg, 0, 1) == "-")
      {
      $prefix = "-";
      $in_arg = SubStr($in_arg, 1);
      }

   $rv = "";
   $groupnum = 0;

   while (strlen($in_arg) > 3)
      {
      $groupnum++;
      if (($groupnum % $in_groupcount) == 0)
         $rv = "," . $in_groupsuffix . SubStr($in_arg, strlen($in_arg)-3) . $rv;
      else
         $rv = "," . SubStr($in_arg, strlen($in_arg)-3) . $rv;

      $in_arg = SubStr($in_arg, 0, strlen($in_arg)-3);
      }

   $rv = $prefix . $in_arg . $rv;

   return($rv);
   }

function ISARITH_decommanate($in_arg)
   {
   $rv = STRFUNC_force_into_subset($in_arg, "-0123456789");

   return($rv);
   }
?>
