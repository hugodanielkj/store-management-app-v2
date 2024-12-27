#ifndef ROUPA_H
#define ROUPA_H

#include <string>

class Roupa{
  private:
    int _id;
    std::string _nome;
    int _quantidade;
    std::string _tamanho;
  
  public:
    Roupa(std::string nome, int quantidade, std::string tamanho);

    // Getters and Setters
    int getID() const;
    void setID(int id);

    std::string getNome() const;
    void setNome(std::string nome);

    int getQuantidade() const;
    void setQuantidade(int quantidade);

    std::string getTamanho() const;
    void setTamanho(std::string tamanho);
};

#endif