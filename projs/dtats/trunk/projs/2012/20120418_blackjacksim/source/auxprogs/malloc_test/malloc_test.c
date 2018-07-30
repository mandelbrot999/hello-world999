//====================================================================================================
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/auxprogs/malloc_test/malloc_test.c,v 1.7 2012/03/11 16:31:29 dashley Exp $
//====================================================================================================
//The purpose of this program is to ensure that the target system can allocate at least 1G of memory
//in fairly small chunks.
//
//This program was used to evaluate the Cygwin C development environment on my PC before beginning
//work on the "bjcceval" program.  It was determined the Cygwin will successfully allocate about 2G
//of memory.  This is more than adequate, and 1G is probably enough.  Systems that won't allow at
//least 1G to be allocated via malloc() may be problematic.  In any case, the "bjcceval" program
//will provide an error message if it runs out of memory (rather than a logical error affecting the
//results). 
//====================================================================================================
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ALLOC_CHUNK    (1024U)       //1K
#define ALLOC_NUM   (1048576U)       //1M
#define ITERATIONS     (1000U)

struct base_struct 
   {
   struct base_struct *next;
   void *chunk;
   };


typedef struct base_struct NODE;


int main(void)
   {
   unsigned i;
   unsigned iteration;
   NODE *head = NULL;
   NODE *cur  = NULL;

   //=================================================================================================
   //=================================================================================================
   //=================================================================================================
   printf("Execution begins.\n"); 

   //=================================================================================================
   //=================================================================================================
   //=================================================================================================
   printf("==============================================================================\n");
   printf("This program will attempt to allocate and deallocate about 1 gigabyte of\n");
   printf("dynamic memory using malloc() and free(), %u times.  This test should\n", ITERATIONS);
   printf("detect any gross anomalies in the computing environment.\n");
   printf("==============================================================================\n");
   printf("CVS version control information for the .c source file:\n   $RCSfile: malloc_test.c,v $\n   $Revision: 1.7 $\n   $Date: 2012/03/11 16:31:29 $\n");
   printf("==============================================================================\n");

   for (iteration = 0; iteration < ITERATIONS; iteration++)
      {
      printf("Iteration number %u/%u.\n", iteration+1, ITERATIONS);
      printf("Attempting to allocate %u elements of a linked list, each occupying %u bytes.\n",
   	     ALLOC_NUM,
             (unsigned)(sizeof(NODE) + ALLOC_CHUNK));

      for (i=1; i<=ALLOC_NUM; i++)
         {
         //Explain to the user what is going on.
         if ((i % 100000) == 0)
	    {
	    printf("   Allocating NODE number %u.\n", i);
	    }

         //Allocate the NODE base.
         cur = malloc(sizeof(NODE));
         if (!cur)
	    {
	    printf("FAILURE:  Out of memory.\n");
            return(1);
	    }

         //No child right now.
         cur->next = NULL;

         //Allocate the chunk.
         cur->chunk = malloc(ALLOC_CHUNK);
         if (!(cur->chunk))
	    {
	    printf("FAILURE:  Out of memory.\n");
            return(1);
	    }

         //Write the chunk.  This is just to trigger an exception
         //hopefully if the allocation system of the target is somehow
         //defective.
         memset(cur->chunk, i, ALLOC_CHUNK);

         //Link the NODE into the list.
         if (!head)
	    {
	    //First one--easy.
	    head = cur;
	    }
         else
	    {
	    //Not the first one.
	    cur->next = head;
	    head = cur;
	    }
         }

      //==============================================================================================
      //==============================================================================================
      //==============================================================================================
      //Count the nodes and walk them, just to be sure no surprises.
      printf("Counting nodes to be sure all accounted for ... ");

      i = 0;
      cur = head;

      while (cur)
         {
         i++;
         cur = cur->next;
         }

      if (i != ALLOC_NUM)
         {
         printf("\nFAILURE:  Node miscount.\n");
         return(1);
         }
      else
         {
         printf("OK.\n");
         }

      //==============================================================================================
      //==============================================================================================
      //==============================================================================================
      //Deallocate the nodes.
      printf("Deallocating nodes ... ");

      while (head)
         {
         cur = head;
         head = head->next;
         free(cur->chunk);
         free(cur);      
         }

      printf("OK.\n");
      printf("Test successful.\n");
      }

   return(0);
   }


//====================================================================================================
//$Log: malloc_test.c,v $
//Revision 1.7  2012/03/11 16:31:29  dashley
//Iterations increased to 1000.
//
//Revision 1.6  2012/03/11 16:30:35  dashley
//Minor changes.
//
//Revision 1.5  2012/03/11 16:29:24  dashley
//Version control information enhanced.
//
//Revision 1.4  2012/03/11 16:27:26  dashley
//Version control information added.
//
//Revision 1.3  2012/03/11 16:24:13  dashley
//Iterations added.
//
//Revision 1.2  2012/03/11 16:09:34  dashley
//Cosmetic edits.
//
//Revision 1.1  2012/03/11 15:26:09  dashley
//Initial checkin.
//====================================================================================================
//End of $RCSfile: malloc_test.c,v $.
//====================================================================================================
