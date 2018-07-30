<?php
require_once("style/std/stdwpstyle.inc");
//----------------------------------------------------------------------------------------------------
//Copyright (c) 2003, 2018 David T. Ashley.
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//----------------------------------------------------------------------------------------------------
//
//Returns TRUE if the passed argument is a digit, or FALSE otherwise.  If the
//passed string has length > 1, only the least significant digit is
//considered.
function euclid_gcd_isdigit($Digit)
   {
   $Digit = (string)$Digit;

   //If the string has zero length, this is an error condition and return 0.
   $Length = strlen($Digit);  

   if ($Length==0)
      {
      return(0);
      }

   //Obtain the trailing character of the string.
   $Trailing_char = Substr($Digit, $Length-1, 1);

   //Do a switch and return an integer based on the character.
   switch($Trailing_char)
      {
      case "9":
	 return 1;
         break;
      case "8":
	 return 1;
	 break;
      case "7":
	 return 1;
	 break;
      case "6":
	 return 1;
	 break;
      case "5":
	 return 1;
	 break;
      case "4":
	 return 1;
	 break;
      case "3":
	 return 1;
	 break;
      case "2":
	 return 1;
	 break;
      case "1":
	 return 1;
	 break;
      case "0":
	 return 1;
	 break;
      default:
	 return 0;
         break;
      }
   }
//
//
//Returns TRUE if the passed argument is a simple integer (no error   
//codes, no commas), or FALSE otherwise.
function euclid_gcd_issimpleint($Intnum)
   {
   $Intnum = (string)$Intnum;

   //If the string has zero length, this is an error condition and return 0.
   $Length = strlen($Intnum);  

   if ($Length==0)
      {
      return(0);
      }

   //If the first digit is "0", this must be the only character in the string,
   //otherwise there is a leading-zero violation.
   if (Substr($Intnum, 0, 1)=="0")
      {
      if ($Length==1)
	 {
	 return 1;
	 }
      else
	 {
	 return 0;
	 }
      }

   //If the first character is a "-" sign, it may not be the only character,
   //and it may not precede a "0" (which would again be a leading 0 violation).
   //If it is a "-", we can exclude "0" and parse as a positive.
   if (Substr($Intnum, 0, 1)=="-")
      {
      if ($Length==1)
	 {
	 return 0;
	 }
      else
	 {
	 if (Substr($Intnum, 1, 1) == "0")
	    {
	    //This is illegal (a "-" followed by a "0").
	    return 0;
	    }
	 else
	    {
	    //We can just remove the "-" and parse as a positive.
	    $Intnum = Substr($Intnum, 1, $Length - 1);
	    $Length--;
	    }
	 }
      }

   //It is known at this point that the length is at least 1 and the leading 
   //character is not zero.  All we need to do at this point is check that each 
   //and every character is a digit.
   for ($index=0; $index < $Length; $index++)
      {
      if (!euclid_gcd_isdigit(Substr($Intnum, $index, 1)))
         return 0;
      }

   return 1;
   }
//
//
//Returns the number of digits in the argument, which must be a valid simple
//integer.
function euclid_gcd_ndigits($Intnum)
   {
   $Intnum = (string)$Intnum;

   if (Substr($Intnum, 0, 1) == "-")
      {
      $rv = strlen($Intnum) - 1;
      }
   else
      {
      $rv = strlen($Intnum);
      }

   return($rv);
   }
//
//
//Given a string, converts the final character to an integer.  If the character
//is not a digit, returns 0.
function euclid_gcd_digittoint($Digit)
   {
   //echo "Digit is: ";
   //echo $Digit;
   //echo "<br>";

   $Digit = (string)$Digit;

   //echo "Digit is: ";
   //echo $Digit;
   //echo "<br>";
   
   //If the string has zero length, this is an error condition and return 0.
   $Length = strlen($Digit);  

   //echo "Length is: ";
   //echo $Length;
   //echo "<br>";

   if ($Length==0)
      {
      return(0);
      }

   //Obtain the trailing character of the string.
   $Trailing_char = Substr($Digit, $Length-1, 1);

   //echo "Trailing char is: ";
   //echo $Trailing_char;
   //echo "<br>";

   //Do a switch and return an integer based on the character.
   //The default case gives 0.

   switch($Trailing_char)
      {
      case "9":
	 return 9;
         break;
      case "8":
	 return 8;
	 break;
      case "7":
	 return 7;
	 break;
      case "6":
	 return 6;
	 break;
      case "5":
	 return 5;
	 break;
      case "4":
	 return 4;
	 break;
      case "3":
	 return 3;
	 break;
      case "2":
	 return 2;
	 break;
      case "1":
	 return 1;
	 break;
      default:
	 return 0;
         break;
      }
   }

