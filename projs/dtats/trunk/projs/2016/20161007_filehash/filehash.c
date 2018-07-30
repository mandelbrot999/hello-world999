//----------------------------------------------------------------------------------------------------
//FILEHASH--Calculates the SHA-512 cryptographic hash (also known as a message
//          digest) of computer files, as defined by FIPS 180-3.
//Copyright (C) 2010, David T. Ashley.
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//(A copy of the GNU General Public License, Version 3 is provided at
//the end of this source file.)
//
//David T. Ashley can be contacted at DASHLEY@GMAIL.COM and/or at
//P.O. Box 918, Marshall MI 49068.
//----------------------------------------------------------------------------------------------------
#include <windows.h>
#include <commdlg.h>

#include <assert.h>
#include <process.h>
#include <stdio.h>

#include "resource.h"


#define FILEHASH_MAXFILES (200)
   //Maximum number of files that will be processed and displayed.
   //Limited to avoid filling up the edit control's buffer.
   
#define FILEHASH_DISPBUFLEN (55000)
   //The point at which we say the edit control buffer has too
   //many characters in it.

#define FILEHASH_FILE_READ_BUF_SIZE (0x10000)
   //The number of bytes for each read buffer.  It is difficult to know
   //how to size this value.  On one hand, larger is better, as it 
   //enables the disk to operate in blocks.  On the other hand, too 
   //large is probably not a good idea, as it will take a lot of
   //time to fill the buffer (several disk seeks).  Suspect that 16K-64K
   //is about the optimum, but may go larger, anyway.

static char FILEHASH_dialog_file_open_buffer[15000];
   //Buffer from the "open files" dialog box, for it to store results
   //in.

static char FILEHASH_dispbuf[FILEHASH_DISPBUFLEN+1];
   //The buffer which holds the contents of the edit control (the main control, the
   //text box).  This is a mirror buffer, probably not a very efficient way of doing
   //things.

static int FILEHASH_use_sound = 1;
   //Remembers the state of the "use sound" option.  Default is YES.

static int FILEHASH_always_on_top = 1;
   //Remembers whether the main window should always be on top.
   //This can be annoying in some contexts, so it can be turned off.

#define WM_USER_EV_CHILD_THREAD_PROGRESS  (WM_USER + 1)
   //The child thread has progress to report (updated information that
   //can be used by the parent).

#define WM_USER_EV_CHILD_THREAD_ENDING    (WM_USER + 2)
   //The child thread is reporting that it is ending.  After this event is
   //posted for the parent, there may be some delay until the thread is actually
   //terminated, so additional OS interaction is required to know the thread
   //is actually dead.

static char FILEHASH_szAppName[] = "FileHash";
   //The application name.

static WNDPROC FILEHASH_old_win_edit_handler = NULL;
   //The old edit control handler.  This is used to remember the function pointer,
   //in order to subclass the behavior, because we must catch the drop files event.

static volatile int FILEHASH_thread_abort_request = 0;
   //This is set TRUE by the main thread if the child thread
   //should abort.  This means the application will terminate
   //(this is the only reason for setting this flag).  This 
   //variable is set by the main thread and read by the
   //child thread.

static DWORD FILEHASH_parent_thread_id = 0;
   //The thread ID of the parent obtained using the 
   //GetCurrentThreadId() call.  The child needs to know this
   //in order to post a message.

static HWND FILEHASH_parent_thread_main_window_handle = 0;
   //Window handle of main window.

static int FILEHASH_child_thread_is_active = 0;
   //Set TRUE when the child thread is kicked off.  Set
   //FALSE when a message from the child thread is received
   //indicating that the thread has terminated and when the
   //thread is confirmed dead.  This variable is used only
   //by the main thread.

static HANDLE FILEHASH_child_handle = 0;
   //The handle of the child process.  This is only valid
   //if a thread is active.  This variable is used only
   //by the main thread to check on status.

static unsigned char FILEHASH_file_read_buf[FILEHASH_FILE_READ_BUF_SIZE];
   //File read buffer for I/O.

struct FILEHASH_FileInfoStructPerFile
   {
   volatile char fpath[MAX_PATH + 1];
      //The full path to the file, which should be recognized by the operating system.
      //If this string is empty, it is a signal that no file is in this slot.
   volatile int  is_directory_valid;
      //TRUE if the is_directory flag is assigned by the child process and so the 
      //parent can rely on it.
   volatile int  is_directory_error;
      //TRUE if the child process could not obtain directory information.
   volatile int  is_directory;
      //TRUE if the file is actually a directory.  This means it cannot be processed.
   volatile int  file_size_valid;
      //TRUE if file size has been assigned by child (or an attempt to assign it was made).
   volatile int  file_size_error;
      //There was an error in the attempt to obtain file size.
   volatile unsigned __int64 file_size;
      //The number of bytes in the file.
   volatile int  sha512_valid;
      //TRUE if the SHA512 is valid or an attempt was made.
   volatile char sha512[200];
      //A string representation of the SHA512 or else an error message from the child.
      //An SHA-512 should be 129 characters long (128 characters for the hash and 1 for
      //the terminating 0).
   };

//Aggregated information about all of the files for which a hash is calculated.
//
struct FILEHASH_FileInfoStruct
   {
   volatile struct FILEHASH_FileInfoStructPerFile file_info[FILEHASH_MAXFILES];
   volatile int terminated_normally;
   volatile int aborted;
   };


volatile struct FILEHASH_FileInfoStruct FILEHASH_file_info;
   //This is the major structure that holds file information.  Here are the three
   //roles it fills:
   //
   //   a)The parent thread fills in this information in preparation for starting
   //     up the child thread.
   //
   //   b)The child thread fills in the information (file size, SHA-512) as it
   //     goes down this list, and notifies the parent thread with an event,
   //     which causes the updating of displayed information.
   //
   //   c)After the child thread is finished with all files, another event is sent
   //     to indicate this.


//Function prototypes, to be sure no miscompilations where the compiled call doesn't match the
//compiled function.
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
static unsigned __stdcall FILEHASH_ChildThreadFunc(void *pArguments);
static void FILEHASH_ChildThreadHardSyncStop(void);
static void FILEHASH_ChildThreadStart(void);
static void FILEHASH_MakeGenericSound(void);


//Maps from a nibble to the corresponding ASCII hexadecimal digit.
//
char CF_nibble_to_lc_hex_digit(int nibble)
   {
   switch (nibble & 0x0F)
      {
      case  0:
         return('0');
         break;
      case  1:
         return('1');
         break;
      case  2:
         return('2');
         break;
      case  3:
         return('3');
         break;
      case  4:
         return('4');
         break;
      case  5:
         return('5');
         break;
      case  6:
         return('6');
         break;
      case  7:
         return('7');
         break;
      case  8:
         return('8');
         break;
      case  9:
         return('9');
         break;
      case 10:
         return('a');
         break;
      case 11:
         return('b');
         break;
      case 12:
         return('c');
         break;
      case 13:
         return('d');
         break;
      case 14:
         return('e');
         break;
      case 15:
         return('f');
         break;
      default:
         return('?');
         break;
      }
   }


//Returns TRUE if the passed string seems to be a
//valid unsigned integer (without commas) or FALSE
//otherwise.
//
int BSF_is_uint_wo_commas(const char *arg)
   {
   if (!*arg)
      return(0);

   if (arg[0] == '0')
      {
      if (arg[1])
         {
         return(0);
         }
      else
         {
         return(1);
         }
      }
   else
      {
      while (*arg)
         {
         if ((*arg < '0') || (*arg > '9'))
            return(0);
         arg++;
         }

      return(1);
      }
   }


//Adds commas (in the traditional place) to a string that represents an unsigned integer.
//
void BSF_commanate(char *s)
   {
   int l;
   int ncommas;
   char *putpt, *getpt;
   int ndigits;

   //If the leading character on the string is a 
   //'-', bump the pointer.  Then everything
   //else applies as for an unsigned.
   if (*s == '-')
     s++;

   //Be sure the string currently meets the syntax for
   //a signed integer.  If not, don't even touch it.
   if (!BSF_is_uint_wo_commas(s))
      return;

   //Get the length of the current string.
   l = strlen(s);

   //Let's agree, just in case something slipped through
   //the cracks, that zero length strings are not of
   //interest to us.
   if (l==0)
     return;

   //The number of commas to add is precisely 
   //(N-1) div 3.
   if (l==0)
      ncommas = 0;
   else
      ncommas = (l-1)/3;

   //Walk through the string, adding commas.
   getpt = s + l - 1;
   putpt = s + l + ncommas;

   *putpt = 0; //Write the zero terminator.
   putpt--;

   ndigits = 0;

   while ((putpt > s) && (getpt > s))
      {
      *putpt = *getpt;
      putpt--;
      getpt--;
      ndigits++;
      if (((ndigits % 3) == 0) && (putpt != s))
         {
         *putpt = ',';
         putpt--;
         }

      assert((putpt >= s) && (getpt>=s));
      }
   }


//Fundamental state for forming SHA-512s.  Conceptually private to this module.
//
struct FILEHASH_SHA512_Sha512StateStruct
   {
   unsigned __int64 H0, H1, H2, H3, H4, H5, H6, H7;
      //Directly from FIPS 180-3.  In retrospect, this might have
      //been better implemented as an array.
   unsigned __int64 bit_count;
      //The count of bits processed thus far.  The algorithm here
      //works in bytes, not bits, so this is advanced by 8 on
      //each byte processed.  FIPS 180-3 calls for processing
	  //messages up to length 2^128, but for obvious reasons
	  //we don't do that.  2^64-1 bits is in excess of 2^61-1
	  //bytes, or somewhere around 2,000 terabytes.  This
	  //isn't a practical limit with current computer technology.
   unsigned __int64 M[16];
      //These are the words corresponding to the chars (below).  We don't
      //dare union to extract them because of big-endian/little-endian concerns.
      //The "M" nomenclature is from FIPS 180-3.  At the time the
	  //SHA-512 rounds are done, the chars (below) are converted to words
	  //(this field) so that the rounds can be done using the words.
   unsigned char buf[128];
      //We can't proceed to execute a round unless we have the 
      //full 1024 bits = 16 words = 128 bytes of data.  We must
      //buffer it because we can't count on being called with data
      //blocks that are a multiple of 128.  We may have data hanging
      //around between calls.  We fill up this buffer from the low
      //end, i.e. [0], then [1], then [2], etc.
   };


//Result structure, used to hold result.  Caller is allowed to
//pick it apart.
//
struct FILEHASH_SHA512_Sha512ResultStruct
   {
   unsigned __int64 sha512_words[8];
      //Hash in binary form, as the 64-bit integers.
   char     sha512_chars[129];
      //Zero-terminated string containing character representation
      //of SHA-512 formed.
   };


//This is a right rotation macro for efficiency.  This
//macro rotates a 64-bit quantity x right (cyclically) by 
//n bits.  Nomenclature from FIPS 180-3.
#define FILEHASH_SHA512_FUNC_ROTR(x, n) (((x) >> (n)) | ((x) << (64-(n))))

//This is a right shift macro for efficiency.  This
//macro shifts a 64-bit quantity x right by 
//n bits.  Nomenclature from FIPS 180-3.
#define FILEHASH_SHA512_FUNC_SHR(x, n) ((x) >> (n))

