#ifndef ROUPA_DAO_H
#define ROUPA_DAO_H

#include "Roupa.h"

class RoupaDAO{
  public:
    // Operacoes CRUD Essenciais
    bool salvar(const Roupa& roupa);
    Roupa capturar(int id);
    Roupa capturar(std::string nome);
    bool atualizar(const Roupa& roupa);   // Atualiza atributos de uma roupa
    bool deletar(std::string nome);

    // Operacoes auxiliares
    int getUltimoId();
    bool existeEssaRoupa(std::string nome);
};

#endif