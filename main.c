#include <18F4620.h>
#include <STDIO.H>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use RS232(BAUD=9600,XMIT=PIN_C6,rcv=PIN_C7,BITS=8,PARITY=N,STOP=1)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)


void main (void){
   setup_oscillator(OSC_16MHZ);
   set_tris_b(0x00);
   set_tris_d(0x00);
   char dato[15];
   signed long resultado = 0x00;
   int contCaracter = 0x00, flagValido = 0x00;
   printf("Hola");
   printf("\r");
   while(1){
      if(kbhit()){
         dato[contCaracter] = getch(); 
         printf("%c", dato[contCaracter]);
         if(dato[contCaracter] == 13){
            for(int i = 0 ; i < contCaracter; i++){
               printf("%c", dato[contCaracter]);
               printf("\r");
            }
         }
      } 
   }
}


