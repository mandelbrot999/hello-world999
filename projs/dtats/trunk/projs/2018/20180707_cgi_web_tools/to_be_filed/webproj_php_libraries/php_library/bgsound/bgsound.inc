<?php
//********************************************************************************
//Copyright (C) 2005 David T. Ashley
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
//Dave Ashley, 10/05
//
//This file defines operations involving web page background sounds.
//
//
//Returns 1 if strings have at least one character in common, 0 otherwise.
//
function BGSOUND_string_intersection($s1, $s2)
   {
   $len1 = strlen($s1);
   $len2 = strlen($s2);
   for ($i1 = 0; $i1 < $len1; $i1 ++)
      {
      for ($i2 = 0; $i2 < $len2; $i2++)
         {
         if (substr($s1, $i1, 1) == substr($s2, $i2, 1))
            {
            return(1);
            }
         }
      }

   return(0);
   }


//Returns, as an array, the full collection of available sounds that meet
//the passed search criteria.
//
function BGSOUND_bgsound_search_db(
                                  $cleanliness,
                                     //String with attributes.  Multiple attributes may/must be included.
                                     //So, for example, to return clean and gray sounds, one must specify
                                     //"CG" or "GC".
                                     //
                                     //   C : Clean.
                                     //   G : Gray.
                                     //   D : Dirty.
                                     //   A : All.
                                     //
                                  $topic,
                                     //Same rules for multiple selections as above.
                                     //
                                     //   S : Science fiction.
                                     //   E : Engineer jokes.
                                     //   G : General humor.
                                     //   N : General notoriety.
                                     //   A : All.
                                     //
                                  $minsize,
                                     //Minimum size, in kilobytes, that the .WAV file may be.
                                     //
                                  $maxsize,
                                     //Maximum size, in kilobytes, that the .WAV file may be.
                                     //Zero here means no upper limit.
                                     //
                                  &$dbsounds_total
                                     //The total number of sounds in the database.
                                  )
   {
   //Define the master table containing all sounds, and their characterisitics.
   $sounds = array(
                  //-----------------------------------------------------
                  "C",
                  "S",
                  36,
                  "/gensounds/2001_space_odyssey/afault.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "S",
                  72,
                  "/gensounds/2001_space_odyssey/afraid.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "S",
                  103,
                  "/gensounds/2001_space_odyssey/airlock.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "S",
                  47,
                  "/gensounds/2001_space_odyssey/cantdo.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "S",
                  67,
                  "/gensounds/2001_space_odyssey/cropped.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "S",
                  762,
                  "/gensounds/2001_space_odyssey/monolith2001.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "S",
                  121,
                  "/gensounds/2001_space_odyssey/stress2001.wav",
                  "<i>2001: A Space Odyssey</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  338,
                  "/gensounds/analyze_this/barnes.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  287,
                  "/gensounds/analyze_this/deadnote.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  106,
                  "/gensounds/analyze_this/fishing.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  387,
                  "/gensounds/analyze_this/getalife.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  119,
                  "/gensounds/analyze_this/hearno.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  127,
                  "/gensounds/analyze_this/nodoctor.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  161,
                  "/gensounds/analyze_this/scotch.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  246,
                  "/gensounds/analyze_this/restrain.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  118,
                  "/gensounds/analyze_this/video.wav",
                  "<i>Analyze This!</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  75,
                  "/gensounds/as_good_as_it_gets/bettrman.wav",
                  "<i>As Good As It Gets</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  130,
                  "/gensounds/as_good_as_it_gets/boyfriend.wav",
                  "<i>As Good As It Gets</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  120,
                  "/gensounds/as_good_as_it_gets/stories.wav",
                  "<i>As Good As It Gets</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  128,
                  "/gensounds/austin_powers/angry.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  38,
                  "/gensounds/austin_powers/beat_drevil.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  23,
                  "/gensounds/austin_powers/bigglesworth.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  56,
                  "/gensounds/austin_powers/failure.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  31,
                  "/gensounds/austin_powers/get_ap.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  27,
                  "/gensounds/austin_powers/grr_baby.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  49,
                  "/gensounds/austin_powers/lair.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  92,
                  "/gensounds/austin_powers/mrevil.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  43,
                  "/gensounds/austin_powers/swingerr.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  56,
                  "/gensounds/austin_powers/trillions.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  38,
                  "/gensounds/austin_powers/ugly_stick.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  20,
                  "/gensounds/austin_powers/yeahbaby.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  149,
                  "/gensounds/austin_powers/zipit.wav",
                  "The <i>Austin Powers</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "H",
                  87,
                  "/gensounds/aviation_accidents/dl191_short.wav",
                  "The last moments of Delta Air Lines Flight 191 (black box recording); " .
                  "which crashed due to wind shear on August 2, 1985 in Dallas, Texas; " .
                  "killing 136 people in the aircraft and one on the ground</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  93,
                  "/gensounds/blues_brothers/106miles.wav",
                  "<i>The Blues Brothers</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  104,
                  "/gensounds/carlin_pa/500islands.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  117,
                  "/gensounds/carlin_pa/dad_drink_more.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  88,
                  "/gensounds/carlin_pa/grand_canyon_yoyo.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  94,
                  "/gensounds/carlin_pa/leave_me_alone.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  79,
                  "/gensounds/carlin_pa/rape_is_funny.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  187,
                  "/gensounds/carlin_pa/rr_tracks.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "G",
                  88,
                  "/gensounds/carlin_pa/stupid_half.wav",
                  "George Carlin, <i>Parental Advisory</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  79,
                  "/gensounds/godfather/blood.wav",
                  "<i>The Godfather</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  77,
                  "/gensounds/godfather/fishes.wav",
                  "<i>The Godfather</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  194,
                  "/gensounds/godfather/goomba.wav",
                  "<i>The Godfather</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  25,
                  "/gensounds/godfather/offer.wav",
                  "<i>The Godfather</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  489,
                  "/gensounds/godfather/peace.wav",
                  "<i>The Godfather</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  148,
                  "/gensounds/godfather/someday.wav",
                  "<i>The Godfather</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  361,
                  "/gensounds/godfather/sonny.wav",
                  "<i>The Godfather</i> (from the famous scene where Sonny [James Caan] is gunned down at the tollbooth)",
                  //-----------------------------------------------------
                  "C",
                  "E",
                  294,
                  "/gensounds/humorous/thenack.wav",
                  "Unknown",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  38,
                  "/gensounds/movie_top_gun/ego.wav",
                  "<i>Top Gun</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  333,
                  "/gensounds/pulp_fiction/bible_passage.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  136,
                  "/gensounds/pulp_fiction/big_brain_brett_long.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  7,
                  "/gensounds/pulp_fiction/big_brain_brett_short.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  119,
                  "/gensounds/pulp_fiction/bowl_of_rice.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  26,
                  "/gensounds/pulp_fiction/chill_them_out.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  294,
                  "/gensounds/pulp_fiction/dn_storage.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  6,
                  "/gensounds/pulp_fiction/english_short.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  325,
                  "/gensounds/pulp_fiction/europe_little_differences.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  7,
                  "/gensounds/pulp_fiction/fatman.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  196,
                  "/gensounds/pulp_fiction/fonzie_is_cool.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  20,
                  "/gensounds/pulp_fiction/gimp.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  86,
                  "/gensounds/pulp_fiction/guy_foot_massage.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  43,
                  "/gensounds/pulp_fiction/hamburger.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  142,
                  "/gensounds/pulp_fiction/jules_quitting.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  271,
                  "/gensounds/pulp_fiction/marvin_shot.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  338,
                  "/gensounds/pulp_fiction/medieval_long.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  289,
                  "/gensounds/pulp_fiction/mushroom_cloud_long.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  15,
                  "/gensounds/pulp_fiction/mushroom_cloud_short.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  154,
                  "/gensounds/pulp_fiction/piercing.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  302,
                  "/gensounds/pulp_fiction/pigs_filthy_animals.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  146,
                  "/gensounds/pulp_fiction/please_clean_car.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  71,
                  "/gensounds/pulp_fiction/postpone_congratulation_long.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  30,
                  "/gensounds/pulp_fiction/postpone_congratulation_short.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  24,
                  "/gensounds/pulp_fiction/rapist.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  20,
                  "/gensounds/pulp_fiction/sending_the_wolf.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  134,
                  "/gensounds/pulp_fiction/take_the_money.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "D",
                  "N",
                  94,
                  "/gensounds/pulp_fiction/towel_dirty.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  2,
                  "/gensounds/pulp_fiction/use_toilet.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  318,
                  "/gensounds/pulp_fiction/wallace_appearance.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  84,
                  "/gensounds/pulp_fiction/we_happy.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  205,
                  "/gensounds/pulp_fiction/weirdest_day.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "G",
                  "N",
                  347,
                  "/gensounds/pulp_fiction/wristwatch_history.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  14,
                  "/gensounds/pulp_fiction/zed_is_dead.wav",
                  "<i>Pulp Fiction</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  38,
                  "/gensounds/r_lee_ermey/dirtbag.wav",
                  "R. Lee Ermey, <i>Full Metal Jacket</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  117,
                  "/gensounds/r_lee_ermey/ermey_1234corp.wav",
                  "<i>Full Metal Jacket</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  28,
                  "/gensounds/r_lee_ermey/ermey_charge.wav",
                  "R. Lee Ermey, <i>Full Metal Jacket</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  26,
                  "/gensounds/r_lee_ermey/ermey_equally.wav",
                  "R. Lee Ermey, <i>Full Metal Jacket</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  12,
                  "/gensounds/r_lee_ermey/ermey_goodnite.wav",
                  "R. Lee Ermey, <i>Full Metal Jacket</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  159,
                  "/gensounds/r_lee_ermey/ermey_kisser.wav",
                  "R. Lee Ermey, from <a href=\"http://www.rleeermey.com\" target=\"_blank\">his web site</a>.",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  99,
                  "/gensounds/star_trek_orig/blow.wav",
                  "<i>Star Trek</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  43,
                  "/gensounds/star_trek_orig/explain.wav",
                  "<i>Star Trek</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  27,
                  "/gensounds/star_trek_orig/guardian.wav",
                  "<i>Star Trek</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  96,
                  "/gensounds/star_trek_mp/vger.wav",
                  "<i>Star Trek: The Motion Picture</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  35,
                  "/gensounds/star_trek_vh/amiracle.wav",
                  "<i>Star Trek IV:  The Voyage Home</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  118,
                  "/gensounds/star_trek_vh/avoidearth.wav",
                  "<i>Star Trek IV:  The Voyage Home</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  127,
                  "/gensounds/star_trek_vh/backpost.wav",
                  "<i>Star Trek IV:  The Voyage Home</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  218,
                  "/gensounds/star_trek_vh/colorful.wav",
                  "<i>Star Trek IV:  The Voyage Home</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  34,
                  "/gensounds/star_trek_vi_tuc/1strule.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  184,
                  "/gensounds/star_trek_vi_tuc/breathing.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  72,
                  "/gensounds/star_trek_vi_tuc/didntfire.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  92,
                  "/gensounds/star_trek_vi_tuc/knees.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  46,
                  "/gensounds/star_trek_vi_tuc/nixon.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  50,
                  "/gensounds/star_trek_vi_tuc/request.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  75,
                  "/gensounds/star_trek_vi_tuc/savedciv.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  26,
                  "/gensounds/star_trek_vi_tuc/screwup.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  55,
                  "/gensounds/star_trek_vi_tuc/shutup.wav",
                  "<i>Star Trek VI:  The Undiscovered Country</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  108,
                  "/gensounds/star_trek_orig/shatner.wav",
                  "William Shatner, during a satirical skit involving speaking at a " .
                  "<i>Star Trek</i> convention, from an unknown episode of <i>Saturday Night Live</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  137,
                  "/gensounds/star_trek_ng/locutus0.wav",
                  "Patrick Stewart, <i>Star Trek: The Next Generation</i>",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  73,
                  "/gensounds/star_wars/beaten.wav",
                  "The <i>Star Wars</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  35,
                  "/gensounds/terminator/back.wav",
                  "Arnold Schwarzenegger, the <i>Terminator</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  35,
                  "/gensounds/terminator/cyborg.wav",
                  "Michael Biehn, the <i>Terminator</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  3,
                  "/gensounds/terminator/get_out.wav",
                  "Arnold Schwarzenegger, the <i>Terminator</i> series of films",
                  //-----------------------------------------------------
                  "C",
                  "N",
                  73,
                  "/gensounds/terminator/yourclot.wav",
                  "Arnold Schwarzenegger, the <i>Terminator</i> series of films",
                  );

   //Copy the elements that match into a parallel array that will be returned.
   $c = count($sounds);
   if ($c % 5)
      {
      //Not a multiple of 5, something is wrong with the array.
      $dbsounds_total = 0;
      return(false);
      }

   $dbsounds_total = $c/5;

   for ($i = 0; $i < $c; $i += 5)
      {
      $excluded = 0;

      if ($cleanliness != "A")
         {
         if (!BGSOUND_string_intersection($cleanliness, $sounds[$i]))
            {
            $excluded = 1;
            }
         }

      if ($topic != "A")
         {
         if (!BGSOUND_string_intersection($topic, $sounds[$i+1]))
            {
            $excluded = 1;
            }
         }

      if (($maxsize != 0) && ($maxsize < $sounds[$i+2]))
         {
         $excluded = 1;
         }

      if ($minsize > $sounds[$i+2])
         {
         $excluded = 1;
         }

      if (!$excluded)
         {
         if (!isset($rv))
            {
            $rv = array($i/5);
            }
         else
            {
            array_push($rv, $i/5);
            }

         array_push($rv, $sounds[$i]);
         array_push($rv, $sounds[$i+1]);
         array_push($rv, $sounds[$i+2]);
         array_push($rv, $sounds[$i+3]);
         array_push($rv, $sounds[$i+4]);
         }      
      } //End for()

   if (isset($rv))
      return($rv);
   else
      return(false);
   }

