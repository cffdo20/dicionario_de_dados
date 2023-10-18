#include <stdio.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include<locale.h>
#include <new>
#include <windows.h>
#include <sstream>
using namespace std;
using std::cin;
using std::getline;
/****************** VARIAVEIS GLOBAIS ******************/
int opc;
char resp;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct Palavras {//Lista de Palavras
    string palavra;//palavra do no
    string descricao;
    struct Palavras *proxPalavra;//ponteiro para o próximo no
   };
typedef struct {//tipo Letra
    string grafia;//letra do no
    int quantidadePalavras;//quantidade de palavras iniciadas pela letra do no
    struct Palavras *palavras;//ponteiro para a lista de palavras iniciadas com a letra do no
    }Letra;
struct Dicionario {//lista de letras
    Letra letra;//variável do tipo Letra do no
    struct Dicionario *proxLetra;//ponteiro para a proxima Letra do no
    struct Dicionario *antLetra;//ponteiro para a Letra anterior do no
   };
struct Dicionario dicionarioInicio, *pAuxLetras;
struct Palavras *pAuxPalavras;
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

//Funções CRUD para letras
void excluirLetra();
void pesquisarLetra();

//Funções CRUD para palavras
void inserirPalavra();
void excluirPalavra();
void editarPalavra();
void pesquisarPalavra();

//Funções de listagem
void ordenarDicionario();
void listarDicionario();

//Funções de menu


//Funções para arquivos

//Outras funções
void gotoXY(int x, int y);
void limpaTela();
main(){
    setlocale(LC_ALL, "portuguese");
    inserirPalavra();
}
//Funções CRUD para letras
void excluirLetra(){}
void pesquisarLetra(){}

//Funções CRUD para palavras
void inserirPalavra(){
    char letras[1];
    char palavra[50];
    string pala;
    string descricao;
    pAuxLetras = &dicionarioInicio; /* aponta para o inicio da lista */
    while(pAuxLetras->proxLetra)
        pAuxLetras = pAuxLetras->proxLetra;

    do
    {
        system("cls");
        pAuxLetras->proxLetra = new Dicionario;
        pAuxLetras = pAuxLetras->proxLetra;
        cout << "************************* CADASTRO DE PALAVRA *************************";
        gotoXY(1,2);
        cout << "*  Palavra:                                                       *";
        gotoXY(1,3);
        cout<<  "*  Descrição:                                                        *";
        cout << "\n*********************************************************************";
        gotoXY(20,2);
        fflush(stdin);
        gets(palavra);
        gotoXY(20,3);
        fflush(stdin);
        getline(cin, descricao);
        strncpy(letras, palavra, 1);
        string letra(letras);
        string pala(palavra);
        pAuxLetras->letra.palavras = new Palavras;
        pAuxPalavras= pAuxLetras->letra.palavras;
        pAuxPalavras->proxPalavra= new Palavras;
        pAuxPalavras= pAuxPalavras->proxPalavra;
        pAuxPalavras->palavra=palavra;
        pAuxPalavras->descricao=descricao;
        pAuxLetras->proxLetra = NULL;
        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    }
    while (resp == 'S');
}
void excluirPalavra(){}
void editarPalavra(){}
void pesquisarPalavra(){}

//Funções de listagem
void ordenarDicionario(){}
void listarDicionario(){}

//Outras funções
void gotoXY(int x, int y)
{
    CursorPosition.X = x; // Locates column
    CursorPosition.Y = y; // Locates Row
    SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}
void limpaTela()
{
    system("cls");
}
