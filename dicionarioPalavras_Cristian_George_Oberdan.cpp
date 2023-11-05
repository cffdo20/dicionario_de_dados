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
    struct Palavras *proxPalavra;//ponteiro para o pr�ximo no
};
typedef struct  //tipo Letra
{
    string grafia;//letra do no
    int quantidadePalavras;//quantidade de palavras iniciadas pela letra do no
    struct Palavras *palavras;//ponteiro para a lista de palavras iniciadas com a letra do no
} Letra;
struct Dicionario  //lista de letras
{
    Letra letra;//vari�vel do tipo Letra do no
    struct Dicionario *proxLetra;//ponteiro para a proxima Letra do no
    struct Dicionario *antLetra;//ponteiro para a Letra anterior do no
};
struct Dicionario dicionarioInicio, *pAuxLetras, *pAuxLetras2, *pAuxLetras3, *pAuxLetraExclusao;

struct Palavras *pAuxPalavras, *pAuxPalavras2, *pAuxPalavraExclusao, *pAuxPalavraEdicao;
/*
struct ListaPalavras {//Lista de Palavras
    string palavra;//palavra do no
    struct ListaPalavras *proxPalavra;//ponteiro para o pr�ximo no
   };
struct ListaLetras {//lista de letras
    string grafia;//letra do no
    int quantidadePalavras;//quantidade de palavras iniciadas pela letra do no
    struct ListaPalavras *palavras;//ponteiro para a lista de palavras iniciadas com a letra do no
    struct ListaLetras *proxLetra;//ponteiro para a proxima Letra do nol
   };
*/

//Fun��es CRUD para letras
void excluirLetra();
void pesquisarLetra();

//Fun��es CRUD para palavras
void inserirPalavra();
void excluirPalavra();
void editarPalavra();
void pesquisarPalavra();
void excluirPalavraEdicao(string pala, string letra);

//Fun��es de listagem
void ordenarDicionario();
void listarDicionario();

//Fun��es de menu
void menuPrincipal();


//Fun��es para arquivos

//Outras fun��es
void gotoXY(int x, int y);
void limpaTela();
/* main()
{
    dicionarioInicio.proxLetra=NULL;
    setlocale(LC_ALL, "portuguese");
    inserirPalavra();
    listarDicionario();
    //pesquisarPalavra();
    editarPalavra();
    listarDicionario();
    pesquisarPalavra();
} */

main()
{
    dicionarioInicio.proxLetra=NULL;
    setlocale(LC_ALL, "portuguese");
    do{
        menuPrincipal();
        switch(opc){
            case 1:
                inserirPalavra();
                break;

            case 2:
                editarPalavra();
                break;

            case 3:
                pesquisarPalavra();
                break;

            case 4:
                excluirPalavra();
                break;

            case 5:
                listarDicionario();
                break;

            case 6:
                break;
    }
    }while(opc !=6);
    //listarDicionario();
    //system("pause");
    //pesquisarPalavra();
}
//Fun��es CRUD para letras

