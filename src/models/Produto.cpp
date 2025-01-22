#include "Produto.h"

int Produto::getID() const{
  return _id;
}

void Produto::setID(int id){
  _id = id;
}

std::string Produto::getNome() const{
  return _nome;
}

void Produto::setNome(std::string nome){
  _nome = nome;
}

int Produto::getQuantidade() const {
  return _quantidade;  
}

void Produto::setQuantidade(int quantidade) {
  if(quantidade < 0);
    // Lancar excecao
    
  _quantidade = quantidade;  
}