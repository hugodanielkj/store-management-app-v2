#ifndef ROUPA_DAO_H
#define ROUPA_DAO_H

#include "../../app/sqlite3.h"
#include "../models/Roupa.h"
#include <vector>

class RoupaDAO{
  public:
    RoupaDAO(sqlite3* _db);

    // Operacoes CRUD Essenciais
    bool salvar(const Roupa& roupa);
    Roupa capturarId(int id);
    Roupa capturarNome(const std::string& nome);
    bool atualizar(const Roupa& roupa);   // Atualiza atributos de uma roupa
    bool deletar(const std::string& nome);
    std::vector<int> obterIdsValidos();

    // Operacoes auxiliares
    int getUltimoId();
    bool existeEssaRoupa(std::string& nome);

  private:
    sqlite3* db;
};

#endif