//These functions come directly from FIPS 180-3.
#define FILEHASH_SHA512_FUNC_CH(x, y, z)  (((x) & (y)) ^ (~(x) & (z)))
#define FILEHASH_SHA512_FUNC_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define FILEHASH_SHA512_FUNC_SIGMABIG_0(x) (FILEHASH_SHA512_FUNC_ROTR(x, 28) ^ FILEHASH_SHA512_FUNC_ROTR(x, 34) ^ FILEHASH_SHA512_FUNC_ROTR(x, 39))
#define FILEHASH_SHA512_FUNC_SIGMABIG_1(x) (FILEHASH_SHA512_FUNC_ROTR(x, 14) ^ FILEHASH_SHA512_FUNC_ROTR(x, 18) ^ FILEHASH_SHA512_FUNC_ROTR(x, 41))
#define FILEHASH_SHA512_FUNC_SIGMASMALL_0(x) (FILEHASH_SHA512_FUNC_ROTR(x,  1) ^ FILEHASH_SHA512_FUNC_ROTR(x,  8) ^ FILEHASH_SHA512_FUNC_SHR(x,  7))
#define FILEHASH_SHA512_FUNC_SIGMASMALL_1(x) (FILEHASH_SHA512_FUNC_ROTR(x, 19) ^ FILEHASH_SHA512_FUNC_ROTR(x, 61) ^ FILEHASH_SHA512_FUNC_SHR(x,  6))


//Constants, from FIPS 180-3.
const unsigned __int64 FILEHASH_SHA512_K[80] =
            {0x428a2f98d728ae22UL, 0x7137449123ef65cdUL,
             0xb5c0fbcfec4d3b2fUL, 0xe9b5dba58189dbbcUL,
             0x3956c25bf348b538UL, 0x59f111f1b605d019UL,
             0x923f82a4af194f9bUL, 0xab1c5ed5da6d8118UL,
             0xd807aa98a3030242UL, 0x12835b0145706fbeUL,
             0x243185be4ee4b28cUL, 0x550c7dc3d5ffb4e2UL,
             0x72be5d74f27b896fUL, 0x80deb1fe3b1696b1UL,
             0x9bdc06a725c71235UL, 0xc19bf174cf692694UL,
             0xe49b69c19ef14ad2UL, 0xefbe4786384f25e3UL,
             0x0fc19dc68b8cd5b5UL, 0x240ca1cc77ac9c65UL,
             0x2de92c6f592b0275UL, 0x4a7484aa6ea6e483UL,
             0x5cb0a9dcbd41fbd4UL, 0x76f988da831153b5UL,
             0x983e5152ee66dfabUL, 0xa831c66d2db43210UL,
             0xb00327c898fb213fUL, 0xbf597fc7beef0ee4UL,
             0xc6e00bf33da88fc2UL, 0xd5a79147930aa725UL,
             0x06ca6351e003826fUL, 0x142929670a0e6e70UL,
             0x27b70a8546d22ffcUL, 0x2e1b21385c26c926UL,
             0x4d2c6dfc5ac42aedUL, 0x53380d139d95b3dfUL,
             0x650a73548baf63deUL, 0x766a0abb3c77b2a8UL,
             0x81c2c92e47edaee6UL, 0x92722c851482353bUL,
             0xa2bfe8a14cf10364UL, 0xa81a664bbc423001UL,
             0xc24b8b70d0f89791UL, 0xc76c51a30654be30UL,
             0xd192e819d6ef5218UL, 0xd69906245565a910UL,
             0xf40e35855771202aUL, 0x106aa07032bbd1b8UL,
             0x19a4c116b8d2d0c8UL, 0x1e376c085141ab53UL,
             0x2748774cdf8eeb99UL, 0x34b0bcb5e19b48a8UL,
             0x391c0cb3c5c95a63UL, 0x4ed8aa4ae3418acbUL,
             0x5b9cca4f7763e373UL, 0x682e6ff3d6b2b8a3UL,
             0x748f82ee5defb2fcUL, 0x78a5636f43172f60UL,
             0x84c87814a1f0ab72UL, 0x8cc702081a6439ecUL,
             0x90befffa23631e28UL, 0xa4506cebde82bde9UL,
             0xbef9a3f7b2c67915UL, 0xc67178f2e372532bUL,
             0xca273eceea26619cUL, 0xd186b8c721c0c207UL,
             0xeada7dd6cde0eb1eUL, 0xf57d4f7fee6ed178UL,
             0x06f067aa72176fbaUL, 0x0a637dc5a2c898a6UL,
             0x113f9804bef90daeUL, 0x1b710b35131c471bUL,
             0x28db77f523047d84UL, 0x32caab7b40c72493UL,
             0x3c9ebe0a15c9bebcUL, 0x431d67c49c100d4cUL,
             0x4cc5d4becb3e42b6UL, 0x597f299cfc657e2aUL,
             0x5fcb6fab3ad6faecUL, 0x6c44198c4a475817UL};


//Initializes an SHA-512 state structure in preparation for adding data.
//
void FILEHASH_SHA512_Sha512StateStructOpen(struct FILEHASH_SHA512_Sha512StateStruct *arg)
   {
   memset(arg, 0, sizeof(struct FILEHASH_SHA512_Sha512StateStruct));
      //Set everything to zero--processed bitcount set to zero.

   //This assignment comes directly from FIPS 180-3.
   arg->H0 = 0x6a09e667f3bcc908UL;
   arg->H1 = 0xbb67ae8584caa73bUL;
   arg->H2 = 0x3c6ef372fe94f82bUL;
   arg->H3 = 0xa54ff53a5f1d36f1UL;
   arg->H4 = 0x510e527fade682d1UL;
   arg->H5 = 0x9b05688c2b3e6c1fUL;
   arg->H6 = 0x1f83d9abfb41bd6bUL;
   arg->H7 = 0x5be0cd19137e2179UL;
   }


//Copies the byte buffer to the word buffer within the state block.
//This is done in a way which hides big-endian/little-endian concerns.
//
static void FILEHASH_SHA512_CopyBytesToWords(struct FILEHASH_SHA512_Sha512StateStruct *arg)
   {
   unsigned int i;

   assert(arg != NULL);

   //Copy the buffer contents into the words.  We need to be careful
   //to do this correctly, because of big-endian/little-endian concerns.
   //From FIPS 180-3 (alluded to, not really stated), the message is
   //loaded in from M[0] down to M[15].  Additionally, per the other
   //conventions in the document, the first byte is uppermost in each
   //word.
   for (i=0; i<16; i++)
      {
      assert((i * 8 + 7) < 128);

      arg->M[i] = (((unsigned __int64)(arg->buf[i*8+0])) << 56)
                  +
                  (((unsigned __int64)(arg->buf[i*8+1])) << 48)
                  +
                  (((unsigned __int64)(arg->buf[i*8+2])) << 40)
                  +
                  (((unsigned __int64)(arg->buf[i*8+3])) << 32)
                  +
                  (((unsigned __int64)(arg->buf[i*8+4])) << 24)
                  +
                  (((unsigned __int64)(arg->buf[i*8+5])) << 16)
                  +
                  (((unsigned __int64)(arg->buf[i*8+6])) <<  8)
                  +
                  (((unsigned __int64)(arg->buf[i*8+7])));
      }
   }


//Copies the buffer of words into a string buffer of string length 128, and also places
//the zero terminator, which means that the string supplied by the caller must be of size
//129 or larger.
//
static void FILEHASH_SHA512_CopyWordsToStringBuffer(struct FILEHASH_SHA512_Sha512ResultStruct *arg)
   {
   unsigned int i, j;
   unsigned char *puc;
   unsigned __int64 woi;

   assert(arg != NULL);

   //Copy the buffer contents into the words.  We need to be careful
   //to do this correctly, because of big-endian/little-endian concerns.
   //From FIPS 180-3 (alluded to, not really stated), the message is
   //loaded in from M[0] down to M[15].  Additionally, per the other
   //conventions in the document, the first byte is uppermost in each
   //word.
   for (i=0; i<8; i++)
      {
      woi = arg->sha512_words[i];

	  //Form a pointer to the buffer location of interest.  We work
	  //backwards.
	  puc = (unsigned char *)(arg->sha512_chars) + (i * 16) + 15;

	  //Fill in the buffer.
      for (j=0; j<16; j++)
	    {
        *puc = (unsigned char)CF_nibble_to_lc_hex_digit((int)(woi & 0xF));
		woi >>= 4;
		puc--;
	    }
      }

   //Place the zero string terminator.
   arg->sha512_chars[128] = 0;
   }


//Do the SHA-512 rounds as specified by FIPS 180-3.
//
static void FILEHASH_SHA512_DoSha512Rounds(struct FILEHASH_SHA512_Sha512StateStruct *arg)
   {
   int i;
      //Iteration variable.
   unsigned __int64 T1, T2;
      //Temporary variables.  Nomenclature is from FIPS 180-3.
   unsigned __int64 M[16];
      //Buffer of message block to avoid repeated dereferences.
   unsigned __int64 H[8];
      //Buffer of hash state to avoid repeated dereferences.
   unsigned __int64 W[80];
      //Working variable.  Nomenclature directly from FIPS 180-3.
   unsigned __int64 a, b, c, d, e, f, g, h;
      //Nomenclature above directly from FIPS 180-3.

   assert(arg != NULL);

   //Copy bytes into words.
   FILEHASH_SHA512_CopyBytesToWords(arg);

   //Copy out the message buffer for speed.  This should avoid repeated
   //dereferences.
   M[ 0] = arg->M[ 0];
   M[ 1] = arg->M[ 1];
   M[ 2] = arg->M[ 2];
   M[ 3] = arg->M[ 3];
   M[ 4] = arg->M[ 4];
   M[ 5] = arg->M[ 5];
   M[ 6] = arg->M[ 6];
   M[ 7] = arg->M[ 7];
   M[ 8] = arg->M[ 8];
   M[ 9] = arg->M[ 9];
   M[10] = arg->M[10];
   M[11] = arg->M[11];
   M[12] = arg->M[12];
   M[13] = arg->M[13];
   M[14] = arg->M[14];
   M[15] = arg->M[15];

   //Copy out the hash state for speed.  This should avoid repeated dereferences.
   H[0]  = arg->H0;
   H[1]  = arg->H1;
   H[2]  = arg->H2;
   H[3]  = arg->H3;
   H[4]  = arg->H4;
   H[5]  = arg->H5;
   H[6]  = arg->H6;
   H[7]  = arg->H7;

   //Prepare the message schedule.  The nomenclature comes directly from FIPS 180-3.
   W[ 0] = M[ 0];
   W[ 1] = M[ 1];
   W[ 2] = M[ 2];
   W[ 3] = M[ 3];
   W[ 4] = M[ 4];
   W[ 5] = M[ 5];
   W[ 6] = M[ 6];
   W[ 7] = M[ 7];
   W[ 8] = M[ 8];
   W[ 9] = M[ 9];
   W[10] = M[10];
   W[11] = M[11];
   W[12] = M[12];
   W[13] = M[13];
   W[14] = M[14];
   W[15] = M[15];

   for (i=16; i<80; i++)
      {
      W[i] =    FILEHASH_SHA512_FUNC_SIGMASMALL_1(W[i-2])
		     +  W[i-7]
	         +  FILEHASH_SHA512_FUNC_SIGMASMALL_0(W[i-15])
			 +  W[i-16];
      }

   //Initialize the 8 working variables as specified in FIPS 180-3.
   a = H[0];
   b = H[1];
   c = H[2];
   d = H[3];
   e = H[4];
   f = H[5];
   g = H[6];
   h = H[7];

   //Perform the rounds as specified in FIPS 180-3.  Nomenclature below comes from 
   //FIPS 180-3.
   for (i=0; i<80; i++)
      {
      T1 =    h 
		    + FILEHASH_SHA512_FUNC_SIGMABIG_1(e) 
			+ FILEHASH_SHA512_FUNC_CH(e, f, g)
			+ FILEHASH_SHA512_K[i]
	        + W[i];
	  //
      T2 =    FILEHASH_SHA512_FUNC_SIGMABIG_0(a)
            + FILEHASH_SHA512_FUNC_MAJ(a, b, c);
      //
	  h = g;
	  //
	  g = f;
	  //
	  f = e;
	  //
	  e = d + T1;
	  //
	  d = c;
	  //
	  c = b;
	  //
	  b = a;
	  //
	  a = T1 + T2;
      }

   //Compute the next hash value.  The nomenclature comes from FIPS 180-3.
   H[0] = a + H[0];
   H[1] = b + H[1];
   H[2] = c + H[2];
   H[3] = d + H[3];
   H[4] = e + H[4];
   H[5] = f + H[5];
   H[6] = g + H[6];
   H[7] = h + H[7];

   //Place the local variables back in the structure.  This the only state that
   //gets preserved between the operation of doing the rounds.
   arg->H0 = H[0];
   arg->H1 = H[1];
   arg->H2 = H[2];
   arg->H3 = H[3];
   arg->H4 = H[4];
   arg->H5 = H[5];
   arg->H6 = H[6];
   arg->H7 = H[7];
   }


