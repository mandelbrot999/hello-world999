//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2016/20161106_kicker/c_main.c 86 2016-11-09 15:49:06Z dashley $
//-------------------------------------------------------------------------------------------------
//This file is part of "kicker", a program for spawning threads periodically in order to
//unstall certain Windows programs and scripts.  The cause of the stall is unknown, but
//it is known that spawning threads unstalls the system.
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the MIT License,
//reproduced below.
//-------------------------------------------------------------------------------------------------
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files(the "Software"), to deal in the
//Software without restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the
//Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-------------------------------------------------------------------------------------------------
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define NELEM(A)  (sizeof(A)/sizeof(A[0]))

void emit_hline_std(void)
{
   printf("-------------------------------------------------------------------------------\n");
}

void emit_mit_license(void)
{
   const char *ref[] =
   {
      "Permission is hereby granted, free of charge, to any person obtaining a copy",
      "of this software and associated documentation files (the \"Software\"), to",
      "deal in the Software without restriction, including without limitation the",
      "rights to use, copy, modify, merge, publish, distribute, sublicense, and / or",
      "sell copies of the Software, and to permit persons to whom the Software is",
      "furnished to do so, subject to the following conditions :",
      "",
      "The above copyright notice and this permission notice shall be included in",
      "all copies or substantial portions of the Software.",
      "",
      "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR",
      "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,",
      "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE",
      "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER",
      "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,",
      "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE",
      "SOFTWARE."
   };

   size_t i;

   for (i=0; i<NELEM(ref); i++)
   {
      printf("%s\n", ref[i]);
   }
}

const char *kickish_words[] = 
{
   "Kick",
   "Smack",
   "Slug",
   "Punch",
   "Assault",
   "Hit",
   "Strike",
   "Slap",
   "Smack",
   "Spank",
   "Cuff",
   "Thump",
   "Swat",
   "Beat",
   "Thrash",
   "Batter",
   "Pound",
   "Pummel",
   "Box",
   "Whip",
   "Flog",
   "Cane",
   "Wallop",
   "Bash",
   "Bop",
   "Clout",
   "Clip",
   "Clobber",
   "Sock",
   "Swipe",
   "Crown",
   "Belt",
   "Tan",
   "Deck",
   "Floor",
   "Bump",
   "Knock",
   "Bang",
   "Tap",
   "Welt"
};

volatile int ctrl_c_or_break_pressed = 0;  //volatile because the Visual C++ environment spawns a thread to handle
                                           //CTRL-C or CTRL-BREAK.
volatile int thread_ran = 0;               //volatile because shared with thread.

BOOL CtrlHandler(DWORD fdwCtrlType)
{
   switch (fdwCtrlType)
   {
      case CTRL_C_EVENT:
      case CTRL_BREAK_EVENT:
         ctrl_c_or_break_pressed = 1;
         return(TRUE);
      //There is no default case.  There is no break statement.  I've assigned a
      //magic number to a variable.  But the function still works fine.
      //Can you believe it?  It must be a miracle!
   }

   return(FALSE);  //Did I mention the multiple return points?  This program should
                   //blow up and wipe out several city blocks!
}

//Thread function.  Parameter ignored.
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
   thread_ran = 1;

   return (0);
}

int c_main(int argc, char* argv[])
{
   size_t selector = NELEM(kickish_words) - 1;
   size_t ui;
   int first_time = 1;
   HANDLE thread_handle;
   DWORD  thread_id;

   emit_hline_std();
   printf("kicker, Copyright 2016 David T. Ashley (dashley@gmail.com)\n");
   emit_hline_std();
   printf("This program is made available under the MIT License, reproduced below.\n");
   emit_hline_std();
   emit_mit_license();
   emit_hline_std();
   printf("This program accepts no command-line arguments and simply spawns a new thread\n");
   printf("approximately every 1 second.  The purpose of the program is to prevent\n");
   printf("certain stalls that occur under Windows when running some programs/scripts\n");
   printf("It is known that spawning a new thread periodically unstalls the programs/\n");
   printf("scripts.  The program can be terminated with CTRL-C or CTRL-BREAK.\n");
   emit_hline_std();

   SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
      //Yes, I know I'm supposed to check the return code.

   while (! ctrl_c_or_break_pressed)
   {
       //Backspace over the previous word.
       if (! first_time)
       {
          //Beep(750, 500);

          for (ui = 0; ui < (strlen(kickish_words[selector]) + 1); ui++)
          {
             printf("%c", (char)8);
          }
          for (ui = 0; ui < (strlen(kickish_words[selector]) + 1); ui++)
          {
             printf(" ");
          }
          for (ui = 0; ui < (strlen(kickish_words[selector]) + 1); ui++)
          {
             printf("%c", (char)8);
          }
       }

       first_time = 0;

       //Go to next string.
       if (selector < (NELEM(kickish_words) - 1))
          selector++;
       else
          selector = 0;

       //Print the description.
       printf("%s!", kickish_words[selector]);

	   //Start the thread.  This will hopefully unstall things.
	   thread_handle = CreateThread(
		   NULL,                   // default security attributes
		   0,                      // use default stack size  
		   MyThreadFunction,       // thread function name
		   0,                      // argument to thread function 
		   0,                      // use default creation flags 
		   &thread_id);            // returns the thread identifier

	   //If the create call failed, terminate.
	   if (thread_handle == NULL)
	   {
		   printf("\nOuch!\n");
		   exit(0);
	   }

	   //Wait for thread termination.  This should be nearly instant.  But it
	   //would seem to be the best way to wait so as not to chew up CPU
	   //cycles.
	   WaitForSingleObject(thread_handle, INFINITE);

	   //At this point, the thread should have run, and the variable should have been
	   //set.  If not, there is a real logical problem.
	   if (!thread_ran)
	   {
		   printf("\nDouble-ouch\n");
		   exit(0);
	   }

	   thread_ran = 0;

	   //Delay.  Sleep() is likely the most effective way to not waste CPU capacity.
       Sleep(1000);
   }

   printf("\n");
   emit_hline_std();
   printf("Program terminated with CTRL-C or CTRL-BREAK.\n");
   emit_hline_std();

   return(0);
}

// End of c_main.c.
