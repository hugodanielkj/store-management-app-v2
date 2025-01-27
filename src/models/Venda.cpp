#include "Venda.h"

Venda::Venda() {}

Venda::Venda(std::string _produto, int _quantidade, std::string _data): produto(_produto), quantidade(_quantidade), data(_data) {}

std::string Venda::getProduto() const {
  return produto;
}

void Venda::setProduto(std::string _produto) {
  produto = _produto;
}

int Venda::getQuantidade() const {
  return quantidade;
}

void Venda::setQuantidade(int _quantidade) {
  quantidade = _quantidade;
}

std::string Venda::getData() const {
  return data;
}

void Venda::setData(std::string _data) {
  data = _data;
}
