#include "ItemDiverso.h"

ItemDiverso::ItemDiverso(std::string nome, int quantidade, std::string tipo): _tipo(tipo) {
  setID(-1);
  setNome(nome);
  setQuantidade(quantidade);
}
ItemDiverso::ItemDiverso(){
  setID(-1);
}

std::string ItemDiverso::getTipo() const{
  return _tipo;
}

void ItemDiverso::setTipo(std::string tipo){
  _tipo = tipo;
}