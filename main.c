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

void mostrarDatos(char vect[],int tam);
int validarCadena(char vect[], int cont);
int evaluarBackSpace(char vect[], int cont);
void operandos(char vect[],int cont );
int32 operacion(char vect[], int cont);
void rutinaDeError();

unsigned int num1, num2;

void main (void){
   setup_oscillator(OSC_16MHZ);
   set_tris_b(0x00);
   set_tris_d(0x00);
   char dato[15];
   int32 resultado = 0x00;
   int contCaracter = 0x00, flagValido = 0x00;
   
   printf("Ingresa los datos en el siguiente formato :");
   printf("\n\r");
   printf("<xxx,yyy,operacion>");
   printf("\n\r");
   
   while(1){
      if(kbhit()){
         dato[contCaracter] = getch(); 
         printf("%c", dato[contCaracter]);
         contCaracter = evaluarBackSpace(dato,contCaracter);
         
         if(dato[contCaracter] == 13){
            if(dato[0] == '<' && dato[contCaracter-1] == '>'){
               flagValido = (dato, contCaracter);
               if(flagValido == 0x01){
                  mostrarDatos(dato,contCaracter);
                  operandos(dato, contCaracter);
                  if(num1 < 0x100 && num2 < 0x100){
                     resultado = operacion(dato, contCaracter);
                     output_b(resultado);
                     output_d(resultado>>8);
                     printf("El resultado es: %ld",resultado);
                     printf("\n\r");
                     resultado = 0x00;
                     contCaracter = 0x00;
                  }
                  else{
                     printf("Valores fuera de rango");
                     printf("\n\r"); 
                     rutinaDeError();
                     resultado = 0x00;
                     contCaracter = 0x00;
                  }
               }
               else{
                  printf("Cadena no valida");
                  printf("\n");
                  contCaracter = 0x00;
               }
            }
            else{
               printf("Valores no validos");
               printf("\n");
               contCaracter = 0x00;
            }
             contCaracter = 0x00;
         }  
         else
            contCaracter++;
      }
   } 
}


void mostrarDatos(char vect[],int tam){
   for(int i = 0; i < tam; i++){
      printf("%c",vect[i]);
      printf("\n\r");                       
   }
}

int validarCadena(char vect[], int cont){
   int contValido = 0x00;
   for(int i = 1; i < cont-1; i++){
      if(vect[i] > 41 && vect[i] < 58){
         contValido++;
         if (contValido == cont-2){
            return 0x01;
         }
      }
      else
         return 0x00;
   }
}

int evaluarBackSpace(char vect[], int cont){
   if(vect[cont] == 8){
      return cont-2;
   }
   else{
      return cont;
   }
}

int32 operacion(char vect[], int cont){
   switch(vect[cont-2]){
   case '+':
      return (int32)num1 + (int32)num2;
      break;
   case '-':
      return (int32)num1 - (int32)num2;
      break;
   case '*':
      return (int32)num1 * (int32)num2;
      break;
   case '/':
      if(num2 == 0){
         printf("Operacion no valida");
         printf("\n");
         rutinaDeError();
      }
      else
         return (int32)num1 / (int32)num2;
      break;
   }
}

void rutinaDeError(){
   for(int i = 0 ; i < 3 ; i++){
      output_b(0xFF);
      output_d(0xFF);
      delay_ms(50);
      output_b(0x00);
      output_d(0x00);
      delay_ms(50);
   }
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