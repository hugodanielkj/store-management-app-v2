#ifndef ITEMDIVERSO_H
#define ITEMDIVERSO_H

#include <string>
#include "Produto.h"

class ItemDiverso : public Produto{
  private:
    std::string _marca;

  public:
    ItemDiverso();
    ItemDiverso(std::string nome, int quantidade, std::string marca);

    std::string getMarca() const;
    void setMarca(std::string marca);
};

#endif