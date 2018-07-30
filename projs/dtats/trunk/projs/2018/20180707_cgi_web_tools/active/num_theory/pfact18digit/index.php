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
function pfact18_isdigit($Digit)
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
function pfact18_issimpleint($Intnum)
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
      if (!pfact18_isdigit(Substr($Intnum, $index, 1)))
         return 0;
      }

   return 1;
   }
//
//
//Returns the number of digits in the argument, which must be a valid simple
//integer.
function pfact18_ndigits($Intnum)
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
function pfact18_digittoint($Digit)
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
function pfact18_decommanate(&$arg)
   {
   $temp = "";

   $len = strlen($arg);

   for ($i=0; $i<$len; $i++)
      {
      $c = (string)Substr($arg, $i, 1);
   
      if (pfact18_isdigit($c) || ($c == "-"))
         $temp = $temp . $c;
      }

   $arg = (string)$temp;
   } 

//Commanates an integer which is assumed to by syntactically correct.
function pfact18_commanate(&$arg)
   {
   pfact18_decommanate($arg);
 
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
   $style->static_page_header_title_std("[Attempted] Prime Factorization Of An Integer (18 Or Fewer Digits)",
			"Prime Factorization Of An Integer (18 Or Fewer Digits)",
			"This utility attempts to factor an integer of 18 or fewer digits into its " .
                        "prime components.");
   }  

function do_footer(&$style)
   {
//   $style->static_page_hrule_std();
//   echo "<p align=\"center\">This utility is powered by the ";
//   echo "<a href=\"http://www.swox.com/gmp\"><img hspace=\"5\" vspace=\"5\" src=\"../genimages/gmplogo1.png\" width=\"232\" height=\"104\" align=\"absmiddle\"></a>.&nbsp; All source code is available ";
//   echo "<a href=\"../howtos/nth_web_gmp_src_code_dist/obtain_all_source.htm\">here</a>.</p>\n";
   $style->static_page_footer_std();
   }