//Fun��es CRUD para palavras
void inserirPalavra()
{
    char letras[1];
    char palavra[50];
    string pala;
    string descricao;
    int existe;


    do
    {
        limpaTela();

        gotoXY(35,2);
        cout << "----------------------- CADASTRO DE PALAVRAS -----------------------";
        gotoXY(35,5);
        cout << "* Palavra: ";
        gotoXY(35,7);
        cout << "* Descricao: ";
        //cout << "\n*********************************************************************";
        gotoXY(47,5);
        fflush(stdin);
        gets(palavra);
        gotoXY(49,7);
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
                    cout << "ATENCAO: A palavra digitada j� foi cadastrada! ";
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

        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->  ";
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

            limpaTela();
            gotoXY(35,2);
            cout << "--------------------------------  EXCLUIR PALAVRAS --------------------------------";
            gotoXY(35,7);
            cout << "Que palavra voce deseja excluir?";
            gotoXY(68,7);
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
                    gotoXY(35,2);
                    cout << "-----------------------------------------------------------------------------------";
                    gotoXY(35,3);
                    cout << "Letra: " << letra;
                    gotoXY(35,5);
                    cout << "Palavra: " << pala;
                    gotoXY(35,6);
                    cout << "Descricao da palavra: " << pAuxPalavras->proxPalavra->descricao;
                    //gotoXY(35,7);
                    //cout << "---------------------------------------------------------------------------";
                    gotoXY(35,15);
                    cout << "DESEJA EXCLUIR A PALAVRA ACIMA? Sim[S] Nao[outra tecla] ";
                    cin >> resp;
                    resp = toupper(resp);
                    if(resp == 'S'){
                        pAuxPalavras->proxPalavra=pAuxPalavraExclusao->proxPalavra;
                        pAuxPalavraExclusao->proxPalavra=NULL;
                        delete(pAuxPalavraExclusao);
                        pAuxLetras->letra.quantidadePalavras--;
                        if(pAuxLetras->letra.quantidadePalavras==0||pAuxLetras->letra.palavras==NULL){
                                pAuxLetras->antLetra->proxLetra=pAuxLetras->proxLetra;
                                delete(pAuxLetras);
                        }
                    }
                    limpaTela();
                }
                else
                {
                    gotoXY(35,9);
                    cout << "ATENCAO: A palavra digitada n�o foi cadastrada! ";
                    cout << "\n---------------------------------------------------------------------------\n";
                    system("pause");
                }
            }
            else
            {
                gotoXY(35,9);
                cout << "ATENCAO: A palavra digitada n�o foi cadastrada! ";
                cout << "\n---------------------------------------------------------------------------\n";
                system("pause");
            }
            cout<<"\n";
            system("pause");
        }
        else
        {
            gotoXY(15,18);
            cout << "ATENCAO: N�o existem palavras cadastradas! ";
            system("pause");
        }
        cout << "\nContinuar excluindo palavras? Sim[S] Nao[outra tecla]---->  ";
        cin >> resp;
        resp = toupper(resp);
    }
    while (resp == 'S');
}
void excluirPalavraEdicao(string pala, string letra) {
    int existe=0;
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

                    pAuxPalavras->proxPalavra=pAuxPalavraExclusao->proxPalavra;
                    pAuxPalavraExclusao->proxPalavra=NULL;
                    delete(pAuxPalavraExclusao);
                    pAuxLetras->letra.quantidadePalavras--;
                    if(pAuxLetras->letra.quantidadePalavras==0||pAuxLetras->letra.palavras==NULL){
                            pAuxLetras->antLetra->proxLetra=pAuxLetras->proxLetra;
                            delete(pAuxLetras);
                    }

                }
            }
}
void editarPalavra() {
    char palavra[60], palavra2[60];
    char letras[1];
    int existe=0;
    int opcao;
    string descricao;
    do
    {
        if(dicionarioInicio.proxLetra != NULL)
        {

            limpaTela();
            gotoXY(35,2);
            cout << "--------------------------------  EDITAR PALAVRAS --------------------------------";
            gotoXY(35,5);
            cout << "Que palavra voce deseja editar?";
            gotoXY(70,5);
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
                        pAuxPalavraEdicao=pAuxPalavras->proxPalavra;
                        existe=2;
                        break;
                    }
                    pAuxPalavras=pAuxPalavras->proxPalavra;
                }
                descricao = pAuxPalavras->proxPalavra->descricao;
                if(existe==2&&pAuxPalavras!=NULL)
                {
                    limpaTela();
                    gotoXY(35,2);
                    /* cout << "-------------------------DESEJA EDITAR A PALAVRA ABAIXO? Sim[S] Nao[outra tecla]  -------------------------\n"; */
                    cout << "-----------------------------------------------------------------------------------";
                   // gotoXY(1,4);
                    gotoXY(35,4);
                    cout << "Letra: " << letra;
                    gotoXY(35,6);
                    cout << "Palavra: " << pala;
                    gotoXY(35,7);
                    cout << "Descricao da palavra: " << descricao;
                    //gotoXY(1,7);
                    //cout << "\n---------------------------------------------------------------------------";
                    //gotoXY(82,2);
                    gotoXY(35,15);
                    cout << "DESEJA EDITAR A PALAVRA ACIMA? Sim[S] Nao[outra tecla] ";
                    cin >> resp;
                    resp = toupper(resp);
                    if(resp == 'S'){
                        do{
                            limpaTela();
                            gotoXY(35,2);
                            cout << "---------------------------------------------------------------------------\n";
                            gotoXY(35,4);
                            cout << "O que deseja editar?: ";
                            gotoXY(35,5);
                            cout << "1 - Palavra;";
                            gotoXY(35,6);
                            cout << "2 - Descri��o;";
                            gotoXY(35,7);
                            cout << "---------------------------------------------------------------------------";
                            gotoXY(57,4);
                            cin >> opcao;
                            switch(opcao){
                            case 1:
                                excluirPalavraEdicao(pala, letra);
                                limpaTela();
                                gotoXY(35,2);
                                cout << "---------------------------------------------------------------------------\n";
                                gotoXY(35,4);
                                cout << "Nova palavra: ";
                                gotoXY(50,4);
                                fflush(stdin);
                                fflush(stdin);
                                gets(palavra);
                                if(palavra!=pala){
                                    string letrar(palavra, 1);
                                    string palas(palavra);
                                    if(letrar!=letra){
                                        pAuxLetras2=dicionarioInicio.proxLetra;
                                        if(pAuxLetras2 != NULL)
                                        {
                                            while(pAuxLetras2)
                                            {
                                                if(letrar==pAuxLetras2->letra.grafia)
                                                {
                                                    existe=1;
                                                    break;
                                                }
                                                pAuxLetras2 = pAuxLetras2->proxLetra;
                                            }
                                        }
                                        if(dicionarioInicio.proxLetra==NULL||existe!=1)
                                        {
                                            pAuxLetras3 = &dicionarioInicio;
                                            while(pAuxLetras3->proxLetra)
                                            {
                                                pAuxLetras3 = pAuxLetras3->proxLetra;
                                            }
                                            pAuxLetras3->proxLetra = new Dicionario;
                                            pAuxLetras3 = pAuxLetras3->proxLetra;
                                            pAuxLetras3->letra.grafia=letrar;
                                            pAuxLetras3->letra.quantidadePalavras++;
                                            pAuxLetras3->letra.palavras = new Palavras;
                                            pAuxPalavras2= pAuxLetras3->letra.palavras;
                                            pAuxPalavras2->proxPalavra= new Palavras;
                                            pAuxPalavras2= pAuxPalavras2->proxPalavra;
                                            pAuxPalavras2->palavra=palas;
                                            pAuxPalavras2->descricao=descricao;
                                            pAuxPalavras2->proxPalavra=NULL;
                                            pAuxLetras3->proxLetra = NULL;
                                        }
                                        else if(dicionarioInicio.proxLetra!=NULL||existe==1)
                                        {
                                            pAuxLetras2->letra.quantidadePalavras++;
                                            pAuxPalavras2= pAuxLetras2->letra.palavras;

                                            while(pAuxPalavras2->proxPalavra)
                                            {
                                                if(pala.compare(pAuxPalavras2->palavra)==0){
                                                    cout << "ATENCAO: A palavra digitada j� foi cadastrada! ";
                                                    break;
                                                }
                                                pAuxPalavras2 = pAuxPalavras2->proxPalavra;
                                            }
                                            pAuxPalavras2->proxPalavra= new Palavras;
                                            pAuxPalavras2= pAuxPalavras2->proxPalavra;
                                            pAuxPalavras2->palavra=palas;
                                            pAuxPalavras2->descricao=descricao;
                                            pAuxPalavras2->proxPalavra=NULL;
                                        }

                                    }/*else if (letrar==pAuxLetras->letra.grafia){
                                        pAuxPalavraEdicao->palavra=palas;
                                    }*/
                                }else{
                                    limpaTela();
                                    cout << "A palavra digitada � a mesma da cadastrada! Tente novamente.";
                                    system("pause");
                                    continue;
                                }
                                gotoXY(1,7);
                                cout << "\n---------------------------------------------------------------------------";
                                break;
                            case 2:
                                limpaTela();
                                gotoXY(1,2);
                                cout << "---------------------------------------------------------------------------\n";
                                gotoXY(1,4);
                                cout << "Nova descri��o: ";
                                gotoXY(16,4);
                                fflush(stdin);
                                getline(cin, pAuxPalavraEdicao->descricao);
                                gotoXY(1,7);
                                cout << "\n---------------------------------------------------------------------------";
                                break;
                            default:
                                limpaTela();
                                cout << "A op��o digitada n�o existe! Tente novamente.";
                                system("pause");
                                continue;
                            }
                        }while(opcao!=1&&opcao!=2);

                    }
                    limpaTela();
                }
                else
                {
                    gotoXY(35,9);
                    cout << "ATENCAO: A palavra digitada n�o foi cadastrada! ";
                    cout << "\n---------------------------------------------------------------------------\n";
                    system("pause");
                }
            }
            else
            {
                gotoXY(35,9);
                cout << "ATENCAO: A palavra digitada n�o foi cadastrada! ";
                cout << "\n---------------------------------------------------------------------------\n";
                system("pause");
            }
            cout<<"\n";
            system("pause");
            //excluirPalavraEdicao(pala, letra);
        }
        else
        {
            gotoXY(15,18);
            cout << "ATENCAO: N�o existem palavras cadastradas! ";
            system("pause");
        }
        cout << "\nContinuar editando palavras? Sim[S] Nao[outra tecla]---->  ";
        cin >> resp;
        resp = toupper(resp);

    }
    while (resp == 'S');
}
void pesquisarPalavra()
{
    char palavra[60];
    char letras[1];
    int existe=0;
    do
    {
        if(dicionarioInicio.proxLetra != NULL)
        {

            limpaTela();
            gotoXY(35,2);
            cout << "----------------------- PESQUISAR PALAVRAS -----------------------";
            gotoXY(35,5);
            cout << "Que palavra você deseja pesquisar?  ";
            gotoXY(72,5);
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
                    gotoXY(35,2);
                    cout << "---------------------------------------------------------------------------\n";
                    gotoXY(35,4);
                    cout << "Letra: " << letra;
                    gotoXY(35,5);
                    cout << "Palavra: " << pala;
                    cout << "\n";
                    gotoXY(35,6);
                    cout << "Descricao da palavra: " << pAuxPalavras->descricao;
                    gotoXY(35,15);
                    cout << "---------------------------------------------------------------------------";
                }
                else
                {
                    gotoXY(35,9);
                    cout << "ATENCAO: A palavra digitada n�o foi cadastrada! ";
                    cout << "\n---------------------------------------------------------------------------\n";
                    system("pause");
                }
            }
            else
            {
                gotoXY(35,9);
                cout << "ATENCAO: A palavra digitada n�o foi cadastrada! ";
                cout << "\n---------------------------------------------------------------------------\n";
                system("pause");
            }
            cout<<"\n";
            system("pause");
        }
        else
        {
            gotoXY(15,18);
            cout << "ATENCAO: Nao existem palavras cadastradas! ";
            system("pause");
        }
        cout << "\nContinuar pesquisando palavras? Sim[S] Nao[outra tecla]---->  ";
        cin >> resp;
        resp = toupper(resp);
    }
    while (resp == 'S');
}

