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
function miller_rabin_isdigit($Digit)
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
function miller_rabin_issimpleint($Intnum)
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
      if (!miller_rabin_isdigit(Substr($Intnum, $index, 1)))
         return 0;
      }

   return 1;
   }
//
//
//Returns the number of digits in the argument, which must be a valid simple
//integer.
function miller_rabin_ndigits($Intnum)
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
function miller_rabin_digittoint($Digit)
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

//Decommanates an integer and removes all other extraneous characters without respect for 
//whether the commas are in the right place or the integer is syntactically valid.
function miller_rabin_decommanate(&$arg)
   {
   $temp = "";

   $len = strlen($arg);

   for ($i=0; $i<$len; $i++)
      {
      $c = (string)Substr($arg, $i, 1);
   
      if (miller_rabin_isdigit($c) || ($c == "-"))
         $temp = $temp . $c;
      }

   $arg = (string)$temp;
   } 

//Commanates an integer which is assumed to by syntactically correct.
function miller_rabin_commanate(&$arg)
   {
   miller_rabin_decommanate($arg);
 
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

function do_header(&$style, $miller_rabin_nrounds)
   {
   $style->static_page_header_title_std("Probable Primality Test (Miller-Rabin)",
			"Miller-Rabin Probable Primality Test",
			"This utility uses " . $miller_rabin_nrounds . " applications of the " .
                        "<a href=\"http://mathworld.wolfram.com/Rabin-MillerStrongPseudoprimeTest.html\">" .
                        "Miller-Rabin test</a> to determine " .
                        "with high probabilistic certainty whether an integer " .
                        "is " .
                        "<a href=\"http://mathworld.wolfram.com/PrimeNumber.html\">prime</a> or " .
                        "<a href=\"http://mathworld.wolfram.com/CompositeNumber.html\">composite</a>." .
                        "&nbsp;  This utility does <i>not</i> " .
                        "factor composite numbers.");
   }  

function do_footer(&$style)
   {
//   $style->static_page_hrule_std();
//   echo "<p align=\"center\">This utility is powered by the ";
//   echo "<a href=\"http://www.swox.com/gmp\"><img hspace=\"5\" vspace=\"5\" src=\"../genimages/gmplogo1.png\" width=\"232\" height=\"104\" align=\"absmiddle\"></a>.&nbsp; All source code is available ";
//   echo "<a href=\"../howtos/nth_web_gmp_src_code_dist/obtain_all_source.htm\">here</a>.</p>\n";
   $style->static_page_footer_std();
   }

function do_form($N_refresh, $Buttontext, $max_digits)
   {
   echo "<form method=get action=\"index.php\" width=\"100%\">\n";
   echo "<table align=\"center\">\n";
   echo "<tr>\n";
   echo "  <td width=\"10%\">\n";
   echo "   <p align=\"right\"><b>N</b> (" . number_format($max_digits) . "-digit maximum):</td>\n";
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


//Main script begins here.
//
//
//Let's agree on a maximum for number of digits in the number to test.  It is known that
//Apache won't process URL's larger than 1024, so let's be conservative and say 500
//digits.
$max_digits = 500;
//
//Let's agree on a number of rounds for the Miller-Rabin test.  This influences the
//probabilities.
$miller_rabin_nrounds = 25;
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
do_header($style, $miller_rabin_nrounds);
//
if (isset($_GET['N']))
   $N = $_GET['N'];
//
//If N was supplied, decommanate it and be sure it is a string.
if (isset($N))
   miller_rabin_decommanate($N);
//
//There are a few cases to break into here, and this affects the overall layout of the page.
//The header and footer are fixed, but the "guts" will change.
if (!isset($N))
   {
   //In this case, we are probably visiting the form for the first time, and have not done a submit.
   //Just display the form itself.
   do_form("", "Is This Prime?", $max_digits);
   }
elseif (!miller_rabin_issimpleint($N))
   {
   do_err_msg("N is a malformed integer. &nbsp;Choose a new value for N and try again.");
   $style->static_page_hrule_std();  
   miller_rabin_commanate($N);
   do_form($N, "Is This Prime?", $max_digits);
   }  
elseif ($N == "1")
   {
   do_err_msg("It is not a valid question to ask if 1 is prime.&nbsp; It is agreed " .
              "in number theory (largely to minimize exception cases in proofs and results) " .
              "that 1 is neither prime nor composite.&nbsp; " .
              "Choose a new value for N and try again.");
   $style->static_page_hrule_std();  
   miller_rabin_commanate($N);
   do_form($N, "Is This Prime?", $max_digits);
   }  
elseif (strlen($N) > $max_digits)
   {
   do_err_msg("N is too long (a " . number_format($max_digits) . "-digit maximum is " .
               "in effect).&nbsp; Choose a shorter value and try again.");
   $style->static_page_hrule_std();  
   miller_rabin_commanate($N);
   do_form($N, "Is This Prime?", $max_digits);
   }
else
   {
   //N seems to be a valid integer.
   //
   //If N is negative, make it positive.
   if (Substr($N, 0, 1)=="-")
     $N = Substr($N, 1, strlen($N)-1);

   //If N is "0", make it "2".
   if ($N=="0")
     $N = (string)"2";

   //We can now run the external program to do the calculation.
   $cgi_command_string = "/hl/cgibin/aux_progs/dtats_cgi_aux_arith_large gmp_prob_prime " . $N . " " . $miller_rabin_nrounds;

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
      if ($cgi_result_nelem != 5)
         $cgi_output_is_sane = 0;
      if ($cgi_result[0] != "S")
         $cgi_output_is_sane = 0;
      if (($cgi_result[3] != "0") && ($cgi_result[3] != "1") && ($cgi_result[3] != "2"))
         $cgi_output_is_sane = 0;
      if ($cgi_result[4] != "S")
         $cgi_output_is_sane = 0;
      }

   if (!$cgi_output_is_sane)
      {
      do_err_msg("An unspecified error occurred when interacting with the CGI-BIN program.&nbsp; Please advise the webmaster.");
      $style->static_page_hrule_std();  
      miller_rabin_commanate($N);
      do_form($N, "Is This Prime", $max_digits);
      }
   else
      {
      miller_rabin_commanate($cgi_result[1]);

      if ($cgi_result[3] == 0)
	 {
         echo "<p align=\"center\"><font size=\"4\">The integer ";
         echo $cgi_result[1];
         echo " is definitely (with 100% certainty) composite.&nbsp; Note, however, that although ";
         echo "it was relatively computationally inexpensive to determine that this integer is composite, ";
         echo "factoring it may be computationally <i>much</i> more expensive.</font></p>\n";
	 }
      elseif ($cgi_result[3] == 1)
	 {
         echo "<p align=\"center\"><font size=\"4\">Based on " . $miller_rabin_nrounds . " applications of ";
         echo "the Miller-Rabin test, the integer ";
         echo $cgi_result[1];
         echo " is probably (with " . $miller_rabin_p_percent . "% certainty) ";
         echo "prime.&nbsp; (This means that there is no more than 1 chance in ";
         echo $miller_rabin_residual_lt_reciprocal . " that this integer is ";
         echo "composite.)</font></p>\n";
	 }
      else
	 {
         echo "<p align=\"center\"><font size=\"4\">The integer ";
         echo $cgi_result[1];
         echo " is prime (with 100% certainty).&nbsp; This means that the ";
         echo "GMP";
         echo " library routine was able to attempt trial division with divisors ";
         echo "up to <i>floor</i>(<i>sqrt</i>(N)).</font></p>\n";
	 }

      $style->static_page_hrule_std();  
?>
<p align="left"><b>Notes on the algorithm:</b>
<ul>
    <li>It is agreed in number theory that 
        <a href="http://www.mth.uct.ac.za/~digest/faq/prime.html">'1' is neither prime nor 
        composite</a>.&nbsp; This definition
	is largely <a href="http://dictionary.reference.com/search?q=arbitrary">arbitrary</a>, 
        and there is some discussion in Usenet newsgroups
	such as <i>sci.math</i> from time to time about this topic.&nbsp; It substantially shortens
	and neatens many results and proofs to define '1' in this way.&nbsp; For this reason,
        this utility refuses to <a href="http://dictionary.reference.com/search?q=opine">opine</a> on '1'. 
        </li>
    <li>The <a href="http://mathworld.wolfram.com/Rabin-MillerStrongPseudoprimeTest.html">Miller-Rabin 
        test</a> and other 
        <a href="http://mathworld.wolfram.com/StrongPseudoprime.html">strong pseudoprime</a> tests 
        are part of the backbone of popular 
        <a href="http://mathworld.wolfram.com/Public-KeyCryptography.html">public-key cryptography</a>,
        specifically 
        <a href="http://mathworld.wolfram.com/RSAEncryption.html">RSA public-key cryptography</a>,
        which relies on the fact that it is much easier to create a large composite number with
        large prime components than to factor it.        
        </li>
    <li>This utility uses the <i>mpz_prob_prime_p()</i> function from
        the <a href="http://www.swox.com/gmp">GMP</a>
        to make its primality assessment.&nbsp; This function has not been proofread
	to verify how it selects bases and applies the Miller-Rabin test.&nbsp; It is assumed 
        that the standard upper bound of 0.25^N can be applied where N is the <i>reps</i>
        parameter to the function (in the case of this utility, <i>reps</i> is  
	<?php echo " " . $miller_rabin_nrounds ; ?>). 
        </li>
    <li>This web site also contains a <a href="pfact18digit.php">factorization
        utility</a> which will factor integers subject to size and CPU time constraints.                
</ul>
<?php
      $style->static_page_hrule_std();  

      miller_rabin_commanate($N);
      do_form($N, "Is This Prime?", $max_digits);
      }
   }

//Now do the footer unconditionally.  The footer is always used on this web page.
do_footer($style);  
?>