//Decommanates an integer and removes all other crap without respect for 
//whether the commas are in the right place or the integer is syntactically valid.
function euclid_gcd_decommanate(&$arg)
   {
   $temp = "";

   $len = strlen($arg);

   for ($i=0; $i<$len; $i++)
      {
      $c = (string)Substr($arg, $i, 1);
   
      if (euclid_gcd_isdigit($c) || ($c == "-"))
         $temp = $temp . $c;
      }

   $arg = (string)$temp;
   } 

//Commanates an integer which is assumed to by syntactically correct.
function euclid_gcd_commanate(&$arg)
   {
   euclid_gcd_decommanate($arg);
 
   $temp = "";
  
   $len = strlen($arg);

   for ($i=0; $i<$len; $i++)
      {
      $c = (string)Substr($arg, $len - $i - 1, 1);

      $temp = $c . $temp;
      
      if ($i != ($len-1))
	 {
	 if (Substr($arg, $len-$i-2, 1) != "-")
	    {
	    if (($i % 3) == 2)
	       $temp = "," . $temp;
	    }
	 }
      }

   $arg = (string)$temp;
   } 

function do_header(&$style)
   {
   $style->static_page_header_title_std("GCD Calculator (Euclid's Algorithm)",
			  "GCD Calculator",
			  "This cgi-bin form calculates the greatest common divisor of two positive " .
                          "integers using " .
                          "<a href=\"http://mathworld.wolfram.com/EuclideanAlgorithm.html\">Euclid's classic algorithm</a>.");
   }  

function do_footer(&$style)
   {
   //$style->static_page_hrule_std();
   //echo "<p align=\"center\">This utility is powered by the ";
   //echo "<a href=\"http://www.swox.com/gmp\"><img hspace=\"5\" vspace=\"5\" src=\"../genimages/gmplogo1.png\" width=\"232\" height=\"104\" align=\"absmiddle\"></a>.&nbsp; All source code is available ";
   //echo "<a href=\"../howtos/nth_web_gmp_src_code_dist/obtain_all_source.htm\">here</a>.</p>\n";
   $style->static_page_footer_std();
   }

function do_form($N1_refresh, $N2_refresh, $Buttontext, $max_gcd_digits)
   {
   echo "<form method=get action=\"index.php\" width=\"100%\">\n";
   echo "<table align=\"center\">\n";
   echo "<tr>\n";
   echo "  <td width=\"10%\">\n";
   echo "   <p align=\"right\"><b>N1</b> (" . number_format($max_gcd_digits) . "-digit maximum):</td>\n";
   echo "    <td width=\"18%\"><p align=\"left\"><input type=\"text\" ";
   if (strlen($N1_refresh))
     {
     echo "value=\"" . $N1_refresh . "\" ";
     }
   echo "name=\"N1\" size=\"50\"></p></td>\n";
   echo "  </tr>\n";
   echo "  <tr>\n";
   echo "    <td width=\"10%\">\n";
   echo "   <p align=\"right\"><b>N2</b> (" . number_format($max_gcd_digits) . "-digit maximum):</td>\n";
   echo "    <td width=\"18%\"><p align=\"left\"><input type=\"text\" ";
   if (strlen($N2_refresh))
     {
     echo "value=\"" . $N2_refresh . "\" ";
     }
   echo "name=\"N2\" size=\"50\"></p></td>\n";
   echo "  </tr>\n";
   echo "  <tr>\n";
   echo "    <td width=\"20%\" colspan=\"2\">\n";
   echo "      <p align=\"center\"><input type=\"submit\" value=\"";
   echo $Buttontext;
   echo "\" name=\"B1\" style=\"margin-top: 12\"></td>\n";
   echo "  </tr>\n";
   echo "</table>\n";
   echo "</form>\n";
}

function do_err_msg($Err_msg)
   {
   echo "<p align=\"center\"><b><font color=\"#FF0000\">";
   echo $Err_msg;
   echo "</font></b></p>\n";
   }


//Main script begins here.
//
//Let's agree on a maximum for number of digits in either
//of the two arguments.  This has been checked out and seems
//to be within operational parameters (script won't time out).
$max_gcd_digits = 200;
//
$style = new StdWpStyle;
//Assign the current style in force.  Also, starts the CPU
//usage clock.

//Do the header unconditionally.  The header is always used on this page.
do_header($style);
//
if (isset($_GET['N1']))
   $N1 = $_GET['N1'];

if (isset($_GET['N2']))
   $N2 = $_GET['N2'];
   
//If N1 was supplied, decommanate it and be sure it is a string.
if (isset($N1))
   euclid_gcd_decommanate($N1);

//Same for N2.
if (isset($N2))
   euclid_gcd_decommanate($N2);
