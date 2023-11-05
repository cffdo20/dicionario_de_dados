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

struct Palavras  //Lista de Palavras
{
    string palavra;//palavra do no
    string descricao;
    struct Palavras *proxPalavra;//ponteiro para o próximo no
};
typedef struct  //tipo Letra
{
    string grafia;//letra do no
    int quantidadePalavras;//quantidade de palavras iniciadas pela letra do no
    struct Palavras *palavras;//ponteiro para a lista de palavras iniciadas com a letra do no
} Letra;
struct Dicionario  //lista de letras
{
    Letra letra;//variável do tipo Letra do no
    struct Dicionario *proxLetra;//ponteiro para a proxima Letra do no
    struct Dicionario *antLetra;//ponteiro para a Letra anterior do no
};
struct Dicionario dicionarioInicio, *pAuxLetras, *pAuxLetras2, *pAuxLetraExclusao;

struct Palavras *pAuxPalavras, *pAuxPalavraExclusao;
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
main()
{
    dicionarioInicio.proxLetra=NULL;
    setlocale(LC_ALL, "portuguese");
    inserirPalavra();
    pesquisarPalavra();
    excluirPalavra();
    pesquisarPalavra();
}
//Funções CRUD para letras

//Funções CRUD para palavras
void inserirPalavra()
{
    char letras[1];
    char palavra[50];
    string pala;
    string descricao;
    int existe;


    do
    {
        system("cls");

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
        string letra(palavra, 1);
        string pala(palavra);
        pAuxLetras2=dicionarioInicio.proxLetra;
        if(pAuxLetras2 != NULL)
        {
            while(pAuxLetras2)
            {
                if(letra==pAuxLetras2->letra.grafia)
                {
                    existe=1;
                    break;
                }
                pAuxLetras2 = pAuxLetras2->proxLetra;
            }
        }

        if(dicionarioInicio.proxLetra==NULL||existe!=1)
        {
            pAuxLetras = &dicionarioInicio;
            while(pAuxLetras->proxLetra)
            {
                pAuxLetras = pAuxLetras->proxLetra;
            }
            pAuxLetras->proxLetra = new Dicionario;
            pAuxLetras = pAuxLetras->proxLetra;
            pAuxLetras->letra.grafia=letra;
            pAuxLetras->letra.quantidadePalavras++;
            pAuxLetras->letra.palavras = new Palavras;
            pAuxPalavras= pAuxLetras->letra.palavras;
            pAuxPalavras->proxPalavra= new Palavras;
            pAuxPalavras= pAuxPalavras->proxPalavra;
            pAuxPalavras->palavra=palavra;
            pAuxPalavras->descricao=descricao;
            pAuxPalavras->proxPalavra=NULL;
            pAuxLetras->proxLetra = NULL;
        }
        else if(dicionarioInicio.proxLetra!=NULL||existe==1)
        {
            pAuxLetras2->letra.quantidadePalavras++;
            pAuxPalavras= pAuxLetras2->letra.palavras;

            while(pAuxPalavras->proxPalavra)
            {
                if(pala.compare(pAuxPalavras->palavra)==0){
                    cout << "ATENCAO: A palavra digitada já foi cadastrada! ";
                    break;
                }
                pAuxPalavras = pAuxPalavras->proxPalavra;
            }
            pAuxPalavras->proxPalavra= new Palavras;
            pAuxPalavras= pAuxPalavras->proxPalavra;
            pAuxPalavras->palavra=palavra;
            pAuxPalavras->descricao=descricao;
            pAuxPalavras->proxPalavra=NULL;
        }

        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    }
    while (resp == 'S');
}
void excluirPalavra() {
    char palavra[60];
    char letras[1];
    int existe=0;
    do
    {
        if(dicionarioInicio.proxLetra != NULL)
        {

            system("cls");
            gotoXY(1,5);
            cout << "********************************  EXCLUIR PALAVRAS *********************************";
            gotoXY(1,7);
            cout << "Que palavra você deseja excluir?";
            gotoXY(36,7);
            fflush(stdin);
            gets(palavra);
            fflush(stdin);
            fflush(stdin);
            string letra(palavra, 1);
            string pala(palavra);
            pAuxLetras = dicionarioInicio.proxLetra;
            while(pAuxLetras)
            {
                if(letra==pAuxLetras->letra.grafia)
                {
                    existe=1;
                    break;
                }
                pAuxLetras = pAuxLetras->proxLetra;
            }
            if(existe==1 && pAuxLetras->letra.palavras!=NULL)
            {
                pAuxPalavras=pAuxLetras->letra.palavras;
                while(pAuxPalavras->proxPalavra)
                {
                    if(pala.compare(pAuxPalavras->proxPalavra->palavra)==0)
                    {
                        pAuxPalavraExclusao=pAuxPalavras->proxPalavra;
                        existe=2;
                        break;
                    }
                    pAuxPalavras=pAuxPalavras->proxPalavra;
                }
                if(existe==2&&pAuxPalavras!=NULL)
                {
                    limpaTela();
                    gotoXY(1,2);
                    cout << "-------------------------DESEJA REMOVER A PALAVRA ABAIXO? Sim[S] Nao[outra tecla]  -------------------------\n";
                    gotoXY(1,4);
                    cout << "Letra: " << letra;
                    gotoXY(1,5);
                    cout << "Palavra: " << pala;
                    gotoXY(1,6);
                    cout << "Descrição da palavra: " << pAuxPalavras->proxPalavra->descricao;
                    gotoXY(1,7);
                    cout << "\n---------------------------------------------------------------------------";
                    gotoXY(82,2);
                    cin >> resp;
                    resp = toupper(resp);
                    if(resp == 'S'){
                        pAuxPalavras->proxPalavra=pAuxPalavraExclusao->proxPalavra;
                        pAuxPalavraExclusao->proxPalavra=NULL;
                        delete(pAuxPalavraExclusao);
                        pAuxLetras->letra.quantidadePalavras--;
                        if(pAuxLetras->letra.quantidadePalavras==0||pAuxLetras->letra.palavras==NULL){
                                pAuxLetras->antLetra->proxLetra==pAuxLetras->proxLetra;
                                delete(pAuxLetras);
                        }
                    }
                    limpaTela();
                }
                else
                {
                    gotoXY(1,9);
                    cout << "ATENCAO: A palavra digitada não foi cadastrada! ";
                    cout << "\n---------------------------------------------------------------------------\n";
                    system("pause");
                }
            }
            else
            {
                gotoXY(1,9);
                cout << "ATENCAO: A palavra digitada não foi cadastrada! ";
                cout << "\n---------------------------------------------------------------------------\n";
                system("pause");
            }
            cout<<"\n";
            system("pause");
        }
        else
        {
            gotoXY(15,18);
            cout << "ATENCAO: Não existem palavras cadastradas! ";
            system("pause");
        }
        cout << "\nContinuar excluindo palavras? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    }
    while (resp == 'S');
}
void editarPalavra() {}
void pesquisarPalavra()
{
    char palavra[60];
    char letras[1];
    int existe=0;
    do
    {
        if(dicionarioInicio.proxLetra != NULL)
        {

            system("cls");
            gotoXY(1,5);
            cout << "********************************  PESQUISAR PALAVRAS *********************************";
            gotoXY(1,7);
            cout << "Que palavra você deseja pesquisar?";
            gotoXY(36,7);
            fflush(stdin);
            gets(palavra);
            fflush(stdin);
            fflush(stdin);
            string letra(palavra, 1);
            string pala(palavra);
            pAuxLetras = dicionarioInicio.proxLetra;
            while(pAuxLetras)
            {
                if(letra==pAuxLetras->letra.grafia)
                {
                    existe=1;
                    break;
                }
                pAuxLetras = pAuxLetras->proxLetra;
            }
            if(existe==1 && pAuxLetras->letra.palavras!=NULL)
            {
                pAuxPalavras=pAuxLetras->letra.palavras;
                do
                {
                    if(pala.compare(pAuxPalavras->palavra)==0)
                    {
                        existe=2;
                        break;
                    }
                    pAuxPalavras=pAuxPalavras->proxPalavra;
                }while(pAuxPalavras);
                if(existe==2&&pAuxPalavras!=NULL)
                {
                    limpaTela();
                    gotoXY(1,2);
                    cout << "---------------------------------------------------------------------------\n";
                    gotoXY(1,4);
                    cout << "Letra: " << letra;
                    gotoXY(1,5);
                    cout << "Palavra: " << pala;
                    gotoXY(1,6);
                    cout << "Descrição da palavra: " << pAuxPalavras->descricao;
                    gotoXY(1,7);
                    cout << "\n---------------------------------------------------------------------------";
                }
                else
                {
                    gotoXY(1,9);
                    cout << "ATENCAO: A palavra digitada não foi cadastrada! ";
                    cout << "\n---------------------------------------------------------------------------\n";
                    system("pause");
                }
            }
            else
            {
                gotoXY(1,9);
                cout << "ATENCAO: A palavra digitada não foi cadastrada! ";
                cout << "\n---------------------------------------------------------------------------\n";
                system("pause");
            }
            cout<<"\n";
            system("pause");
        }
        else
        {
            gotoXY(15,18);
            cout << "ATENCAO: Não existem palavras cadastradas! ";
            system("pause");
        }
        cout << "\nContinuar pesquisando palavras? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    }
    while (resp == 'S');
}

//Funções de listagem
void ordenarDicionario() {}
void listarDicionario()
{
    limpaTela();
    pAuxLetras = dicionarioInicio.proxLetra;

    do{
        cout<<pAuxLetras->letra.palavras->proxPalavra->palavra;
        pAuxLetras=pAuxLetras->proxLetra;
    }while(pAuxLetras->proxLetra);
    system("pause");
}

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
