#ifndef PRODUTO_H
#define PRODUTO_H
#include <string>
class Produto{
  private:
    int _id;
    std::string _nome;
    int _quantidade;

  public:
    // Getters and Setters
    int getID() const;
    void setID(int id);

    std::string getNome() const;
    void setNome(std::string nome);

    int getQuantidade() const;
    void setQuantidade(int quantidade);
};
#endif