function do_form($N_refresh, $Buttontext)
   {
   echo "<form method=get action=\"index.php\" width=\"100%\">\n";
   echo "<table align=\"center\">\n";
   echo "<tr>\n";
   echo "  <td width=\"10%\">\n";
   echo "   <p align=\"right\"><b>N</b> (18-digit maximum):</td>\n";
   echo "    <td width=\"18%\"><p align=\"left\"><input type=\"text\" ";
   if (strlen($N_refresh))
     {
     echo "value=\"" . $N_refresh . "\" ";
     }
   echo "name=\"N\" size=\"50\"></p></td>\n";
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

//Prints algorithm notes with no extraneous HTML (no horizontal lines, etc.)
//
function pfact18_algorithm_notes($cgi_max)
 {
?>
<p><b><u>Algorithm Notes:</u></b></p>
<ul>
<li>This web page uses trial division combined with the 
<a href="http://mathworld.wolfram.com/EratosthenesSieve.html">Sieve of Eratosthenes</a> 
with a sieve of 2,310 = 2 * 3 * 5 * 7 * 11 elements.&nbsp; The
sieve is automatically generated, automatically compacted into a
difference table containing 480 elements, and packaged as a C-language source 
file containing a 480-element lookup table of 
integers.&nbsp; The algorithm checks divisibility by increasing trial divisors,
but it does so with all multiples of 2, 3, 5, 7, and 11 omitted (this is the
role of the Sieve of Eratosthenes).</li>
<li>Although this web page does factor effectively,
it is strictly "parlor amusement" grade, and will answer questions 
such as <i>Is the year I was born a prime number?</i> or <i>Is my street address
prime?</i>, but is inadequate for serious factoring.&nbsp; Because this CGI-BIN
application runs on a shared server, it protects itself by only allowing 
<?php echo " " . $cgi_max . " "; ?>seconds to elapse while factoring.&nbsp; The busier
the server is, the less actual CPU time is represented by
<?php echo " " . $cgi_max . " "; ?>seconds of elapsed time.&nbsp; This means that    
factoring operations may be less successful when the server is busy.</li>
<li>This utility uses the <a href="http://www.swox.com/gmp">GMP library</a>
for arithmetic.&nbsp; The limit of 18-digit integers is in place so that
machine-native integers can be used for the trial divisor (it is more 
efficient that way, and the GMP provides special function calls 
for small divisors).&nbsp; Since the trial divisor need only attain
the square root of the number to be factored, any trial divisor for
an 18-digit integer will fit in one machine-native integer.</li>
</ul>
<?php
   }

function pfact18_print_tabular_results(&$style, 
                                        $cgi_result, 
                                        $cgi_result_nelem, 
                                        $mr_nrounds, 
                                        $mr_pcntprime,
                                        $mr_recip,
                                        $cgi_max)
   {
   //Add commas to the number to factor, the number of Miller-Rabin rounds, and 
   //the timeout.
   pfact18_commanate($cgi_result[1]);
   pfact18_commanate($cgi_result[2]);
   pfact18_commanate($cgi_result[3]);

   //Add commas to each prime factor and its multiplicity.
   $nfactors = ($cgi_result_nelem - 6)/3;

   for ($i=0; $i<$nfactors; $i++)
     {
     pfact18_commanate($cgi_result[$i * 3 + 5]);
     pfact18_commanate($cgi_result[$i * 3 + 6]);
     }

   //echo "<br>" . $cgi_result_nelem . "<br>";

   //Announce the overall result.
   $print_table = 0;
   echo "<p align=\"center\"><font size=\"4\">";
   if (($cgi_result[$cgi_result_nelem - 5] == "P") && ($cgi_result_nelem == 9) && ($cgi_result[$cgi_result_nelem - 3] == "1"))
      {
      echo "The integer " . $cgi_result[1] . " is prime (with 100% certainty)."; 
      }
   elseif (($cgi_result[$cgi_result_nelem - 5] == "p") && ($cgi_result_nelem == 9))
      {
      echo "Based on " . $mr_nrounds . " applications of the Miller-Rabin test, the integer ";
      echo $cgi_result[1] . " is probably (with " . $mr_pcntprime . "% probability) ";
      echo "prime.&nbsp; (This means that there is no more than 1 chance ";
      echo "in " . $mr_recip . " that this integer is composite.)"; 
      }
   elseif (($cgi_result[$cgi_result_nelem - 5] == "C") && ($cgi_result_nelem == 9))
      {
      echo "The integer " . $cgi_result[1] . " has been verified by the Miller-Rabin test ";
      echo "to be composite.&nbsp; However, ";
      echo "due to server CPU time restrictions (" . $cgi_max . " seconds of elapsed time), ";
      echo "it was not possible to make any progress in factoring ";
      echo "this integer.&nbsp; Please try again when the server is less active ";
      echo "or try another factoring resource."; 
      }
   elseif ($cgi_result[$cgi_result_nelem - 5] == "P")
      {
      echo "The composite integer " ;
      echo $cgi_result[1] . " was successfully factored into its prime components with ";
      echo "100% certainty.&nbsp; Its prime factors and their multiplicities are listed ";
      echo "in the table below."; 
      $print_table = 1;
      }
   elseif ($cgi_result[$cgi_result_nelem - 5] == "p")
      {
      echo "The composite integer " ;
      echo $cgi_result[1] . " was successfully factored into its prime components, ";
      echo "and these prime components and their multiplicities are listed in the ";
      echo "table below.&nbsp; ";
      echo "The last component listed in the table was judged to be prime based on ";
      echo $mr_nrounds . " applications of the Miller-Rabin test, meaning that it is ";
      echo $mr_pcntprime . "% probable ";
      echo "that this last component is prime (i.e. that there is no more than 1 chance ";
      echo "in " . $mr_recip . " that it is composite)."; 
      $print_table = 1;
      }
   elseif ($cgi_result[$cgi_result_nelem - 5] == "C")
      {
      echo "Due to server CPU time restrictions (" . $cgi_max . " seconds of elapsed time), ";
      echo "the integer ";
      echo $cgi_result[1] . " could only be partially factored.&nbsp; In the results below, note that ";
      echo "the last component ";
      echo "listed bears the category code <i>C</i> (for <u>c</u>omposite).&nbsp; Please ";
      echo " try again when the server is less active ";
      echo "or try another factoring resource."; 
      $print_table = 1;
      }
   echo "</p></font>";

   //Print the table if demanded.
   if ($print_table)
      {
      $style->static_page_hrule_std();  

      //Assign the table column widths.  They are centralized here for easy change.
      $width[0] = 10;
      $width[1] = 10;
      $width[2] = 10;
      $width[3] = 10;

      echo "<p><table align=\"center\" border=\"1\" width=\"90%\">\n";

      for ($i=0; $i <= ($cgi_result_nelem/3 - 2); $i++)
         {
	 //Factor number.
         echo "<tr>\n";

         echo "   <td width=\"" . $width[0] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>Factor<br>Number</b></p>\n";
	    }
         else
	    {
	    echo "      <p align=\"center\">" . $i . "</p>\n";
	    }
         echo "   </td>\n";

         //Prime Factor
         echo "   <td width=\"" . $width[1] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>Component<br>Factor</b></p>\n";
	    }
         else
	    {
	    echo "      <p align=\"center\">" . $cgi_result[$i * 3 + 2] . "</p>\n";
	    }
         echo "   </td>\n";

         //Multiplicity.
         echo "   <td width=\"" . $width[2] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>Multiplicity</b></p>\n";
	    }
         else
	    {
	    echo "      <p align=\"center\">" . $cgi_result[$i * 3 + 3] . "</p>\n";
	    }
         echo "   </td>\n";

         //Category code.
         echo "   <td width=\"" . $width[3] . "%\">\n";
         if ($i==0)
	    {
	    echo "      <p align=\"center\"><b>Category<br>Code</b></p>\n";
	    }
         else
	    {
	    echo "      <p align=\"center\">" . $cgi_result[$i * 3 + 1] . "</p>\n";
	    }
         echo "   </td>\n";


         echo "</tr>\n";
	 }

      echo "</table></p>\n";
      echo "<p align=\"center\"><b>Table legend:</b>&nbsp; <b>P</b>=prime with absolute certainty, ";
      echo "<b>p</b>=prime established by Miller-Rabin test with ";
      echo $mr_pcntprime . "% certainty, and <b>C</b>=composite established by Miller-Rabin test ";
      echo "with absolute certainty, but not factorable in the time allowed.</p>\n";

      $style->static_page_hrule_std();  
      pfact18_algorithm_notes($cgi_max);
      }
   }
