#ifndef VENDA_H
#define VENDA_H

#include <string>
#include <vector>

class Venda{
  private:
    std::string cliente;
    std::vector<std::string> produtos;
    std::vector<int> quantidades_de_produtos;
    std::string data;

  public:
    Venda();
    Venda(std::string _cliente, std::vector<std::string> _produtos, std::vector<int> _quantidades_de_produtos, std::string _data);

    // Getters e Setters
    std::string getCliente() const;

    std::vector<std::string> getProdutos() const;
    void setProdutos(std::vector<std::string> _produtos);

    std::vector<int> getQuantidadesDeProdutos() const;
    void setQuantidades(std::vector<int> _quantidades_de_produtos);

    std::string getData() const;
    void setData(std::string _data);
};

#endif