//
//There are a few cases to break into here, and this affects the overall layout of the page.
//The header and footer are fixed, but the "guts" will change.
if (!isset($N1) && !isset($N2))
   {
   //In this case, we are probably visiting the form for the first time, and have not done a submit.
   //Just display the form itself.
   do_form("", "", "Calculate GCD", $max_gcd_digits);
   }
elseif (!isset($N1) && isset($N2))
   {
   //Only $N2 is supplied.
     do_err_msg("You must supply both N1 and N2 to calculate a GCD. &nbsp;Only N2 was supplied.  &nbsp;Please try again.");
     $style->hrule_std();
     euclid_gcd_commanate($N2);  
     do_form("", $N2, "Calculate GCD", $max_gcd_digits);
   }  
elseif (isset($N1) && !isset($N2))
   {
   //Only $N1 is supplied.
     do_err_msg("You must supply both N1 and N2 to calculate a GCD. &nbsp;Only N1 was supplied.  &nbsp;Please try again.");
     $style->hrule_std();  
     euclid_gcd_commanate($N1);
     do_form($N1, "", "Calculate GCD", $max_gcd_digits);
   }  
elseif (!euclid_gcd_issimpleint($N1) || !euclid_gcd_issimpleint($N2))
   {
   //$N1 and $N2 are both supplied, but one or both is malformed.  Need to advise.
   if (!euclid_gcd_issimpleint($N1) && !euclid_gcd_issimpleint($N2))
      {
      do_err_msg("N1 and N2 are both malformed integers. &nbsp;Choose new values and try again.");
      $style->hrule_std();  
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      }
   elseif (!euclid_gcd_issimpleint($N1))
      {
      do_err_msg("N1 is a malformed integer. &nbsp;Choose a new value for N1 and try again.");
      $style->hrule_std();  
      euclid_gcd_commanate($N2);
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      }
   else
      {
      do_err_msg("N2 is a malformed integer. &nbsp;Choose a new value for N2 and try again.");
      $style->hrule_std();  
      euclid_gcd_commanate($N1);
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      } 
   }  
elseif ((strlen($N1) > $max_gcd_digits) || (strlen($N2) > $max_gcd_digits))
   {
   if ((strlen($N1) > $max_gcd_digits) && (strlen($N2) > $max_gcd_digits))
      {
      do_err_msg("N1 and N2 are both too long (a " . number_format($max_gcd_digits) . "-digit maximum is " .
                 "in effect).&nbsp; Choose shorter values and try again.");
      $style->hrule_std();  
      euclid_gcd_commanate($N1);
      euclid_gcd_commanate($N2);
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      }
   elseif (strlen($N1) > $max_gcd_digits)
      {
      do_err_msg("N1 is too long (a " . number_format($max_gcd_digits) . "-digit maximum is " .
                 "in effect).&nbsp; Choose a shorter value and try again.");
      $style->hrule_std();  
      euclid_gcd_commanate($N1);
      euclid_gcd_commanate($N2);
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      }
   else
      {
      do_err_msg("N2 is too long (a " . number_format($max_gcd_digits) . "-digit maximum is " .
                 "in effect).&nbsp; Choose a shorter value and try again.");
      $style->hrule_std();  
      euclid_gcd_commanate($N1);
      euclid_gcd_commanate($N2);
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      }
   }
