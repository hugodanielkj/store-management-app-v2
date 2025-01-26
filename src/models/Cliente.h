#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

class Cliente {
  private:
    int _id;
    std::string _nome;
    std::string _telefone;
    std::string _email;
  
  public:
    Cliente();
    Cliente(std::string nome, std::string telefone, std::string email);

    // Getters and Setters
    int getID() const;
    void setID(int id);
    std::string getNome() const;
    void setNome(std::string nome);
    std::string getTelefone() const;
    void setTelefone(std::string telefone);
    std::string getEmail() const;
    void setEmail(std::string email);
};

#endif