//Adds a block of data to the SHA-512 structure.  Zero length is allowed.
//
void FILEHASH_SHA512_Sha512StateStructAddData(struct    FILEHASH_SHA512_Sha512StateStruct *arg,
                                              void      *pointer_in,
                                              unsigned  len)
   {
   unsigned int   low_32;
   unsigned int   byte_offset;
   unsigned char *data;

   assert((len == 0) || (arg != NULL));
   assert(pointer_in != NULL);

   data = (unsigned char *)pointer_in;
      //It is easier to do it this way, rather than cast all the time.

   low_32 = (unsigned int)arg->bit_count;
      //Copy off the least significant bits.  Easier to do once.  We only
      //need the 32 least significant because the block size is 0 modulo 1024.

   byte_offset = low_32 >> 3;
      //This gives our byte offset, up to 500+Mb or so.

   while(len--)
      {
      //We process rounds AFTER a byte is added to the buffer.  So
      //it is always safe to add a byte first.
      arg->buf[byte_offset & 0x7F] = *data;

      //Nothing to do unless this was the final byte of the buffer.
      if ((byte_offset & 0x7F) == 127)
         {
         FILEHASH_SHA512_DoSha512Rounds(arg);
         }

      //Increment.
      data++;
      byte_offset++;
      arg->bit_count += 8;
      }
   }


//Closes the SHA-512 structure and places the SHA-512 result into the result structure.
//After this operation, state is destroyed and no further data may be added.
//
void FILEHASH_SHA512_Sha512StateStructClose(struct FILEHASH_SHA512_Sha512StateStruct  *state,
                                            struct FILEHASH_SHA512_Sha512ResultStruct *result)
   {
   unsigned __int64 msglen;
      //Used to hold message length before we pad the message.
   unsigned char c80 = 0x80;
      //Used to append the "1" per FIPS 180-3.
   unsigned char c00 = 0x00;
      //Used to add 0's per FIPS 180-3.
   unsigned char  length_buf[16];
      //Buffer used to form the message length and append it to the message per FIPS 180-3.

   //Be sure the input pointers aren't obviously invalid.
   assert(state  != NULL);
   assert(result != NULL);

   //Snapshot the message length.  We'll be changing it when we pad the message.
   msglen = state->bit_count;

   //Add the required "1" to the end of the message, per FIPS 180-3.  Because
   //this software module only allows the addition of bytes (not bits), adding the
   //"1" will always involve adding the byte 0x80.
   FILEHASH_SHA512_Sha512StateStructAddData(state, &c80, 1);

   //Add enough 0's to the message so that we have exactly room for 16 bytes (128 bits)
   //of length information at the end of the message.
   while ((state->bit_count & 0x3FF) != 896)
      FILEHASH_SHA512_Sha512StateStructAddData(state, &c00, 1);

   //Calculate the length as a series of bytes.
   length_buf[ 0] = 0;
   length_buf[ 1] = 0;
   length_buf[ 2] = 0;
   length_buf[ 3] = 0;
   length_buf[ 4] = 0;
   length_buf[ 5] = 0;
   length_buf[ 6] = 0;
   length_buf[ 7] = 0;
   length_buf[ 8] = (unsigned char)((msglen >> 56) & 0xFF);
   length_buf[ 9] = (unsigned char)((msglen >> 48) & 0xFF);
   length_buf[10] = (unsigned char)((msglen >> 40) & 0xFF);
   length_buf[11] = (unsigned char)((msglen >> 32) & 0xFF);
   length_buf[12] = (unsigned char)((msglen >> 24) & 0xFF);
   length_buf[13] = (unsigned char)((msglen >> 16) & 0xFF);
   length_buf[14] = (unsigned char)((msglen >>  8) & 0xFF);
   length_buf[15] = (unsigned char)((msglen) & 0xFF);

   //Add the length to the message.  This should work out to generate the
   //final manipulation round.
   FILEHASH_SHA512_Sha512StateStructAddData(state, length_buf, 16);

   //Copy the words from the state vector to the result vector.
   result->sha512_words[0] = state->H0;
   result->sha512_words[1] = state->H1;
   result->sha512_words[2] = state->H2;
   result->sha512_words[3] = state->H3;
   result->sha512_words[4] = state->H4;
   result->sha512_words[5] = state->H5;
   result->sha512_words[6] = state->H6;
   result->sha512_words[7] = state->H7;

   //Form a string from the hash vector.
   FILEHASH_SHA512_CopyWordsToStringBuffer(result);

   //Destroy the state, which may contain sensitive information.
   memset(state, 0, sizeof(struct FILEHASH_SHA512_Sha512StateStruct));
   }


//Main function for Windows.
//
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
   {
   HWND         hwnd ;
   HMENU        hmenu;
   MSG          msg ;
   WNDCLASS     wndclass ;

   //Store our current parent thread ID.  The child process will need
   //to know this to post a message.  This is expected to be
   //invariant for the life of the program.
   FILEHASH_parent_thread_id = GetCurrentThreadId();

   //Zero out the file information block.
   memset((char *)&FILEHASH_file_info, 0, sizeof(FILEHASH_file_info));

   wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
   wndclass.lpfnWndProc   = WndProc ;
   wndclass.cbClsExtra    = 0 ;
   wndclass.cbWndExtra    = 0 ;
   wndclass.hInstance     = hInstance ;
   wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON)) ;
   wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
   wndclass.hbrBackground = (HBRUSH) (COLOR_BTNFACE+1) ;
   wndclass.lpszMenuName  = NULL ;
   wndclass.lpszClassName = FILEHASH_szAppName ;

   if (!RegisterClass (&wndclass))
      {
      MessageBox (NULL, 
                 TEXT ("Error code from RegisterClass() Win32 API function.    \nThe most probable cause is an incompatible operating system."), 
                 FILEHASH_szAppName, 
                 MB_ICONERROR) ;
      return 0 ;
      }
     
   //We need to do some voodoo to figure out how large to make the main window.
   //The feeling is that the window should be as small as possible to display the
   //results from an individual file (the most common application), and if the user
   //wants it bigger it can be resized.  Three lines are required (file name, file 
   //size, and SHA-512), so that needs to be the height.  A file
   //SHA-512 is 512 bits = 128 characters.  In addition, there is the constraint that we
   //cannot go beyond the width and height of a screen.  The guess below is quite
   //crude, assuming that the edit box has a larger font, etc.
   {
   int initial_width = 0;
   int initial_height = 0;

   //Get a crude measure of how big text is.
   initial_width =  LOWORD(GetDialogBaseUnits());
   initial_height = HIWORD(GetDialogBaseUnits());

   //Dope it up linearly.
   initial_width  = (initial_width * 1500)/10;
   initial_height = (initial_height * 150)/10; 

   {
   int temp;

   //Be sure nothing is bigger than 2/3 screen dimensions.
   temp = (GetSystemMetrics(SM_CXFULLSCREEN) * 2) / 3;
   if (initial_width > temp)
      initial_width = temp;
   temp = (GetSystemMetrics(SM_CYFULLSCREEN) * 2) / 3;
   if (initial_height > temp)
      initial_height = temp;
   }

   //Load up the menu resources.  I have verified in documentation that this will be destroyed
   //automatically.
   hmenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_FILEHASH));

   //Create the window.  The "Ex" call is used to make it a topmost window.
   hwnd = CreateWindowEx (
                       WS_EX_TOPMOST,
                       FILEHASH_szAppName,         // window class name
                       TEXT ("FileHash"),          // window caption
                       WS_OVERLAPPEDWINDOW,        // window style
                       CW_USEDEFAULT,              // initial x position
                       CW_USEDEFAULT,              // initial y position
                       initial_width,              // initial x size
                       initial_height,             // initial y size
                       NULL,                       // parent window handle
                       hmenu,                      // window menu handle
                       hInstance,                  // program instance handle
                       NULL) ;                     // creation parameters
   }
     
   
   FILEHASH_parent_thread_main_window_handle = hwnd;

   //This is standard code from Petzold's book.  Don't know _exactly_ what it does, but
   //every Windows program seems to have it.
   ShowWindow (hwnd, iCmdShow) ;
   UpdateWindow (hwnd) ;
     
   while (GetMessage (&msg, NULL, 0, 0))
      {
      TranslateMessage (&msg) ;
      DispatchMessage (&msg) ;
      }

   return msg.wParam ;
   }


//This is the subclass WndProc.   This had to be done to allow the edit 
//control to catch the WM_DROPFILES event.
//
LRESULT CALLBACK FILEHASH_ReplacementEditProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
   static int iDeltaPerLine = 120, iAccumDelta = 0;
      //These are for mouse wheel logic.  It may happen in the future that more
      //precise mice without notches are introduced.

   //We need to watch for the drop target notification message, and take action 
   //in that case.
   switch(message)
      {
      case WM_DROPFILES:
         {
         int iFiles;
         int i;
         HDROP hDropInfo = (HANDLE)wParam;

         //Do a hard sync stop on the child thread.  This should not take
         //very long.  A new drag'n'drop event will just cause restart
         //with the new set of files.
         FILEHASH_ChildThreadHardSyncStop();

         //Zero out the file information area and the text buffer mirror.
         memset((char *)&FILEHASH_file_info, 0, sizeof(FILEHASH_file_info));
         FILEHASH_dispbuf[0] = 0;

         // Get the number of files and folders that were dropped.
         iFiles = DragQueryFile (hDropInfo, (DWORD)(-1), (LPSTR)NULL, 0);

         //Copy the paths to the right buffer area.
         for (i=0; (i<iFiles) && (i<FILEHASH_MAXFILES); i++)
            {
            DragQueryFile (hDropInfo, i, (LPSTR)(FILEHASH_file_info.file_info[i].fpath), MAX_PATH);
            }

         //Start up the child thread.
         FILEHASH_ChildThreadStart();

         break;
         }
      case WM_MOUSEWHEEL:
         {
         iAccumDelta += (short) HIWORD (wParam);

         while (iAccumDelta >= iDeltaPerLine)
            {
            SendMessage(hwnd, WM_VSCROLL, SB_PAGEUP, 0);
            iAccumDelta -= iDeltaPerLine;
            //iAccumDelta = 0;
            }

         while (iAccumDelta <= -iDeltaPerLine)
            {
            SendMessage(hwnd, WM_VSCROLL, SB_PAGEDOWN, 0);
            iAccumDelta += iDeltaPerLine;
            //iAccumDelta = 0;
            }

         break;
         }
      }

   //Call the old Window procedure.
   return (CallWindowProc(FILEHASH_old_win_edit_handler, hwnd, message, wParam, lParam));
   }


