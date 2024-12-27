#include "Roupa.h"

Roupa::Roupa(std::string nome, int quantidade, std::string tamanho): _id(-1), _nome(nome), _quantidade(quantidade), _tamanho(tamanho) {}

int Roupa::getID() const{
  return _id;
}

void Roupa::setID(int id){
  _id = id;
}

std::string Roupa::getNome() const{
  return _nome;
}

void Roupa::setNome(std::string nome){
  _nome = nome;
}

int Roupa::getQuantidade() const {
  return _quantidade;  
}

void Roupa::setQuantidade(int quantidade) {
  if(quantidade < 0)
    // Lancar excecao
  _quantidade = quantidade;  
}

std::string Roupa::getTamanho() const {
  return _tamanho;  
}

void Roupa::setTamanho(std::string tamanho) {
  _tamanho = tamanho;
}