else
   {
   //N1 and N2 were both supplied and seem to be valid integers.
   //
   //If either integer is negative, make it positive.
   if (Substr($N1, 0, 1)=="-")
     $N1 = Substr($N1, 1, strlen($N1)-1);
   if (Substr($N2, 0, 1)=="-")
     $N2 = Substr($N2, 1, strlen($N2)-1);

   //If either is "0", make it "1".
   if ($N1=="0")
     $N1 = (string)"1";
   if ($N2=="0")
     $N2 = (string)"1";

   //We can now run the external program to do the calculation.
   $cgi_command_string = "/hl/cgibin/aux_progs/dtats_cgi_aux_arith_large gcd " . $N1 . " " . $N2;
   //echo "CGI command string is : " . $cgi_command_string . "<br>\n";

   exec($cgi_command_string, $cgi_result);
   $cgi_result_nelem = count($cgi_result);

   //echo "Result is : " . $cgi_result_nelem . "<br>\n";

   //for ($i=0; $i<$cgi_result_nelem; $i++)
   //{
   //  echo $cgi_result[$i] . "<br>\n";
   //}

   //We need to perform some sanity checks on the CGI output to be sure it
   //is what we want.  If it seems wrong, we need to generate an error message
   //and not try to display the output.
   $cgi_output_is_sane = 1;
   if ($cgi_result_nelem == 0)
      $cgi_output_is_sane = 0;
   if ($cgi_result_nelem > 0)
      {
      if (($cgi_result_nelem % 5) != 0)
         $cgi_output_is_sane = 0;
      if ($cgi_result[0] != "S")
         $cgi_output_is_sane = 0;
      if ($cgi_result[$cgi_result_nelem - 1] != "S")
         $cgi_output_is_sane = 0;
      }

   if (!$cgi_output_is_sane)
      {
      do_err_msg("An unspecified error occurred when interacting with the CGI-BIN program.&nbsp; Please advise the webmaster.");
      $style->hrule_std();  
      euclid_gcd_commanate($N1);
      euclid_gcd_commanate($N2);
      do_form($N1, $N2, "Calculate GCD", $max_gcd_digits);
      }
   else
      {
      euclid_gcd_commanate($cgi_result[1]);
      euclid_gcd_commanate($cgi_result[2]);
      euclid_gcd_commanate($cgi_result[$cgi_result_nelem - 2]);

      echo "<p align=\"center\"><font size=\"4\">The greatest common divisor of ";
      echo $cgi_result[1];
      echo " and ";
      echo $cgi_result[2];
      echo " is ";
      echo $cgi_result[$cgi_result_nelem - 2];
      echo ".</font></p>\n";

      $style->static_page_hrule_std();  

      echo "<p align=\"left\"><b>Notes on the algorithm: &nbsp;</b>\n";
      echo "Euclid's classic GCD algorithm was known no later than about 200 B.C. and is documented \n";
      echo "at the \n";
      echo "<a href=\"http://mathworld.wolfram.com/EuclideanAlgorithm.html\">Wolfram Research site</a> \n";
      echo "and also in Knuth's classic reference work, ";
      echo "<a href=\"http://www.amazon.com/exec/obidos/tg/detail/-/0201896842/qid=1041826693/sr=8-2/ref=sr_8_2/102-1371170-8580943?v=glance&s=books&n=507846\"><i>The \n";
      echo "Art Of Computer Programming</i></a>. &nbsp;Euclid's GCD algorithm ends with the GCD being the \n";
      echo "last non-zero remainder (in yellow below unless <i>a</i> is a multiple of <i>b</i>).\n";
      echo "</p>\n";

      //Assign the table column widths.  They are centralized here for easy change.
      $width[0] = 5;
      $width[1] = 10;
      $width[2] = 10;
      $width[3] = 10;
      $width[4] = 10;

      echo "<table align=\"center\" border=\"1\" width=\"90%\">\n";

      for ($i=0; $i <= ($cgi_result_nelem/5 - 1); $i++)
         {
         echo "<tr>\n";

         echo "   <td width=\"" . $width[0] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>Round</b></p>\n";
	    }
         else
	    {
	    euclid_gcd_commanate($cgi_result[$i*5-2]);
	    echo "      <p align=\"center\">" . $cgi_result[$i*5-2] . "</p>\n";
	    }
         echo "   </td>\n";

         echo "   <td width=\"" . $width[1] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>a</b></p>\n";
	    }
         else
	    { 
	    euclid_gcd_commanate($cgi_result[$i*5-1]);
	    echo "      <p align=\"right\">" . $cgi_result[$i*5-1] . "</p>\n";
	    }
         echo "   </td>\n";

         echo "   <td width=\"" . $width[2] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>b</b></p>\n";
	    }
         else
	    {
	    euclid_gcd_commanate($cgi_result[$i*5]);
	    echo "      <p align=\"right\">" . $cgi_result[$i*5] . "</p>\n";
	    }
         echo "   </td>\n";

         echo "   <td width=\"" . $width[3] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>a <i>div</i> b</b></p>\n";
	    }
         else
	    {
	    euclid_gcd_commanate($cgi_result[$i*5+1]);
	    echo "      <p align=\"right\">" . $cgi_result[$i*5+1] . "</p>\n";
	    }
         echo "   </td>\n";

         if ($i > 0)
	    euclid_gcd_commanate($cgi_result[$i*5+2]);
         echo "   <td width=\"" . $width[4] . "%\"";
         if (($i > 0) && ($cgi_result[$i*5+2] == $cgi_result[$cgi_result_nelem - 2]))
	    echo " bgcolor=\"#FFFF00\"";      
         echo ">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>a <i>mod</i> b</b></p>\n";
	    }
         else
	    {
	    //euclid_gcd_commanate($cgi_result[$i*5+2]);
	    echo "      <p align=\"right\">" . $cgi_result[$i*5+2] . "</p>\n";
	    }
         echo "   </td>\n";

         echo "</tr>\n";
         }

      echo "</table><br>\n";
      $style->static_page_hrule_std();  

      euclid_gcd_commanate($N1);
      euclid_gcd_commanate($N2);
      do_form($N1, $N2, "Calculate Another GCD", $max_gcd_digits);
      }
   }

//Now do the footer unconditionally.  The footer is always used on this web page.
do_footer($style);  
?>
