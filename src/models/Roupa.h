#ifndef ROUPA_H
#define ROUPA_H

#include <string>
#include "Produto.h"

class Roupa : public Produto{
  private:
    std::string _tamanho;
  
  public:
    Roupa();
    Roupa(std::string nome, int quantidade, std::string tamanho);

    // Getters and Setters
    std::string getTamanho() const;
    void setTamanho(std::string tamanho);
};

#endif