//
//Returns a random sound subject to the parameters.  If a sound matching the criteria can't be found,
//the $soundpath and the $soundcredit are set to be the empty string.  The total number of sounds in the database,
//the number selected per the query, and the effective array index of the sound selected are returned.
//
function BGSOUND_bgsound_random(
                                $cleanliness,
                                $topic,
                                $minsize,
                                $maxsize,
                                &$soundpath,
                                &$soundcredit,
                                &$dbsounds_total,
                                &$dbsounds_query,
                                &$dbsound_selected
                                )

   {
   //Dope the return variables for consistency.
   $dbsounds_total   = 0;
   $dbsounds_query   = 0;
   $dbsound_selected = 0;

   $possibles = BGSOUND_bgsound_search_db($cleanliness, $topic, $minsize, $maxsize, $dbsounds_total);
   if ($possibles === false)
      {
      //Nothing found.
      $soundpath   = "";
      $soundcredit = "";  
      }
   else
      {
      $c              = count($possibles) / 6;
      $dbsounds_query = $c;
      //echo $c;

      $target      = rand(0, $c-1);
      $dbsound_selected = $possibles[$target * 6];
      //echo " ";
      //echo $target;

      $soundpath   = $possibles[$target * 6 + 4];
      $soundcredit = $possibles[$target * 6 + 5];
      }
   }
?>
