#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void arquivoParaNodeList(){

}

void criarOuLerAquivos() {
  fstream arquivo("database.txt", ios::in | fstream::out | ios::trunc);
  
  if(arquivo.is_open()){
    cout << "arquivo aberto\n";
    arquivo << "teste2\n";
    arquivo.close();
  } else {
    cout << "arquivo nao aberto\n";
  }
 
  cout << "fim arquivo";
}


void readFile(){
  fstream file("database.bin", ios::in | ios::out); 
  if(!file.is_open()){
    cout << "Sem arquivo de database";
  } else {
    while(!file.eof()){
      string line;
      getline(file, line);
      cout << line << "\n";
    }
  }
}


void writeBinaryToFile(){
  fstream file("database.bin", ios::out | ios::ate);
  file << "Palavra;Descrição;Letra \n";
  file.close();
}

void readBinaryFile(){
  fstream file;("database.bin", ios::in | ios::binary);
  string line;
  while(getline(file, line)){
    cout << line << "\n";
  }
  file.close();
}

void pushWordToDatabase(string word, string description, char firstLetter){

}