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
   int flagDato = 0x00, contCaracter = 0x00;
   char dato[13];
   printf("Hola \n\r");
   
   while(1){
      if(kbhit()){
         flagDato = 0x01;
      }
      if(flagDato == 0x01){
         dato[contCaracter] = getch();           
         contCaracter++; 
         flagDato = 0x00;
      } 
      if (dato[contCaracter-1] == '>'){
         printf("\n\r");
         printf("Fin de la cadena");
         printf("\n\r");
         for(int i = 0; i < contCaracter; i++){
            printf("%c", dato[i]);
         }
          printf("\n\r");
         contCaracter = 0x00;
      }    
   }
}