//Fun��es de listagem
void ordenarDicionario() {}

void listarDicionario()
{
    int i=1;
    limpaTela();
    pAuxLetras2 = dicionarioInicio.proxLetra;
    while(pAuxLetras2){
        //cout << "\n---------------------------------------------------------------------------\n";
        cout<<"\n\tLETRA: "<<pAuxLetras2->letra.grafia<<endl;
        pAuxPalavras=pAuxLetras2->letra.palavras->proxPalavra;
        while(pAuxPalavras){
        cout << "\n  ---------------------------------------------------------------------------\n";
        cout<<"\t* Palavra "<<i<<": "<<pAuxPalavras->palavra<<endl;
        cout<<"\t--> Descricao: "<<pAuxPalavras->descricao<<endl;
        //cout << "\n---------------------------------------------------------------------------\n";
        pAuxPalavras=pAuxPalavras->proxPalavra;
        i++;
        }
        pAuxLetras2=pAuxLetras2->proxLetra;
        cout << "\n  ---------------------------------------------------------------------------\n";
    }
    system("pause");
}
//funções de menu
void menuPrincipal(){
    //int opcao;
    limpaTela();
    gotoXY(47,2);
    cout << "DICIONARIO DE PALAVRAS - ESPORTES";

    gotoXY(35,4);
    //cout << "*********************** MENU ***********************";
    cout << "----------------------- MENU -----------------------";
    gotoXY(35,5);
    cout << "* Inserir palavra...............................[1]*";
    gotoXY(35,7);
    cout << "* Editar palavra................................[2]*";
    gotoXY(35,9);
    cout << "* Pesquisar palavra.............................[3]*";
    gotoXY(35,11);
    cout << "* Excluir palavra...............................[4]*";
    gotoXY(35,13);
    cout << "* Listar dicionario.............................[5]*";
    gotoXY(35,15);
    cout << "* Sair..........................................[6]*";
    gotoXY(35,16);
    //cout << "****************************************************";
    cout << "----------------------------------------------------";

    gotoXY(24,18);
    cout << "Digite o numero da opcao desejada: ";
    cin >> opc;

}

//Outras fun��es
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
