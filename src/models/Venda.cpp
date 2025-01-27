#include "Venda.h"

Venda::Venda() {}

Venda::Venda(std::string _cliente, std::vector<std::string> _produtos, std::vector<int> _quantidades_de_produtos, std::string _data): cliente(_cliente), produtos(_produtos), quantidades_de_produtos(_quantidades_de_produtos), data(_data) {}

std::string Venda::getCliente() const {
  return cliente;
}

std::vector<std::string> Venda::getProdutos() const {
  return produtos;
}

void Venda::setProdutos(std::vector<std::string> _produtos) {
  produtos = _produtos;
}

std::vector<int> Venda::getQuantidadesDeProdutos() const {
  return quantidades_de_produtos;
}

void Venda::setQuantidades(std::vector<int> _quantidades_de_produtos) {
  quantidades_de_produtos = _quantidades_de_produtos;
}

std::string Venda::getData() const {
  return data;
}

void Venda::setData(std::string _data) {
  data = _data;
}
