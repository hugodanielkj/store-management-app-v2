#include "Roupa.h"

Roupa::Roupa(){
  setID(-1);
}

Roupa::Roupa(std::string nome, int quantidade, std::string tamanho): _tamanho(tamanho) {
  setID(-1);
  setNome(nome);
  setQuantidade(quantidade);
}

std::string Roupa::getTamanho() const {
  return _tamanho;  
}

void Roupa::setTamanho(std::string tamanho) {
  _tamanho = tamanho;
}
