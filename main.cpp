#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include<locale.h>
using namespace std;

struct ListaPalavras {//Lista de Palavras
    string palavra;//palavra do no
    struct ListaPalavras *proxPalavra;//ponteiro para o próximo no
   };
typedef struct {//tipo Letra
    string grafia;//letra do no
    int quantidadePalavras;//quantidade de palavras iniciadas pela letra do no
    struct ListaPalavras *palavras;//ponteiro para a lista de palavras iniciadas com a letra do no
    }Letra;
struct ListaLetras {//lista de letras
    Letra letra;//variável do tipo Letra do no
    struct ListaLetras *proxLetra;//ponteiro para a proxima Letra do nol
   };
/*
struct ListaPalavras {//Lista de Palavras
    string palavra;//palavra do no
    struct ListaPalavras *proxPalavra;//ponteiro para o próximo no
   };
struct ListaLetras {//lista de letras
    string grafia;//letra do no
    int quantidadePalavras;//quantidade de palavras iniciadas pela letra do no
    struct ListaPalavras *palavras;//ponteiro para a lista de palavras iniciadas com a letra do no
    struct ListaLetras *proxLetra;//ponteiro para a proxima Letra do nol
   };
*/


void main(){

}
