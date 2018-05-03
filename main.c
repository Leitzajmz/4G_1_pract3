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

int validarCadena(char vect[], int tam);
void operandos(char vect[], int tam);

int num1, num2;
void main (void){
   setup_oscillator(OSC_16MHZ);
   set_tris_b(0x00);
   set_tris_d(0x00);
   int flagDato = 0x00, contCaracter = 0x00, flagValido = 0x00;
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
         flagValido = validarCadena(dato, contCaracter);
         if (flagValido == 0x01){
            printf("\n\r Datos ingresados validos \n\r");
            operandos(dato, contCaracter);
            /*printf("%lx",num1);
            printf("\n\r");
            printf("%lx",num2);
            printf("\n\r");*/

            contCaracter = 0x00;
            flagValido = 0x00;
         }
         else{
            printf("\n\r Datos ingresados no validos \n\r");
            contCaracter = 0x00;
         } 
      }   
   }
}



int validarCadena(char vect[], int tam){
   int contValido = 0x00;
   
   if(vect[0] == '<'){
      for(int i = 1; i < tam-1; i++){
         if(vect[i] > 41 && vect[i] < 58)
            contValido++;
      }
      if (contValido == tam-2)
         return 0x01;
      else 
         return 0x00;
   }
   else
      return 0x00; 
}

void operandos(char vect[], int tam){
   int contAux = 0x00,num[3], contDigitos = 0x00;

   
   for(int i = 1; i < tam-1; i++){
      num[contAux] = vect[i];
      contAux++;
      if(num[contAux-1] == ','){
         switch(contAux){
         case 3:
            num[2] = num[1];
            num[1] = num[0];
            num[0] = 0x00;
            //num[3] = NULL;
            break;
         }
         num1 = atoi(num);
         printf("%lx", num1);
         /*for(int i = 0; i < 3 ; i++){
            printf("%c", num[i]);
            printf("  \n\r");
         }*/

      }
   }
}
/*      if(vect[i] == ','){
         switch(contAux){
         case 1:
            num[3] = NULL;
            num[2] = num[0];
            num[1] = 0x00;
            num[0] = 0x00;
            contAux = 0x00;
            contDigitos++;
            break;
         case 2:
            num[3] = NULL;
            num[2] = num[1];
            num[1] = num[0];
            num[0] = 0x00;
            contAux = 0x00;
            contDigitos++;
            break;
         case 3:
            contAux = 0x00;
            contDigitos++;
            break;
         }
         if(contDigitos == 1){
            num1 = atoi(num);
            num[3] = NULL;
            num[2] = NULL;
            num[1] = NULL;
            num[0] = NULL;
         }
         else if(contDigitos == 2){
            num2 = atoi(num);
            num[3] = NULL;
            num[2] = NULL;
            num[1] = NULL;
            num[0] = NULL;
         }
      }   */
