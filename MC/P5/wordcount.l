%{
#include <stdio.h>
#include <stdlib.h>
int num_caracteres = 0, num_palabras = 0, num_lineas = 0;
%}

caracter [a-zA-ZáäàâÁÄÀÂéëêèÉËÈÊíïìîÍÏÌÎóöòôÓÖÒÔúùûüÚÜÙûçÇñÑ]
digito [0-9]
palabra ({caracter}|{digito})+
linea \n

%%

{linea} {num_caracteres++; num_lineas++;}
{palabra} {num_palabras++; num_caracteres += strlen(yytext);}
. {num_caracteres++;}

%%

int main(){
    yylex();
    printf("Numero de caracteres: %d // ", num_caracteres);
    printf("Numero de palabras: %d // ", num_palabras);
    printf("Numero de lineas: %d\n", num_lineas);
}
