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
long operacion(char vect[], int cont);

unsigned int num1, num2;

void main (void){
   setup_oscillator(OSC_16MHZ);
   set_tris_b(0x00);
   set_tris_d(0x00);
   
   int flagDato = 0x00, contCaracter = 0x00, flagValido = 0x00;
   char dato[13];
   signed long resultado = 0x00;
   printf("Hola \n\r");
   
   while(1){
      if(kbhit()){
         dato[contCaracter] = getch();           
         contCaracter++; 
      }

      if (dato[contCaracter-1] == '>'){
         flagValido = validarCadena(dato, contCaracter);
         if (flagValido == 0x01){
            printf("\n\r Datos ingresados validos \n\r");
            operandos(dato, contCaracter);
            printf("Primer numero : %lx", num1);
            printf("\n\r");            
            printf("Segundo numero: %lx", num2);
            printf("\n\r");
            resultado = operacion(dato,contCaracter);
            //resultado = (long)num1 + (long)num2;
            printf("El resultado es : %ld", resultado);
            printf("\n\r");
            output_b(resultado);
            output_d(resultado>>8);
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
   int contAux = 0x00,num[4], contDigitos = 0x00;
  
   for(int i = 1; i < tam-1; i++){
      num[contAux] = vect[i];
      contAux++;
      if(num[contAux-1] == ','){
         switch(contAux){
         case 4:
            num[2] = num[2];
            num[1] = num[1];
            num[0] = num[0];
            num[3] = NULL;
            contAux = 0x00;
            contDigitos++;
            break;
         case 3:
            num[2] = num[1];
            num[1] = num[0];
            num[0] = '0';
            num[3] = NULL;
            contAux = 0x00;
            contDigitos++;
            break;
         case 2:
            num[2] = num[0];
            num[1] = '0';
            num[0] = '0';
            num[3] = NULL;
            contAux = 0x00;
            contDigitos++;
            break;
         }
         if(contDigitos == 1){
            num1 = atoi(num);
            /*printf("%lx", num1);
            printf("\n\r");*/ 
            num[3] = NULL;
            num[2] = NULL;
            num[1] = NULL;
            num[0] = NULL;
         }
         else if(contDigitos == 2){
            num2 = atoi(num);
            /*printf("%lx", num2);
            printf("\n\r"); */
            num[3] = NULL;
            num[2] = NULL;
            num[1] = NULL;
            num[0] = NULL;
         }
      }
   }
}

long operacion(char vect[], int cont){
   switch(vect[cont-2]){
   case '+':
      return (long)num1 + (long)num2;
      break;
   case '-':
      return (long)num1 - (long)num2;
      break;
   case '*':
      return (long)num1 * (long)num2;
      break;
   case '/':
      if(num2 == 0){
         printf("Operacion no valida");
         printf("\n\r");
         //rutinaDeError();
      }
      else
         return (long)num1 / (long)num2;
      break;
   }
}