//Stages the display buffer in preparation for outputting it out
//to the edit child window.  This function generally interacts
//with the file information data structure even while the
//child thread is running.  This is OK, as race conditions are
//covered.  Essentially, as the child thread proceeds, it updates
//data then afterwards flags it as valid.  This function
//never proceeds into invalid data.
//
static void FILEHASH_StageDisplayBuffer(void)
   {
   int dispbufidx;
   int nfiles;
   int len;
   int i;
   char buf[2*MAX_PATH+200];

   //Count the number of files queued, and put that in the buffer.
   dispbufidx = 0;
   nfiles=0;
   for (i=0; i<FILEHASH_MAXFILES; i++)
      {
      if (FILEHASH_file_info.file_info[i].fpath[0])
         {
         nfiles++;
         }
      else
         {
         break;
         }
      }
   sprintf_s(buf, sizeof(buf), "Files to signature:  %d.\x0d\x0a", nfiles);
   len = strlen(buf);
   if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
      {
      strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf) - dispbufidx,buf);
      dispbufidx += len;
      }

   //Loop through and output the information for each file.
   for (i=0; i<FILEHASH_MAXFILES; i++)
      {
      if ((FILEHASH_file_info.file_info[i].fpath[0]) && (FILEHASH_file_info.file_info[i].is_directory_valid))
         {
         sprintf_s(buf, sizeof(buf), "--------------------\x0d\x0a");
         len = strlen(buf);
         if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
            {
            strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
            dispbufidx += len;
            }

         sprintf_s(buf, sizeof(buf), "[%03d/%03d] %s\x0d\x0a", i+1, nfiles, FILEHASH_file_info.file_info[i].fpath);
         len = strlen(buf);
         if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
            {
            strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
            dispbufidx += len;
            }

         //If the file is actually a directory or there was an error, we can't
         //do further processing on it.
         if (FILEHASH_file_info.file_info[i].is_directory_error)
            {
            sprintf_s(buf, sizeof(buf), "\tError obtaining file attributes--cannot process this file.\x0d\x0a");
            len = strlen(buf);
            if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
               {
               strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
               dispbufidx += len;
               }
            }
         else if (FILEHASH_file_info.file_info[i].is_directory)
            {
            sprintf_s(buf, sizeof(buf), "\tThis item is a directory and will not be signatured.\x0d\x0a");
            len = strlen(buf);
            if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
               {
               strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
               dispbufidx += len;
               }
            }
         else
            {
            //This is not a directory.  We can print the rest of the 
            //information.
            //
            //First, the file size.
            if (FILEHASH_file_info.file_info[i].file_size_valid)
               {
               char buf2[100];

               buf2[0] = 0;  //Just in case conversion doesn't go right.
               sprintf_s(buf2, sizeof(buf2), "%I64u", FILEHASH_file_info.file_info[i].file_size);
               BSF_commanate(buf2);
               sprintf_s(buf, sizeof(buf), "\tSize:\t%s\x0d\x0a", buf2);

               len = strlen(buf);
               if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
                  {
                  strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
                  dispbufidx += len;
                  }
               }

			//Now, the SHA512.
            if (FILEHASH_file_info.file_info[i].sha512_valid)
               {
               sprintf_s(buf, sizeof(buf), "\tSHA-512:\t%s\x0d\x0a", FILEHASH_file_info.file_info[i].sha512);
               len = strlen(buf);
               if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
                  {
                  strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
                  dispbufidx += len;
                  }
               }
            }
         }
      else
         {
         break;
         }

      }

   //Process the termination condition information.
   if (FILEHASH_file_info.aborted)
      {
      sprintf_s(buf, sizeof(buf), "-------------------- FILE SIGNATURE ABORTED --------------------");
      }
   else if (FILEHASH_file_info.terminated_normally)
      {
      sprintf_s(buf, sizeof(buf), "-------------------- FILE SIGNATURE COMPLETE --------------------");
      }
   else
      {
      sprintf_s(buf, sizeof(buf), "-------------------- FILE SIGNATURE IN PROGRESS -------------------");
      }

   len = strlen(buf);
   if ((len + dispbufidx + 2) < FILEHASH_DISPBUFLEN)
      {
      strcpy_s(FILEHASH_dispbuf+dispbufidx, sizeof(FILEHASH_dispbuf)-dispbufidx, buf);
      dispbufidx += len;
      }
   }


//Pushes the display buffer out to the edit control.
//
static int FILEHASH_UpdateEditControl(HWND te_wind)
   {
   SetWindowText(te_wind, FILEHASH_dispbuf);

   //Must set the buffer position (i.e. the display position) to the end.
   //The "/10" assumes that there can't be more than 8 chars or so per line--
   //couldn't find a way to go to the end automatically.
   SendMessage(te_wind,EM_LINESCROLL,0,FILEHASH_DISPBUFLEN/8);

   return(0);
   }


