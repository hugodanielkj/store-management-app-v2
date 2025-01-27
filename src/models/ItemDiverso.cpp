#include "ItemDiverso.h"

ItemDiverso::ItemDiverso(std::string nome, int quantidade, std::string marca): _marca(marca) {
  setID(-1);
  setNome(nome);
  setQuantidade(quantidade);
}
ItemDiverso::ItemDiverso(){
  setID(-1);
}

std::string ItemDiverso::getMarca() const{
  return _marca;
}

void ItemDiverso::setMarca(std::string marca){
  _marca = marca;
}