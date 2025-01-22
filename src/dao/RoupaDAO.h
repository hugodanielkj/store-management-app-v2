#ifndef ROUPA_DAO_H
#define ROUPA_DAO_H

#include <sqlite3.h>
#include "../models/Roupa.h"

class RoupaDAO{
  public:
    RoupaDAO(sqlite3* _db);

    // Operacoes CRUD Essenciais
    bool salvar(const Roupa& roupa);
    Roupa capturar(int id);
    Roupa capturar(std::string nome);
    bool atualizar(const Roupa& roupa);   // Atualiza atributos de uma roupa
    bool deletar(std::string nome);

    // Operacoes auxiliares
    int getUltimoId();
    bool existeEssaRoupa(std::string nome);

  private:
    sqlite3* db;
};

#endif