//This is the Windows procedure and event loop for the 
//main Window.
//
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
   HDC         hdc ;
   PAINTSTRUCT ps ;
   static RECT        rect ;
   static HWND te_wind = 0;

   switch (message)
      {
      case WM_CREATE:
         {
         //Need to get the size of our current window so we can create the
         //child same size.
         //
         GetClientRect (hwnd, &rect);

         te_wind = CreateWindow ("EDIT",                            // window class name
                             "",                                    // window caption
                             WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_WANTRETURN,        // window style
                             0,                                     // initial x position
                             0,                                     // initial y position
                             rect.right,                            // initial x size
                             rect.bottom,                           // initial y size
                             hwnd,                                  // parent window handle
                             (HMENU) 1,                             // window menu handle
                             ((LPCREATESTRUCT)lParam)->hInstance,   // program instance handle
                             NULL) ;                                // creation parameters
         //Print initial usage instructions.
         SetWindowText(te_wind, "FILEHASH, Copyright \xA9 2010 David T. Ashley\x0d\x0a"
                                "\x0d\x0a"
                                "This program is provided under the GNU General Public License, Version 3, and comes with ABSOLUTELY NO WARRANTY.  "
                                "This is free software, and you are welcome to redistribute it.  For a copy of the source code and license, please write to "
                                "David T. Ashley (dashley@gmail.com)."
                                "\x0d\x0a"
                                "\x0d\x0a"
                                "To calculate "
			                    "SHA-512 message digests, "
                                "drag and drop files into this box (from Windows Explorer "
                                "or a similar application), or use the FILE->OPEN "
                                "menu selection.  Text can be freely selected and "
                                "copied from this window (select the desired text "
                                "and use the right mouse button to obtain a popup menu "
                                "which includes COPY).");

         //Tell Windows that this child is a fair drop target for files.
         DragAcceptFiles (te_wind, TRUE);

         //We need to subclass the child window, which is to define a new wndproc
         //for it.
         FILEHASH_old_win_edit_handler = (WNDPROC) SetWindowLong(te_wind, GWL_WNDPROC, (long) FILEHASH_ReplacementEditProc);

         return 0 ;
         }
      case WM_SIZE:
         {
         rect.left = 0;
         rect.top = 0;
         rect.right = LOWORD(lParam);
         rect.bottom = HIWORD(lParam);
         MoveWindow(te_wind, 0, 0, rect.right, rect.bottom, TRUE);
         return 0;
         }
      case WM_PAINT:
         {
         hdc = BeginPaint (hwnd, &ps) ;

         GetClientRect (hwnd, &rect) ;
          
         EndPaint (hwnd, &ps) ;
         return 0 ;
         }
      case WM_DESTROY:
         {
         PostQuitMessage (0) ;
         FILEHASH_ChildThreadHardSyncStop();
         return 0 ;
         }
      //This is a home-spun event which means that there are files to be processed.
      //This is sent once when the drop is initially done and then each time a file
      //is processed another event is used to continue the process, until finally
      //there are no more files to do.
      case WM_USER_EV_CHILD_THREAD_PROGRESS:
         {
         //Just recalc the mirror buffer and redisplay it.
         FILEHASH_StageDisplayBuffer();
         FILEHASH_UpdateEditControl(te_wind);
         return 0;
         }
      case WM_USER_EV_CHILD_THREAD_ENDING:
         {
         HMENU hMenu;

         //Just recalc the mirror buffer and redisplay it.
         FILEHASH_StageDisplayBuffer();
         FILEHASH_UpdateEditControl(te_wind);
         FILEHASH_MakeGenericSound();

         hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);

         EnableMenuItem(hMenu, ID_ACTIONS_HALTSIGOP, MF_GRAYED);

         return 0;
         }
      case WM_COMMAND:
         {
         switch(LOWORD(wParam))
            {
            case ID_FILE_OPEN_FOR_SIG:
               {
               OPENFILENAME ofn;
               static char szFilter[] = "All Files (*.*)\0*.*\0\0";

               //Set up for the dialog.
               FILEHASH_dialog_file_open_buffer[0] = 0;  //Be sure that initial name zero'd out.
               FILEHASH_dialog_file_open_buffer[1] = 0;

               ofn.lStructSize = sizeof(OPENFILENAME);
               ofn.hwndOwner         = hwnd ;
               ofn.hInstance         = NULL ;
               ofn.lpstrFilter       = szFilter;
               ofn.lpstrCustomFilter = NULL ;
               ofn.nMaxCustFilter    = 0 ;
               ofn.nFilterIndex      = 0 ;
               ofn.lpstrFile         = FILEHASH_dialog_file_open_buffer;
               ofn.nMaxFile          = sizeof(FILEHASH_dialog_file_open_buffer) - 1;
               ofn.lpstrFileTitle    = NULL;
               ofn.nMaxFileTitle     = 0;
               ofn.lpstrInitialDir   = NULL ;
               ofn.lpstrTitle        = "Open File(s) For Message Digest Calculation" ;
               ofn.Flags             = OFN_ALLOWMULTISELECT
                                     | OFN_FILEMUSTEXIST
                                     | OFN_HIDEREADONLY
                                     | OFN_NODEREFERENCELINKS
                                     | OFN_PATHMUSTEXIST
                                     | OFN_EXPLORER
                                     | OFN_SHAREAWARE;           
               ofn.nFileOffset       = 0 ;
               ofn.nFileExtension    = 0 ;
               ofn.lpstrDefExt       = NULL;
               ofn.lCustData         = 0L ;
               ofn.lpfnHook          = NULL ;
               ofn.lpTemplateName    = NULL ;
     
               //Zero out the dialog return area buffer.
               FILEHASH_dialog_file_open_buffer[0] = 0;
               FILEHASH_dialog_file_open_buffer[1] = 0;

               if (GetOpenFileName (&ofn))
                  {
                  int dstarridx=0;
                  int srccharidx=0;

                  //There was success and something specified.  This means we must
                  //kill the child thread if it is running.
                  //Do a hard sync stop on the child thread.  This should not take
                  //very long.  A new drag'n'drop event will just cause restart
                  //with the new set of files.
                  FILEHASH_ChildThreadHardSyncStop();

                  //Zero out the file information area and the text buffer mirror.
                  memset((char *)&FILEHASH_file_info, 0, sizeof(FILEHASH_file_info));
                  FILEHASH_dispbuf[0] = 0;

                  dstarridx=0;
                  srccharidx=0;

                  //Advance to first string terminator.
                  while (FILEHASH_dialog_file_open_buffer[srccharidx] != 0)
                     srccharidx++;

                  //In the special case where the double-null is encountered immediately, there is
                  //only one file, and full path is specified.
                  //
                  if (!FILEHASH_dialog_file_open_buffer[srccharidx+1])
                     {
                     strcpy_s((char *)FILEHASH_file_info.file_info[0].fpath, sizeof(FILEHASH_file_info.file_info[0].fpath), FILEHASH_dialog_file_open_buffer);
                     }
                  else
                     {
                     //This is the multiple file case.
                     while ((dstarridx < FILEHASH_MAXFILES) && (FILEHASH_dialog_file_open_buffer[srccharidx+1]))
                        {
                        int len;

                        srccharidx++;
                        strcpy_s((char *)FILEHASH_file_info.file_info[dstarridx].fpath, sizeof(FILEHASH_file_info.file_info[dstarridx].fpath), FILEHASH_dialog_file_open_buffer);

                        //Watch out for adding two backslashes.  This can happen if the path
                        //contains only a drive letter ("c:\", for example) so that the OS
                        //adds a path on.
                        len = strlen(FILEHASH_dialog_file_open_buffer);
                        if ((len != 0) && (FILEHASH_dialog_file_open_buffer[len-1]=='\\'))
                           {
                           //Do nothing.  Watch out in modifying this.  The "len != 0" test
                           //above is to prevent an access violation in the second test--watch
                           //out when modifying this if-then-else construct.
                           }
                        else
                           {
                           strcat_s((char *)FILEHASH_file_info.file_info[dstarridx].fpath, sizeof(FILEHASH_file_info.file_info[dstarridx].fpath), "\\");
                           }
                        strcat_s((char *)FILEHASH_file_info.file_info[dstarridx].fpath, sizeof(FILEHASH_file_info.file_info[dstarridx].fpath), FILEHASH_dialog_file_open_buffer+srccharidx);
                        while (FILEHASH_dialog_file_open_buffer[srccharidx] != 0)
                           srccharidx++;
                        dstarridx++;
                        }
                     }

                  //Start up the child thread.
                  FILEHASH_ChildThreadStart();

                  //Redisplay the edit buffer.
                  FILEHASH_StageDisplayBuffer();
                  FILEHASH_UpdateEditControl(te_wind);
                  }

               return 0;
               }
            case ID_FILE_EXIT:
               {
               SendMessage(hwnd, WM_CLOSE, 0, 0);
               return 0;
               }
            case ID_ACTIONS_HALTSIGOP:
               {
               FILEHASH_ChildThreadHardSyncStop();
               FILEHASH_MakeGenericSound();
               FILEHASH_StageDisplayBuffer();
               FILEHASH_UpdateEditControl(te_wind);
               return 0;
               }
            case ID_OPTIONS_USE_SOUND:
               {
               if (FILEHASH_use_sound)
                  {
                  HMENU hMenu;

                  hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);
                  FILEHASH_use_sound = 0;
                  CheckMenuItem(hMenu, ID_OPTIONS_USE_SOUND, MF_UNCHECKED);
                  }
               else
                  {
                  HMENU hMenu;

                  hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);
                  FILEHASH_use_sound = 1;
                  CheckMenuItem(hMenu, ID_OPTIONS_USE_SOUND, MF_CHECKED);
                  }
               return 0;
               }
            case ID_OPTIONS_WINDOWALWAYSONTOP:
               {
               if (FILEHASH_always_on_top)
                  {
                  HMENU hMenu;

                  hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);
                  FILEHASH_always_on_top = 0;
                  CheckMenuItem(hMenu, ID_OPTIONS_WINDOWALWAYSONTOP, MF_UNCHECKED);
                  SetWindowPos(FILEHASH_parent_thread_main_window_handle,
                               HWND_NOTOPMOST,
                               0,
                               0,
                               0,
                               0,
                               SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
                  }
               else
                  {
                  HMENU hMenu;

                  hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);
                  FILEHASH_always_on_top = 1;
                  CheckMenuItem(hMenu, ID_OPTIONS_WINDOWALWAYSONTOP, MF_CHECKED);
                  SetWindowPos(FILEHASH_parent_thread_main_window_handle,
                               HWND_TOPMOST,
                               0,
                               0,
                               0,
                               0,
                               SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
                  }
               return 0;
               }
            case ID_HELP_ABOUT:
            case ID_HELP_HELP:
               {
               char *msg;
               char *first_line   = "FILEHASH, Copyright \xA9 2010 David T. Ashley\n\n";
               char *second_line  = "This program is provided under the GNU General Public License, Version 3, and comes with ABSOLUTELY NO WARRANTY.\n\n";
               char *third_line   = "This is free software, and you are welcome to redistribute it.  For a copy of the source code and license or to inquire "
                                    "about technical matters, please write to "
                                    "David T. Ashley (dashley@gmail.com).\n\n";
               char *fourth_line   = "[Built on " __DATE__ " at " __TIME__ "]";

               msg = malloc(
                           strlen(first_line)       +
                           strlen(second_line)      +
                           strlen(third_line)       +
                           strlen(fourth_line)      +
                           1);

               assert(msg != NULL);

               if (msg)
                  {
                  strcpy_s(msg, strlen(first_line)+strlen(second_line)+strlen(third_line)+strlen(fourth_line)+1,   first_line);
                  strcat_s(msg, strlen(first_line)+strlen(second_line)+strlen(third_line)+strlen(fourth_line)+1,   second_line);
                  strcat_s(msg, strlen(first_line)+strlen(second_line)+strlen(third_line)+strlen(fourth_line)+1,   third_line);
                  strcat_s(msg, strlen(first_line)+strlen(second_line)+strlen(third_line)+strlen(fourth_line)+1,   fourth_line);
                  MessageBox (hwnd, 
                              msg, 
                              FILEHASH_szAppName, 
                              MB_OK|MB_ICONINFORMATION) ;
                  free(msg);
                  }
               return 0 ;
               }
            }
         break;
         }
      }

   return DefWindowProc (hwnd, message, wParam, lParam) ;
   }


