#include <iostream>
using std::cin;
using std::cout;
using namespace std;

struct Node {
  Node* anterior;
  int data;
  Node* proximo;
};

int teste(){

  Node* novo = new Node;
  Node* temporario = new Node;
  Node* header = NULL;

  novo->data = 1; 
  temporario = novo;
  header = novo;

  novo = new Node;
  novo->data = 2;
  temporario->proximo = novo;
  temporario = novo;

  novo = new Node;
  novo->data = 3;
  temporario->proximo = novo;

  // loop through the linked list and print the data values
  for(Node* current = header; current != NULL; current = current->proximo){
    cout << current->data << " ";
  }

  Node* teste = header;
  while(teste != NULL){
    cout << "meu: " << teste->data << "\n";
    teste = teste->proximo;
  }

  return 1;
}