//
//Main script begins here.
//
//Let's agree on a number of rounds for the Miller-Rabin test.  This influences the
//probabilities.
$miller_rabin_nrounds = 25;
//
//Let's agree how long the CGI may take to factor.
$max_cgi_time = 10;
//     
//We need to establish the probability that a number which passes the rounds specified
//above is still in fact composite.  This values need to be calculated by hand whenever
//the value above is changed.
$miller_rabin_p_real                 =  "0.99999999999999911182";
$miller_rabin_p_percent              = "99.999999999999911182";
$miller_rabin_residual_real          =  "0.00000000000000088818";
$miller_rabin_residual_percent       =  "0.000000000000088818";
$miller_rabin_residual_lt_reciprocal =  "1,125,899,906,842,624";
//
$style = new StdWpStyle;
//Assign the current style in force.  Also, starts the CPU
//usage clock.

//Do the header unconditionally.  The header is always used on this page.
do_header($style);
//
if (isset($_GET['N']))
   $N = $_GET['N'];
//
//If N was supplied, decommanate it and be sure it is a string.
if (isset($N))
   pfact18_decommanate($N);
//
//There are a few cases to break into here, and this affects the overall layout of the page.
//The header and footer are fixed, but the "guts" will change.
if (!isset($N))
   {
   //In this case, we are probably visiting the form for the first time, and have not done a submit.
   //Just display the form itself.
   do_form("", "Attempt To Factor Integer");
   }
elseif (!pfact18_issimpleint($N))
   {
   //N is supplied, but is malformed.  Need to advise.
   do_err_msg("N is a malformed integer. &nbsp;Choose a new value for N and try again.");
   $style->static_page_hrule_std();  
   pfact18_commanate($N2);
   do_form($N, "Attempt To Factor Integer");
   }  
elseif (strlen($N) > 18)
   {
   //N is supplied, but is too long.  Need to advise.
   do_err_msg("N is too long (the maximum is 18 digits). &nbsp;Choose a new value for N and try again.");
   $style->static_page_hrule_std();  
   pfact18_commanate($N);
   do_form($N, "Attempt To Factor Integer");
   }
else
   {
   //N is supplied and seems to be a valid integer.
   //
   //If N is negative, make it positive.
   if (Substr($N, 0, 1)=="-")
     $N = Substr($N, 1, strlen($N)-1);

   //If N is "0" or "1", make it "2".
   if ($N=="0")
     $N = (string)"1";
   if ($N=="1")
     $N = (string)"2";

   //We can now run the external program to do the calculation.
   $cgi_command_string = "/hl/cgibin/aux_progs/dtats_cgi_aux_arith_large pfact_18 " . $N . " " . $miller_rabin_nrounds . " " . $max_cgi_time;
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
   if ($cgi_result_nelem < 9)
      $cgi_output_is_sane = 0;
   if ($cgi_result_nelem >= 9)
      {
      if (($cgi_result_nelem % 3) != 0)
         $cgi_output_is_sane = 0;
      if ($cgi_result[0] != "S")
         $cgi_output_is_sane = 0;
      if ($cgi_result[$cgi_result_nelem - 2] != "X")
         $cgi_output_is_sane = 0;
      if ($cgi_result[$cgi_result_nelem - 1] != "S")
         $cgi_output_is_sane = 0;
      }

   if (!$cgi_output_is_sane)
      {
      do_err_msg("An unspecified error occurred when interacting with the CGI-BIN program.&nbsp; Please advise the webmaster.");
      $style->static_page_hrule_std();  
      pfact18_commanate($N);
      do_form($N, "Attempt To Factor Integer");
      }
   else
      {
      pfact18_print_tabular_results($style, 
                                    $cgi_result, 
                                    $cgi_result_nelem,
                                    $miller_rabin_nrounds,
                                    $miller_rabin_p_percent,
                                    $miller_rabin_residual_lt_reciprocal,
                                    $max_cgi_time);
      $style->static_page_hrule_std();  

      pfact18_commanate($N);
      do_form($N, "Attempt To Factor Another Integer");
      }
   }

//Now do the footer unconditionally.  The footer is always used on this web page.
do_footer($style);  
?>
