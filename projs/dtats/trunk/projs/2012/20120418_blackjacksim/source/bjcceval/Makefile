#----------------------------------------------------------------------------------------------------
#$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/Makefile,v 1.4 2012/03/15 23:38:08 dashley Exp $
#----------------------------------------------------------------------------------------------------

bjcceval.exe : cassert.o                    \
               charfunc.o                   \
               main.o                       \
               memops.o                     \
               random.o                     \
               sha512.o                     \
               stdformat.o                  \
               vcinfo.o
	gcc -o bjcceval.exe                 \
               cassert.o                    \
               charfunc.o                   \
               main.o                       \
               memops.o                     \
               random.o                     \
               sha512.o                     \
               stdformat.o                  \
               vcinfo.o
     
     cassert.o : cassert.c
	gcc -c cassert.c

     charfunc.o : charfunc.c
	gcc -c charfunc.c

     main.o : main.c
	gcc -c main.c

     memops.o : memops.c
	gcc -c memops.c

     random.o : random.c
	gcc -c random.c

     sha512.o : sha512.c
	gcc -c sha512.c

     stdformat.o : stdformat.c
	gcc -c stdformat.c

     vcinfo.o : vcinfo.c
	gcc -c vcinfo.c

     clean :
	rm bjcceval.exe *.o *~

#----------------------------------------------------------------------------------------------------
#End of $RCSfile: Makefile,v $.
#----------------------------------------------------------------------------------------------------
