#ifndef VENDA_H
#define VENDA_H

#include <string>

class Venda{
  private:
    std::string cliente;
    std::string produto;
    int quantidade;
    std::string data;

  public:
    Venda();
    Venda(std::string _cliente, std::string _produto, int _quantidade, std::string _data);

    // Getters e Setters
    std::string getCliente() const;

    std::string getProduto() const;
    void setProduto(std::string _produto);

    int getQuantidade() const;
    void setQuantidade(int _quantidade);

    std::string getData() const;
    void setData(std::string _data);
};

#endif