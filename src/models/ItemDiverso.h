#ifndef ITEMDIVERSO_H
#define ITEMDIVERSO_H

#include <string>
#include "Produto.h"

class ItemDiverso : public Produto{
  private:
    std::string _tipo;

  public:
    ItemDiverso();
    ItemDiverso(std::string nome, int quantidade, std::string tipo);

    std::string getTipo() const;
    void setTipo(std::string tipo);
};

#endif