//This is the child thread which is started in order to calculate the SHA-512
//of a single group of files.  This is done because a single-threaded approach
//does not allow the GUI to continue to receive Windows events, and it
//clogs up the desktop with an unmoveable unresponsive blob.  This child
//thread keeps its eye on the abort flag, and will terminate if it sees that.
//It takes its input from the top of the list of filenames, and returns
//the SHA-512, which takes some time to compute.
//
static unsigned __stdcall FILEHASH_ChildThreadFunc(void *pArguments)
   {
   int fidx;
      //The index of the table entry we're currently processing.
   DWORD file_attributes;
      //The returned file attributes from the OS.
   HANDLE hFile = (HANDLE) -1;
      //The file handle used to get size and to open for reading.  This being
      //not the error value signals that it is valid and will need to be closed.
   DWORD file_size=0;
      //File size obtained from a call to the GetFileSize() function.
   DWORD file_size_high=0;
      //High 32 bits of same.
   DWORD last_error=0;
      //Result of the GetLastError() function.  This is required to properly decode
      //the file size when very large files are involved.
   DWORD rc = 0;
      //Return code from file seek.
   BOOL  rv = 0;

   struct FILEHASH_SHA512_Sha512StateStruct  sha512s;
   struct FILEHASH_SHA512_Sha512ResultStruct sha512r;
   int exit_flag = 0;
   DWORD bytes_read = 0;


   //We have been invoked.  We now just signature files until the list is
   //done or until we are asked to gracefully abort.
   for (
       fidx = 0; 
       (fidx<FILEHASH_MAXFILES) && (FILEHASH_file_info.file_info[fidx].fpath[0] != 0) && (!FILEHASH_thread_abort_request);
       fidx++
       )
      {
      //Set any values here that are critical to have right in case we must abort.
      hFile = (HANDLE) -1;
         //This has to be the error value.  If we abort, need to know whether
         //to try to close this.

      /********************************************************************************/
      /********************************************************************************/
      /*******  F I L E    A T T R I B U T E S  ***************************************/
      /********************************************************************************/
      /********************************************************************************/
      file_attributes = GetFileAttributes((char *)FILEHASH_file_info.file_info[fidx].fpath);
      if (file_attributes == 0xFFFFFFFF)
         {
         FILEHASH_file_info.file_info[fidx].is_directory_error = 1;
            //Signal trouble trying to figure out if this is a directory.  This also
            //signals that the OS does not understand the file path, so can't do much.
         }
      else if (file_attributes & FILE_ATTRIBUTE_DIRECTORY)
         {
         FILEHASH_file_info.file_info[fidx].is_directory = 1;
            //This is a directory.
         }

      //In any case, the is_directory information is now valid.
      FILEHASH_file_info.file_info[fidx].is_directory_valid = 1;

      /********************************************************************************/
      /********************************************************************************/
      /*******  F I L E    S I Z E  ***************************************************/
      /********************************************************************************/
      /********************************************************************************/
      //If this is a directory or if there was an error getting information, we
      //cannot go forward with finding file size information.
      if (FILEHASH_file_info.file_info[fidx].is_directory || FILEHASH_file_info.file_info[fidx].is_directory_error)
         {
         FILEHASH_file_info.file_info[fidx].file_size_error = 1;
         }
      else
         {
         hFile = CreateFile ((char *)FILEHASH_file_info.file_info[fidx].fpath,
                             GENERIC_READ,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                             (HANDLE)NULL);
            //Try to open the file to look at it.  The documentation
            //of the CreateFile() call is misleading in the MSDN help.
            //A web reference said that the flag combination above,
            //
            //   FILE_SHARE_READ | FILE_SHARE_WRITE,
            //
            //means "exclude none", i.e. allow others to have file open for both read
            //and write.  This seems to be the right combination to allow
            //the signaturing of documents that are open with Microsoft
            //Word or other applications.  I have no idea what will happen
            //if the file size changes while the file is open, but I
            //assume that the EOF will become true or there will be an error,
            //either of which will terminate processing of the file.
         if (hFile == (HANDLE) -1)
            {
            //Open error.  Can't go further.
            FILEHASH_file_info.file_info[fidx].file_size_error = 1;
            }
         else
            {
            //Try to obtain the file size.
            file_size = GetFileSize(hFile, &file_size_high);

            //Try to get the error flags, which we may need.
            last_error = GetLastError();
 
            //There is some voodoo involved with file size and the
            //error code.  This is documented in the GetFileSize() docs.
            if ((file_size == 0xFFFFFFFF) && (last_error != NO_ERROR))
               {
               FILEHASH_file_info.file_info[fidx].file_size_error = 1;
               }
            else
               {
               unsigned __int64 lo, hi, composite;
               //If we're here, we have a clean size.  Convert it and display it.

               //Play the bit games to get the size.
               lo = (unsigned __int64)file_size;
               hi = (unsigned __int64)file_size_high;
               composite = lo + (hi << 32);
               FILEHASH_file_info.file_info[fidx].file_size = composite;
               }
            }
         }

      //The file size information is now valid in any case.
      FILEHASH_file_info.file_info[fidx].file_size_valid = 1;

      //At this point there is potentially progress to report to
      //the main thread.  We will sit and spin until the main
      //thread will accept a posted event announcing progress
      //or until we are aborted.
      while (!PostMessage(FILEHASH_parent_thread_main_window_handle,
                          WM_USER_EV_CHILD_THREAD_PROGRESS,
                          0,
                          0)
             &&
             !FILEHASH_thread_abort_request)
         {
         Sleep(1000);  //Wait 1 second until trying again.
                       //1000ms is a long time for a modern computer,
                       //and this should be OK to ease the load if
                       //the system is encountering performance difficulties.
         }
 
      /********************************************************************************/
      /********************************************************************************/
      /*******  S H A - 5 1 2   *******************************************************/
      /********************************************************************************/
      /********************************************************************************/
      if (hFile == (HANDLE) -1)      
         {
         //File handle signals an error condition.  We cannot
         //even read the file for SHA-512.  Just set info
         //and boogie.
         strcpy_s((char *)FILEHASH_file_info.file_info[fidx].sha512, sizeof(FILEHASH_file_info.file_info[fidx].sha512), "INVALID FILE HANDLE");
         }
      else
         {
         //This is the meat of the matter where we read the file contents and do
         //the hash calculations.  The assumption made is the the buffer size
         //will be somewhere in the range of 16K-1M, so that the time to process
         //that much data is fairly small.  This should be enough granularity 
         //for a graceful voluntary thread abort.
         //
         //Rewind the file to positon 0.
         rc = SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
         if (rc == 0xFFFFFFFF)
            {
            strcpy_s((char *)FILEHASH_file_info.file_info[fidx].sha512, sizeof(FILEHASH_file_info.file_info[fidx].sha512), "FILE SEEK ERROR");
            goto file_read_loop_endpoint;
            }

         //Initialize the SHA512 state block.
         FILEHASH_SHA512_Sha512StateStructOpen(&sha512s);

         //Iterate through, reading the file and processing the blocks.  In the case
         //of an abort, we assign the strings appropriately.
         exit_flag = 0;
         while (!exit_flag)
            {
            rv = ReadFile(hFile, FILEHASH_file_read_buf, FILEHASH_FILE_READ_BUF_SIZE, &bytes_read, NULL);

            //Add whatever has been read to the running calculation.
            if (bytes_read)
               {
               FILEHASH_SHA512_Sha512StateStructAddData(&sha512s, FILEHASH_file_read_buf, bytes_read);
               }

            //Process error conditions.
            if (!rv)
               {
               strcpy_s((char *)FILEHASH_file_info.file_info[fidx].sha512, sizeof(FILEHASH_file_info.file_info[fidx].sha512), "FILE READ ERROR");
               goto file_read_loop_endpoint;
               }

            if (!bytes_read)
               {
               //This is the no-error abort when we hit the end of the file naturally.
               exit_flag = 1;
               }
            else if (FILEHASH_thread_abort_request)
               {
               strcpy_s((char *)FILEHASH_file_info.file_info[fidx].sha512, sizeof(FILEHASH_file_info.file_info[fidx].sha512), "OPERATION ABORTED");
               goto file_read_loop_endpoint;
               }
            }

         //This is the natural fallthrough when there was no error.
         //
		 //Close up the SHA-512 structure.
         FILEHASH_SHA512_Sha512StateStructClose(&sha512s, &sha512r);

         //Form up an SHA-512 string.
         strcpy_s((char *)FILEHASH_file_info.file_info[fidx].sha512, sizeof(FILEHASH_file_info.file_info[fidx].sha512), sha512r.sha512_chars);

         //Report progress to parent thread.
         while (!PostMessage(FILEHASH_parent_thread_main_window_handle,
                             WM_USER_EV_CHILD_THREAD_PROGRESS,
                             0,
                             0))
            {
            Sleep(1000);  //Wait 1 second until trying again.
            }

         file_read_loop_endpoint: ;
         }

      //In any case both CRC32 and MD5 info filled in.
      FILEHASH_file_info.file_info[fidx].sha512_valid = 1;

      //If the file handle is valid (i.e. we opened the file) we must
      //close it, regardless of cause.
      if (hFile != (HANDLE)-1)
         {
         BOOL close_result;

         close_result = CloseHandle(hFile);

         if (!close_result)
            {
            strcpy_s((char *)FILEHASH_file_info.file_info[fidx].sha512, sizeof(FILEHASH_file_info.file_info[fidx].sha512), "FILE HANDLE CLOSE ERROR");
            }
         }
      } // End for() each table entry loop.  


   //Report completion to parent thread.
   if (FILEHASH_thread_abort_request)
         FILEHASH_file_info.aborted = 1;
   else
         FILEHASH_file_info.terminated_normally = 1;

   while (!PostMessage(FILEHASH_parent_thread_main_window_handle,
                       WM_USER_EV_CHILD_THREAD_ENDING,
                       0,
                       0))
      {
      Sleep(1000);  //Wait 1 second until trying again.
      }

   return 0;
   }


//This function does a hard sync stop on the child thread if it is running.
//If not running, returns immediately.  Because the time to CRC32 or MD5 a
//single buffer is negligible, it shouldn't take long for the thread to 
//gracefully end itself.
//
static void FILEHASH_ChildThreadHardSyncStop(void)
   {
   if (FILEHASH_child_thread_is_active)
      {
      HMENU hMenu;

      FILEHASH_thread_abort_request = 1;

      WaitForSingleObject(FILEHASH_child_handle, INFINITE);

      //The thread is done.
      FILEHASH_child_thread_is_active = 0;
      FILEHASH_thread_abort_request   = 0;
      FILEHASH_child_handle           = 0;

      hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);

      EnableMenuItem(hMenu, ID_ACTIONS_HALTSIGOP, MF_GRAYED);
      }
   }


//Starts up a child thread.
//
static void FILEHASH_ChildThreadStart(void)
   {
   unsigned thread_id;
     //We just discard this.

   //We don't dare start up our single child thread unless none is already running.
   //In the release version, such an error is just ignored, but in the debug version,
   //hard stop.
   assert(!FILEHASH_child_thread_is_active);

   if (!FILEHASH_child_thread_is_active)
      {
      //Test compilation of second thread invocation.
      FILEHASH_child_handle = (HANDLE) _beginthreadex(NULL, 
                                                  0, 
                                                  &FILEHASH_ChildThreadFunc, 
                                                  NULL,
                                                  0,
                                                  &thread_id);
      if (!FILEHASH_child_handle)
         {
         //This is an error return from _beginthreadex.
         assert(0);
         }
      else
         {
         HMENU hMenu;

         FILEHASH_child_thread_is_active = 1;

         hMenu = GetMenu(FILEHASH_parent_thread_main_window_handle);

         EnableMenuItem(hMenu, ID_ACTIONS_HALTSIGOP, MF_ENABLED);
         }
      }
   }


//Makes a generic sound to alert user.  Honors the FILEHASH_use_sound state.
//
static void FILEHASH_MakeGenericSound(void)
   {
   if (FILEHASH_use_sound)
      {
      MessageBeep(MB_ICONEXCLAMATION);
      }
   }


//----------------------------------------------------------------------------------------------------
//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//
//                            Preamble
//
//  The GNU General Public License is a free, copyleft license for
//software and other kinds of works.
//
//  The licenses for most software and other practical works are designed
//to take away your freedom to share and change the works.  By contrast,
//the GNU General Public License is intended to guarantee your freedom to
//share and change all versions of a program--to make sure it remains free
//software for all its users.  We, the Free Software Foundation, use the
//GNU General Public License for most of our software; it applies also to
//any other work released this way by its authors.  You can apply it to
//your programs, too.
//
//  When we speak of free software, we are referring to freedom, not
//price.  Our General Public Licenses are designed to make sure that you
//have the freedom to distribute copies of free software (and charge for
//them if you wish), that you receive source code or can get it if you
//want it, that you can change the software or use pieces of it in new
//free programs, and that you know you can do these things.
//
//  To protect your rights, we need to prevent others from denying you
//these rights or asking you to surrender the rights.  Therefore, you have
//certain responsibilities if you distribute copies of the software, or if
//you modify it: responsibilities to respect the freedom of others.
//
//  For example, if you distribute copies of such a program, whether
//gratis or for a fee, you must pass on to the recipients the same
//freedoms that you received.  You must make sure that they, too, receive
//or can get the source code.  And you must show them these terms so they
//know their rights.
//
//  Developers that use the GNU GPL protect your rights with two steps:
//(1) assert copyright on the software, and (2) offer you this License
//giving you legal permission to copy, distribute and/or modify it.
//
//  For the developers' and authors' protection, the GPL clearly explains
//that there is no warranty for this free software.  For both users' and
//authors' sake, the GPL requires that modified versions be marked as
//changed, so that their problems will not be attributed erroneously to
//authors of previous versions.
//
//  Some devices are designed to deny users access to install or run
//modified versions of the software inside them, although the manufacturer
//can do so.  This is fundamentally incompatible with the aim of
//protecting users' freedom to change the software.  The systematic
//pattern of such abuse occurs in the area of products for individuals to
//use, which is precisely where it is most unacceptable.  Therefore, we
//have designed this version of the GPL to prohibit the practice for those
//products.  If such problems arise substantially in other domains, we
//stand ready to extend this provision to those domains in future versions
//of the GPL, as needed to protect the freedom of users.
//
//  Finally, every program is threatened constantly by software patents.
//States should not allow patents to restrict development and use of
//software on general-purpose computers, but in those that do, we wish to
//avoid the special danger that patents applied to a free program could
//make it effectively proprietary.  To prevent this, the GPL assures that
//patents cannot be used to render the program non-free.
//
//  The precise terms and conditions for copying, distribution and
//modification follow.
//
//                       TERMS AND CONDITIONS
//
//  0. Definitions.
//
//  "This License" refers to version 3 of the GNU General Public License.
//
//  "Copyright" also means copyright-like laws that apply to other kinds of
//works, such as semiconductor masks.
//
//  "The Program" refers to any copyrightable work licensed under this
//License.  Each licensee is addressed as "you".  "Licensees" and
//"recipients" may be individuals or organizations.
//
//  To "modify" a work means to copy from or adapt all or part of the work
//in a fashion requiring copyright permission, other than the making of an
//exact copy.  The resulting work is called a "modified version" of the
//earlier work or a work "based on" the earlier work.
//
//  A "covered work" means either the unmodified Program or a work based
//on the Program.
//
//  To "propagate" a work means to do anything with it that, without
//permission, would make you directly or secondarily liable for
//infringement under applicable copyright law, except executing it on a
//computer or modifying a private copy.  Propagation includes copying,
//distribution (with or without modification), making available to the
//public, and in some countries other activities as well.
//
//  To "convey" a work means any kind of propagation that enables other
//parties to make or receive copies.  Mere interaction with a user through
//a computer network, with no transfer of a copy, is not conveying.
//
//  An interactive user interface displays "Appropriate Legal Notices"
//to the extent that it includes a convenient and prominently visible
//feature that (1) displays an appropriate copyright notice, and (2)
//tells the user that there is no warranty for the work (except to the
//extent that warranties are provided), that licensees may convey the
//work under this License, and how to view a copy of this License.  If
//the interface presents a list of user commands or options, such as a
//menu, a prominent item in the list meets this criterion.
//
//  1. Source Code.
//
//  The "source code" for a work means the preferred form of the work
//for making modifications to it.  "Object code" means any non-source
//form of a work.
//
//  A "Standard Interface" means an interface that either is an official
//standard defined by a recognized standards body, or, in the case of
//interfaces specified for a particular programming language, one that
//is widely used among developers working in that language.
//
//  The "System Libraries" of an executable work include anything, other
//than the work as a whole, that (a) is included in the normal form of
//packaging a Major Component, but which is not part of that Major
//Component, and (b) serves only to enable use of the work with that
//Major Component, or to implement a Standard Interface for which an
//implementation is available to the public in source code form.  A
//"Major Component", in this context, means a major essential component
//(kernel, window system, and so on) of the specific operating system
//(if any) on which the executable work runs, or a compiler used to
//produce the work, or an object code interpreter used to run it.
//
//  The "Corresponding Source" for a work in object code form means all
//the source code needed to generate, install, and (for an executable
//work) run the object code and to modify the work, including scripts to
//control those activities.  However, it does not include the work's
//System Libraries, or general-purpose tools or generally available free
//programs which are used unmodified in performing those activities but
//which are not part of the work.  For example, Corresponding Source
//includes interface definition files associated with source files for
//the work, and the source code for shared libraries and dynamically
//linked subprograms that the work is specifically designed to require,
//such as by intimate data communication or control flow between those
//subprograms and other parts of the work.
//
//  The Corresponding Source need not include anything that users
//can regenerate automatically from other parts of the Corresponding
//Source.
//
//  The Corresponding Source for a work in source code form is that
//same work.
//
//  2. Basic Permissions.
//
//  All rights granted under this License are granted for the term of
//copyright on the Program, and are irrevocable provided the stated
//conditions are met.  This License explicitly affirms your unlimited
//permission to run the unmodified Program.  The output from running a
//covered work is covered by this License only if the output, given its
//content, constitutes a covered work.  This License acknowledges your
//rights of fair use or other equivalent, as provided by copyright law.
//
//  You may make, run and propagate covered works that you do not
//convey, without conditions so long as your license otherwise remains
//in force.  You may convey covered works to others for the sole purpose
//of having them make modifications exclusively for you, or provide you
//with facilities for running those works, provided that you comply with
//the terms of this License in conveying all material for which you do
//not control copyright.  Those thus making or running the covered works
//for you must do so exclusively on your behalf, under your direction
//and control, on terms that prohibit them from making any copies of
//your copyrighted material outside their relationship with you.
//
//  Conveying under any other circumstances is permitted solely under
//the conditions stated below.  Sublicensing is not allowed; section 10
//makes it unnecessary.
//
//  3. Protecting Users' Legal Rights From Anti-Circumvention Law.
//
//  No covered work shall be deemed part of an effective technological
//measure under any applicable law fulfilling obligations under article
//11 of the WIPO copyright treaty adopted on 20 December 1996, or
//similar laws prohibiting or restricting circumvention of such
//measures.
//
//  When you convey a covered work, you waive any legal power to forbid
//circumvention of technological measures to the extent such circumvention
//is effected by exercising rights under this License with respect to
//the covered work, and you disclaim any intention to limit operation or
//modification of the work as a means of enforcing, against the work's
//users, your or third parties' legal rights to forbid circumvention of
//technological measures.
//
//  4. Conveying Verbatim Copies.
//
//  You may convey verbatim copies of the Program's source code as you
//receive it, in any medium, provided that you conspicuously and
//appropriately publish on each copy an appropriate copyright notice;
//keep intact all notices stating that this License and any
//non-permissive terms added in accord with section 7 apply to the code;
//keep intact all notices of the absence of any warranty; and give all
//recipients a copy of this License along with the Program.
//
//  You may charge any price or no price for each copy that you convey,
//and you may offer support or warranty protection for a fee.
//
//  5. Conveying Modified Source Versions.
//
//  You may convey a work based on the Program, or the modifications to
//produce it from the Program, in the form of source code under the
//terms of section 4, provided that you also meet all of these conditions:
//
//    a) The work must carry prominent notices stating that you modified
//    it, and giving a relevant date.
//
//    b) The work must carry prominent notices stating that it is
//    released under this License and any conditions added under section
//    7.  This requirement modifies the requirement in section 4 to
//    "keep intact all notices".
//
//    c) You must license the entire work, as a whole, under this
//    License to anyone who comes into possession of a copy.  This
//    License will therefore apply, along with any applicable section 7
//    additional terms, to the whole of the work, and all its parts,
//    regardless of how they are packaged.  This License gives no
//    permission to license the work in any other way, but it does not
//    invalidate such permission if you have separately received it.
//
//    d) If the work has interactive user interfaces, each must display
//    Appropriate Legal Notices; however, if the Program has interactive
//    interfaces that do not display Appropriate Legal Notices, your
//    work need not make them do so.
//
//  A compilation of a covered work with other separate and independent
//works, which are not by their nature extensions of the covered work,
//and which are not combined with it such as to form a larger program,
//in or on a volume of a storage or distribution medium, is called an
//"aggregate" if the compilation and its resulting copyright are not
//used to limit the access or legal rights of the compilation's users
//beyond what the individual works permit.  Inclusion of a covered work
//in an aggregate does not cause this License to apply to the other
//parts of the aggregate.
//
//  6. Conveying Non-Source Forms.
//
//  You may convey a covered work in object code form under the terms
//of sections 4 and 5, provided that you also convey the
//machine-readable Corresponding Source under the terms of this License,
//in one of these ways:
//
//    a) Convey the object code in, or embodied in, a physical product
//    (including a physical distribution medium), accompanied by the
//    Corresponding Source fixed on a durable physical medium
//    customarily used for software interchange.
//
//    b) Convey the object code in, or embodied in, a physical product
//    (including a physical distribution medium), accompanied by a
//    written offer, valid for at least three years and valid for as
//    long as you offer spare parts or customer support for that product
//    model, to give anyone who possesses the object code either (1) a
//    copy of the Corresponding Source for all the software in the
//    product that is covered by this License, on a durable physical
//    medium customarily used for software interchange, for a price no
//    more than your reasonable cost of physically performing this
//    conveying of source, or (2) access to copy the
//    Corresponding Source from a network server at no charge.
//
//    c) Convey individual copies of the object code with a copy of the
//    written offer to provide the Corresponding Source.  This
//    alternative is allowed only occasionally and noncommercially, and
//    only if you received the object code with such an offer, in accord
//    with subsection 6b.
//
//    d) Convey the object code by offering access from a designated
//    place (gratis or for a charge), and offer equivalent access to the
//    Corresponding Source in the same way through the same place at no
//    further charge.  You need not require recipients to copy the
//    Corresponding Source along with the object code.  If the place to
//    copy the object code is a network server, the Corresponding Source
//    may be on a different server (operated by you or a third party)
//    that supports equivalent copying facilities, provided you maintain
//    clear directions next to the object code saying where to find the
//    Corresponding Source.  Regardless of what server hosts the
//    Corresponding Source, you remain obligated to ensure that it is
//    available for as long as needed to satisfy these requirements.
//
//    e) Convey the object code using peer-to-peer transmission, provided
//    you inform other peers where the object code and Corresponding
//    Source of the work are being offered to the general public at no
//    charge under subsection 6d.
//
//  A separable portion of the object code, whose source code is excluded
//from the Corresponding Source as a System Library, need not be
//included in conveying the object code work.
//
//  A "User Product" is either (1) a "consumer product", which means any
//tangible personal property which is normally used for personal, family,
//or household purposes, or (2) anything designed or sold for incorporation
//into a dwelling.  In determining whether a product is a consumer product,
//doubtful cases shall be resolved in favor of coverage.  For a particular
//product received by a particular user, "normally used" refers to a
//typical or common use of that class of product, regardless of the status
//of the particular user or of the way in which the particular user
//actually uses, or expects or is expected to use, the product.  A product
//is a consumer product regardless of whether the product has substantial
//commercial, industrial or non-consumer uses, unless such uses represent
//the only significant mode of use of the product.
//
//  "Installation Information" for a User Product means any methods,
//procedures, authorization keys, or other information required to install
//and execute modified versions of a covered work in that User Product from
//a modified version of its Corresponding Source.  The information must
//suffice to ensure that the continued functioning of the modified object
//code is in no case prevented or interfered with solely because
//modification has been made.
//
//  If you convey an object code work under this section in, or with, or
//specifically for use in, a User Product, and the conveying occurs as
//part of a transaction in which the right of possession and use of the
//User Product is transferred to the recipient in perpetuity or for a
//fixed term (regardless of how the transaction is characterized), the
//Corresponding Source conveyed under this section must be accompanied
//by the Installation Information.  But this requirement does not apply
//if neither you nor any third party retains the ability to install
//modified object code on the User Product (for example, the work has
//been installed in ROM).
//
//  The requirement to provide Installation Information does not include a
//requirement to continue to provide support service, warranty, or updates
//for a work that has been modified or installed by the recipient, or for
//the User Product in which it has been modified or installed.  Access to a
//network may be denied when the modification itself materially and
//adversely affects the operation of the network or violates the rules and
//protocols for communication across the network.
//
//  Corresponding Source conveyed, and Installation Information provided,
//in accord with this section must be in a format that is publicly
//documented (and with an implementation available to the public in
//source code form), and must require no special password or key for
//unpacking, reading or copying.
//
//  7. Additional Terms.
//
//  "Additional permissions" are terms that supplement the terms of this
//License by making exceptions from one or more of its conditions.
//Additional permissions that are applicable to the entire Program shall
//be treated as though they were included in this License, to the extent
//that they are valid under applicable law.  If additional permissions
//apply only to part of the Program, that part may be used separately
//under those permissions, but the entire Program remains governed by
//this License without regard to the additional permissions.
//
//  When you convey a copy of a covered work, you may at your option
//remove any additional permissions from that copy, or from any part of
//it.  (Additional permissions may be written to require their own
//removal in certain cases when you modify the work.)  You may place
//additional permissions on material, added by you to a covered work,
//for which you have or can give appropriate copyright permission.
//
//  Notwithstanding any other provision of this License, for material you
//add to a covered work, you may (if authorized by the copyright holders of
//that material) supplement the terms of this License with terms:
//
//    a) Disclaiming warranty or limiting liability differently from the
//    terms of sections 15 and 16 of this License; or
//
//    b) Requiring preservation of specified reasonable legal notices or
//    author attributions in that material or in the Appropriate Legal
//    Notices displayed by works containing it; or
//
//    c) Prohibiting misrepresentation of the origin of that material, or
//    requiring that modified versions of such material be marked in
//    reasonable ways as different from the original version; or
//
//    d) Limiting the use for publicity purposes of names of licensors or
//    authors of the material; or
//
//    e) Declining to grant rights under trademark law for use of some
//    trade names, trademarks, or service marks; or
//
//    f) Requiring indemnification of licensors and authors of that
//    material by anyone who conveys the material (or modified versions of
//    it) with contractual assumptions of liability to the recipient, for
//    any liability that these contractual assumptions directly impose on
//    those licensors and authors.
//
//  All other non-permissive additional terms are considered "further
//restrictions" within the meaning of section 10.  If the Program as you
//received it, or any part of it, contains a notice stating that it is
//governed by this License along with a term that is a further
//restriction, you may remove that term.  If a license document contains
//a further restriction but permits relicensing or conveying under this
//License, you may add to a covered work material governed by the terms
//of that license document, provided that the further restriction does
//not survive such relicensing or conveying.
//
//  If you add terms to a covered work in accord with this section, you
//must place, in the relevant source files, a statement of the
//additional terms that apply to those files, or a notice indicating
//where to find the applicable terms.
//
//  Additional terms, permissive or non-permissive, may be stated in the
//form of a separately written license, or stated as exceptions;
//the above requirements apply either way.
//
//  8. Termination.
//
//  You may not propagate or modify a covered work except as expressly
//provided under this License.  Any attempt otherwise to propagate or
//modify it is void, and will automatically terminate your rights under
//this License (including any patent licenses granted under the third
//paragraph of section 11).
//
//  However, if you cease all violation of this License, then your
//license from a particular copyright holder is reinstated (a)
//provisionally, unless and until the copyright holder explicitly and
//finally terminates your license, and (b) permanently, if the copyright
//holder fails to notify you of the violation by some reasonable means
//prior to 60 days after the cessation.
//
//  Moreover, your license from a particular copyright holder is
//reinstated permanently if the copyright holder notifies you of the
//violation by some reasonable means, this is the first time you have
//received notice of violation of this License (for any work) from that
//copyright holder, and you cure the violation prior to 30 days after
//your receipt of the notice.
//
//  Termination of your rights under this section does not terminate the
//licenses of parties who have received copies or rights from you under
//this License.  If your rights have been terminated and not permanently
//reinstated, you do not qualify to receive new licenses for the same
//material under section 10.
//
//  9. Acceptance Not Required for Having Copies.
//
//  You are not required to accept this License in order to receive or
//run a copy of the Program.  Ancillary propagation of a covered work
//occurring solely as a consequence of using peer-to-peer transmission
//to receive a copy likewise does not require acceptance.  However,
//nothing other than this License grants you permission to propagate or
//modify any covered work.  These actions infringe copyright if you do
//not accept this License.  Therefore, by modifying or propagating a
//covered work, you indicate your acceptance of this License to do so.
//
//  10. Automatic Licensing of Downstream Recipients.
//
//  Each time you convey a covered work, the recipient automatically
//receives a license from the original licensors, to run, modify and
//propagate that work, subject to this License.  You are not responsible
//for enforcing compliance by third parties with this License.
//
//  An "entity transaction" is a transaction transferring control of an
//organization, or substantially all assets of one, or subdividing an
//organization, or merging organizations.  If propagation of a covered
//work results from an entity transaction, each party to that
//transaction who receives a copy of the work also receives whatever
//licenses to the work the party's predecessor in interest had or could
//give under the previous paragraph, plus a right to possession of the
//Corresponding Source of the work from the predecessor in interest, if
//the predecessor has it or can get it with reasonable efforts.
//
//  You may not impose any further restrictions on the exercise of the
//rights granted or affirmed under this License.  For example, you may
//not impose a license fee, royalty, or other charge for exercise of
//rights granted under this License, and you may not initiate litigation
//(including a cross-claim or counterclaim in a lawsuit) alleging that
//any patent claim is infringed by making, using, selling, offering for
//sale, or importing the Program or any portion of it.
//
//  11. Patents.
//
//  A "contributor" is a copyright holder who authorizes use under this
//License of the Program or a work on which the Program is based.  The
//work thus licensed is called the contributor's "contributor version".
//
//  A contributor's "essential patent claims" are all patent claims
//owned or controlled by the contributor, whether already acquired or
//hereafter acquired, that would be infringed by some manner, permitted
//by this License, of making, using, or selling its contributor version,
//but do not include claims that would be infringed only as a
//consequence of further modification of the contributor version.  For
//purposes of this definition, "control" includes the right to grant
//patent sublicenses in a manner consistent with the requirements of
//this License.
//
//  Each contributor grants you a non-exclusive, worldwide, royalty-free
//patent license under the contributor's essential patent claims, to
//make, use, sell, offer for sale, import and otherwise run, modify and
//propagate the contents of its contributor version.
//
//  In the following three paragraphs, a "patent license" is any express
//agreement or commitment, however denominated, not to enforce a patent
//(such as an express permission to practice a patent or covenant not to
//sue for patent infringement).  To "grant" such a patent license to a
//party means to make such an agreement or commitment not to enforce a
//patent against the party.
//
//  If you convey a covered work, knowingly relying on a patent license,
//and the Corresponding Source of the work is not available for anyone
//to copy, free of charge and under the terms of this License, through a
//publicly available network server or other readily accessible means,
//then you must either (1) cause the Corresponding Source to be so
//available, or (2) arrange to deprive yourself of the benefit of the
//patent license for this particular work, or (3) arrange, in a manner
//consistent with the requirements of this License, to extend the patent
//license to downstream recipients.  "Knowingly relying" means you have
//actual knowledge that, but for the patent license, your conveying the
//covered work in a country, or your recipient's use of the covered work
//in a country, would infringe one or more identifiable patents in that
//country that you have reason to believe are valid.
//
//  If, pursuant to or in connection with a single transaction or
//arrangement, you convey, or propagate by procuring conveyance of, a
//covered work, and grant a patent license to some of the parties
//receiving the covered work authorizing them to use, propagate, modify
//or convey a specific copy of the covered work, then the patent license
//you grant is automatically extended to all recipients of the covered
//work and works based on it.
//
//  A patent license is "discriminatory" if it does not include within
//the scope of its coverage, prohibits the exercise of, or is
//conditioned on the non-exercise of one or more of the rights that are
//specifically granted under this License.  You may not convey a covered
//work if you are a party to an arrangement with a third party that is
//in the business of distributing software, under which you make payment
//to the third party based on the extent of your activity of conveying
//the work, and under which the third party grants, to any of the
//parties who would receive the covered work from you, a discriminatory
//patent license (a) in connection with copies of the covered work
//conveyed by you (or copies made from those copies), or (b) primarily
//for and in connection with specific products or compilations that
//contain the covered work, unless you entered into that arrangement,
//or that patent license was granted, prior to 28 March 2007.
//
//  Nothing in this License shall be construed as excluding or limiting
//any implied license or other defenses to infringement that may
//otherwise be available to you under applicable patent law.
//
//  12. No Surrender of Others' Freedom.
//
//  If conditions are imposed on you (whether by court order, agreement or
//otherwise) that contradict the conditions of this License, they do not
//excuse you from the conditions of this License.  If you cannot convey a
//covered work so as to satisfy simultaneously your obligations under this
//License and any other pertinent obligations, then as a consequence you may
//not convey it at all.  For example, if you agree to terms that obligate you
//to collect a royalty for further conveying from those to whom you convey
//the Program, the only way you could satisfy both those terms and this
//License would be to refrain entirely from conveying the Program.
//
//  13. Use with the GNU Affero General Public License.
//
//  Notwithstanding any other provision of this License, you have
//permission to link or combine any covered work with a work licensed
//under version 3 of the GNU Affero General Public License into a single
//combined work, and to convey the resulting work.  The terms of this
//License will continue to apply to the part which is the covered work,
//but the special requirements of the GNU Affero General Public License,
//section 13, concerning interaction through a network will apply to the
//combination as such.
//
//  14. Revised Versions of this License.
//
//  The Free Software Foundation may publish revised and/or new versions of
//the GNU General Public License from time to time.  Such new versions will
//be similar in spirit to the present version, but may differ in detail to
//address new problems or concerns.
//
//  Each version is given a distinguishing version number.  If the
//Program specifies that a certain numbered version of the GNU General
//Public License "or any later version" applies to it, you have the
//option of following the terms and conditions either of that numbered
//version or of any later version published by the Free Software
//Foundation.  If the Program does not specify a version number of the
//GNU General Public License, you may choose any version ever published
//by the Free Software Foundation.
//
//  If the Program specifies that a proxy can decide which future
//versions of the GNU General Public License can be used, that proxy's
//public statement of acceptance of a version permanently authorizes you
//to choose that version for the Program.
//
//  Later license versions may give you additional or different
//permissions.  However, no additional obligations are imposed on any
//author or copyright holder as a result of your choosing to follow a
//later version.
//
//  15. Disclaimer of Warranty.
//
//  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
//APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
//HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
//OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
//IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
//ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
//
//  16. Limitation of Liability.
//
//  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
//WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
//THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
//GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
//USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
//DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
//PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
//EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
//SUCH DAMAGES.
//
//  17. Interpretation of Sections 15 and 16.
//
//  If the disclaimer of warranty and limitation of liability provided
//above cannot be given local legal effect according to their terms,
//reviewing courts shall apply local law that most closely approximates
//an absolute waiver of all civil liability in connection with the
//Program, unless a warranty or assumption of liability accompanies a
//copy of the Program in return for a fee.
//
//                     END OF TERMS AND CONDITIONS
//
//            How to Apply These Terms to Your New Programs
//
//  If you develop a new program, and you want it to be of the greatest
//possible use to the public, the best way to achieve this is to make it
//free software which everyone can redistribute and change under these terms.
//
//  To do so, attach the following notices to the program.  It is safest
//to attach them to the start of each source file to most effectively
//state the exclusion of warranty; and each file should have at least
//the "copyright" line and a pointer to where the full notice is found.
//
//    <one line to give the program's name and a brief idea of what it does.>
//    Copyright (C) <year>  <name of author>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//Also add information on how to contact you by electronic and paper mail.
//
//  If the program does terminal interaction, make it output a short
//notice like this when it starts in an interactive mode:
//
//    <program>  Copyright (C) <year>  <name of author>
//    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//    This is free software, and you are welcome to redistribute it
//    under certain conditions; type `show c' for details.
//
//The hypothetical commands `show w' and `show c' should show the appropriate
//parts of the General Public License.  Of course, your program's commands
//might be different; for a GUI interface, you would use an "about box".
//
//  You should also get your employer (if you work as a programmer) or school,
//if any, to sign a "copyright disclaimer" for the program, if necessary.
//For more information on this, and how to apply and follow the GNU GPL, see
//<http://www.gnu.org/licenses/>.
//
//  The GNU General Public License does not permit incorporating your program
//into proprietary programs.  If your program is a subroutine library, you
//may consider it more useful to permit linking proprietary applications with
//the library.  If this is what you want to do, use the GNU Lesser General
//Public License instead of this License.  But first, please read
//<http://www.gnu.org/philosophy/why-not-lgpl.html>.
//----------------------------------------------------------------------------------------------------
// End of FILEHASH.C. */
//----------------------------------------------------------------------------------------------------

